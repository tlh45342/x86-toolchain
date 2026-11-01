#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifndef _WIN32
#include <sys/stat.h>
#endif

#define X86_LD_VERSION "0.0.4"
#define EI_NIDENT 16
#define ET_REL 1
#define ET_EXEC 2
#define EM_X86_64 62
#define EV_CURRENT 1
#define PT_LOAD 1
#define PF_X 1
#define PF_R 4
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHN_UNDEF 0
#define STB_GLOBAL 1
#define R_X86_64_PC32 2
#define MAX_INPUTS 128
#define MAX_GLOBALS 2048

#pragma pack(push,1)
typedef struct { unsigned char e_ident[EI_NIDENT]; uint16_t e_type,e_machine; uint32_t e_version; uint64_t e_entry,e_phoff,e_shoff; uint32_t e_flags; uint16_t e_ehsize,e_phentsize,e_phnum,e_shentsize,e_shnum,e_shstrndx; } Elf64_Ehdr;
typedef struct { uint32_t sh_name,sh_type; uint64_t sh_flags,sh_addr,sh_offset,sh_size; uint32_t sh_link,sh_info; uint64_t sh_addralign,sh_entsize; } Elf64_Shdr;
typedef struct { uint32_t st_name; unsigned char st_info,st_other; uint16_t st_shndx; uint64_t st_value,st_size; } Elf64_Sym;
typedef struct { uint64_t r_offset,r_info; int64_t r_addend; } Elf64_Rela;
typedef struct { uint32_t p_type,p_flags; uint64_t p_offset,p_vaddr,p_paddr,p_filesz,p_memsz,p_align; } Elf64_Phdr;
#pragma pack(pop)

typedef struct {
    const char *path; unsigned char *buf; size_t size;
    const Elf64_Ehdr *eh; const Elf64_Shdr *shdrs;
    const Elf64_Shdr *text,*symtab,*strtab,*rela; uint16_t text_index;
    const Elf64_Sym *syms; size_t sym_count; const char *strings;
    uint64_t text_out_off;
} Obj;
typedef struct { char *name; Obj *obj; const Elf64_Sym *sym; } Global;

static uint32_t rela_type(uint64_t x){return (uint32_t)x;}
static uint32_t rela_sym(uint64_t x){return (uint32_t)(x>>32);}
static unsigned bind_of(unsigned char info){return info>>4;}
static uint64_t align_up(uint64_t v,uint64_t a){return a?((v+a-1)/a)*a:v;}
static int range_ok(size_t n,uint64_t o,uint64_t l){return o<=n && l<=n-(size_t)o;}
static char *dupstr(const char*s){size_t n=strlen(s)+1;char*p=(char*)malloc(n);if(p)memcpy(p,s,n);return p;}

static void usage(FILE*f){fprintf(f,"x86-ld %s\nusage: x86-ld [-m elf_x86_64] input.o [input2.o ...] -o output\n",X86_LD_VERSION);}
static unsigned char *read_file(const char*p,size_t*n){FILE*f=fopen(p,"rb");long z;unsigned char*b;if(!f){fprintf(stderr,"x86-ld: cannot open %s: %s\n",p,strerror(errno));return NULL;}if(fseek(f,0,SEEK_END)||(z=ftell(f))<0||fseek(f,0,SEEK_SET)){fclose(f);return NULL;}b=(unsigned char*)malloc(z?((size_t)z):1);if(!b){fclose(f);return NULL;}if(z&&fread(b,1,(size_t)z,f)!=(size_t)z){free(b);fclose(f);return NULL;}fclose(f);*n=(size_t)z;return b;}
static const char *secname(Obj*o,uint16_t i){const Elf64_Shdr*n;if(o->eh->e_shstrndx>=o->eh->e_shnum||i>=o->eh->e_shnum)return NULL;n=&o->shdrs[o->eh->e_shstrndx];if(!range_ok(o->size,n->sh_offset,n->sh_size)||o->shdrs[i].sh_name>=n->sh_size)return NULL;return (const char*)(o->buf+n->sh_offset+o->shdrs[i].sh_name);}
static const char *symname(Obj*o,const Elf64_Sym*s){if(s->st_name>=o->strtab->sh_size)return NULL;return o->strings+s->st_name;}

static int load_obj(Obj*o,const char*path){size_t i;memset(o,0,sizeof(*o));o->path=path;o->buf=read_file(path,&o->size);if(!o->buf)return 0;if(o->size<sizeof(Elf64_Ehdr)){fprintf(stderr,"x86-ld: %s: file too small\n",path);return 0;}o->eh=(const Elf64_Ehdr*)o->buf;if(memcmp(o->eh->e_ident,"\x7f""ELF",4)||o->eh->e_ident[4]!=2||o->eh->e_ident[5]!=1||o->eh->e_type!=ET_REL||o->eh->e_machine!=EM_X86_64||o->eh->e_version!=EV_CURRENT){fprintf(stderr,"x86-ld: %s: expected ELF64 x86-64 relocatable object\n",path);return 0;}if(o->eh->e_shentsize!=sizeof(Elf64_Shdr)||!o->eh->e_shnum||!range_ok(o->size,o->eh->e_shoff,(uint64_t)o->eh->e_shnum*sizeof(Elf64_Shdr))){fprintf(stderr,"x86-ld: %s: invalid section table\n",path);return 0;}o->shdrs=(const Elf64_Shdr*)(o->buf+o->eh->e_shoff);for(i=0;i<o->eh->e_shnum;i++){const char*n=secname(o,(uint16_t)i);if(!n){fprintf(stderr,"x86-ld: %s: invalid section names\n",path);return 0;}if(!strcmp(n,".text")&&o->shdrs[i].sh_type==SHT_PROGBITS){o->text=&o->shdrs[i];o->text_index=(uint16_t)i;}else if(!strcmp(n,".symtab")&&o->shdrs[i].sh_type==SHT_SYMTAB)o->symtab=&o->shdrs[i];else if(!strcmp(n,".rela.text")&&o->shdrs[i].sh_type==SHT_RELA)o->rela=&o->shdrs[i];}if(!o->text||!o->symtab||!range_ok(o->size,o->text->sh_offset,o->text->sh_size)||!range_ok(o->size,o->symtab->sh_offset,o->symtab->sh_size)||o->symtab->sh_entsize!=sizeof(Elf64_Sym)||o->symtab->sh_link>=o->eh->e_shnum){fprintf(stderr,"x86-ld: %s: requires valid .text and .symtab\n",path);return 0;}o->strtab=&o->shdrs[o->symtab->sh_link];if(o->strtab->sh_type!=SHT_STRTAB||!range_ok(o->size,o->strtab->sh_offset,o->strtab->sh_size)){fprintf(stderr,"x86-ld: %s: invalid symbol string table\n",path);return 0;}o->syms=(const Elf64_Sym*)(o->buf+o->symtab->sh_offset);o->sym_count=(size_t)(o->symtab->sh_size/sizeof(Elf64_Sym));o->strings=(const char*)(o->buf+o->strtab->sh_offset);if(o->rela&&(o->rela->sh_entsize!=sizeof(Elf64_Rela)||!range_ok(o->size,o->rela->sh_offset,o->rela->sh_size)||o->rela->sh_info!=o->text_index)){fprintf(stderr,"x86-ld: %s: invalid .rela.text\n",path);return 0;}return 1;}
static Global *find_global(Global*g,size_t n,const char*name){size_t i;for(i=0;i<n;i++)if(!strcmp(g[i].name,name))return &g[i];return NULL;}
static int add_globals(Obj*o,Global*g,size_t*ng){size_t i;for(i=0;i<o->sym_count;i++){const Elf64_Sym*s=&o->syms[i];const char*n;if(bind_of(s->st_info)!=STB_GLOBAL||s->st_shndx==SHN_UNDEF)continue;n=symname(o,s);if(!n||!*n)continue;if(s->st_shndx!=o->text_index){fprintf(stderr,"x86-ld: %s: global '%s' is outside .text (not supported yet)\n",o->path,n);return 0;}if(find_global(g,*ng,n)){fprintf(stderr,"x86-ld: duplicate symbol: %s\n",n);return 0;}if(*ng>=MAX_GLOBALS){fprintf(stderr,"x86-ld: too many global symbols\n");return 0;}g[*ng].name=dupstr(n);g[*ng].obj=o;g[*ng].sym=s;if(!g[*ng].name)return 0;(*ng)++;}return 1;}
static int64_t symbol_addr(Obj*o,uint32_t idx,Global*g,size_t ng,uint64_t text_va,int*ok){const Elf64_Sym*s;const char*n;Global*d;*ok=0;if(idx>=o->sym_count)return 0;s=&o->syms[idx];if(s->st_shndx==o->text_index){*ok=1;return (int64_t)(text_va+o->text_out_off+s->st_value);}if(s->st_shndx==SHN_UNDEF&&bind_of(s->st_info)==STB_GLOBAL){n=symname(o,s);if(!n)return 0;d=find_global(g,ng,n);if(!d){fprintf(stderr,"x86-ld: undefined symbol: %s\n",n);return 0;}*ok=1;return (int64_t)(text_va+d->obj->text_out_off+d->sym->st_value);}return 0;}

static int link_all(const char**inputs,int ninputs,const char*outpath){Obj objs[MAX_INPUTS];Global globals[MAX_GLOBALS];size_t ng=0,i,j,total=0;unsigned char*outtext=NULL;FILE*f=NULL;const uint64_t base=0x400000,text_file=0x1000,text_va=0x401000;uint64_t entry=UINT64_MAX;Elf64_Ehdr eh;Elf64_Phdr ph;int rc=1;memset(objs,0,sizeof(objs));memset(globals,0,sizeof(globals));if(ninputs<1||ninputs>MAX_INPUTS)return 1;
    for(i=0;i<(size_t)ninputs;i++)if(!load_obj(&objs[i],inputs[i]))goto done;
    for(i=0;i<(size_t)ninputs;i++){uint64_t a=objs[i].text->sh_addralign?objs[i].text->sh_addralign:1;total=(size_t)align_up(total,a);objs[i].text_out_off=total;if(objs[i].text->sh_size>SIZE_MAX-total){fprintf(stderr,"x86-ld: output too large\n");goto done;}total+=(size_t)objs[i].text->sh_size;}
    for(i=0;i<(size_t)ninputs;i++)if(!add_globals(&objs[i],globals,&ng))goto done;
    {Global*s=find_global(globals,ng,"_start");if(!s){fprintf(stderr,"x86-ld: missing defined _start\n");goto done;}entry=text_va+s->obj->text_out_off+s->sym->st_value;}
    outtext=(unsigned char*)calloc(total?total:1,1);if(!outtext)goto done;for(i=0;i<(size_t)ninputs;i++)if(objs[i].text->sh_size)memcpy(outtext+objs[i].text_out_off,objs[i].buf+objs[i].text->sh_offset,(size_t)objs[i].text->sh_size);
    for(i=0;i<(size_t)ninputs;i++)if(objs[i].rela){const Elf64_Rela*r=(const Elf64_Rela*)(objs[i].buf+objs[i].rela->sh_offset);size_t nr=(size_t)(objs[i].rela->sh_size/sizeof(*r));for(j=0;j<nr;j++){int ok;int64_t S,P,V;int32_t v32;if(rela_type(r[j].r_info)!=R_X86_64_PC32){fprintf(stderr,"x86-ld: %s: unsupported relocation type %u\n",objs[i].path,rela_type(r[j].r_info));goto done;}if(r[j].r_offset+4>objs[i].text->sh_size){fprintf(stderr,"x86-ld: %s: relocation outside .text\n",objs[i].path);goto done;}S=symbol_addr(&objs[i],rela_sym(r[j].r_info),globals,ng,text_va,&ok);if(!ok)goto done;P=(int64_t)(text_va+objs[i].text_out_off+r[j].r_offset);V=S+r[j].r_addend-P;if(V<INT32_MIN||V>INT32_MAX){fprintf(stderr,"x86-ld: PC32 relocation overflow\n");goto done;}v32=(int32_t)V;memcpy(outtext+objs[i].text_out_off+r[j].r_offset,&v32,4);}}
    memset(&eh,0,sizeof(eh));memcpy(eh.e_ident,"\x7f""ELF",4);eh.e_ident[4]=2;eh.e_ident[5]=1;eh.e_ident[6]=1;eh.e_type=ET_EXEC;eh.e_machine=EM_X86_64;eh.e_version=EV_CURRENT;eh.e_entry=entry;eh.e_phoff=sizeof(eh);eh.e_ehsize=sizeof(eh);eh.e_phentsize=sizeof(ph);eh.e_phnum=1;memset(&ph,0,sizeof(ph));ph.p_type=PT_LOAD;ph.p_flags=PF_R|PF_X;ph.p_vaddr=ph.p_paddr=base;ph.p_filesz=ph.p_memsz=text_file+total;ph.p_align=0x1000;
    f=fopen(outpath,"wb");if(!f){fprintf(stderr,"x86-ld: cannot create %s: %s\n",outpath,strerror(errno));goto done;}if(fwrite(&eh,1,sizeof(eh),f)!=sizeof(eh)||fwrite(&ph,1,sizeof(ph),f)!=sizeof(ph)){fprintf(stderr,"x86-ld: write failed\n");goto done;}for(i=sizeof(eh)+sizeof(ph);i<text_file;i++)fputc(0,f);if(total&&fwrite(outtext,1,total,f)!=total){fprintf(stderr,"x86-ld: write failed\n");goto done;}if(fclose(f)){f=NULL;goto done;}f=NULL;
#ifndef _WIN32
    if(chmod(outpath,0755)!=0)fprintf(stderr,"x86-ld: warning: cannot chmod %s: %s\n",outpath,strerror(errno));
#endif
    printf("linked %d objects -> %s (ELF64, entry 0x%llx, %llu text bytes)\n",ninputs,outpath,(unsigned long long)entry,(unsigned long long)total);rc=0;
done: if(f)fclose(f);if(rc)remove(outpath);free(outtext);for(i=0;i<ng;i++)free(globals[i].name);for(i=0;i<(size_t)ninputs;i++)free(objs[i].buf);return rc;}

typedef struct { char name[65]; uint32_t value; int defined; } BjSym;
typedef struct { char name[65]; uint32_t off; unsigned type; } BjRel;
typedef struct { const char *path; unsigned char *buf,*text; size_t size,text_size,out_off; uint32_t origin; BjSym *syms; size_t nsyms; BjRel *rels; size_t nrels; } BjObj;
typedef struct { char name[65]; size_t obj; uint32_t value; } BjGlobal;
static uint16_t rd16(const unsigned char*p){return (uint16_t)(p[0]|((uint16_t)p[1]<<8));}
static uint32_t rd32(const unsigned char*p){return (uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);}
static int link_bj(const char**inputs,int n,const char*outpath,uint32_t link_base,int medium){
 BjObj o[MAX_INPUTS];BjGlobal g[MAX_GLOBALS];size_t ng=0,total=0;unsigned char*out=NULL;FILE*f=NULL;int rc=1;
 memset(o,0,sizeof(o));memset(g,0,sizeof(g));
 for(int i=0;i<n;i++){size_t p=12;int bjo2=0;size_t record_size=69;o[i].path=inputs[i];o[i].buf=read_file(inputs[i],&o[i].size);if(!o[i].buf||o[i].size<12){fprintf(stderr,"x86-ld: invalid object: %s\n",inputs[i]);goto done;}
  bjo2=!memcmp(o[i].buf,"BJO2",4);
  if(bjo2){
   if(o[i].size<20||rd16(o[i].buf+4)!=1||rd16(o[i].buf+12)!=1||rd16(o[i].buf+18)!=16){
    fprintf(stderr,"x86-ld: unsupported BJO2 section layout: %s\n",inputs[i]);goto done;
   }
   o[i].text_size=rd32(o[i].buf+14);
   o[i].nsyms=rd16(o[i].buf+6);o[i].nrels=rd16(o[i].buf+8);
   p=20;record_size=71;
  }else if(!memcmp(o[i].buf,"BJO1",4)){
   o[i].text_size=rd32(o[i].buf+4);o[i].nsyms=rd16(o[i].buf+8);o[i].nrels=rd16(o[i].buf+10);
  }else{fprintf(stderr,"x86-ld: unknown object format: %s\n",inputs[i]);goto done;}
  if(p+o[i].nsyms*record_size+o[i].nrels*record_size+o[i].text_size>o[i].size){fprintf(stderr,"x86-ld: %s: truncated BJO1 object\n",inputs[i]);goto done;}o[i].syms=calloc(o[i].nsyms?o[i].nsyms:1,sizeof(BjSym));o[i].rels=calloc(o[i].nrels?o[i].nrels:1,sizeof(BjRel));if(!o[i].syms||!o[i].rels)goto done;
  for(size_t s=0;s<o[i].nsyms;s++){memcpy(o[i].syms[s].name,o[i].buf+p,64);o[i].syms[s].name[64]=0;if(bjo2&&rd16(o[i].buf+p+64)>1){fprintf(stderr,"x86-ld: unsupported BJO2 symbol section\n");goto done;}
   o[i].syms[s].value=rd32(o[i].buf+p+(bjo2?66:64));o[i].syms[s].defined=o[i].buf[p+(bjo2?70:68)];p+=record_size;if(!strcmp(o[i].syms[s].name,"__bjo_origin")){o[i].origin=o[i].syms[s].value;continue;}if(o[i].syms[s].defined){for(size_t k=0;k<ng;k++)if(!strcmp(g[k].name,o[i].syms[s].name)){fprintf(stderr,"x86-ld: duplicate symbol: %s\n",g[k].name);goto done;}snprintf(g[ng].name,sizeof(g[ng].name),"%s",o[i].syms[s].name);g[ng].obj=(size_t)i;g[ng].value=o[i].syms[s].value-o[i].origin;ng++;}}
  for(size_t r=0;r<o[i].nrels;r++){memcpy(o[i].rels[r].name,o[i].buf+p,64);o[i].rels[r].name[64]=0;if(bjo2&&rd16(o[i].buf+p+64)!=1){fprintf(stderr,"x86-ld: unsupported BJO2 relocation section\n");goto done;}
   o[i].rels[r].off=rd32(o[i].buf+p+(bjo2?66:64));o[i].rels[r].type=o[i].buf[p+(bjo2?70:68)];p+=record_size;}
  o[i].text=o[i].buf+p;
  /* Medium code units begin on paragraph boundaries, giving each object
   * a stable CS:IP mapping even after the image crosses physical 64K. */
  if(medium){total=(total+15u)&~(size_t)15u;}
  o[i].out_off=total;total+=o[i].text_size;
  if(medium && (o[i].text_size>65536u || (uint64_t)link_base+total>0x100000u)){
   fprintf(stderr,"x86-ld: Medium object exceeds 64K or 8086 address space: %s\n",o[i].path);goto done;
  }
 }
 out=calloc(total?total:1,1);if(!out)goto done;for(int i=0;i<n;i++)memcpy(out+o[i].out_off,o[i].text,o[i].text_size);
 for(int i=0;i<n;i++)for(size_t r=0;r<o[i].nrels;r++){BjGlobal *s=NULL;int32_t v;size_t P=o[i].out_off+o[i].rels[r].off;if(o[i].rels[r].off+2>o[i].text_size){fprintf(stderr,"x86-ld: %s: relocation outside object\n",o[i].path);goto done;}if(o[i].rels[r].type==1){for(size_t k=0;k<ng;k++)if(!strcmp(g[k].name,o[i].rels[r].name)){s=&g[k];break;}if(!s&&strcmp(o[i].rels[r].name,"__kernel_end")){fprintf(stderr,"x86-ld: undefined symbol: %s\n",o[i].rels[r].name);goto done;}if(!s)v=(int32_t)total-(int32_t)(P+2);else v=(int32_t)(o[s->obj].out_off+s->value)-(int32_t)(P+2);/* A near call cannot cross the current CS window.  The legacy
 * blackjack16 flat layout uses CS=0 and -Ttext as its IP base. */
{uint64_t source=(uint64_t)link_base+P;
 uint64_t target=(uint64_t)link_base+(s ? o[s->obj].out_off+s->value : total);
 if((!medium && (source>0xffffu || target>0xffffu)) ||
    (medium && (source < link_base+o[i].out_off ||
     target < link_base+o[i].out_off ||
     target >= link_base+o[i].out_off+65536u))){
  fprintf(stderr,"x86-ld: near relocation crosses 64K code segment: %s at 0x%05llX -> %s at 0x%05llX (requires segmented model)\n",
   o[i].path,(unsigned long long)source,o[i].rels[r].name,(unsigned long long)target);
  goto done;
 }}
 /* 8086 rel16 arithmetic is modulo 16 bits.  A same-CS target may be
 * more than 32767 bytes away linearly and still be exactly representable
 * because IP wraps within the 64 KiB code segment. */
out[P]=(unsigned char)((uint16_t)v);out[P+1]=(unsigned char)((uint16_t)v>>8);}else if(o[i].rels[r].type==2){uint32_t add=rd16(out+P);uint32_t av=link_base+(uint32_t)o[i].out_off+(uint16_t)(add-o[i].origin);if(medium){
   /* BJO1 ABS16 has no code/data section distinction.  Refuse to
    * guess a DS-relative address; otherwise a successful link can
    * silently produce an invalid global or string reference. */
   fprintf(stderr,
    "x86-ld: Medium ABS16 requires a typed code/data relocation: "
    "%s +0x%04lX (encoded=0x%04lX, origin=0x%04lX). "
    "BJO1 cannot identify the target section; refusing unsafe placement.\n",
    o[i].path, (unsigned long)o[i].rels[r].off,
    (unsigned long)add, (unsigned long)o[i].origin);
   goto done;
  }else if(av>0xffffu){fprintf(stderr,"x86-ld: ABS16 relocation overflow in %s\n",o[i].path);goto done;}out[P]=(unsigned char)av;out[P+1]=(unsigned char)(av>>8);}else if(o[i].rels[r].type==3){
  uint64_t linear;
  if(o[i].rels[r].off+4>o[i].text_size){fprintf(stderr,"x86-ld: far relocation outside object\n");goto done;}
  for(size_t k=0;k<ng;k++)if(!strcmp(g[k].name,o[i].rels[r].name)){s=&g[k];break;}
  if(!s){fprintf(stderr,"x86-ld: undefined symbol: %s\n",o[i].rels[r].name);goto done;}
  linear=(uint64_t)link_base+o[s->obj].out_off+s->value;
  if(linear>0xfffffu){fprintf(stderr,"x86-ld: far address overflow\n");goto done;}
  if(medium){
   uint32_t segment=(link_base+(uint32_t)o[s->obj].out_off)>>4;
   uint32_t offset=s->value;
   out[P]=(unsigned char)offset;out[P+1]=(unsigned char)(offset>>8);
   out[P+2]=(unsigned char)segment;out[P+3]=(unsigned char)(segment>>8);
  }else{
   out[P]=(unsigned char)(linear&15u);out[P+1]=0;
   out[P+2]=(unsigned char)((linear>>4)&255u);
   out[P+3]=(unsigned char)((linear>>12)&255u);
  }
 }else{fprintf(stderr,"x86-ld: %s: unsupported BJO1 relocation type %u\n",o[i].path,o[i].rels[r].type);goto done;}}
 f=fopen(outpath,"wb");if(!f){fprintf(stderr,"x86-ld: cannot create %s: %s\n",outpath,strerror(errno));goto done;}if(total&&fwrite(out,1,total,f)!=total)goto done;if(fclose(f)){f=NULL;goto done;}f=NULL;printf("linked %d objects -> %s (Blackjack16 flat, %llu bytes)\n",n,outpath,(unsigned long long)total);rc=0;
done: if(f)fclose(f);if(rc)remove(outpath);free(out);for(int i=0;i<n;i++){free(o[i].buf);free(o[i].syms);free(o[i].rels);}return rc;
}


/* Blackjack16 archive selection: only pull members satisfying unresolved relocations. */
typedef struct {unsigned char *buf;size_t size;int selected;char name[256];} ArMember;
static int bj_has_def(const unsigned char*b,size_t n,const char*name){if(n<12||memcmp(b,"BJO1",4))return 0;size_t ns=rd16(b+8);if(ns>(n-12)/69)return 0;for(size_t i=0;i<ns;i++){size_t p=12+i*69;if(b[p+68]&&strlen(name)<64&&!memcmp(b+p,name,strlen(name))&&b[p+strlen(name)]==0)return 1;}return 0;}
static int link_bj_archives(const char**inputs,int n,const char*out,uint32_t base,int medium){
 ArMember m[4096];unsigned char *direct[MAX_INPUTS]={0};size_t dn[MAX_INPUTS]={0};const char *selected[MAX_INPUTS];char temps[4096][128]={{0}};int count=0,ns=0,rc=1;memset(m,0,sizeof(m));
 for(int i=0;i<n;i++){size_t z=0;unsigned char*b=read_file(inputs[i],&z);if(!b)goto cleanup;if(z>=8&&!memcmp(b,"!<arch>\n",8)){size_t pos=8;while(pos<z){if(z-pos<60||b[pos+58]!='`'||b[pos+59]!='\n'){fprintf(stderr,"x86-ld: malformed archive\n");free(b);goto cleanup;}char num[11];memcpy(num,b+pos+48,10);num[10]=0;size_t len=(size_t)strtoull(num,NULL,10);char name[17];memcpy(name,b+pos,16);name[16]=0;for(int k=15;k>=0&&name[k]==' ';k--)name[k]=0;size_t l=strlen(name);if(l&&name[l-1]=='/')name[l-1]=0;pos+=60;if(len>z-pos||count>=4096){free(b);goto cleanup;}if(strcmp(name,"/")&&strcmp(name,"//")&&name[0]){m[count].buf=malloc(len?len:1);if(!m[count].buf){free(b);goto cleanup;}memcpy(m[count].buf,b+pos,len);m[count].size=len;snprintf(m[count].name,sizeof(m[count].name),"%s",name);count++;}pos+=len+(len&1);}free(b);}else{direct[i]=b;dn[i]=z;}}
 /* Repeatedly resolve undefined relocation names against selected objects. */
 for(int pass=0;pass<count+1;pass++){int changed=0;for(int i=0;i<n;i++){const unsigned char*b=direct[i];size_t z=dn[i];if(!b||z<12||memcmp(b,"BJO1",4))continue;size_t sy=rd16(b+8),nr=rd16(b+10);if(sy>(z-12)/69||nr>(z-12-sy*69)/69)continue;for(size_t r=0;r<nr;r++){size_t at=12+(sy+r)*69;char name[65];memcpy(name,b+at,64);name[64]=0;int found=0;for(int j=0;j<n;j++)if(direct[j]&&bj_has_def(direct[j],dn[j],name))found=1;for(int j=0;j<count;j++)if(m[j].selected&&bj_has_def(m[j].buf,m[j].size,name))found=1;if(found||!strcmp(name,"__kernel_end"))continue;for(int j=0;j<count;j++)if(!m[j].selected&&bj_has_def(m[j].buf,m[j].size,name)){m[j].selected=1;changed=1;break;}}}
 for(int i=0;i<count;i++)if(m[i].selected){const unsigned char*b=m[i].buf;size_t z=m[i].size;if(z<12||memcmp(b,"BJO1",4))continue;size_t sy=rd16(b+8),nr=rd16(b+10);if(sy>(z-12)/69||nr>(z-12-sy*69)/69)continue;for(size_t r=0;r<nr;r++){size_t at=12+(sy+r)*69;char name[65];memcpy(name,b+at,64);name[64]=0;int found=0;for(int j=0;j<n;j++)if(direct[j]&&bj_has_def(direct[j],dn[j],name))found=1;for(int j=0;j<count;j++)if(m[j].selected&&bj_has_def(m[j].buf,m[j].size,name))found=1;if(found||!strcmp(name,"__kernel_end"))continue;for(int j=0;j<count;j++)if(!m[j].selected&&bj_has_def(m[j].buf,m[j].size,name)){m[j].selected=1;changed=1;break;}}}
 if(!changed)break;}
 for(int i=0;i<n;i++)if(direct[i])selected[ns++]=inputs[i];
 for(int i=0;i<count;i++)if(m[i].selected){if(ns>=MAX_INPUTS){fprintf(stderr,"x86-ld: too many selected archive objects\n");goto cleanup;}snprintf(temps[i],sizeof(temps[i]),"x86_ld_member_%d_%d.tmp",0,i);FILE*f=fopen(temps[i],"wb");if(!f)goto cleanup;fwrite(m[i].buf,1,m[i].size,f);fclose(f);selected[ns++]=temps[i];}
 rc=link_bj(selected,ns,out,base,medium);
cleanup:
 for(int i=0;i<count;i++){if(temps[i][0])remove(temps[i]);free(m[i].buf);}for(int i=0;i<n;i++)free(direct[i]);return rc;
}

#include "bjo3_link.h"

int main(int argc,char**argv){const char*inputs[MAX_INPUTS],*out=NULL;int ni=0,i;int bj=0,medium=0;uint32_t text_base=0;if(argc==2&&(!strcmp(argv[1],"--version")||!strcmp(argv[1],"-V"))){printf("x86-ld %s\n",X86_LD_VERSION);return 0;}if(argc==2&&(!strcmp(argv[1],"--help")||!strcmp(argv[1],"-h"))){usage(stdout);return 0;}for(i=1;i<argc;i++){if(!strcmp(argv[i],"-o")){if(++i>=argc){usage(stderr);return 2;}out=argv[i];}else if(!strcmp(argv[i],"-Ttext")){char*e=NULL;unsigned long v;if(++i>=argc){usage(stderr);return 2;}v=strtoul(argv[i],&e,0);if(!e||*e||v>0xffffu){fprintf(stderr,"x86-ld: bad -Ttext value: %s\n",argv[i]);return 2;}text_base=(uint32_t)v;}else if(!strcmp(argv[i],"-m")){if(++i>=argc){usage(stderr);return 2;}if(!strcmp(argv[i],"blackjack16"))bj=1;else if(!strcmp(argv[i],"blackjack16-medium")){bj=1;medium=1;}else if(strcmp(argv[i],"elf_x86_64")){fprintf(stderr,"x86-ld: supported emulations: elf_x86_64, blackjack16\n");return 2;}}else if(argv[i][0]=='-'){fprintf(stderr,"x86-ld: unknown option: %s\n",argv[i]);return 2;}else{if(ni>=MAX_INPUTS){fprintf(stderr,"x86-ld: too many input objects\n");return 2;}inputs[ni++]=argv[i];}}if(!ni||!out){usage(stderr);return 2;}if(bj){size_t first_size=0;unsigned char *first=read_file(inputs[0],&first_size);int is_bjo3=first&&first_size>=4&&!memcmp(first,"BJO3",4);free(first);return is_bjo3?link_bjo3(inputs,ni,out,text_base,medium):link_bj_archives(inputs,ni,out,text_base,medium);}return link_all(inputs,ni,out);}


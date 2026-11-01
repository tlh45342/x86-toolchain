from pathlib import Path
p=Path('O:/x86/toolchain/x86-ld/x86-ld.c')
s=p.read_text()
needle='int main(int argc,char**argv)'
assert needle in s
helper=r'''
/* Blackjack16 archive selection: only pull members satisfying unresolved relocations. */
typedef struct {unsigned char *buf;size_t size;int selected;char name[256];} ArMember;
static int bj_has_def(const unsigned char*b,size_t n,const char*name){if(n<12||memcmp(b,"BJO1",4))return 0;size_t ns=rd16(b+8);if(ns>(n-12)/69)return 0;for(size_t i=0;i<ns;i++){size_t p=12+i*69;if(b[p+68]&&strlen(name)<64&&!memcmp(b+p,name,strlen(name))&&b[p+strlen(name)]==0)return 1;}return 0;}
static int bj_need(const unsigned char*b,size_t n,const char*name){if(n<12||memcmp(b,"BJO1",4))return 0;size_t ns=rd16(b+8),nr=rd16(b+10);if(ns>(n-12)/69||nr>(n-12-ns*69)/69)return 0;for(size_t i=0;i<nr;i++){size_t p=12+(ns+i)*69;if(strlen(name)<64&&!memcmp(b+p,name,strlen(name))&&b[p+strlen(name)]==0)return 1;}return 0;}
static int link_bj_archives(const char**inputs,int n,const char*out,uint32_t base){
 ArMember m[4096];unsigned char *direct[MAX_INPUTS]={0};size_t dn[MAX_INPUTS]={0};const char *selected[MAX_INPUTS];char temps[4096][128];int count=0,ns=0,rc=1;memset(m,0,sizeof(m));
 for(int i=0;i<n;i++){size_t z=0;unsigned char*b=read_file(inputs[i],&z);if(!b)goto cleanup;if(z>=8&&!memcmp(b,"!<arch>\n",8)){size_t pos=8;while(pos<z){if(z-pos<60||b[pos+58]!='`'||b[pos+59]!='\n'){fprintf(stderr,"x86-ld: malformed archive\n");free(b);goto cleanup;}char num[11];memcpy(num,b+pos+48,10);num[10]=0;size_t len=(size_t)strtoull(num,NULL,10);char name[17];memcpy(name,b+pos,16);name[16]=0;for(int k=15;k>=0&&name[k]==' ';k--)name[k]=0;size_t l=strlen(name);if(l&&name[l-1]=='/')name[l-1]=0;pos+=60;if(len>z-pos||count>=4096){free(b);goto cleanup;}if(strcmp(name,"/")&&strcmp(name,"//")&&name[0]){m[count].buf=malloc(len?len:1);if(!m[count].buf){free(b);goto cleanup;}memcpy(m[count].buf,b+pos,len);m[count].size=len;snprintf(m[count].name,sizeof(m[count].name),"%s",name);count++;}pos+=len+(len&1);}free(b);}else{direct[i]=b;dn[i]=z;}}
 /* Repeatedly resolve undefined relocation names against selected objects. */
 for(int pass=0;pass<count+1;pass++){int changed=0;for(int i=0;i<n;i++){const unsigned char*b=direct[i];size_t z=dn[i];if(!b||z<12||memcmp(b,"BJO1",4))continue;size_t sy=rd16(b+8),nr=rd16(b+10);if(sy>(z-12)/69||nr>(z-12-sy*69)/69)continue;for(size_t r=0;r<nr;r++){size_t at=12+(sy+r)*69;char name[65];memcpy(name,b+at,64);name[64]=0;int found=0;for(int j=0;j<n;j++)if(direct[j]&&bj_has_def(direct[j],dn[j],name))found=1;for(int j=0;j<count;j++)if(m[j].selected&&bj_has_def(m[j].buf,m[j].size,name))found=1;if(found||!strcmp(name,"__kernel_end"))continue;for(int j=0;j<count;j++)if(!m[j].selected&&bj_has_def(m[j].buf,m[j].size,name)){m[j].selected=1;changed=1;break;}}}
 for(int i=0;i<count;i++)if(m[i].selected){const unsigned char*b=m[i].buf;size_t z=m[i].size;if(z<12||memcmp(b,"BJO1",4))continue;size_t sy=rd16(b+8),nr=rd16(b+10);if(sy>(z-12)/69||nr>(z-12-sy*69)/69)continue;for(size_t r=0;r<nr;r++){size_t at=12+(sy+r)*69;char name[65];memcpy(name,b+at,64);name[64]=0;int found=0;for(int j=0;j<n;j++)if(direct[j]&&bj_has_def(direct[j],dn[j],name))found=1;for(int j=0;j<count;j++)if(m[j].selected&&bj_has_def(m[j].buf,m[j].size,name))found=1;if(found||!strcmp(name,"__kernel_end"))continue;for(int j=0;j<count;j++)if(!m[j].selected&&bj_has_def(m[j].buf,m[j].size,name)){m[j].selected=1;changed=1;break;}}}
 if(!changed)break;}
 for(int i=0;i<n;i++)if(direct[i])selected[ns++]=inputs[i];
 for(int i=0;i<count;i++)if(m[i].selected){if(ns>=MAX_INPUTS){fprintf(stderr,"x86-ld: too many selected archive objects\n");goto cleanup;}snprintf(temps[i],sizeof(temps[i]),"x86_ld_member_%d_%d.tmp",(int)_getpid(),i);FILE*f=fopen(temps[i],"wb");if(!f)goto cleanup;fwrite(m[i].buf,1,m[i].size,f);fclose(f);selected[ns++]=temps[i];}
 rc=link_bj(selected,ns,out,base);
cleanup:
 for(int i=0;i<count;i++){if(temps[i][0])remove(temps[i]);free(m[i].buf);}for(int i=0;i<n;i++)free(direct[i]);return rc;
}
'''
# use standard portable tmp names without getpid
helper=helper.replace('(int)_getpid()','0')
helper=helper.replace('ArMember m[4096];','ArMember m[4096];').replace('char temps[4096][128];','char temps[4096][128]={{0}};')
s=s.replace(needle,helper+'\n'+needle)
s=s.replace('return bj?link_bj(inputs,ni,out,text_base):link_all(inputs,ni,out);','return bj?link_bj_archives(inputs,ni,out,text_base):link_all(inputs,ni,out);')
p.write_text(s)

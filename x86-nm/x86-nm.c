#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
static unsigned short u16(const unsigned char*p){return (unsigned short)(p[0]|(p[1]<<8));}
static unsigned u32(const unsigned char*p){return (unsigned)p[0]|((unsigned)p[1]<<8)|((unsigned)p[2]<<16)|((unsigned)p[3]<<24);}
static int inspect(const char*name,const unsigned char*b,size_t n){
 size_t p=12,i;unsigned ns,nr,sz;
 if(n<12||memcmp(b,"BJO1",4)){fprintf(stderr,"x86-nm: %s: not BJO1\n",name);return 1;}
 sz=u32(b+4);ns=u16(b+8);nr=u16(b+10);
 if((size_t)ns> (n-p)/69 || (size_t)nr>(n-p-(size_t)ns*69)/69 || sz>n-p-(size_t)(ns+nr)*69){fprintf(stderr,"x86-nm: %s: truncated BJO1\n",name);return 1;}
 for(i=0;i<ns;i++,p+=69){char s[65];memcpy(s,b+p,64);s[64]=0;printf("%04X %c %s\n",u32(b+p+64),b[p+68]?'T':'U',s);}
 return 0;
}
static int inspect_archive(const char*path,const unsigned char*b,size_t n){
 size_t pos=8;int rc=0;
 while(pos<n){char name[17],num[11];size_t z,k;if(n-pos<60||b[pos+58]!='`'||b[pos+59]!='\n'){fprintf(stderr,"x86-nm: %s: invalid archive header\n",path);return 1;}
 memcpy(name,b+pos,16);name[16]=0;for(k=16;k&&name[k-1]==' ';k--)name[--k]=0;if(k&&name[k-1]=='/')name[--k]=0;
 memcpy(num,b+pos+48,10);num[10]=0;z=(size_t)strtoull(num,NULL,10);pos+=60;
 if(z>n-pos){fprintf(stderr,"x86-nm: %s: truncated archive\n",path);return 1;}
 if(name[0]&&strcmp(name,"/")&&strcmp(name,"//")){printf("\n%s(%s):\n",path,name);rc|=inspect(name,b+pos,z);}
 pos+=z+(z&1);if(pos>n)return 1;
 }
 return rc;
}int main(int argc,char**argv){int status=0,i;if(argc<2){fprintf(stderr,"usage: x86-nm file.o ...\n");return 2;}for(i=1;i<argc;i++){FILE*f=fopen(argv[i],"rb");long z;unsigned char*b;if(!f){perror(argv[i]);status=1;continue;}if(fseek(f,0,SEEK_END)||(z=ftell(f))<0||fseek(f,0,SEEK_SET)){fclose(f);status=1;continue;}b=malloc(z?z:1);if(!b){fclose(f);return 1;}if(fread(b,1,z,f)!=(size_t)z){status=1;}else{if(argc>2)printf("\n%s:\n",argv[i]);status|=((size_t)z>=8&&!memcmp(b,"!<arch>\n",8))?inspect_archive(argv[i],b,(size_t)z):inspect(argv[i],b,(size_t)z);}free(b);fclose(f);}return status;}



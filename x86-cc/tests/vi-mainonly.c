#include <stdint.h>

/* Blackjack tiny vi 0.0.1 -- deliberately small, recognizable vi semantics. */
#define CAP 16384u
#define O_WRONLY 0x0001
#define O_CREAT  0x0040
#define O_TRUNC  0x0200

extern int bj_write(int,const void*,uint32_t);
extern int bj_read(int,void*,uint32_t);
extern int bj_open(const char*,int);
extern int bj_close(int);

static char text[CAP];
static uint32_t len, pos, top_line;
static int modified;
static const char *filename;
static char message[80];

int main(int argc,char**argv){int insert=0,pending_g=0,pending_d=0,k;if(argc!=2){out("usage: vi FILE\n");return 2;}filename=argv[1];message[0]=0;load_file();pos=0;for(;;){redraw(insert);k=key();message[0]=0;if(k<0)continue;
 if(insert){if(k==27){insert=0;continue;}if(k==8||k==127){if(pos>0&&text[pos-1]!='\n'){uint32_t i;pos--;for(i=pos;i+1<len;i++)text[i]=text[i+1];len--;modified=1;}continue;}if(k==13)k='\n';if(k>=32||k=='\n'||k=='\t')insert_char((char)k);continue;}
 if(pending_g){pending_g=0;if(k=='g'){pos=0;top_line=0;}continue;}if(pending_d){pending_d=0;if(k=='d')delete_line();continue;}
 switch(k){case 'i':insert=1;break;case 'a':if(pos<len&&text[pos]!='\n')pos++;insert=1;break;case 'h':if(pos>line_start(line_of(pos)))pos--;break;case 'l':if(pos<line_end(pos)&&pos<len)pos++;break;case 'j':move_vert(1);break;case 'k':move_vert(-1);break;case '0':pos=line_start(line_of(pos));break;case '$':{uint32_t e=line_end(pos);pos=(e>line_start(line_of(pos)))?e-1:e;}break;case 'x':delete_at();break;case 'o':{uint32_t e=line_end(pos);pos=e;if(pos<len)pos++;insert_char('\n');insert=1;}break;case 'G':{uint32_t n=line_count();pos=line_start(n?n-1:0);top_line=(n>23)?n-23:0;}break;case 'g':pending_g=1;break;case 'd':pending_d=1;break;case ':':if(command()){term_clear();return 0;}break;default:break;}}
}

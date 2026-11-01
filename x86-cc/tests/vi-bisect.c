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

static uint32_t slen(const char*s){return 0;}
static void out(const char*s){(void)bj_write(1,s,slen(s));}
static void term_clear(void){out("\x1b[2J\x1b[H");}
static void term_cursor(uint32_t row,uint32_t col){char b[24];uint32_t n=0,v,i;char t[10];b[n++]=27;b[n++]='[';v=row+1u;i=0;do{t[i++]=(char)('0'+(v%10u));v/=10u;}while(v);while(i)b[n++]=t[--i];b[n++]=';';v=col+1u;i=0;do{t[i++]=(char)('0'+(v%10u));v/=10u;}while(v);while(i)b[n++]=t[--i];b[n++]='H';(void)bj_write(1,b,n);}
static void setmsg(const char*s){uint32_t i=0;while(s&&s[i]&&i+1u<sizeof(message)){message[i]=s[i];i++;}message[i]=0;}
static int key(void){char c;if(bj_read(0,&c,1)==1)return (unsigned char)c;return -1;}
static uint32_t line_of(uint32_t p){uint32_t i,n=0;for(i=0;i<p&&i<len;i++)if(text[i]=='\n')n++;return n;}
static uint32_t line_start(uint32_t line){uint32_t i=0,n=0;if(line==0)return 0;while(i<len){if(text[i++]=='\n'&&++n==line)return i;}return len;}
static uint32_t line_end(uint32_t p){while(p<len&&text[p]!='\n')p++;return p;}
static uint32_t col_of(uint32_t p){uint32_t s=p;while(s>0&&text[s-1]!='\n')s--;return p-s;}
static uint32_t line_count(void){uint32_t i,n=1;for(i=0;i<len;i++)if(text[i]=='\n')n++;return n;}
static void insert_char(char c){uint32_t i;if(len+1u>=CAP){setmsg("buffer full");return;}for(i=len;i>pos;i--)text[i]=text[i-1];text[pos++]=c;len++;modified=1;}
static void delete_at(void){uint32_t i;if(pos>=len||text[pos]=='\n')return;for(i=pos;i+1<len;i++)text[i]=text[i+1];len--;modified=1;}
static void delete_line(void){uint32_t l=line_of(pos),a=line_start(l),b=line_end(a),cut,i;if(b<len)b++;cut=b-a;if(a==0&&b==len){len=0;pos=0;}else{for(i=a;b<len;i++,b++)text[i]=text[b];len-=cut;pos=(a<len)?a:(len?len-1:0);if(pos<len&&text[pos]=='\n'&&pos>0)pos--;}modified=1;}
static void move_vert(int d){uint32_t l=line_of(pos),c=col_of(pos),n=line_count(),s,e;if(d<0){if(l==0)return;l--;}else{if(l+1>=n)return;l++;}s=line_start(l);e=line_end(s);pos=s+c;if(pos>e)pos=e;if(pos==e&&e>s)pos=e-1;}
static int load_file(void){int fd,n;len=0;fd=bj_open(filename,0);if(fd<0){setmsg("[New File]");return 0;}while(len<CAP-1u&&(n=bj_read(fd,text+len,CAP-1u-len))>0)len+=(uint32_t)n;(void)bj_close(fd);if(len>=CAP-1u)setmsg("file truncated to editor capacity");return 0;}
static int save_file(void){int fd,n;uint32_t off=0;fd=bj_open(filename,O_WRONLY|O_CREAT|O_TRUNC);if(fd<0){setmsg("write failed");return -1;}while(off<len){n=bj_write(fd,text+off,len-off);if(n<=0){bj_close(fd);setmsg("write failed");return -1;}off+=(uint32_t)n;}bj_close(fd);modified=0;setmsg("written");return 0;}
static void put_visible(uint32_t a,uint32_t b){uint32_t n=b-a;if(n>79)n=79;if(n)bj_write(1,text+a,n);}
static void redraw(int insert){uint32_t cur=line_of(pos),row,l,s,e;char status[80];uint32_t i=0;
 if (cur < top_line)
  top_line = cur;
 if (cur >= top_line + 23u)
  top_line = cur - 22u;
 term_clear();
 for(row=0,l=top_line;row<23u;row++,l++){if(l>=line_count()){out("~");}else{s=line_start(l);e=line_end(s);put_visible(s,e);}out("\n");}
 status[i++]=insert?'I':'N';status[i++]=' ';status[i++]=modified?'*':' ';status[i++]=' ';{uint32_t j=0;while(filename[j]&&i+1<sizeof(status))status[i++]=filename[j++];}status[i]=0;out(status);
 if(message[0]){out("  ");out(message);} 
 row=cur-top_line;{uint32_t c=col_of(pos);if(c>79)c=79;term_cursor(row,c);} }
static int command(void){char c,cmd[64];uint32_t n=0;term_cursor(24,0);out(":");while((c=(char)key())!=13&&c!='\n'){if(c==27)return 0;if((c==8||c==127)&&n){n--;out("\b \b");}else if(c>=32&&c<127&&n+1<sizeof(cmd)){cmd[n++]=c;bj_write(1,&c,1);}}cmd[n]=0;
 if(n==1&&cmd[0]=='w'){save_file();return 0;}if(n==1&&cmd[0]=='q'){if(modified){setmsg("No write since last change (use :q!)");return 0;}return 1;}if(n==2&&cmd[0]=='q'&&cmd[1]=='!')return 1;if(n==2&&cmd[0]=='w'&&cmd[1]=='q'){if(save_file()==0)return 1;return 0;}setmsg("? unknown command");return 0;}

int main(int argc,char**argv){int insert=0,pending_g=0,pending_d=0,k;if(argc!=2){out("usage: vi FILE\n");return 2;}filename=argv[1];message[0]=0;load_file();pos=0;for(;;){redraw(insert);k=key();message[0]=0;if(k<0)continue;
 if(insert){if(k==27){insert=0;continue;}if(k==8||k==127){if(pos>0&&text[pos-1]!='\n'){uint32_t i;pos--;for(i=pos;i+1<len;i++)text[i]=text[i+1];len--;modified=1;}continue;}if(k==13)k='\n';if(k>=32||k=='\n'||k=='\t')insert_char((char)k);continue;}
 if(pending_g){pending_g=0;if(k=='g'){pos=0;top_line=0;}continue;}if(pending_d){pending_d=0;if(k=='d')delete_line();continue;}
 switch(k){case 'i':insert=1;break;case 'a':if(pos<len&&text[pos]!='\n')pos++;insert=1;break;case 'h':if(pos>line_start(line_of(pos)))pos--;break;case 'l':if(pos<line_end(pos)&&pos<len)pos++;break;case 'j':move_vert(1);break;case 'k':move_vert(-1);break;case '0':pos=line_start(line_of(pos));break;case '$':{uint32_t e=line_end(pos);pos=(e>line_start(line_of(pos)))?e-1:e;}break;case 'x':delete_at();break;case 'o':{uint32_t e=line_end(pos);pos=e;if(pos<len)pos++;insert_char('\n');insert=1;}break;case 'G':{uint32_t n=line_count();pos=line_start(n?n-1:0);top_line=(n>23)?n-23:0;}break;case 'g':pending_g=1;break;case 'd':pending_d=1;break;case ':':if(command()){term_clear();return 0;}break;default:break;}}
}

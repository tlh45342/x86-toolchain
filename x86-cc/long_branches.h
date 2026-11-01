/* 8086 has only rel8 conditional branches. Lower them to inverted
 * short conditional + near unconditional branch. This is valid for both
 * forward and backward targets and independent of optimization level.
 */
static int x86cc_expand_conditional_branches(const char *path) {
 static const char *ops[]={"je","jne","jz","jnz","ja","jna","jae","jnae","jb","jnb","jbe","jnbe","jg","jng","jge","jnge","jl","jnl","jle","jnle","jo","jno","js","jns","jp","jnp","jpe","jpo","jc","jnc",NULL};
 static const char *inverse[]={"jne","je","jnz","jz","jbe","ja","jb","jae","jae","jb","ja","jbe","jle","jg","jl","jge","jge","jl","jg","jle","jno","jo","jns","js","jnp","jp","jpo","jpe","jnc","jc"};
 char temp[1200],line[2048],op[32],target[1024];
 FILE *in,*out;
 unsigned long serial=0;
 int k,matched;
 if(strlen(path)+16>=sizeof(temp)) return 0;
 snprintf(temp,sizeof(temp),"%s.branch.tmp",path);
 in=fopen(path,"rb"); if(!in) return 0;
 out=fopen(temp,"wb"); if(!out){fclose(in);return 0;}
 while(fgets(line,sizeof(line),in)) {
  op[0]=target[0]=0; matched=0;
  if(sscanf(line," %31s %1023s",op,target)==2 && !strchr(target,',') && target[0]!=';') {
   for(k=0;ops[k];k++) if(!strcmp(op,ops[k])) {
    fprintf(out,"    %s .Lcc_long_skip_%lu\n    jmp %s\n.Lcc_long_skip_%lu:\n",inverse[k],serial,target,serial);
    serial++;matched=1;break;
   }
  }
  if(!matched) fputs(line,out);
 }
 if(ferror(in)||ferror(out)||fclose(out)!=0){fclose(in);remove(temp);return 0;}
 fclose(in);
 /* Keep original safe until replacement succeeds. */
 if(remove(path)!=0){remove(temp);return 0;}
 if(rename(temp,path)!=0){fprintf(stderr,"x86-cc: cannot replace %s with expanded branches\n",path);return 0;}
 return 1;
}

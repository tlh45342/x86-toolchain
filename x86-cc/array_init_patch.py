from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
s=s.replace("    long init_value;\n} GlobalObject;","    long init_value;\n    int init_count;\n    long init_values[64];\n} GlobalObject;",1)
old="""            if (*q=='=') {
                char *ep; if(array_len || ptr || type_width > 2) { fprintf(stderr,"x86-cc: global: initializer not yet supported for %s near %.120s\\n",name,q); return 0; } q++; while(isspace((unsigned char)*q)) q++;
                errno=0; init_value=strtol(q,&ep,0); if(ep==q||errno) { fprintf(stderr,"x86-cc: global: non-integer initializer for %s near %.120s\\n",name,q); return 0; }
                q=ep; has_init=1; while(isspace((unsigned char)*q)) q++;
            }"""
new="""            if (*q=='=') {
                char *ep;
                q++; while(isspace((unsigned char)*q)) q++;
                if (*q=='{') {
                    int ic=0; q++;
                    if(ptr || type_width>4) { fprintf(stderr,"x86-cc: global: aggregate initializer type not yet supported for %s\\n",name); return 0; }
                    for (;;) {
                        while(isspace((unsigned char)*q))q++;
                        if(*q=='}'){q++;break;}
                        if(ic>=64){fprintf(stderr,"x86-cc: global: initializer too large for %s\\n",name);return 0;}
                        errno=0; init_value=strtol(q,&ep,0);
                        if(ep==q||errno){fprintf(stderr,"x86-cc: global: non-integer aggregate initializer for %s near %.100s\\n",name,q);return 0;}
                        g_globals[g_global_count].init_values[ic++]=init_value; q=ep;
                        while(isspace((unsigned char)*q))q++;
                        if(*q==','){q++;continue;}
                        if(*q=='}'){q++;break;}
                        fprintf(stderr,"x86-cc: global: expected comma/} in initializer for %s\\n",name);return 0;
                    }
                    if(array_len<0) array_len=ic;
                    if(array_len<ic){fprintf(stderr,"x86-cc: global: too many initializers for %s\\n",name);return 0;}
                    g_globals[g_global_count].init_count=ic; has_init=1;
                    while(isspace((unsigned char)*q))q++;
                } else {
                    if(array_len || ptr || type_width > 2) { fprintf(stderr,"x86-cc: global: initializer not yet supported for %s near %.120s\\n",name,q); return 0; }
                    errno=0; init_value=strtol(q,&ep,0); if(ep==q||errno) { fprintf(stderr,"x86-cc: global: non-integer initializer for %s near %.120s\\n",name,q); return 0; }
                    q=ep; has_init=1; while(isspace((unsigned char)*q)) q++;
                }
            }"""
assert old in s
s=s.replace(old,new,1)
old="""            g_globals[g_global_count].array_len=array_len; g_globals[g_global_count].has_init=has_init;
            g_globals[g_global_count].init_value=init_value; g_global_count++;"""
new="""            g_globals[g_global_count].array_len=array_len; g_globals[g_global_count].has_init=has_init;
            g_globals[g_global_count].init_value=init_value;
            if(!has_init) g_globals[g_global_count].init_count=0;
            g_global_count++;"""
assert old in s
s=s.replace(old,new,1)
old="""        if (g_globals[i].has_init) {
            if (g_globals[i].is_char) fprintf(out, "    db %ld\\n", g_globals[i].init_value & 255L);
            else fprintf(out, "    dw %ld\\n", g_globals[i].init_value & 65535L);
        } else {"""
new="""        if (g_globals[i].has_init) {
            if (g_globals[i].init_count) {
                int j;
                for(j=0;j<g_globals[i].init_count;j++) {
                    if(g_globals[i].width==1) fprintf(out,"    db %ld\\n",g_globals[i].init_values[j]&255L);
                    else if(g_globals[i].width==2) fprintf(out,"    dw %ld\\n",g_globals[i].init_values[j]&65535L);
                    else fprintf(out,"    dd %ld\\n",g_globals[i].init_values[j]);
                }
                if(g_globals[i].array_len>g_globals[i].init_count)
                    fprintf(out,"    times %d db 0\\n",(g_globals[i].array_len-g_globals[i].init_count)*g_globals[i].width);
            } else if (g_globals[i].is_char) fprintf(out, "    db %ld\\n", g_globals[i].init_value & 255L);
            else fprintf(out, "    dw %ld\\n", g_globals[i].init_value & 65535L);
        } else {"""
assert old in s
s=s.replace(old,new,1)
p.write_text(s)
print("integer brace-array initialization added")

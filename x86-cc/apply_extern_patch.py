from pathlib import Path
p=Path(r"O:\x86\toolchain\x86-cc\x86-cc.c")
s=p.read_text()
old="""            if (*q=='[') {
                char *ep; long v; q++; errno=0; v=strtol(q,&ep,0);
                if(ep==q||errno||v<=0||v>32767) { fprintf(stderr,"x86-cc: global: unsupported array bound near %.100s\\n",q); return 0; }
                q=ep; while(isspace((unsigned char)*q)) q++;
                if(*q++!=']') { fprintf(stderr,"x86-cc: global: missing ] after %s near %.100s\\n",name,q); return 0; }
                array_len=(int)v;
                while(isspace((unsigned char)*q)) q++;
            }"""
new="""            if (*q=='[') {
                char *ep; long v; q++; while(isspace((unsigned char)*q)) q++;
                if (*q==']') {
                    if (!is_extern_decl) { fprintf(stderr,"x86-cc: global: incomplete array requires extern near %s\\n",name); return 0; }
                    q++; array_len=-1;
                } else {
                    errno=0; v=strtol(q,&ep,0);
                    if(ep==q||errno||v<=0||v>32767) { fprintf(stderr,"x86-cc: global: unsupported array bound near %.100s\\n",q); return 0; }
                    q=ep; while(isspace((unsigned char)*q)) q++;
                    if(*q++!=']') { fprintf(stderr,"x86-cc: global: missing ] after %s near %.100s\\n",name,q); return 0; }
                    array_len=(int)v;
                }
                while(isspace((unsigned char)*q)) q++;
            }"""
assert old in s
s=s.replace(old,new,1)
old="""            if(g_global_count>=MAX_GLOBALS) { fprintf(stderr,"x86-cc: global: object table full at %s\\n",name); return 0; }"""
new="""            if(is_extern_decl && !has_init) {
                if(*q==',') { q++; continue; }
                if(*q!=';') { fprintf(stderr,"x86-cc: global: expected comma/semicolon after extern %s near %.100s\\n",name,q); return 0; }
                p=q+1; break;
            }
            if(g_global_count>=MAX_GLOBALS) { fprintf(stderr,"x86-cc: global: object table full at %s\\n",name); return 0; }"""
assert old in s
s=s.replace(old,new,1)
old="""            p=q+1; break;
        }
    }
    return 1;
}"""
new="""            p=q+1; break;
        }
        }
    }
    return 1;
}"""
assert old in s
s=s.replace(old,new,1)
p.write_text(s)
print("patched x86-cc.c")

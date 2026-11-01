from pathlib import Path
p=Path(r'O:\x86\toolchain\x86-as\x86-as.c')
s=p.read_text()
s=s.replace('#define X86AS_VERSION "0.0.30"','#define X86AS_VERSION "0.0.31"')
needle='        if(!work[0]){continue;}'
assert s.count(needle)==1
s=s.replace(needle,'''        if(!work[0]){continue;}
        if(!strncmp(low,"%include ",9)){
            char resolved[1024]; char *q=work+9; trim(q); size_t len=strlen(q);
            if(len<3 || q[0]!='"' || q[len-1]!='"'){fprintf(stderr,"%s:%d: bad include syntax\\\\n",path,ln);exit(1);}
            q[len-1]=0;
            FILE *inc=open_include(path,q+1,resolved,sizeof(resolved));
            if(!inc){fprintf(stderr,"%s:%d: include not found: %s\\\\n",path,ln,q+1);exit(1);}
            fclose(inc); preprocess(a,resolved); continue;
        }'''.replace('\\\\n','\\n'))
needle='    }fclose(f);\n}\n\nstatic int parse_db_string'
assert s.count(needle)==1
s=s.replace(needle,'    }fclose(f);include_depth--;\n}\n\nstatic int parse_db_string')
needle='        else if(!strcmp(argv[i],"-o")&&i+1<argc)out=argv[++i];'
assert s.count(needle)==1
s=s.replace(needle,'''        else if(!strcmp(argv[i],"-I")&&i+1<argc){if(n_include_dirs<32)include_dirs[n_include_dirs++]=argv[++i];else return 2;}
        else if(!strncmp(argv[i],"-I",2)&&argv[i][2]){if(n_include_dirs<32)include_dirs[n_include_dirs++]=argv[i]+2;else return 2;}
'''+needle)
p.write_text(s)
print('patched',p)

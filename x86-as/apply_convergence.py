from pathlib import Path
p = Path(r'O:\x86\toolchain\x86-as\x86-as.c')
s = p.read_text(encoding='utf-8')
start = s.index('    /*\n     * Pass 2 may change instruction widths')
end = s.index('    uint32_t code_bytes=a->pc;', start)
replacement = """    int settled=0;
    for(int iteration=0;iteration<32;iteration++){
        uint32_t old_pc=a->pc;
        int old_nsyms=a->nsyms;
        uint32_t old_values[MAX_SYMS];
        for(int i=0;i<old_nsyms;i++)old_values[i]=a->syms[i].value;
        if(!run_pass(a,2,passout)){remove(passout);free(rawpath);free(a);return 1;}
        settled=(a->pc==old_pc && a->nsyms==old_nsyms);
        if(settled)for(int i=0;i<old_nsyms;i++){
            if(a->syms[i].value!=old_values[i]){settled=0;break;}
        }
        if(settled)break;
    }
    if(!settled){
        fprintf(stderr,"x86-as: symbol layout did not converge after 32 passes\\n");
        remove(passout);free(rawpath);free(a);return 1;
    }
"""
backup = p.with_name('x86-as.c.pre-convergence.bak')
if backup.exists():
    raise SystemExit('Backup already exists; refusing to overwrite')
backup.write_text(s, encoding='utf-8')
p.write_text(s[:start] + replacement + s[end:], encoding='utf-8')
print('Patched', p, 'backup', backup)

import os, pathlib, platform, struct, subprocess, sys
HERE=pathlib.Path(__file__).resolve().parent; ROOT=HERE.parent; BUILD=HERE/'build'
IS_WIN=os.name=='nt'; LD=ROOT/('x86-ld.exe' if IS_WIN else 'x86-ld'); AS=ROOT.parent/'x86-as'/('x86-as.exe' if IS_WIN else 'x86-as')

def run(cmd): return subprocess.run([str(x) for x in cmd],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
def fail(msg,p=None):
    print('FAIL:',msg)
    if p:
        if p.stdout: print(p.stdout.decode(errors='replace'),end='')
        if p.stderr: print(p.stderr.decode(errors='replace'),end='')
    sys.exit(1)
def align(v,a): return (v+a-1)&~(a-1)

def make_obj(path,text,defs=(),undefs=(),relocs=()):
    # Minimal ELF64 ET_REL: null,.text,.rela.text,.symtab,.strtab,.shstrtab
    names=['']+[n for n,_ in defs]+list(undefs); strtab=b'\0'; noff={}
    for n in names[1:]:
        if n not in noff: noff[n]=len(strtab); strtab+=n.encode()+b'\0'
    syms=[(0,0,0,0,0,0),(0,3,0,1,0,0)]
    idx={}
    for n,val in defs: idx[n]=len(syms); syms.append((noff[n],0x10,0,1,val,0))
    for n in undefs: idx[n]=len(syms); syms.append((noff[n],0x10,0,0,0,0))
    shstr=b'\0.text\0.rela.text\0.symtab\0.strtab\0.shstrtab\0'
    textoff=64; relaoff=align(textoff+len(text),8); reladata=b''.join(struct.pack('<QQq',off,(idx[sym]<<32)|2,add) for off,sym,add in relocs)
    symoff=align(relaoff+len(reladata),8); symdata=b''.join(struct.pack('<IBBHQQ',*s) for s in syms)
    stroff=symoff+len(symdata); shstroff=stroff+len(strtab); shoff=align(shstroff+len(shstr),8)
    hdr=bytearray(64); hdr[:16]=b'\x7fELF\x02\x01\x01'+b'\0'*9
    struct.pack_into('<HHIQQQIHHHHHH',hdr,16,1,62,1,0,0,shoff,0,64,0,0,64,6,5)
    def sh(name,typ,flags,off,size,link=0,info=0,al=1,ent=0): return struct.pack('<IIQQQQIIQQ',name,typ,flags,0,off,size,link,info,al,ent)
    sht=b''.join([sh(0,0,0,0,0),sh(1,1,6,textoff,len(text),al=16),sh(7,4,0,relaoff,len(reladata),3,1,8,24),sh(18,2,0,symoff,len(symdata),4,2,8,24),sh(26,3,0,stroff,len(strtab)),sh(34,3,0,shstroff,len(shstr))])
    data=bytearray(shoff+len(sht)); data[:64]=hdr; data[textoff:textoff+len(text)]=text; data[relaoff:relaoff+len(reladata)]=reladata; data[symoff:symoff+len(symdata)]=symdata; data[stroff:stroff+len(strtab)]=strtab; data[shstroff:shstroff+len(shstr)]=shstr; data[shoff:]=sht; path.write_bytes(data)

def main():
    BUILD.mkdir(exist_ok=True)
    # Preserve Phase 1A single-object path through our x86-as.
    if not AS.exists(): fail(f'x86-as not found at {AS}; build ../x86-as first')
    obj=BUILD/'hello.o'; exe=BUILD/('hello.exe' if IS_WIN else 'hello')
    p=run([AS,'-m64','-f','elf64',HERE/'001_elf64_hello.asm','-o',obj]);
    if p.returncode: fail('assembly',p)
    p=run([LD,'-m','elf_x86_64',obj,'-o',exe]);
    if p.returncode: fail('single-object link',p)
    data=exe.read_bytes(); et,em=struct.unpack_from('<HH',data,16); entry=struct.unpack_from('<Q',data,24)[0]
    if data[:4]!=b'\x7fELF' or et!=2 or em!=62 or entry!=0x401000: fail('single-object ELF structure')
    print('001_elf64_hello        PASS (single object)')

    # start.o: call helper; mov rax,60; syscall. helper.o: mov rdi,42; ret.
    start=bytes.fromhex('E8 00 00 00 00 48 B8 3C 00 00 00 00 00 00 00 0F 05')
    helper=bytes.fromhex('48 BF 2A 00 00 00 00 00 00 00 C3')
    a=BUILD/'start.o'; b=BUILD/'helper.o'; multi=BUILD/('multi.exe' if IS_WIN else 'multi')
    make_obj(a,start,defs=[('_start',0)],undefs=['helper'],relocs=[(1,'helper',-4)])
    make_obj(b,helper,defs=[('helper',0)])
    p=run([LD,'-m','elf_x86_64',a,b,'-o',multi]);
    if p.returncode: fail('multi-object link',p)
    m=multi.read_bytes(); disp=struct.unpack_from('<i',m,0x1001)[0]
    if disp != 27: fail(f'cross-object relocation expected +27, got {disp}')
    print('002_multi_object       PASS (cross-object PC32)')

    bad=BUILD/'bad.o'; make_obj(bad,start,defs=[('_start',0)],undefs=['missing'],relocs=[(1,'missing',-4)])
    p=run([LD,bad,'-o',BUILD/'bad']);
    if p.returncode==0 or b'undefined symbol: missing' not in p.stderr: fail('undefined-symbol diagnostic',p)
    print('003_undefined_symbol    PASS (rejected as expected)')

    dup=BUILD/'dup.o'; make_obj(dup,b'\xC3',defs=[('_start',0)])
    p=run([LD,a,dup,b,'-o',BUILD/'dup']);
    if p.returncode==0 or b'duplicate symbol: _start' not in p.stderr: fail('duplicate-symbol diagnostic',p)
    print('004_duplicate_symbol    PASS (rejected as expected)')

    if platform.system()=='Linux' and platform.machine().lower() in ('x86_64','amd64'):
        multi.chmod(0o755); p=run([multi])
        if p.returncode!=42: fail(f'native multi-object execution returned {p.returncode}, expected 42',p)
        print('005_native_multi_exec  PASS (Linux x86-64, exit=42)')
    else: print('005_native_multi_exec  SKIP (requires Linux x86-64)')
    print('========================================================================'); print('PASS')
if __name__=='__main__': main()

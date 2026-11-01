import argparse, os, shutil, struct, subprocess, sys
from pathlib import Path

HERE=Path(__file__).resolve().parent
ROOT=HERE.parent
BUILD=HERE/'build'
TESTS=[p for p in sorted(HERE.glob('[0-9][0-9][0-9]_*.asm')) if p.stem not in ('039_bjobj_abs16_local','040_bjobj_abs16_matrix')]
EXPECTED_FAIL={'009_jcc_range_fail','036_push_immediate_8086_fail','037_pop_cs_fail','042_include_missing','043_include_cycle'}
EXPECTED={
'001_mov_imm':'b8efbebb3412f4',
'002_segment_mov':'b800b88ec08cc0f4',
'003_vga_store':'b800b88ec0bf0000b84807268905b8690726894502f4',
'004_interrupt':'b8410ecd10cf',
'005_control':'3c78750190e80100f4c3',
'006_directives':'5838360d0a341200000000000000000055aa',
'007_macro':'b84f0ecd10b84b0ecd10f4',
'008_arith':'b8010083c00283e80131db09d8f4',
'010_string_call':'aaace80100f4c3',
'011_freedos_reloc':'fafc31c0b90300f3a5fda4fbf4',
'012_common_data':'8d50048a078847018b5202c705341250575f58f4',
'013_freedos_data':'8c5ec68e5ec6c640027f0307015702130711570298',
'014_mul_div_shift':'b81000bb0300f7e3d1e8b90200d3eaf76616f7f3d36e10f4',
'015_far_string':'c45e5aa6a7f3a6f3a7abad',
'016_chs_prep':'84d2f6661a91f7f192f67618d0c908e1417200f4',
'017_group83_memory':'8346c8018356ca00836ecc01837ece074f',
'018_freedos_fat':'26803d0080e40f81e7ff0009c073001e070e1fff6e5a',
'019_reg_mov':'89c289df88c588d988d6',
'020_indirect_jmp':'ffe0ffe3ffe6ff665a',
'021_8086_bingo1':'a880a9b58085cb854604fdaeaff3af2e806c1210c3c20400cbca0600',
'022_8086_bingo2':'b800008ed88ec0b70100ffb80010bb100001d801c3040183c010b80100bb020011d811c3140183d001b80a00bb030019d819c31c0183d801b81400bb030029d829c32c0183e80139d839c33c0183f801b41080c408b9010083d9feb30ff6d3baff00f7d2b80100d1e0b90000e303beaddebeefbef4',
'024_8086_bingo4':'b8018099b07ffec0fec8345535341231c3a80fc7060020efbeff3600208f060220b800008ec0c606102011c606112022c606122042bf1020b90300b042f2ae39c07e03beadde7703beefbef4',
'025_io_ports':'e480e580e680e780ecedeeef',
'026_literals':'475550505920424f4f54310d0a004141424300b03004303c39',
'027_inc_family':'4041fec0fe060020ff060220fe4005ff4604f4',
'038_inc_dec_family':'4041484ffec0fec8fe060020fe0e0120ff060220ff0e0420fe4005fe4806ff4604ff4e06f4',
'028_m64_seed':'48b8010000000000000048bf010000000000000048ba19000000000000004831ff0f05',
'033_group2_shift_rotate':'d0c0d1c0d24004d34004d0c9d1c9d24804d34804d0d2d1d2d25004d35004d0dbd1dbd25804d35804d0e4d1e4d26004d36004d0edd1edd26804d36804d0fed1fed27804d37804d0e0d3e0',
'034_group3_unary_mul_div':'f6c312f7c33412f6400456f740047856f6d3f7d3f65004f75004f6dbf7dbf65804f75804f6e3f7e3f66004f76004f6ebf7ebf66804f76804f6f3f7f3f67004f77004f6fbf7fbf67804f77804f4',
'035_stack_family':'505152535455565758595a5b5c5d5e5f060e161e07171f9c9dff3600208f060220ff70048f4006ff73088f430a26ff700c268f400ef4',
'031_group1_immediate':'80c31283c31281c334128000128300128100341280cb1283cb1281cb34128008128308128108341280d31283d31281d334128010128310128110341280db1283db1281db34128018128318128118341280e31283e31281e334128020128320128120341280eb1283eb1281eb34128028128328128128341280f31283f31281f334128030128330128130341280fb1283fb1281fb341280381283381281383412f4',
'032_group1_regmem':'00cb01cb00480401480402480403480408cb09cb0848040948040a48040b480410cb11cb10480411480412480413480418cb19cb1848041948041a48041b480420cb21cb20480421480422480423480428cb29cb2848042948042a48042b480430cb31cb30480431480432480433480438cb39cb3848043948043a48043b4804f4',
}

def exe(name):
    if os.name=='nt':
        local=ROOT/(name+'.exe')
    else:
        local=ROOT/name
    return str(local) if local.exists() else name

def assemble_x86(src,out):
    cmd=[exe('x86-as')]
    if src.stem in ('028_m64_seed','029_elf64_seed','030_elf64_relocation'): cmd.append('-m64')
    cmd += ['-f','elf64' if src.stem in ('029_elf64_seed','030_elf64_relocation') else 'bin',str(src),'-o',str(out)]
    return subprocess.run(cmd,capture_output=True,text=True)

def assemble_nasm(src,out):
    fmt='elf64' if src.stem in ('029_elf64_seed','030_elf64_relocation') else 'bin'
    return subprocess.run(['nasm','-f',fmt,str(src),'-o',str(out)],capture_output=True,text=True)

def validate_elf64_seed(path):
    data=path.read_bytes()
    if len(data) < 64: return 'ELF file shorter than ELF64 header'
    if data[:4] != b'\x7fELF': return 'bad ELF magic'
    if data[4] != 2: return f'EI_CLASS={data[4]} (expected ELFCLASS64=2)'
    if data[5] != 1: return f'EI_DATA={data[5]} (expected little-endian=1)'
    if data[6] != 1: return f'EI_VERSION={data[6]} (expected 1)'
    e_type,e_machine,e_version=struct.unpack_from('<HHI',data,16)
    if e_type != 1: return f'e_type={e_type} (expected ET_REL=1)'
    if e_machine != 62: return f'e_machine={e_machine} (expected EM_X86_64=62)'
    if e_version != 1: return f'e_version={e_version} (expected 1)'
    e_shoff=struct.unpack_from('<Q',data,40)[0]
    e_ehsize,e_shentsize,e_shnum,e_shstrndx=struct.unpack_from('<HHHH',data,52)[0],struct.unpack_from('<H',data,58)[0],struct.unpack_from('<H',data,60)[0],struct.unpack_from('<H',data,62)[0]
    if e_ehsize != 64 or e_shentsize != 64: return f'bad ELF64 header sizes eh={e_ehsize} shent={e_shentsize}'
    if e_shnum != 6 or e_shstrndx != 5: return f'bad section table shape shnum={e_shnum} shstrndx={e_shstrndx}'
    if e_shoff + e_shnum*e_shentsize > len(data): return 'section header table extends past EOF'
    sh=[]
    for i in range(e_shnum):
        off=e_shoff+i*e_shentsize
        sh.append(struct.unpack_from('<IIQQQQIIQQ',data,off))
    shstr_hdr=sh[e_shstrndx]
    shstr=data[shstr_hdr[4]:shstr_hdr[4]+shstr_hdr[5]]
    def cstr(blob,off):
        end=blob.find(b'\0',off)
        return blob[off:end].decode('ascii') if end>=0 else ''
    names=[cstr(shstr,h[0]) for h in sh]
    if names != ['', '.text', '.rela.text', '.symtab', '.strtab', '.shstrtab']:
        return f'wrong section names {names!r}'
    text=sh[1]
    if text[1] != 1 or text[2] != 0x6: return 'bad .text type/flags'
    text_bytes=data[text[4]:text[4]+text[5]]
    if text_bytes != b'\x0f\x05': return f'.text bytes={text_bytes.hex()} expected 0f05'
    rela=sh[2]; sym=sh[3]; st=sh[4]
    if rela[1] != 4 or rela[6] != 3 or rela[7] != 1 or rela[9] != 24: return 'bad .rela.text metadata'
    if rela[5] != 0: return f'.rela.text unexpectedly nonempty size={rela[5]}'
    if sym[1] != 2 or sym[6] != 4 or sym[9] != 24: return 'bad .symtab metadata'
    strtab=data[st[4]:st[4]+st[5]]
    found=False
    for off in range(sym[4],sym[4]+sym[5],24):
        st_name,st_info,st_other,st_shndx,st_value,st_size=struct.unpack_from('<IBBHQQ',data,off)
        name=cstr(strtab,st_name) if st_name < len(strtab) else ''
        if name=='_start':
            found=True
            if (st_info>>4)!=1 or st_shndx!=1 or st_value!=0:
                return f'_start has bad symbol metadata bind={st_info>>4} shndx={st_shndx} value={st_value}'
    if not found: return 'missing global _start symbol'
    return None

def validate_elf64_relocation(path):
    data=path.read_bytes()
    if len(data) < 64 or data[:4] != b'\x7fELF': return 'bad ELF64 header'
    if data[4:7] != bytes([2,1,1]): return 'bad ELF identification'
    e_type,e_machine=struct.unpack_from('<HH',data,16)
    if (e_type,e_machine)!=(1,62): return f'wrong type/machine {(e_type,e_machine)!r}'
    e_shoff=struct.unpack_from('<Q',data,40)[0]
    e_shentsize=struct.unpack_from('<H',data,58)[0]
    e_shnum=struct.unpack_from('<H',data,60)[0]
    e_shstrndx=struct.unpack_from('<H',data,62)[0]
    if (e_shentsize,e_shnum,e_shstrndx)!=(64,6,5): return f'bad section table shape {(e_shentsize,e_shnum,e_shstrndx)!r}'
    sh=[struct.unpack_from('<IIQQQQIIQQ',data,e_shoff+i*64) for i in range(e_shnum)]
    shstr=data[sh[e_shstrndx][4]:sh[e_shstrndx][4]+sh[e_shstrndx][5]]
    def cstr(blob,off):
        end=blob.find(b'\0',off)
        return blob[off:end].decode('ascii') if end>=0 else ''
    names=[cstr(shstr,h[0]) for h in sh]
    if names != ['', '.text', '.rela.text', '.symtab', '.strtab', '.shstrtab']: return f'wrong section names {names!r}'
    text=sh[1]; rela=sh[2]; sym=sh[3]; st=sh[4]
    text_bytes=data[text[4]:text[4]+text[5]]
    expected=b'\x48\x8d\x35\x00\x00\x00\x00\x0f\x05X\x00'
    if text_bytes != expected: return f'.text bytes={text_bytes.hex()} expected {expected.hex()}'
    if rela[1] != 4 or rela[6] != 3 or rela[7] != 1 or rela[9] != 24 or rela[5] != 24: return 'bad .rela.text metadata'
    if sym[1] != 2 or sym[6] != 4 or sym[9] != 24: return 'bad .symtab metadata'
    strtab=data[st[4]:st[4]+st[5]]
    symbols=[]
    for off in range(sym[4],sym[4]+sym[5],24):
        st_name,st_info,st_other,st_shndx,st_value,st_size=struct.unpack_from('<IBBHQQ',data,off)
        symbols.append((cstr(strtab,st_name) if st_name<len(strtab) else '',st_info,st_shndx,st_value))
    byname={x[0]:(i,x) for i,x in enumerate(symbols) if x[0]}
    if '_start' not in byname or 'message' not in byname: return f'missing symbols: {symbols!r}'
    if byname['_start'][1][3] != 0 or byname['message'][1][3] != 9: return f'bad symbol values: {symbols!r}'
    roff,rinfo,radd=struct.unpack_from('<QQq',data,rela[4])
    rsym=rinfo>>32; rtype=rinfo & 0xffffffff
    if roff != 3: return f'relocation offset={roff} expected 3'
    if rtype != 2: return f'relocation type={rtype} expected R_X86_64_PC32=2'
    if radd != -4: return f'relocation addend={radd} expected -4'
    if rsym != byname['message'][0]: return f'relocation symbol index={rsym} expected message index={byname["message"][0]}'
    return None

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--assembler',choices=['x86','nasm','compare'],default='x86');args=ap.parse_args()
    BUILD.mkdir(exist_ok=True)
    if args.assembler in ('nasm','compare') and not shutil.which('nasm'):
        print('ERROR: nasm not found in PATH');return 2
    fails=0
    print(f'x86-as test inventory: {HERE}')
    print('='*72)
    for src in TESTS:
        stem=src.stem
        suffix='.o' if stem in ('029_elf64_seed','030_elf64_relocation') else '.bin'; xo=BUILD/(stem+'.x86'+suffix); no=BUILD/(stem+'.nasm'+suffix)
        expect_fail = stem in EXPECTED_FAIL
        rx = rn = None
        if args.assembler in ('x86','compare'):
            rx=assemble_x86(src,xo)
            if expect_fail:
                if rx.returncode == 0:
                    print(f'{stem:24} FAIL x86-as accepted expected-failure source'); fails+=1; continue
            elif rx.returncode:
                print(f'{stem:24} FAIL x86-as'); print(rx.stderr.strip()); fails+=1; continue
            else:
                if stem=='029_elf64_seed':
                    problem=validate_elf64_seed(xo)
                    if problem:
                        print(f'{stem:24} FAIL ELF64 structure'); print(' ',problem);fails+=1;continue
                elif stem=='030_elf64_relocation':
                    problem=validate_elf64_relocation(xo)
                    if problem:
                        print(f'{stem:24} FAIL ELF64 structure'); print(' ',problem);fails+=1;continue
                else:
                    got=xo.read_bytes().hex()
                    exp=EXPECTED.get(stem)
                    if exp is not None and got!=exp:
                        print(f'{stem:24} FAIL expected bytes'); print(' expected',exp); print(' got     ',got);fails+=1;continue
        if args.assembler in ('nasm','compare'):
            rn=assemble_nasm(src,no)
            if expect_fail:
                if rn.returncode == 0:
                    print(f'{stem:24} FAIL nasm accepted expected-failure source'); fails+=1; continue
            elif rn.returncode:
                print(f'{stem:24} FAIL nasm'); print(rn.stderr.strip());fails+=1;continue
        if expect_fail:
            print(f'{stem:24} PASS (rejected as expected)'); continue
        if args.assembler=='compare':
            if stem=='029_elf64_seed':
                problem=validate_elf64_seed(no)
                if problem:
                    print(f'{stem:24} FAIL NASM ELF64 validation'); print(' ',problem);fails+=1;continue
            elif stem=='030_elf64_relocation':
                pass
            elif xo.read_bytes()!=no.read_bytes():
                print(f'{stem:24} FAIL byte mismatch')
                print(' x86-as ',xo.read_bytes().hex())
                print(' nasm   ',no.read_bytes().hex())
                fails+=1;continue
        print(f'{stem:24} PASS')
    print('='*72)
    print('PASS' if not fails else f'FAIL ({fails})')
    return 1 if fails else 0
if __name__=='__main__': raise SystemExit(main())

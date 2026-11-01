import pathlib,subprocess,collections,re,os
cc=r"O:\x86\toolchain\x86-cc\x86-cc.exe"
root=pathlib.Path(r"O:\src\lacc-master\test\c89")
files=sorted(root.glob("*.c"))
cats=collections.Counter(); rows=[]
for f in files:
    try:
        p=subprocess.run([cc,"-S",str(f),"-o",os.devnull],capture_output=True,text=True,timeout=10)
        msg=(p.stderr+p.stdout).strip().splitlines()
        first=msg[0] if msg else ""
        if p.returncode==0: cat="PASS"
        elif "include" in first.lower(): cat="include/preprocessor"
        elif "struct definition" in first: cat="struct"
        elif "global declaration" in first: cat="global declaration"
        elif "function body" in first or "statement or expression" in first: cat="body/expression"
        elif "main" in first: cat="translation-unit scan"
        else: cat=first[:80] or "other"
    except subprocess.TimeoutExpired:
        cat="TIMEOUT"; first="timeout"
    cats[cat]+=1; rows.append((f.name,cat,first))
print("LACC C89 COMPILE FRONTIER")
print("TOTAL",len(files))
for k,v in cats.most_common(): print(f"{v:3} {k}")
print("\nFIRST FAILURES")
for name,cat,msg in [x for x in rows if x[1]!="PASS"][:40]: print(name,"::",msg)

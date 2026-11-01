import subprocess, pathlib, json, re
root=pathlib.Path(r"O:\src\coreutils-master\src")
cc=r"O:\x86\toolchain\x86-cc\x86-cc.exe"
out=pathlib.Path(r"O:\x86\toolchain\x86-cc\tests\coreutils-survey")
out.mkdir(exist_ok=True)
rows=[]
for f in sorted(root.glob("*.c")):
    asm=out/(f.stem+".asm")
    p=subprocess.run([cc,"-S",str(f),"-o",str(asm)],capture_output=True,text=True,timeout=15)
    msg=(p.stderr or p.stdout).strip().replace("\r","")
    lines=[x.strip() for x in msg.split("\n") if x.strip()]
    first=lines[0] if lines else ""
    rows.append({"file":f.name,"ok":p.returncode==0,"first":first,"all":msg})
path=out/"survey.json"
path.write_text(json.dumps(rows,indent=2))
print("TOTAL",len(rows),"PASS",sum(x["ok"] for x in rows),"FAIL",sum(not x["ok"] for x in rows))
from collections import Counter
def cat(x):
    s=x["first"]
    if x["ok"]: return "PASS"
    if "cannot find include" in s: return "missing include: "+s.split("include",1)[1].strip()
    if "preprocessor" in s: return "preprocessor"
    if "struct definition" in s: return "struct"
    if "global declaration" in s: return "global declaration"
    if "function body" in s or "statement or expression" in s: return "function/expr"
    return s[:100]
c=Counter(cat(x) for x in rows)
for k,n in c.most_common(): print(n,k)
print("PASSES:",", ".join(x["file"] for x in rows if x["ok"]))

import pathlib,subprocess,collections,os,re
cc=r"O:\x86\toolchain\x86-cc\x86-cc.exe"
root=pathlib.Path(r"O:\src\coreutils-master")
files=sorted((root/"src").glob("*.c"))
views=[
 ("RAW",[]),
 ("TARGET_LIBC",[r"O:\x86\toolchain\libc\include"])
]
for label,incs in views:
 c=collections.Counter(); rows=[]; passed=[]
 for f in files:
  cmd=[cc]
  for i in incs: cmd += ["-I",i]
  cmd += ["-S",str(f),"-o",os.devnull]
  try:
   p=subprocess.run(cmd,capture_output=True,text=True,timeout=12)
   lines=(p.stderr+p.stdout).strip().splitlines(); first=lines[0] if lines else ""
   if p.returncode==0: key="PASS"; passed.append(f.name)
   else:
    m=re.search(r"cannot find include ([^ ]+)",first)
    if m:key="missing include: "+m.group(1)
    elif "invalid Phase 6C preprocessor directive" in first:key="preprocessor directive"
    elif "requires int main" in first:key="translation-unit/function scan"
    elif "global declaration" in first:key="global declaration"
    elif "function declaration" in first:key="function declaration"
    elif "struct definition" in first:key="struct"
    elif "function body" in first or "statement or expression" in first:key="body/expression"
    else:key=first[:100] or "other"
   c[key]+=1; rows.append((f.name,key,first))
  except subprocess.TimeoutExpired:
   c["TIMEOUT"]+=1; rows.append((f.name,"TIMEOUT","timeout"))
 print("\n==",label,"==")
 print("TOTAL",len(files),"PASS",len(passed),"FAIL",len(files)-len(passed))
 for k,v in c.most_common(): print(f"{v:3} {k}")
 if passed: print("PASS FILES:",", ".join(passed))
 print("SAMPLE NON-INCLUDE FRONTIER:")
 n=0
 for name,key,msg in rows:
  if key!="PASS" and not key.startswith("missing include"):
   print(name,"::",msg); n+=1
   if n>=20:break

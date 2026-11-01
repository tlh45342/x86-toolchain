import subprocess,pathlib,collections,json,os
cc=r"O:\x86\toolchain\x86-cc\x86-cc-new.exe"
sets=[
 ("lua",pathlib.Path(r"O:\src\lua-5.5.1\src"),[r"O:\x86\toolchain\libc\include",r"O:\src\lua-5.5.1\src"],["*.c"]),
 ("bash",pathlib.Path(r"O:\src\gnu_bash-master"),[r"O:\x86\toolchain\libc\include",r"O:\src\gnu_bash-master",r"O:\src\gnu_bash-master\include"],["*.c"]),
]
for name,root,incs,pats in sets:
 files=[]
 for pat in pats: files+=list(root.glob(pat))
 files=sorted(set(files))
 rows=[]
 for f in files:
  cmd=[cc]+sum((["-I",x] for x in incs),[])+["-S",str(f),"-o",os.devnull]
  try:
   p=subprocess.run(cmd,capture_output=True,text=True,timeout=15)
   msg=(p.stderr or p.stdout).strip().replace("\r","")
  except subprocess.TimeoutExpired: p=None; msg="TIMEOUT"
  first=next((x.strip() for x in msg.split("\n") if x.strip()),"")
  rows.append((f.name,p is not None and p.returncode==0,first))
 print("\n==",name,"== TOTAL",len(rows),"PASS",sum(x[1] for x in rows),"FAIL",sum(not x[1] for x in rows))
 def cat(s):
  if "cannot find include" in s:return "missing "+s.split("include",1)[1].strip()
  if "preprocessor" in s:return "preprocessor"
  if "requires int main" in s:return "no/int-main gate"
  if "struct definition" in s:return "struct"
  if "global declaration" in s:return "global declaration"
  if "function body" in s or "statement or expression" in s:return "function/expr"
  return s[:100]
 c=collections.defaultdict(list)
 for f,ok,s in rows:c["PASS" if ok else cat(s)].append(f)
 for k,v in sorted(c.items(),key=lambda z:-len(z[1])): print(len(v),k,":",", ".join(v[:8]),"..." if len(v)>8 else "")

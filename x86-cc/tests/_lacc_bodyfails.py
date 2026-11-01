import pathlib,subprocess,os,re
cc=r"O:\x86\toolchain\x86-cc\x86-cc.exe"; root=pathlib.Path(r"O:\src\lacc-master\test\c89")
for f in sorted(root.glob("*.c")):
 p=subprocess.run([cc,"-S",str(f),"-o",os.devnull],capture_output=True,text=True)
 if p.returncode:
  m=(p.stderr+p.stdout).strip().splitlines()
  first=m[0] if m else ""
  if "statement or expression" in first or "function body" in first:
   print(f.name,"::",first)

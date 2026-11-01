import pathlib,subprocess,os
cc=r"O:\x86\toolchain\x86-cc\x86-cc.exe"; root=pathlib.Path(r"O:\src\lacc-master\test\c89")
P=[];F=[]
for f in sorted(root.glob("*.c")):
 p=subprocess.run([cc,"-S",str(f),"-o",os.devnull],capture_output=True,text=True)
 (P if p.returncode==0 else F).append(f.name)
print("PASS",len(P)); print("\n".join(P))

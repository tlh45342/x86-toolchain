from pathlib import Path
import subprocess
p=Path(__file__).resolve().parent
for stem in ('pipe_literal_regression','pipe_struct_regression'):
 src=p/(stem+'.c'); dest=p/(stem+'.bin'); log=p/(stem+'.log')
 cc=subprocess.run([str(p.parent/'x86-cc.exe'),str(src),'-o',str(dest)],capture_output=True,text=True)
 print(stem,'compile',cc.returncode,cc.stdout,cc.stderr)
 if cc.returncode: continue
 script=(p/'test.script.in').read_text().replace('@LOG@',str(log)).replace('@BIN@',str(dest))
 vm=subprocess.run(['x86-run'],input=script,capture_output=True,text=True)
 print(stem,'VM',vm.returncode,'AX=002A' in log.read_text() if log.exists() else 'NO LOG')
 if log.exists(): print('\n'.join(log.read_text().splitlines()[-10:]))

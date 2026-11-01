from pathlib import Path
import subprocess,tempfile
AS=Path(__file__).resolve().parents[1]/'x86-as.exe'
with tempfile.TemporaryDirectory() as t:
 d=Path(t); vals=','.join(str(i%256) for i in range(100))
 (d/'long.asm').write_text('cpu 8086\nbits 16\n_start:\n db '+vals+'\n')
 p=subprocess.run([str(AS),'-f','bin',str(d/'long.asm'),'-o',str(d/'long.bin')],capture_output=True,text=True)
 assert p.returncode==0,(p.stdout,p.stderr)
 assert (d/'long.bin').read_bytes()==bytes(range(100)), 'long db data truncated'
 print('PASS: 100 comma-separated db values retained')

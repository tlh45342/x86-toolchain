from pathlib import Path
p=Path(__file__).resolve().parent.parent/'Makefile'
s=p.read_text()
old='\tpython tests/test_peephole_production.py\n'
new=old+'\tpython tests/test_peephole_analyzer.py\n'
assert s.count(old)==2
p.write_text(s.replace(old,new))
print('Wired analyzer test into both targets')

import json, pathlib, collections, re
p=pathlib.Path(r"O:\x86\toolchain\x86-cc\tests\coreutils-survey\survey.json")
r=json.loads(p.read_text())
groups=collections.defaultdict(list)
for x in r:
 s=x["first"]
 if "cannot find include" in s: k="missing "+s.split("include",1)[1].strip()
 elif "requires int main" in s:k="no/int-main gate"
 elif "global declaration" in s:k="global declaration"
 else:k=s
 groups[k].append(x["file"])
for k,v in sorted(groups.items(),key=lambda kv:-len(kv[1])):
 print("\n",len(v),k,":",", ".join(v[:15]),("..." if len(v)>15 else ""))

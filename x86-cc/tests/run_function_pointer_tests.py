import sys
import run_tests as r
r.BUILD.mkdir(exist_ok=True)
ok = r.compile_and_run("function_pointer_struct_member.c","function_pointer_struct_member",42)
ok = r.compile_and_run("function_pointer_ops_chain.c","function_pointer_ops_chain",42) and ok
sys.exit(0 if ok else 1)

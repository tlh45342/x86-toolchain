"""Manage local Make configuration and optional component cleanup."""
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
CONFIG = ROOT / 'config.mk'
TOOLS = ('x86-as', 'x86-cc', 'x86-ld', 'x86-ar', 'x86-nm', 'x86-objdump', 'x86-disk')
KEY_RE = re.compile(r'^[A-Za-z_][A-Za-z_0-9]*$')


def main():
    action = sys.argv[1] if len(sys.argv) > 1 else 'show'
    if action == 'show':
        print('Configuration:', CONFIG)
        print(CONFIG.read_text() if CONFIG.exists() else '(defaults; no overrides)', end='\n')
    elif action == 'set':
        if len(sys.argv) != 4 or not KEY_RE.fullmatch(sys.argv[2]):
            sys.exit('Usage: make config-set KEY=NAME VALUE=VALUE')
        key, value = sys.argv[2:]
        if '\n' in value or '\r' in value or '$' in value or '#' in value:
            sys.exit('VALUE cannot contain newlines, $, or #')
        lines = CONFIG.read_text().splitlines() if CONFIG.exists() else []
        lines = [line for line in lines if not re.match(r'^\s*' + re.escape(key) + r'\s*[:?+]?=', line)]
        lines.append(f'{key} := {value}')
        CONFIG.write_text('\n'.join(lines) + '\n')
        print(f'Saved {key} in {CONFIG}')
    elif action == 'reset':
        CONFIG.unlink(missing_ok=True)
        print('Configuration reset to defaults')
    elif action == 'clean':
        for tool in TOOLS:
            makefile = ROOT / tool / 'Makefile'
            if not makefile.exists():
                continue
            if re.search(r'^clean\s*:', makefile.read_text(errors='replace'), re.M):
                subprocess.run(['make', '-C', tool, 'clean'], cwd=ROOT, check=True)
            else:
                print(f'Skipping {tool}: no clean target')
    else:
        sys.exit(f'Unknown action: {action}')


if __name__ == '__main__':
    main()

# GNU ls / Blackjack compatibility checklist

Status: compiler-led integration audit.

Legend:
- HAVE: implemented and usable
- WRAP: Blackjack primitive exists; libc/POSIX wrapper required
- SHIM: truthful compatibility implementation is acceptable initially
- SVC: kernel primitive likely required
- CONFIG: optional host feature should be configured out
- PROBE: verify as GNU ls reaches it

## Core process / I/O
- write: WRAP (SYS_WRITE exists; retire application-facing bj_write)
- read: WRAP (SYS_READ)
- open: WRAP (SYS_OPEN)
- close: WRAP (SYS_CLOSE)
- exit/_exit: WRAP (SYS_EXIT)
- argc/argv/exec ABI: PROBE

## Filesystem / directory
- opendir/readdir/closedir: WRAP over SYS_GETDENTS64; prefer conventional dirent API
- stat: WRAP over SYS_STAT; audit struct stat completeness
- lstat: SVC/PROBE; do not fake symlink semantics once needed
- readlink: SVC/PROBE
- chdir: WRAP (SYS_CHDIR)
- getcwd: PROBE; libc implementation if clean, otherwise add kernel primitive

## TTY
- isatty: SHIM/WRAP initially
- terminal width / TIOCGWINSZ: SHIM default width initially; add tty primitive when real behavior matters
- generic ioctl: do not add merely for source compatibility

## libc support
- malloc/calloc/free: HAVE; audit realloc
- getopt/getopt_long: implement libc
- errno: implement/integrate
- fnmatch: implement libc
- locale: C-locale SHIM initially
- time/localtime/gmtime/strftime: implement using existing date/time primitives
- getpwuid/getpwnam/getgrgid/getgrnam: SHIM simple Blackjack account database initially
- setjmp/longjmp: implement if gnulib/runtime path requires
- signal API: SHIM initially; real kernel signal semantics only when required
- error/error_at_line: libc
- alloca: compiler/runtime support as required

## Optional host facilities
- ACLs: CONFIG out initially
- SELinux/security contexts: CONFIG out
- capabilities: CONFIG out
- xattrs: CONFIG out
- full locale/multibyte: CONFIG to C/ASCII initially

## Compiler frontier
- extern declaration vs definition: HAVE (new regression)
- incomplete extern arrays: HAVE
- unsized array length inferred from brace initializer: HAVE for integer constants
- partial array initialization zero-fill: HAVE
- constant expressions / named constants in global initializers: CURRENT
- richer global/aggregate initializers: PROBE
- nested aggregate member access: PROBE
- function-pointer/richer declarators: PROBE
- FP type/expression/ABI phases: planned

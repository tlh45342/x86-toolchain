/* 'dir', 'vdir' and 'ls' directory listing programs for GNU.
   Copyright (C) 1985-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* If ls_mode is LS_MULTI_COL,
   the multi-column format is the default regardless
   of the type of output device.
   This is for the 'dir' program.

   If ls_mode is LS_LONG_FORMAT,
   the long format is the default regardless of the
   type of output device.
   This is for the 'vdir' program.

   If ls_mode is LS_LS,
   the output format depends on whether the output
   device is a terminal.
   This is for the 'ls' program.  */

/* Written by Richard Stallman and David MacKenzie.  */

/* Color support by Peter Anvin <Peter.Anvin@linux.org> and Dennis
   Flaherty <dennisf@denix.elk.miles.com> based on original patches by
   Greg Lee <lee@uhunix.uhcc.hawaii.edu>.  */

/* Blackjack/x86 target configuration for source-compatibility work.
 * This is deliberately small and truthful: define capabilities only when
 * the Blackjack target/runtime provides them.
 */


/* Target model. */

/* Facilities not presently supplied by Blackjack.  Keep these numeric so
 * upstream #if HAVE_* expressions select their portable/fallback paths. */

/* Gnulib normally derives these through extern-inline.m4/configure.
 * x86-cc accepts inline declarations; use the conservative static-inline
 * form for header helpers on the Blackjack target. */

/* Gnulib's generated config normally supplies compiler-attribute wrappers.
 * x86-cc does not implement GCC attributes yet, so the semantically safe
 * compatibility form for pure is an empty annotation. */

/* No gettext/NLS layer yet. */





/* Blackjack does not yet expose POSIX terminal-control attributes.
 * This header intentionally advertises no tc* interfaces.  Programs
 * that only conditionally use termios can select their fallback path.
 */


/* No generic ioctl ABI yet.  In particular TIOCGWINSZ is deliberately
 * left undefined so portable callers use their terminal-width fallback.
 */




/* Blackjack userspace ABI placeholder for the real non-local-jump API.
 * Runtime implementation is tracked separately; declaring it lets source
 * using the standard interface be type-checked by x86-cc.
 */
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int value);


struct passwd {
    char *pw_name;
    char *pw_passwd;
    uid_t pw_uid;
    gid_t pw_gid;
    char *pw_gecos;
    char *pw_dir;
    char *pw_shell;
};

struct passwd *getpwuid(uid_t uid);
struct passwd *getpwnam(const char *name);


extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;

struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};


int getopt(int argc, char *const argv[], const char *optstring);
int getopt_long(int argc, char *const argv[], const char *optstring,                 const struct option *longopts, int *longindex);



struct sigaction {
    sighandler_t sa_handler;
    sigset_t sa_mask;
    int sa_flags;
};


int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int sig);
int sigismember(const sigset_t *set, int sig);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact);
sighandler_t signal(int sig, sighandler_t handler);
int raise(int sig);



/* NonStop circa 2011 lacks both SA_RESTART and siginterrupt, so don't
   restart syscalls after a signal handler fires.  This may cause
   colors to get messed up on the screen if 'ls' is interrupted, but
   that's the best we can do on such a platform.  */



int fnmatch(const char *pattern, const char *string, int flags);


/* Gnulib includes.  */
/* acl.c - access control lists

   Copyright (C) 2002, 2008-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.

   Written by Paul Eggert.  */


/* This file uses _GL_ATTRIBUTE_CONST, _GL_ATTRIBUTE_DEPRECATED.  */


struct stat {
    ino_t st_ino;
    mode_t st_mode;
    uid_t st_uid;
    gid_t st_gid;
    unsigned int st_size;
    unsigned long st_mtime;
    unsigned int st_nlink;
};


int stat(const char *path, struct stat *st);
int lstat(const char *path, struct stat *st);



/* file_has_acl flags guaranteed to not collide with any <dirent.h>
   DT_* or _GL_DT_* value.  */
enum
  {
    /* Get scontext information as well.  */
    ACL_GET_SCONTEXT = 0x10000,

    /* Follow symlinks.  */
    ACL_SYMLINK_FOLLOW = 0x20000,
  };

/* Information about an ACL.  */
struct aclinfo
{
  /* If 'size' is nonnegative, a buffer holding the concatenation
     of extended attribute names, each terminated by NUL
     (either u._gl_acl_ch, or heap-allocated).  */
  char *buf;

  /* The number of useful bytes at the start of buf, counting trailing NULs.
     If negative, there was an error in getting the ACL info,
     and u.err is the corresponding errno.  */
  ssize_t size;

  /* Security context string.  Do not modify its contents.  */
  char *scontext;
  /* Security context errno value.  It is zero if there was no
     error getting the security context.  When nonzero, scontext is "?".  */
  int scontext_err;

  union
  {
    /* An errno value, when there was an error getting the ACL info.  */
    int err;

    /* A small array of char, big enough for most listxattr results.
       The size is somewhat arbitrary; it equals the max length of a
       trivial NFSv4 ACL (a size used by file-has-acl.c in 2023-2024
       but no longer relevant now), and a different value might be
       better once experience is gained.  For internal use only.  */
    char _gl_acl_ch[152];
  } u;
};

bool acl_errno_valid (int) _GL_ATTRIBUTE_CONST;
int file_has_acl (char const *, struct stat const *);
int file_has_aclinfo (char const *restrict, struct aclinfo *restrict, int);
int fdfile_has_aclinfo (int, char const *restrict,                          struct aclinfo *restrict, int);


int qset_acl (char const *, int, mode_t);
int xset_acl (char const *, int, mode_t);
/* Old name of xset_acl.  */
 int set_acl (char const *, int, mode_t);

int qcopy_acl (char const *, int, char const *, int, mode_t);
int xcopy_acl (char const *, int, char const *, int, mode_t);
/* Old name of xcopy_acl.  */
 int copy_acl (char const *, int, char const *, int,                                         mode_t);

int chmod_or_fchmod (char const *, int, mode_t);



/* Read symbolic links without size limitation.

   Copyright (C) 2001, 2003-2004, 2007, 2009-2026 Free Software Foundation,
   Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering <jim@meyering.net>  */

/* This file uses _GL_ATTRIBUTE_DEALLOC_FREE.  */




extern char *areadlink (char const *filename)
  _GL_ATTRIBUTE_DEALLOC_FREE;
extern char *areadlink_with_size (char const *filename, size_t size_hint)
  _GL_ATTRIBUTE_DEALLOC_FREE;




/* argmatch.h -- definitions and prototypes for argmatch.c

   Copyright (C) 1990, 1998-1999, 2001-2002, 2004-2005, 2009-2026 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by David MacKenzie <djm@ai.mit.edu>
   Modified by Akim Demaille <demaille@inf.enst.fr> */


/* This file uses _GL_ATTRIBUTE_PURE.  */

/* Copyright 2025-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2025.  */


@PRAGMA_COLUMNS@

/* The include_next requires a split double-inclusion guard.  */


/* This file uses _GL_GNUC_PREREQ.  */

/* Get size_t.  */

/* Returns the number of elements of the array A, as a value of type size_t.

   Example declarations of arrays:
     extern int a[];
     extern int a[10];
     static int a[10][20];
     void func () { int a[10]; ... }
   It works for arrays that are declared outside functions and for local
   variables of array type.  It does *not* work for function parameters
   of array type, because they are actually parameters of pointer type.
   In this case, i.e. if A is a pointer, e.g. in
     void func (int a[10]) { ... }
   this macro attempts to produce an error.
 */

/* Attempts to verify that A is an array.  */
/* In C, we can use typeof and __builtin_types_compatible_p.  */
/* Work around clang bug <https://github.com/llvm/llvm-project/issues/143284>.  */
/* The compiler does not have the necessary built-ins.  */

size_t strlen(const char *s);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);
char *strcat(char *d, const char *s);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
void *memcpy(void *d, const void *s, size_t n);
void *memmove(void *d, const void *s, size_t n);
void *memset(void *d, int c, size_t n);
int memcmp(const void *a, const void *b, size_t n);

/* Convenience header for conditional use of GNU <libintl.h>.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



/* NLS can be disabled through the configure --disable-nls option
   or through "#define ENABLE NLS 0" before including this file.  */

/* Solaris /usr/include/locale.h includes /usr/include/libintl.h, which
   chokes if dcgettext is defined as a macro.  So include it now, to make
   later inclusions of <locale.h> a NOP.  We don't include <libintl.h>
   as well because people using "gettext.h" will not include <libintl.h>.  */

/* Many header files from the libstdc++ coming with g++ 3.3 or newer include
   <libintl.h>, which chokes if dcgettext is defined as a macro.  So include
   it now, to make later inclusions of <libintl.h> a NOP.  */

/* Like the C cast ((type) (expr)), but do only conversions that an
   ordinary assignment would do.  This can diagnose invalid arguments
   better than a cast would.  */

/* Disabled NLS.  */
/* When gcc or clang is used with option -Wformat=2, we need to silence
   gcc: "warning: format not a string literal, argument types not checked [-Wformat-nonliteral]"
   clang: "warning: format string is not a string literal [-Wformat-nonliteral]",
          "warning: format string is not a string literal (potentially insecure) [-Wformat-security]"
   warnings that would occur at every invocation of a *gettext function
   in a *printf format string position.
   Do this with inline functions when possible.  */
/* These warnings would not occur with enabled NLS.  */
/* A test case:
   ================================ foo.c ================================
   #include <stdio.h>
   #include "gettext.h"
   extern const char *some_computed_string (void);

   void foo (int n)
   {
     textdomain ("pkg");
     bindtextdomain ("pkg", "/usr/share/locale");
     bind_textdomain_codeset ("pkg", "UTF-8");

     printf (gettext ("foo %d"), n);
     printf (dgettext ("toto", "foo %d"), n);
     printf (dcgettext ("toto", "foo %d", LC_MESSAGES), n);
     printf (ngettext ("foo %d", "bar %d", n), n);
     printf (dngettext ("toto", "foo %d", "bar %d", n), n);
     printf (dcngettext ("toto", "foo %d", "bar %d", n, LC_MESSAGES), n);

     printf ("%s", gettext ("between 7% & 19%."));
     printf ("%s", dgettext ("toto", "between 7% & 19%."));
     printf ("%s", dcgettext ("toto", "between 7% & 19%.", LC_MESSAGES));

     printf (gettext (some_computed_string ()));
     printf (dgettext ("toto", some_computed_string ()));
     printf (dcgettext ("toto", some_computed_string (), LC_MESSAGES));
   }
   =======================================================================
   $CC -Wall -Wformat=2 -S foo.c
   $CC -Wall -Wformat=2 -S -x c++ foo.c
 */






/* Prefer gnulib's setlocale override over libintl's setlocale override.  */


/* A pseudo function call that serves as a marker for the automated
   extraction of messages, but does not call gettext().  The run-time
   translation is done at a different place in the code.
   The argument, String, should be a literal string.  Concatenated strings
   and other string expressions won't work.
   The macro's expansion is not parenthesized, so that it is suitable as
   initializer for static 'char[]' or 'const char[]' variables.  */


/* The separator between msgctxt and msgid in a .mo file.  */

/* Pseudo function calls, taking a MSGCTXT and a MSGID instead of just a
   MSGID.  MSGCTXT and MSGID must be string literals.  MSGCTXT should be
   short and rarely need to change.
   The letter 'p' stands for 'particular' or 'special'.  */

struct lconv { char *decimal_point; };
char *setlocale(int category, const char *locale);
struct lconv *localeconv(void);
/* The LC_MESSAGES locale category is specified in POSIX, but not in ISO C.
   On systems that don't define it, use the same value as GNU libintl.  */


static const char *
pgettext_aux (const char *domain,                const char *msg_ctxt_id, const char *msgid,                int category)
{
  const char *translation = ((void) (int) {(category)},        ((void) (const char *) {(domain)}, (const char *) {(msg_ctxt_id)}));
  if (translation == msg_ctxt_id)
    return msgid;
  else
    return translation;
}

static const char *
npgettext_aux (const char *domain,                 const char *msg_ctxt_id, const char *msgid,                 const char *msgid_plural, unsigned long int n,                 int category)
{
  const char *translation =
    ((void) (int) {(category)},       ((void) (const char *) {(domain)},       ((n) == 1       ? ((void) (const char *) {(msgid_plural)},          (const char *) {(msg_ctxt_id)})       : ((void) (const char *) {(msg_ctxt_id)},          (const char *) {(msgid_plural)}))));
  if (translation == msg_ctxt_id || translation == msgid_plural)
    return (n == 1 ? msgid : msgid_plural);
  else
    return translation;
}


/* The same thing extended for non-constant arguments.  Here MSGCTXT and MSGID
   can be arbitrary expressions.  But for string literals these macros are
   less efficient than those above.  */


/* GNULIB_NO_VLA can be defined to disable use of VLAs even if supported.
   This relates to the -Wvla and -Wvla-larger-than warnings, enabled in
   the default GCC many warnings set.  This allows programs to disable use
   of VLAs, which may be unintended, or may be awkward to support portably,
   or may have security implications due to non-deterministic stack usage.  */




static const char *
dcpgettext_expr (const char *domain,                   const char *msgctxt, const char *msgid,                   int category)
{
  size_t msgctxt_len = strlen (msgctxt) + 1;
  size_t msgid_len = strlen (msgid) + 1;
  const char *translation;
  char buf[1024];
  char *msg_ctxt_id =
    (msgctxt_len + msgid_len <= sizeof (buf)       ? buf       : (char *) malloc (msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)
    {
      memcpy (msg_ctxt_id, msgctxt, msgctxt_len - 1);
      msg_ctxt_id[msgctxt_len - 1] = '\004';
      memcpy (msg_ctxt_id + msgctxt_len, msgid, msgid_len);
      translation = ((void) (int) {(category)},        ((void) (const char *) {(domain)}, (const char *) {(msg_ctxt_id)}));
      int found_translation = (translation != msg_ctxt_id);
      if (found_translation)
        return translation;
    }
  return msgid;
}


static const char *
dcnpgettext_expr (const char *domain,                    const char *msgctxt, const char *msgid,                    const char *msgid_plural, unsigned long int n,                    int category)
{
  size_t msgctxt_len = strlen (msgctxt) + 1;
  size_t msgid_len = strlen (msgid) + 1;
  const char *translation;
  char buf[1024];
  char *msg_ctxt_id =
    (msgctxt_len + msgid_len <= sizeof (buf)       ? buf       : (char *) malloc (msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)
    {
      memcpy (msg_ctxt_id, msgctxt, msgctxt_len - 1);
      msg_ctxt_id[msgctxt_len - 1] = '\004';
      memcpy (msg_ctxt_id + msgctxt_len, msgid, msgid_len);
      translation = ((void) (int) {(category)},       ((void) (const char *) {(domain)},       ((n) == 1       ? ((void) (const char *) {(msgid_plural)},          (const char *) {(msg_ctxt_id)})       : ((void) (const char *) {(msg_ctxt_id)},          (const char *) {(msgid_plural)}))));
      int found_translation = !(translation == msg_ctxt_id || translation == msgid_plural);
      if (found_translation)
        return translation;
    }
  return (n == 1 ? msgid : msgid_plural);
}


/* quote.h - prototypes for quote.c

   Copyright (C) 1998-2001, 2003, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */





/* The quoting options used by quote_n and quote.  Its type is incomplete,
   so it's useful only in expressions like '&quote_quoting_options'.  */
extern struct quoting_options quote_quoting_options;

/* Return an unambiguous printable representation of ARG (of size
   ARGSIZE), allocated in slot N, suitable for diagnostics.  If
   ARGSIZE is SIZE_MAX, use the string length of the argument for
   ARGSIZE.  */
char const *quote_n_mem (int n, char const *arg, size_t argsize);

/* Return an unambiguous printable representation of ARG (of size
   ARGSIZE), suitable for diagnostics.  If ARGSIZE is SIZE_MAX, use
   the string length of the argument for ARGSIZE.  */
char const *quote_mem (char const *arg, size_t argsize);

/* Return an unambiguous printable representation of ARG, allocated in
   slot N, suitable for diagnostics.  */
char const *quote_n (int n, char const *arg);

/* Return an unambiguous printable representation of ARG, suitable for
   diagnostics.  */
char const *quote (char const *arg);





/* Assert there are as many real arguments as there are values
   (argument list ends with a NULL guard).  */


/* Return the index of the element of ARGLIST (NULL terminated) that
   matches with ARG.  If VALLIST is not NULL, then use it to resolve
   false ambiguities (i.e., different matches of ARG but corresponding
   to the same values in VALLIST).  */

ptrdiff_t argmatch (char const *arg, char const *const *arglist,                      void const *vallist, size_t valsize) ;

ptrdiff_t argmatch_exact (char const *arg, char const *const *arglist)
  ;



/* xargmatch calls this function when it fails.  This function should not
   return.  By default, this is a function that calls ARGMATCH_DIE which
   in turn defaults to 'exit (exit_failure)'.  */
extern argmatch_exit_fn argmatch_die;

/* Report on stderr why argmatch failed.  Report correct values. */

void argmatch_invalid (char const *context, char const *value,                         ptrdiff_t problem);

/* Left for compatibility with the old name invalid_arg */




/* Report on stderr the list of possible arguments.  */

void argmatch_valid (char const *const *arglist,                       void const *vallist, size_t valsize);




/* Like argmatch/argmatch_exact, but upon failure, report an explanation
   of the failure, and exit using the function EXIT_FN. */

ptrdiff_t __xargmatch_internal (char const *context,                                  char const *arg, char const *const *arglist,                                  void const *vallist, size_t valsize,                                  argmatch_exit_fn exit_fn,                                  bool allow_abbreviation);

/* Programmer friendly interface to __xargmatch_internal. */



/* Convert a value into a corresponding argument. */

char const *argmatch_to_argument (void const *value,                                    char const *const *arglist,                                    void const *vallist, size_t valsize)
  ;




/* Run-time assert-like macros.

   Copyright (C) 2014-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert.  */




/* Compile-time assert-like macros.

   Copyright (C) 2005-2006, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert, Bruno Haible, and Jim Meyering.  */



/* Define _GL_HAVE__STATIC_ASSERT to 1 if _Static_assert (R, DIAGNOSTIC)
   works as per C11.  This is supported by GCC 4.6.0+ and by clang 4+.
   Check for __clang_major__ >= 5 instead of >= 4 because clang on Mac OS 10.7.5
   sets __clang_major__ to 4 even though it was derived from clang 3.2.

   Define _GL_HAVE__STATIC_ASSERT1 to 1 if _Static_assert (R) works as
   per C23.  This is supported by GCC 9.1+.

   Support compilers claiming conformance to the relevant standard,
   and also support GCC when not pedantic.  If we were willing to slow
   'configure' down we could also use it with other compilers, but
   since this affects only the quality of diagnostics, why bother?  */

/* <sys/cdefs.h> in glibc may define _Static_assert with two arguments if the
   compiler is in C89 or C99 mode.  This matters especially with Clang:
   (1) glibc < 2.34, before the commit c8ba52ab3350 ("misc: Sync cdefs.h
       with gnulib"), doesn't check for __clang_major__ >= 4.
   (2) The above condition for _GL_HAVE__STATIC_ASSERT checks for
       __clang_major__ >= 5, so it's not in sync with glibc.  */

/* FreeBSD 9.1 <sys/cdefs.h>, included by <stddef.h> and lots of other
   system headers, defines a conflicting _Static_assert that is no
   better than ours; override it unless Gnulib's replacement <assert.h>
   (included from config.h) already overrode it.  */

/* Each of these macros verifies that its argument R is nonzero.  To
   be portable, R should be an integer constant expression.  Unlike
   assert (R), there is no run-time overhead.

   If _Static_assert works, verify (R) uses it directly.  Similarly,
   _GL_VERIFY_TRUE works by packaging a _Static_assert inside a struct
   that is an operand of sizeof.

   The code below uses several ideas for C++ compilers, and for C
   compilers that do not support _Static_assert:

   * The first step is ((R) ? 1 : -1).  Given an expression R, of
     integral or boolean or floating-point type, this yields an
     expression of integral type, whose value is later verified to be
     constant and nonnegative.

   * Next this expression W is wrapped in a type
     struct _gl_verify_type {
       unsigned int _gl_verify_error_if_negative: W;
     }.
     If W is negative, this yields a compile-time error.  No compiler can
     deal with a bit-field of negative size.

     One might think that an array size check would have the same
     effect, that is, that the type struct { unsigned int dummy[W]; }
     would work as well.  However, inside a function, some compilers
     (such as C++ compilers and GNU C) allow local parameters and
     variables inside array size expressions.  With these compilers,
     an array size check would not properly diagnose this misuse of
     the verify macro:

       void function (int n) { verify (n < 0); }

   * For the verify macro, the struct _gl_verify_type will need to
     somehow be embedded into a declaration.  To be portable, this
     declaration must declare an object, a constant, a function, or a
     typedef name.  If the declared entity uses the type directly,
     such as in

       struct dummy {...};
       typedef struct {...} dummy;
       extern struct {...} *dummy;
       extern void dummy (struct {...} *);
       extern struct {...} *dummy (void);

     two uses of the verify macro would yield colliding declarations
     if the entity names are not disambiguated.  A workaround is to
     attach the current line number to the entity name:

       #define _GL_CONCAT0(x, y) x##y
       #define _GL_CONCAT(x, y) _GL_CONCAT0 (x, y)
       extern struct {...} * _GL_CONCAT (dummy, __LINE__);

     But this has the problem that two invocations of verify from
     within the same macro would collide, since the __LINE__ value
     would be the same for both invocations.  (The GCC __COUNTER__
     macro solves this problem, but is not portable.)

     A solution is to use the sizeof operator.  It yields a number,
     getting rid of the identity of the type.  Declarations like

       extern int dummy [sizeof (struct {...})];
       extern void dummy (int [sizeof (struct {...})]);
       extern int (*dummy (void)) [sizeof (struct {...})];

     can be repeated.

   * Should the implementation use a named struct or an unnamed struct?
     Which of the following alternatives can be used?

       extern int dummy [sizeof (struct {...})];
       extern int dummy [sizeof (struct _gl_verify_type {...})];
       extern void dummy (int [sizeof (struct {...})]);
       extern void dummy (int [sizeof (struct _gl_verify_type {...})]);
       extern int (*dummy (void)) [sizeof (struct {...})];
       extern int (*dummy (void)) [sizeof (struct _gl_verify_type {...})];

     In the second and sixth case, the struct type is exported to the
     outer scope; two such declarations therefore collide.  GCC warns
     about the first, third, and fourth cases.  So the only remaining
     possibility is the fifth case:

       extern int (*dummy (void)) [sizeof (struct {...})];

   * GCC warns about duplicate declarations of the dummy function if
     -Wredundant-decls is used.  GCC 4.3 and later have a builtin
     __COUNTER__ macro that can let us generate unique identifiers for
     each dummy function, to suppress this warning.

   * This implementation exploits the fact that older versions of GCC,
     which do not support _Static_assert, also do not warn about the
     last declaration mentioned above.

   * GCC warns if -Wnested-externs is enabled and 'verify' is used
     within a function body; but inside a function, you can always
     arrange to use verify_expr instead.

   * In C++, any struct definition inside sizeof is invalid.
     Use a template type to work around the problem.  */

/* Concatenate two preprocessor tokens.  */

/* _GL_COUNTER is an integer, preferably one that changes each time we
   use it.  Use __COUNTER__ if it works (it does so with most compilers,
   see <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3457.htm>),
   falling back on __LINE__ otherwise.  __LINE__ isn't perfect, but it's
   better than a constant.  */

/* Generate a symbol with the given prefix, making it unique if
   possible.  */

/* Verify requirement R at compile-time, as an integer constant expression
   that returns 1.  If R is false, fail at compile-time, preferably
   with a diagnostic that includes the string-literal DIAGNOSTIC.  */



/* Verify requirement R at compile-time, as a declaration without a
   trailing ';'.  If R is false, fail at compile-time.

   This macro requires three or more arguments but uses at most the first
   two, so that the _Static_assert macro optionally defined below supports
   both the C11 two-argument syntax and the C23 one-argument syntax.

   Unfortunately, unlike C11, this implementation must appear as an
   ordinary declaration, and cannot appear inside struct { ... }.  */


/* _GL_STATIC_ASSERT_H is defined if this code is copied into assert.h.  */

/* @assert.h omit start@  */



/* Each of these macros verifies that its argument R is nonzero.  To
   be portable, R should be an integer constant expression.  Unlike
   assert (R), there is no run-time overhead.

   There are two macros, since no single macro can be used in all
   contexts in C.  verify_expr (R, E) is for scalar contexts, including
   integer constant expression contexts.  verify (R) is for declaration
   contexts, e.g., the top level.  */

/* Verify requirement R at compile-time.  Return the value of the
   expression E.  */


/* Verify requirement R at compile-time, as a declaration without a
   trailing ';'.  verify (R) acts like static_assert (R) except that
   it is portable to C11/C++14 and earlier, it can issue better
   diagnostics, and its name is shorter and may be more convenient.  */


/* Assume that R always holds.  Behavior is undefined if R is false,
   fails to evaluate, or has side effects.

   'assume (R)' is a directive from the programmer telling the
   compiler that R is true so the compiler needn't generate code to
   test R.  This is why 'assume' is in verify.h: it's related to
   static checking (in this case, static checking done by the
   programmer), not dynamic checking.

   'assume (R)' can affect compilation of all the code, not just code
   that happens to be executed after the assume (R) is "executed".
   For example, if the code mistakenly does 'assert (R); assume (R);'
   the compiler is entitled to optimize away the 'assert (R)'.

   Although assuming R can help a compiler generate better code or
   diagnostics, performance can suffer if R uses hard-to-optimize
   features such as function calls not inlined by the compiler.

   Avoid Clang's __builtin_assume, as it breaks GNU Emacs master
   as of 2020-08-23T21:09:49Z!eggert@cs.ucla.edu; see
   <https://bugs.gnu.org/43152#71>.  It's not known whether this breakage
   is a Clang bug or an Emacs bug; play it safe for now.  */

  /* Some older tools grok NOTREACHED, e.g., Oracle Studio 12.6 (2017).  */

/* @assert.h omit end@  */


/* Evaluate an assertion E that is guaranteed to be true.
   If NDEBUG is not defined, abort the program if E is false.
   If NDEBUG is defined, the compiler can assume E and behavior is
   undefined if E is false, fails to evaluate, or has side effects.

   Unlike standard 'assert', this macro evaluates E even when NDEBUG
   is defined, so as to catch typos, avoid some GCC warnings, and
   improve performance when E is simple enough.

   Also see the documentation for 'assume' in verify.h.  */


/* Check E's value at runtime, and report an error and abort if not.
   However, do nothing if NDEBUG is defined.

   Unlike standard 'assert', this macro compiles E even when NDEBUG
   is defined, so as to catch typos and avoid some GCC warnings.
   Unlike 'affirm', it is OK for E to use hard-to-optimize features,
   since E is not executed if NDEBUG is defined.  */


/* Character handling in C locale.

   These functions work like the corresponding functions in <ctype.h>,
   except that they have the C (POSIX) locale hardwired, whereas the
   <ctype.h> functions' behaviour depends on the current locale set via
   setlocale.

   Copyright (C) 2000-2003, 2006, 2008-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_INLINE_HEADER_BEGIN, _GL_INLINE.  */

_GL_INLINE_HEADER_BEGIN



/* The functions defined in this file assume the "C" locale and a character
   set without diacritics (ASCII-US or EBCDIC-US or something like that).
   Even if the "C" locale on a particular system is an extension of the ASCII
   character set (like on BeOS, where it is UTF-8, or on AmigaOS, where it
   is ISO-8859-1), the functions in this file recognize only the ASCII
   characters.  */




/* Cases for control characters.  */


/* ASCII control characters other than those with \-letter escapes.  */

   /* Use EBCDIC code page 1047's assignments for ASCII control chars;
      assume all EBCDIC code pages agree about these assignments.  */

/* Cases for lowercase hex letters, and lowercase letters, all offset by N.  */


/* Cases for hex letters, digits, lower, punct, and upper.  */



/* Function definitions.  */

/* Unlike the functions in <ctype.h>, which require an argument in the range
   of the 'unsigned char' type, the functions here operate on values that are
   in the 'unsigned char' range or in the 'char' range.  In other words,
   when you have a 'char' value, you need to cast it before using it as
   argument to a <ctype.h> function:

         const char *s = ...;
         if (isalpha ((unsigned char) *s)) ...

   but you don't need to cast it for the functions defined in this file:

         const char *s = ...;
         if (c_isalpha (*s)) ...
 */

static inline bool
c_isalnum (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3':    case '4': case '5': case '6': case '7':    case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

static inline bool
c_isalpha (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

/* The function isascii is not locale dependent.
   Its use in EBCDIC is questionable. */
static inline bool
c_isascii (int c)
{
  switch (c)
    {
    case ' ':
    case '\a': case '\b': case '\f': case '\n':    case '\r': case '\t': case '\v':    case '\x00': case '\x01': case '\x02': case '\x03':     case '\x07': case '\x0e': case '\x0f': case '\x10':     case '\x11': case '\x12': case '\x13': case '\x18':     case '\x19': case '\x1c': case '\x1d': case '\x1e':     case '\x1f': case '\x26': case '\x27': case '\x2d':     case '\x2e': case '\x32': case '\x37': case '\x3c':     case '\x3d': case '\x3f':
    case '0': case '1': case '2': case '3':    case '4': case '5': case '6': case '7':    case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$':     case '%': case '&': case '\'': case '(':    case ')': case '*': case '+': case ',':     case '-': case '.': case '/': case ':':     case ';': case '<': case '=': case '>':     case '?': case '@': case '[': case '\\':    case ']': case '^': case '@GUARD_PREFIX@_STDCOUNTOF_H': case '`':     case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

static inline bool
c_isblank (int c)
{
  return c == ' ' || c == '\t';
}

static inline bool
c_iscntrl (int c)
{
  switch (c)
    {
    case '\a': case '\b': case '\f': case '\n':    case '\r': case '\t': case '\v':    case '\x00': case '\x01': case '\x02': case '\x03':     case '\x07': case '\x0e': case '\x0f': case '\x10':     case '\x11': case '\x12': case '\x13': case '\x18':     case '\x19': case '\x1c': case '\x1d': case '\x1e':     case '\x1f': case '\x26': case '\x27': case '\x2d':     case '\x2e': case '\x32': case '\x37': case '\x3c':     case '\x3d': case '\x3f':
      return true;
    default:
      return false;
    }
}

static inline bool
c_isdigit (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3':    case '4': case '5': case '6': case '7':    case '8': case '9':
      return true;
    default:
      return false;
    }
}

static inline bool
c_isgraph (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3':    case '4': case '5': case '6': case '7':    case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$':     case '%': case '&': case '\'': case '(':    case ')': case '*': case '+': case ',':     case '-': case '.': case '/': case ':':     case ';': case '<': case '=': case '>':     case '?': case '@': case '[': case '\\':    case ']': case '^': case '@GUARD_PREFIX@_STDCOUNTOF_H': case '`':     case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

static inline bool
c_islower (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
      return true;
    default:
      return false;
    }
}

static inline bool
c_isprint (int c)
{
  switch (c)
    {
    case ' ':
    case '0': case '1': case '2': case '3':    case '4': case '5': case '6': case '7':    case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$':     case '%': case '&': case '\'': case '(':    case ')': case '*': case '+': case ',':     case '-': case '.': case '/': case ':':     case ';': case '<': case '=': case '>':     case '?': case '@': case '[': case '\\':    case ']': case '^': case '@GUARD_PREFIX@_STDCOUNTOF_H': case '`':     case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

static inline bool
c_ispunct (int c)
{
  switch (c)
    {
    case '!': case '"': case '#': case '$':     case '%': case '&': case '\'': case '(':    case ')': case '*': case '+': case ',':     case '-': case '.': case '/': case ':':     case ';': case '<': case '=': case '>':     case '?': case '@': case '[': case '\\':    case ']': case '^': case '@GUARD_PREFIX@_STDCOUNTOF_H': case '`':     case '{': case '|': case '}': case '~':
      return true;
    default:
      return false;
    }
}

static inline bool
c_isspace (int c)
{
  switch (c)
    {
    case ' ': case '\t': case '\n': case '\v': case '\f': case '\r':
      return true;
    default:
      return false;
    }
}

static inline bool
c_isupper (int c)
{
  switch (c)
    {
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

static inline bool
c_isxdigit (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3':    case '4': case '5': case '6': case '7':    case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):
      return true;
    default:
      return false;
    }
}

static inline int
c_tolower (int c)
{
  switch (c)
    {
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'):    case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):    case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'):    case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'):    case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'):    case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'):    case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return c - 'A' + 'a';
    default:
      return c;
    }
}

static inline int
c_toupper (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0):    case 'e' + (0): case 'f' + (0):    case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0):    case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0):    case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0):    case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0):    case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
      return c - 'a' + 'A';
    default:
      return c;
    }
}


_GL_INLINE_HEADER_END

/* Case-insensitive string comparison functions in C locale.
   Copyright (C) 1995-1996, 2001, 2003, 2005, 2009-2026 Free Software
   Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_ATTRIBUTE_PURE.  */



/* The functions defined in this file assume the "C" locale and a character
   set without diacritics (ASCII-US or EBCDIC-US or something like that).
   Even if the "C" locale on a particular system is an extension of the ASCII
   character set (like on BeOS, where it is UTF-8, or on AmigaOS, where it
   is ISO-8859-1), the functions in this file recognize only the ASCII
   characters.  More precisely, one of the string arguments must be an ASCII
   string; the other one can also contain non-ASCII characters (but then
   the comparison result will be nonzero).  */




/* Compare strings S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than, equal to or greater
   than S2.  */
extern int c_strcasecmp (const char *s1, const char *s2) ;

/* Compare no more than N characters of strings S1 and S2, ignoring case,
   returning less than, equal to or greater than zero if S1 is
   lexicographically less than, equal to or greater than S2.  */
extern int c_strncasecmp (const char *s1, const char *s2, size_t n)
  ;




/* Return the canonical absolute name of a given file.
   Copyright (C) 1996-2007, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_ATTRIBUTE_MALLOC.  */




enum canonicalize_mode_t
  {
    /* All components must exist.  */
    CAN_EXISTING = 0,

    /* All components excluding last one must exist.  */
    CAN_ALL_BUT_LAST = 1,

    /* No requirements on components existence.  */
    CAN_MISSING = 2,

    /* Don't expand symlinks.  */
    CAN_NOLINKS = 4
  };
typedef enum canonicalize_mode_t canonicalize_mode_t;

/* Return the canonical absolute name of file NAME, while treating
   missing elements according to CAN_MODE.  A canonical name
   does not contain any `.', `..' components nor any repeated file name
   separators ('/') or, depending on other CAN_MODE flags, symlinks.
   Whether components must exist or not depends on canonicalize mode.
   The result is malloc'd.
   Upon failure, return NULL with errno set.  */
char *canonicalize_filename_mode (const char *, canonicalize_mode_t)
   _GL_ATTRIBUTE_DEALLOC_FREE;


/* A simple (device, inode) struct.
   Copyright (C) 2003-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering, 2003.  */





struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
};



/* Make a string describing file modes.

   Copyright (C) 1998-1999, 2003, 2006, 2009-2026 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses HAVE_DECL_STRMODE.  */


/* Get the declaration of strmode.  */



extern void filemodestring (struct stat const *statp, char *str);


/* Concatenate two arbitrary file names.

   Copyright (C) 1996-1997, 2003, 2005, 2007, 2009-2026 Free Software
   Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering.  */

/* This file uses _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_RETURNS_NONNULL.  */





char *mfile_name_concat (char const *dir, char const *base,                           char **base_in_result)
   _GL_ATTRIBUTE_DEALLOC_FREE;


/* Compare file names containing version numbers.

   Copyright (C) 1995 Ian Jackson <iwj10@cus.cam.ac.uk>
   Copyright (C) 2001 Anthony Towns <aj@azure.humbug.org.au>
   Copyright (C) 2008-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_ATTRIBUTE_PURE.  */




/* Compare strings A and B as file names containing version numbers,
   and return an integer that is negative, zero, or positive depending
   on whether A compares less than, equal to, or greater than B.

   Use the following version sort algorithm:

     1. Compare the strings' maximal-length non-digit prefixes lexically.
        If there is a difference return that difference.
        Otherwise discard the prefixes and continue with the next step.

     2. Compare the strings' maximal-length digit prefixes, using
        numeric comparison of the numbers represented by each prefix.
        (Treat an empty prefix as zero; this can happen only at string end.)
        If there is a difference, return that difference.
        Otherwise discard the prefixes and continue with the next step.

     3. If both strings are empty, return 0.  Otherwise continue with step 1.

   In version sort, lexical comparison is left to right, byte by byte,
   using the byte's numeric value (0-255), except that:

     1. ASCII letters sort before other bytes.
     2. A tilde sorts before anything, even an empty string.

   In addition to the version sort rules, the following strings have
   special priority and sort before all other strings (listed in order):

     1. The empty string.
     2. ".".
     3. "..".
     4. Strings starting with "." sort before other strings.

   Before comparing two strings where both begin with non-".",
   or where both begin with "." but neither is "." or "..",
   suffixes matching the C-locale extended regular expression
   (\.[A-Za-z~][A-Za-z0-9~]*)*$ are removed and the strings compared
   without them, using version sort without special priority;
   if they do not compare equal, this comparison result is used and
   the suffixes are effectively ignored.  Otherwise, the entire
   strings are compared using version sort.  When removing a suffix
   from a nonempty string, remove the maximal-length suffix such that
   the remaining string is nonempty.

   This function is intended to be a replacement for strverscmp.  */
int filevercmp (char const *a, char const *b) ;

/* Like filevercmp, except compare the byte arrays A (of length ALEN)
   and B (of length BLEN) so that A and B can contain '\0', which
   sorts just before '\1'.  But if ALEN is -1 treat A as a string
   terminated by '\0', and similarly for BLEN.  */
int filenvercmp (char const *a, ptrdiff_t alen, char const *b, ptrdiff_t blen)
  ;



/* Determine whether a locale is hard.

   Copyright (C) 1999, 2003-2004, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */




/* Return true if the specified CATEGORY of the current locale is hard, i.e.
   different from the C or POSIX locale that has a fixed behavior.
   CATEGORY must be one of the LC_* values, but not LC_ALL.
   Note: This function uses the current global locale; it ignores the
   per-thread locale.  */
extern bool hard_locale (int category);



/* hash - hashing table processing.
   Copyright (C) 1998-1999, 2001, 2003, 2009-2026 Free Software Foundation,
   Inc.
   Written by Jim Meyering <meyering@ascend.com>, 1998.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* A generic hash table package.  */

/* Make sure USE_OBSTACK is defined to 1 if you want the allocator to use
   obstacks instead of malloc, and recompile 'hash.c' with same setting.  */


/* This file uses _GL_ATTRIBUTE_DEALLOC, _GL_ATTRIBUTE_DEPRECATED,
   _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_NODISCARD, _GL_ATTRIBUTE_PURE,
   _GL_ATTRIBUTE_RETURNS_NONNULL.  */



struct hash_tuning
  {
    /* This structure is mainly used for 'hash_initialize', see the block
       documentation of 'hash_reset_tuning' for more complete comments.  */

    float shrink_threshold;     /* ratio of used buckets to trigger a shrink */
    float shrink_factor;        /* ratio of new smaller size to original size */
    float growth_threshold;     /* ratio of used buckets to trigger a growth */
    float growth_factor;        /* ratio of new bigger size to original size */
    bool is_n_buckets;          /* if CANDIDATE really means table size */
  };

typedef struct hash_tuning Hash_tuning;

struct hash_table;

typedef struct hash_table Hash_table;

/*
 * Information and lookup.
 */

/* The following few functions provide information about the overall hash
   table organization: the number of entries, number of buckets and maximum
   length of buckets.  */

/* Return the number of buckets in the hash table.  The table size, the total
   number of buckets (used plus unused), or the maximum number of slots, are
   the same quantity.  */
extern size_t hash_get_n_buckets (const Hash_table *table)
       ;

/* Return the number of slots in use (non-empty buckets).  */
extern size_t hash_get_n_buckets_used (const Hash_table *table)
       ;

/* Return the number of active entries.  */
extern size_t hash_get_n_entries (const Hash_table *table)
       ;

/* Return the length of the longest chain (bucket).  */
extern size_t hash_get_max_bucket_length (const Hash_table *table)
       ;

/* Do a mild validation of a hash table, by traversing it and checking two
   statistics.  */
extern bool hash_table_ok (const Hash_table *table)
       ;

extern void hash_print_statistics (const Hash_table *table, FILE *stream);

/* If ENTRY matches an entry already in the hash table, return the
   entry from the table.  Otherwise, return NULL.  */
extern void *hash_lookup (const Hash_table *table, const void *entry);

/*
 * Walking.
 */

/* The functions in this page traverse the hash table and process the
   contained entries.  For the traversal to work properly, the hash table
   should not be resized nor modified while any particular entry is being
   processed.  In particular, entries should not be added, and an entry
   may be removed only if there is no shrink threshold and the entry being
   removed has already been passed to hash_get_next.  */

/* Return the first data in the table, or NULL if the table is empty.  */
extern void *hash_get_first (const Hash_table *table)
       ;

/* Return the user data for the entry following ENTRY, where ENTRY has been
   returned by a previous call to either 'hash_get_first' or 'hash_get_next'.
   Return NULL if there are no more entries.  */
extern void *hash_get_next (const Hash_table *table, const void *entry);

/* Fill BUFFER with pointers to active user entries in the hash table, then
   return the number of pointers copied.  Do not copy more than BUFFER_SIZE
   pointers.  */
extern size_t hash_get_entries (const Hash_table *table, void **buffer,                                  size_t buffer_size);


/* Call a PROCESSOR function for each entry of a hash table, and return the
   number of entries for which the processor function returned success.  A
   pointer to some PROCESSOR_DATA which will be made available to each call to
   the processor function.  The PROCESSOR accepts two arguments: the first is
   the user entry being walked into, the second is the value of PROCESSOR_DATA
   as received.  The walking continue for as long as the PROCESSOR function
   returns nonzero.  When it returns zero, the walking is interrupted.  */
extern size_t hash_do_for_each (const Hash_table *table,                                  Hash_processor processor, void *processor_data);

/* Return a hash code of ENTRY, in the range 0..TABLE_SIZE-1.
   This hash code function must have the property that if the comparator of
   ENTRY1 and ENTRY2 returns true, the hasher returns the same value for ENTRY1
   and for ENTRY2.
   The hash code function typically computes an unsigned integer and at the end
   performs a % TABLE_SIZE modulo operation.  This modulo operation is performed
   as part of this hash code function, not by the caller, because in some cases
   the unsigned integer will be a 'size_t', in other cases an 'uintmax_t' or
   even larger.  */

/* Compare two entries, ENTRY1 (being looked up or being inserted) and
   ENTRY2 (already in the table) for equality.  Return true for equal,
   false otherwise.  */

/* This function is invoked when an ENTRY is removed from the hash table.  */

/*
 * Allocation and clean-up.
 */

extern void hash_reset_tuning (Hash_tuning *tuning);

/* Reclaim all storage associated with a hash table.  If a data_freer
   function has been supplied by the user when the hash table was created,
   this function applies it to the data of each entry before freeing that
   entry.  This function preserves errno, like 'free'.  */
extern void hash_free (Hash_table *table);

/* Allocate and return a new hash table, or NULL upon failure.  The initial
   number of buckets is automatically selected so as to _guarantee_ that you
   may insert at least CANDIDATE different user entries before any growth of
   the hash table size occurs.  So, if have a reasonably tight a-priori upper
   bound on the number of entries you intend to insert in the hash table, you
   may save some table memory and insertion time, by specifying it here.  If
   the IS_N_BUCKETS field of the TUNING structure is true, the CANDIDATE
   argument has its meaning changed to the wanted number of buckets.

   TUNING points to a structure of user-supplied values, in case some fine
   tuning is wanted over the default behavior of the hasher.  If TUNING is
   NULL, the default tuning parameters are used instead.  If TUNING is
   provided but the values requested are out of bounds or might cause
   rounding errors, return NULL.

   The user-supplied HASHER function, when not NULL, accepts two
   arguments ENTRY and TABLE_SIZE.  It computes, by hashing ENTRY contents, a
   slot number for that entry which should be in the range 0..TABLE_SIZE-1.
   This slot number is then returned.

   The user-supplied COMPARATOR function, when not NULL, accepts two
   arguments pointing to user data, it then returns true for a pair of entries
   that compare equal, or false otherwise.  This function is internally called
   on entries which are already known to hash to the same bucket index,
   but which are distinct pointers.

   The user-supplied DATA_FREER function, when not NULL, may be later called
   with the user data as an argument, just before the entry containing the
   data gets freed.  This happens from within 'hash_free' or 'hash_clear'.
   You should specify this function only if you want these functions to free
   all of your 'data' data.  This is typically the case when your data is
   simply an auxiliary struct that you have malloc'd to aggregate several
   values.

   Set errno on failure; otherwise errno is unspecified.  */

extern Hash_table *hash_initialize (size_t candidate,                                      const Hash_tuning *tuning,                                      Hash_hasher hasher,                                      Hash_comparator comparator,                                      Hash_data_freer data_freer)
   ;

/* Like hash_initialize, but invokes xalloc_die instead of returning NULL.  */
/* This function is defined by module 'xhash'.  */

extern Hash_table *hash_xinitialize (size_t candidate,                                       const Hash_tuning *tuning,                                       Hash_hasher hasher,                                       Hash_comparator comparator,                                       Hash_data_freer data_freer)
   
  ;

/* Make all buckets empty, placing any chained entries on the free list.
   Apply the user-specified function data_freer (if any) to the data of any
   affected entries.  */
extern void hash_clear (Hash_table *table);

/*
 * Insertion and deletion.
 */

/* For an already existing hash table, change the number of buckets through
   specifying CANDIDATE.  The contents of the hash table are preserved.  The
   new number of buckets is automatically selected so as to _guarantee_ that
   the table may receive at least CANDIDATE different user entries, including
   those already in the table, before any other growth of the hash table size
   occurs.  If TUNING->IS_N_BUCKETS is true, then CANDIDATE specifies the
   exact number of buckets desired.  Return true iff the rehash succeeded,
   false (setting errno) otherwise.  */

extern bool hash_rehash (Hash_table *table, size_t candidate);

/* If ENTRY matches an entry already in the hash table, return the pointer
   to the entry from the table.  Otherwise, insert ENTRY and return ENTRY.
   Return NULL (setting errno) if the storage required for insertion
   cannot be allocated.  This implementation does not support
   duplicate entries or insertion of NULL.  */

extern void *hash_insert (Hash_table *table, const void *entry);

/* Same as hash_insert, but invokes xalloc_die instead of returning NULL.  */
/* This function is defined by module 'xhash'.  */
extern void *hash_xinsert (Hash_table *table, const void *entry);

/* Insert ENTRY into hash TABLE if there is not already a matching entry.

   Return -1 (setting errno) upon memory allocation failure.
   Return 1 if insertion succeeded.
   Return 0 if there is already a matching entry in the table,
   and in that case, if MATCHED_ENT is non-NULL, set *MATCHED_ENT
   to that entry.

   This interface is easier to use than hash_insert when you must
   distinguish between the latter two cases.  More importantly,
   hash_insert is unusable for some types of ENTRY values.  When using
   hash_insert, the only way to distinguish those cases is to compare
   the return value and ENTRY.  That works only when you can have two
   different ENTRY values that point to data that compares "equal".  Thus,
   when the ENTRY value is a simple scalar, you must use
   hash_insert_if_absent.  ENTRY must not be NULL.  */
extern int hash_insert_if_absent (Hash_table *table, const void *entry,                                    const void **matched_ent);

/* If ENTRY is already in the table, remove it and return the just-deleted
   data (the user may want to deallocate its storage).  If ENTRY is not in the
   table, don't modify the table and return NULL.  */
extern void *hash_remove (Hash_table *table, const void *entry);




/* human.h -- print human readable file size

   Copyright (C) 1996-2007, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert and Larry McVoy.  */




ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int chdir(const char *path);
int isatty(int fd);
char *getcwd(char *buf, size_t size);
ssize_t readlink(const char *path, char *buf, size_t size);


/* A more useful interface to strtol.

   Copyright (C) 1995-1996, 1998-1999, 2001-2004, 2006-2026 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* Get intmax_t, uintmax_t.  */



enum strtol_error
  {
    LONGINT_OK = 0,

    /* These two values can be ORed together, to indicate that both
       errors occurred.  */
    LONGINT_OVERFLOW = 1,
    LONGINT_INVALID_SUFFIX_CHAR = 2,

    LONGINT_INVALID_SUFFIX_CHAR_WITH_OVERFLOW = (LONGINT_INVALID_SUFFIX_CHAR                                                   | LONGINT_OVERFLOW),
    LONGINT_INVALID = 4
  };
typedef enum strtol_error strtol_error;

/* Act like the system's strtol (NPTR, ENDPTR, BASE) except:
   - The TYPE of the result might be something other than long int.
   - Return strtol_error, and store any result through an additional
     TYPE *VAL pointer instead of returning the result.
   - If TYPE is unsigned, reject leading '-'.
   - Behavior is undefined if BASE is negative, 1, or greater than 36.
     (In this respect xstrtol acts like the C standard, not like POSIX.)
   - Accept an additional char const *VALID_SUFFIXES pointer to a
     possibly-empty string containing allowed numeric suffixes,
     which multiply the value.  These include SI suffixes like 'k' and 'M';
     these normally stand for powers of 1024, but if VALID_SUFFIXES also
     includes '0' they can be followed by "B" to stand for the usual
     SI powers of 1000 (or by "iB" to stand for powers of 1024 as before).
     Other supported suffixes include 'K' for 1024 or 1000, 'b' for 512,
     'c' for 1, and 'w' for 2.
   - Suppose that after the initial whitespace, the number is missing
     but there is a valid suffix.  Then the number is treated as 1.  */

strtol_error xstrtol (char const *restrict /*nptr*/,                                  char **restrict /*endptr*/,                                     int /*base*/,                                                   long int *restrict /*val*/,                                         char const *restrict /*valid_suffixes*/);
strtol_error xstrtoul (char const *restrict /*nptr*/,                                  char **restrict /*endptr*/,                                     int /*base*/,                                                   unsigned long int *restrict /*val*/,                                         char const *restrict /*valid_suffixes*/);
strtol_error xstrtoll (char const *restrict /*nptr*/,                                  char **restrict /*endptr*/,                                     int /*base*/,                                                   long long int *restrict /*val*/,                                         char const *restrict /*valid_suffixes*/);
strtol_error xstrtoull (char const *restrict /*nptr*/,                                  char **restrict /*endptr*/,                                     int /*base*/,                                                   unsigned long long int *restrict /*val*/,                                         char const *restrict /*valid_suffixes*/);
strtol_error xstrtoimax (char const *restrict /*nptr*/,                                  char **restrict /*endptr*/,                                     int /*base*/,                                                   intmax_t *restrict /*val*/,                                         char const *restrict /*valid_suffixes*/);
strtol_error xstrtoumax (char const *restrict /*nptr*/,                                  char **restrict /*endptr*/,                                     int /*base*/,                                                   uintmax_t *restrict /*val*/,                                         char const *restrict /*valid_suffixes*/);






/* A conservative bound on the maximum length of a human-readable string.
   The output can be the square of the largest uintmax_t, so double
   its size before converting to a bound.
   log10 (2.0) < 146/485.  Add 1 for integer division truncation.
   Also, the output can have a thousands separator between every digit,
   so multiply by MB_LEN_MAX + 1 and then subtract MB_LEN_MAX.
   Append 1 for a space before the suffix.
   Finally, append 3, the maximum length of a suffix.  */

/* Options for human_readable.  */
enum
{
  /* Unless otherwise specified these options may be ORed together.  */

  /* The following three options are mutually exclusive.  */
  /* Round to plus infinity (default).  */
  human_ceiling = 0,
  /* Round to nearest, ties to even.  */
  human_round_to_nearest = 1,
  /* Round to minus infinity.  */
  human_floor = 2,

  /* Group digits together, e.g. "1,000,000".  This uses the
     locale-defined grouping; the traditional C locale does not group,
     so this has effect only if some other locale is in use.  */
  human_group_digits = 4,

  /* When autoscaling, suppress ".0" at end.  */
  human_suppress_point_zero = 8,

  /* Scale output and use SI-style units, ignoring the output block size.  */
  human_autoscale = 16,

  /* Prefer base 1024 to base 1000.  */
  human_base_1024 = 32,

  /* Prepend " " before unit symbol.  */
  human_space_before_unit = 64,

  /* Append SI prefix, e.g. "k" or "M".  */
  human_SI = 128,

  /* Append "B" (if base 1000) or "iB" (if base 1024) to SI prefix.  */
  human_B = 256
};

char *human_readable (uintmax_t, char *, int, uintmax_t, uintmax_t);

enum strtol_error human_options (char const *, int *, uintmax_t *);



/* Username <--> uid and groupname <--> gid conversions, with cache for speed.
   Copyright (C) 2007-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering, 2007.  */





extern char *getuser (uid_t uid);
extern char *getgroup (gid_t gid);
extern uid_t *getuidbyname (const char *user);
extern gid_t *getgidbyname (const char *group);



/* Determine the number of screen columns needed for a string.
   Copyright (C) 2000-2004, 2007, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* This file uses HAVE_DECL_MBSWIDTH_IN_WCHAR_H.  */


/* Avoid a clash of our mbswidth() with a function of the same name defined
   in UnixWare 7.1.1 <wchar.h>.  We need this #include before the #define
   below.  */




/* Optional flags to influence mbswidth/mbsnwidth behavior.  */

/* If this bit is set, return -1 upon finding an invalid or incomplete
   character.  Otherwise, assume invalid characters have width 1.  */

/* If this bit is set, return -1 upon finding a non-printable character.
   Otherwise, assume unprintable characters have width 0 if they are
   control characters and 1 otherwise.  */


/* Returns the number of screen columns needed for STRING.  */
extern int gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (const char *string, int flags);

/* Returns the number of screen columns needed for the NBYTES bytes
   starting at BUF.  */
extern int mbsnwidth (const char *buf, size_t nbytes, int flags);


/* Sort a vector of pointers to data.

   Copyright (C) 2007-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */




void mpsort (void const **, size_t, int (*) (void const *, void const *));


/* obstack.h - object stack macros
   Copyright (C) 1988-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Summary:

   All the apparent functions defined here are macros. The idea
   is that you would use these pre-tested macros to solve a
   very specific set of problems, and they would run fast.
   Caution: no side-effects in arguments please!! They may be
   evaluated MANY times!!

   These macros operate a stack of objects.  Each object starts life
   small, and may grow to maturity.  (Consider building a word syllable
   by syllable.)  An object can move while it is growing.  Once it has
   been "finished" it never changes address again.  So the "top of the
   stack" is typically an immature growing object, while the rest of the
   stack is of mature, fixed size and fixed address objects.

   These routines grab large chunks of memory, using a function you
   supply, called 'obstack_chunk_alloc'.  On occasion, they free chunks,
   by calling 'obstack_chunk_free'.  You must define them and declare
   them before using any obstack macros.

   Each independent stack is represented by a 'struct obstack'.
   Each of the obstack macros expects a pointer to such a structure
   as the first argument.

   One motivation for this package is the problem of growing char strings
   in symbol tables.  Unless you are "fascist pig with a read-only mind"
   --Gosper's immortal quote from HAKMEM item 154, out of context--you
   would not like to put any arbitrary upper limit on the length of your
   symbols.

   In practice this often means you will build many short symbols and a
   few long symbols.  At the time you are reading a symbol you don't know
   how long it is.  One traditional method is to read a symbol into a
   buffer, realloc()ating the buffer every time you try to read a symbol
   that is longer than the buffer.  This is beaut, but you still will
   want to copy the symbol from the buffer to a more permanent
   symbol-table entry say about half the time.

   With obstacks, you can work differently.  Use one obstack for all symbol
   names.  As you read a symbol, grow the name in the obstack gradually.
   When the name is complete, finalize it.  Then, if the symbol exists already,
   free the newly read name.

   The way we do this is to take a large chunk, allocating memory from
   low addresses.  When you want to build a symbol in the chunk you just
   add chars above the current "high water mark" in the chunk.  When you
   have finished adding chars, because you got to the end of the symbol,
   you know how long the chars are, and you can create a new object.
   Mostly the chars will not burst over the highest address of the chunk,
   because you would typically expect a chunk to be (say) 100 times as
   long as an average object.

   In case that isn't clear, when we have enough chars to make up
   the object, THEY ARE ALREADY CONTIGUOUS IN THE CHUNK (guaranteed)
   so we just point to it where it lies.  No moving of chars is
   needed and this is the second win: potentially long strings need
   never be explicitly shuffled. Once an object is formed, it does not
   change its address during its lifetime.

   When the chars burst over a chunk boundary, we allocate a larger
   chunk, and then copy the partly formed object from the end of the old
   chunk to the beginning of the new larger chunk.  We then carry on
   accreting characters to the end of the object as we normally would.

   A special macro is provided to add a single char at a time to a
   growing object.  This allows the use of register variables, which
   break the ordinary 'growth' macro.

   Summary:
        We allocate large chunks.
        We carve out one object at a time from the current chunk.
        Once carved, an object never moves.
        We are free to append data of any size to the currently
          growing object.
        Exactly one object is growing in an obstack at any one time.
        You can run one obstack per control block.
        You may have as many control blocks as you dare.
        Because of the way we do it, you can "unwind" an obstack
          back to a previous state. (You may remove objects much
          as you would with a stack.)
 */

/* Documentation (part of the GNU libc manual):
   <https://www.gnu.org/software/libc/manual/html_node/Obstacks.html>  */


/* Don't do the contents of this file more than once.  */


/* For backward compatibility with older glibc,
   define the otherwise-unused macro PTR_INT_TYPE.  If __PTRDIFF_TYPE__ is
   defined, as with GNU C, use that; that way we don't pollute the
   namespace with <stddef.h>'s symbols.  Otherwise, include <stddef.h>
   and use ptrdiff_t.  */

/* An integer type wide enough to hold a pointer value,
   if such a type is available.  */

/* A type suitable for comparing pointers regardless of whether they
   point into the same object, e.g., (_OBSTACK_CPTR) p < (_OBSTACK_CPTR) q.
   If possible, use uintptr_t to avoid undefined behavior and pacify
   sanitizers.  Otherwise, use a pointer directly and hope for the best.  */

/* These macros highlight the places where this implementation
   is different from the one in GNU libc.  */
/* For backward compatibility, glibc limits object sizes to int range.  */

/* If B is the base of an object addressed by P, return the result of
   aligning P to the next multiple of A + 1.  B and P must be of type
   char *.  A + 1 must be a power of 2.  With no uintptr_t, play it
   safe and compute the alignment relative to B.  Otherwise, use the
   faster strategy of computing the alignment through uintptr_t.  */

/* For memcpy, size_t.  */


/* Not the same as _Noreturn, since it also works with function pointers.  */


struct _obstack_chunk           /* Lives at front of each chunk. */
{
  char *limit;                  /* 1 past end of this chunk */
  struct _obstack_chunk *prev;  /* address of prior chunk or NULL */
  char contents[4]; /* objects begin here */
};

struct obstack          /* control current object in current chunk */
{
  long int chunk_size;  /* preferred size to allocate chunks in */
  struct _obstack_chunk *chunk; /* address of current struct obstack_chunk */
  char *object_base;            /* address of object we are building */
  char *next_free;              /* where to add next char to current object */
  char *chunk_limit;            /* address of char after current chunk */
  union
  {
    unsigned int tempint;
    void *tempptr;
  } temp;                       /* Temporary for some macros.  */
  int alignment_mask;  /* Mask of alignment for each object. */

  /* These prototypes vary based on 'use_extra_arg'.  */
  union
  {
    void *(*plain) (long int);
    void *(*extra) (void *, long int);
  } chunkfun;
  union
  {
    void (*plain) (void *);
    void (*extra) (void *, void *);
  } freefun;

  void *extra_arg;              /* first arg for chunk alloc/dealloc funcs */
  unsigned use_extra_arg : 1;     /* chunk alloc/dealloc funcs take extra arg */
  unsigned maybe_empty_object : 1; /* There is a possibility that the current
                                      chunk contains a zero-length object.  This
                                      prevents freeing the chunk if we allocate
                                      a bigger chunk to replace it. */
  unsigned alloc_failed : 1;      /* No longer used, as we now call the failed
                                     handler on error, but retained for binary
                                     compatibility.  */
};

/* Declare the external functions we use; they are in obstack.c.  */

/* Symbol mapping for gnulib.  */

/* The default name of the function for freeing a chunk is '_obstack_free',
   but gnulib overrides this by defining '__obstack_free' above.  */

extern void _obstack_newchunk (struct obstack *, int);
extern int _obstack_begin (struct obstack *,                             int, int,                             void *(*) (long int),                             void (*) (void *));
extern int _obstack_begin_1 (struct obstack *,                               int, int,                               void *(*) (void *, long int),                               void (*) (void *, void *), void *);
extern int _obstack_memory_used (struct obstack *)
  ;
extern void _obstack_free (struct obstack *, void *);


/* Error handler called when 'obstack_chunk_alloc' failed to allocate
   more memory.  This can be set to a user defined function which
   should either abort gracefully or use longjump - but shouldn't
   return.  The default action is to print a message and abort.  */
extern  void (*obstack_alloc_failed_handler) (void);

/* Exit value used when 'print_and_abort' is used.  */
extern int obstack_exit_failure;

/* Pointer to beginning of object being allocated or to be allocated next.
   Note that this might not be the final address of the object
   because a new chunk might be needed to hold the final size.  */


/* Size for allocating ordinary chunks.  */


/* Pointer to next byte not yet allocated in current chunk.  */


/* Mask specifying low bits that should be clear in address of an object.  */


/* To prevent prototype warnings provide complete argument list.  */













/* Note that the call to _obstack_newchunk is enclosed in (..., 0)
   so that we can avoid having void expressions
   in the arms of the conditional expression.
   Casting the third operand to void was tried before,
   but some compilers won't accept it.  */

















/* quote.h - prototypes for quote.c

   Copyright (C) 1998-2001, 2003, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Yield size-related values in struct stat.
   Copyright (C) 1989, 1991-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses HAVE_SYS_PARAM_H, HAVE_STRUCT_STAT_ST_BLOCKS.  */

/* sys/param.h may define DEV_BSIZE */

/* The device blocksize, or a faked version thereof.
   But use ST_NBLOCKSIZE instead.
   Usually defined by sys/param.h (if at all).  */

/* Extract or fake data from a struct stat *st.
   STP_BLKSIZE(st): Preferred performance I/O blocksize, in bytes.
   STP_NBLOCKS(st): Number of blocks, including indirect blocks.
   ST_NBLOCKSIZE: Size of blocks used when calculating ST_NBLOCKS.  */
  /* coreutils' fileblocks.c also uses BSIZE.  */
   /* This definition calls st_blocks, which is in the fileblocks module. */



/* Preferred blocksize and number of blocks for a struct stat object.  */

/* stat-related time functions.

   Copyright (C) 2005, 2007, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert.  */


/* This file uses _GL_INLINE_HEADER_BEGIN, _GL_INLINE, _GL_UNUSED,
   _GL_ATTRIBUTE_PURE, HAVE_STRUCT_STAT_*.  */


extern int errno;


/* stdckdint.h -- checked integer arithmetic

   Copyright 2022-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

@PRAGMA_COLUMNS@

/* Copyright 2025-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2025.  */



struct timespec { time_t tv_sec; long tv_nsec; };
struct tm {
    int tm_sec, tm_min, tm_hour;
    int tm_mday, tm_mon, tm_year;
    int tm_wday, tm_yday, tm_isdst;
};

time_t time(time_t *result);
struct tm *localtime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
size_t strftime(char *s, size_t max, const char *format,                 const struct tm *tm);


_GL_INLINE_HEADER_BEGIN


/* STAT_TIMESPEC (ST, ST_XTIM) is the ST_XTIM member for *ST of type
   struct timespec, if available.  If not, then STAT_TIMESPEC_NS (ST,
   ST_XTIM) is the nanosecond component of the ST_XTIM member for *ST,
   if available.  ST_XTIM can be st_atim, st_ctim, st_mtim, or st_birthtim
   for access, status change, data modification, or birth (creation)
   time respectively.

   These macros are private to stat-time.h.  */

/* Return the nanosecond component of *ST's access time.  */
static inline long int 
get_stat_atime_ns (struct stat const *st)
{
  return 0;
}

/* Return the nanosecond component of *ST's status change time.  */
static inline long int 
get_stat_ctime_ns (struct stat const *st)
{
  return 0;
}

/* Return the nanosecond component of *ST's data modification time.  */
static inline long int 
get_stat_mtime_ns (struct stat const *st)
{
  return 0;
}

/* Return the nanosecond component of *ST's birth time.  */
static inline long int 
get_stat_birthtime_ns (_GL_UNUSED struct stat const *st)
{
  return 0;
}

/* Constructs a 'struct timespec' with the given contents.
   This macro / function is private to stat-time.h.  */
/* C++ does not have C99 compound literals.
   A constructor invocation
     timespec { (sec), (nsec) }
   would make assumptions about the order of the fields of 'struct timespec',
   which are not guaranteed by POSIX.  So, use an inline function.  */
static inline struct timespec
_gl_make_timespec (time_t sec, long nsec)
{
  struct timespec ts;
  ts.tv_sec = sec;
  ts.tv_nsec = nsec;
  return ts;
}

/* Return *ST's access time.  */
static inline struct timespec 
get_stat_atime (struct stat const *st)
{
  return _gl_make_timespec (st->st_atime, get_stat_atime_ns (st));
}

/* Return *ST's status change time.  */
static inline struct timespec 
get_stat_ctime (struct stat const *st)
{
  return _gl_make_timespec (st->st_ctime, get_stat_ctime_ns (st));
}

/* Return *ST's data modification time.  */
static inline struct timespec 
get_stat_mtime (struct stat const *st)
{
  return _gl_make_timespec (st->st_mtime, get_stat_mtime_ns (st));
}

/* Return *ST's birth time, if available; otherwise return a value
   with tv_sec and tv_nsec both equal to -1.  */
static inline struct timespec 
get_stat_birthtime (_GL_UNUSED struct stat const *st)
{
  struct timespec t;

  /* Birth time is not supported.  */
  t = _gl_make_timespec (-1, -1);


  return t;
}

/* If a stat-like function returned RESULT, normalize the timestamps
   in *ST, if this platform suffers from a macOS and Solaris bug where
   tv_nsec might be negative.  Return the adjusted RESULT, setting
   errno to EOVERFLOW if normalization overflowed.  This function
   is intended to be private to Gnulib.  */
static inline int
stat_time_normalize (int result, _GL_UNUSED struct stat *st)
{
  return result;
}


_GL_INLINE_HEADER_END

/* declarations for strftime.c

   Copyright (C) 2002, 2004, 2008-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



/* Format the broken-down time *__TP, with additional __NS nanoseconds,
   into the buffer __S of size __MAXSIZE, according to the rules of the
   LC_TIME category of the current locale.

   Use the time zone __TZ.
   If *__TP represents local time, __TZ should be set to
     tzalloc (getenv ("TZ")).
   If *__TP represents universal time (a.k.a. GMT), __TZ should be set to
     (timezone_t) 0.

   The format string __FORMAT, including GNU extensions, is described in
   the GNU libc's strftime() documentation:
   <https://www.gnu.org/software/libc/manual/html_node/Formatting-Calendar-Time.html>
   Additionally, the following conversion is supported:
     %N   The number of nanoseconds, passed as __NS argument.
   Here's a summary of the available conversions (= format directives):
     literal characters      %n %t %%
     date:
       century               %C
       year                  %Y %y
       week-based year       %G %g
       month (in year)       %m %B %b %h
       week in year          %U %W %V
       day in year           %j
       day (in month)        %d %e
       day in week           %u %w %A %a
       year, month, day      %x %F %D
     time:
       half-day              %p %P
       hour                  %H %k %I %l
       minute (in hour)      %M
       hour, minute          %R
       second (in minute)    %S
       hour, minute, second  %r %T %X
       second (since epoch)  %s
     date and time:          %c
     time zone:              %z %Z
     nanosecond              %N
   In locales with non-Gregorian calendars, the following conversions don't
   apply in the expected way:
     date:
       century               %C
       year                  %y
       week-based year       %G %g
       week in year          %U %W %V
       day in year           %j
       year, month, day      %D

   Store the result, as a string with a trailing NUL character, at the
   beginning of the array __S[0..__MAXSIZE-1] and return the length of
   that string, not counting the trailing NUL.
   If unsuccessful, possibly change the array __S, set errno, and return -1;
   errno == ERANGE means the string didn't fit.

   As a glibc extension if __S is null, do not store anything, and
   return the value that would have been returned had __S been non-null.

   A __MAXSIZE greater than PTRDIFF_MAX is silently treated as if
   it were PTRDIFF_MAX, so that the caller can safely add 1 to
   any return value without overflow.

   This function is like strftime, but with two more arguments:
     * __TZ instead of the local timezone information,
     * __NS as the number of nanoseconds in the %N directive,
   and on success it does not preserve errno,
   and on failure it returns -1 not 0.
 */
ptrdiff_t nstrftime (char *restrict __s, size_t __maxsize,                       char const *__format,                       struct tm const *__tp, timezone_t __tz, int __ns);

/* Like nstrftime, except that it uses the "C" locale instead of the
   current locale.  */
ptrdiff_t c_nstrftime (char *restrict __s, size_t __maxsize,                         char const *__format,                         struct tm const *__tp, timezone_t __tz, int __ns);

/* Convert decimal strings with bounds checking and exit on error.

   Copyright (C) 2014-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



/* Flags for xnumtoimax and xnumtoumax.  They can be ORed together.  */
enum
  {
    /* If the number is less than MIN, do not diagnose the problem;
       instead, return MIN and set errno to EOVERFLOW or ERANGE.  */
    XTOINT_MIN_QUIET = 1 << 0,

    /* Likewise for the MAX argument.  */
    XTOINT_MAX_QUIET = 1 << 1,

    /* The MIN argument is imposed by the caller, not by the type of
       the result.  This causes the function to use ERANGE rather
       than EOVERFLOW behavior when issuing diagnostics or setting errno.  */
    XTOINT_MIN_RANGE = 1 << 2,

    /* Likewise for the MAX argument.  */
    XTOINT_MAX_RANGE = 1 << 3
  };


intmax_t xdectoimax (char const *n_str, intmax_t min, intmax_t max,              char const *suffixes, char const *err, int err_exit)     _GL_ATTRIBUTE_NONNULL ((1, 5));
uintmax_t xdectoumax (char const *n_str, uintmax_t min, uintmax_t max,              char const *suffixes, char const *err, int err_exit)     _GL_ATTRIBUTE_NONNULL ((1, 5));

intmax_t xnumtoimax (char const *n_str, int base, intmax_t min, intmax_t max,              char const *suffixes, char const *err, int err_exit, int flags)     _GL_ATTRIBUTE_NONNULL ((1, 6));
uintmax_t xnumtoumax (char const *n_str, int base, uintmax_t min, uintmax_t max,              char const *suffixes, char const *err, int err_exit, int flags)     _GL_ATTRIBUTE_NONNULL ((1, 6));

/* Return current hostname with unlimited length.

   Copyright (C) 2003-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* This file uses _GL_ATTRIBUTE_MALLOC.  */




char *xgethostname (void)
   _GL_ATTRIBUTE_DEALLOC_FREE;


/* xmemdup0.h -- copy a block of arbitrary bytes, plus a trailing NUL

   Copyright (C) 2008-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_RETURNS_NONNULL.  */




char *xmemdup0 (void const *p, size_t s)
   _GL_ATTRIBUTE_DEALLOC_FREE
  ;


/* Error reporting interface for xstrto* functions.

   Copyright (C) 1995-1996, 1998-1999, 2001-2004, 2006-2026 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _Noreturn.  */

/* A more useful interface to strtol.

   Copyright (C) 1995-1996, 1998-1999, 2001-2004, 2006-2026 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



/* Report an error for an invalid integer in an option argument.

   ERR is the error code returned by one of the xstrto* functions.

   Use OPT_IDX to decide whether to print the short option string "C"
   or "-C" or a long option string derived from LONG_OPTIONS.  OPT_IDX
   is -2 if the short option "C" was used, without any leading "-"; it
   is -1 if the short option "-C" was used; otherwise it is an index
   into LONG_OPTIONS, which should have a name preceded by two '-'
   characters.

   ARG is the option-argument containing the integer.

   After reporting an error, exit with a failure status.  */

_Noreturn void xstrtol_fatal (enum strtol_error /* err */,                                int /* opt_idx */, char /* c */,                                struct option const * /* long_options */,                                char const * /* arg */);

/* A more useful interface to strtol.

   Copyright (C) 1995-1996, 1998-1999, 2001-2004, 2006-2026 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* system-dependent definitions for coreutils
   Copyright (C) 1989-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Include this file _after_ system headers if possible.  */

/* ATTRIBUTE_* macros for using attributes in GCC and similar compilers

   Copyright 2020-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert.  */

/* Provide public ATTRIBUTE_* names for the private _GL_ATTRIBUTE_*
   macros used within Gnulib.  */

/* The placement of these attributes depends on the kind of declaration
   and, in some cases, also on the programming language (C vs. C++).

   In function declarations and function definitions:

     * ATTRIBUTE_NOTHROW must come after the parameter list.

     * The macros
         ATTRIBUTE_CONST
         ATTRIBUTE_PURE
         DEPRECATED
         MAYBE_UNUSED
         NODISCARD
         REPRODUCIBLE
         UNSEQUENCED
       must come before the return type, and more precisely:
         - In a function declaration/definition without a storage-class
           specifier: at the beginning of the declaration/definition.
         - In a function declaration/definition with a storage-class
           specifier:
             - In C: before the storage-class specifier.
             - In C++: between the storage-class specifier and the return type.

     * The other macros can be placed
         - Either
             - In a function declaration/definition without a storage-class
               specifier: at the beginning of the declaration/definition.
             - In a function declaration/definition with a storage-class
               specifier: between the storage-class specifier and the return
               type.
        - Or, in a function declaration:
          after the parameter list,
            ∙ but after ATTRIBUTE_NOTHROW if present.

   In other declarations, such as variable declarations:

     * Either
         - In C: before the storage-class specifier.
         - In C++: between the storage-class specifier and the return type.
       Then they apply to all entities that are declared by the declaration.

     * Or immediately after the name of an entity being declared by the
       declaration.  Then they apply to that entity only.
 */



/* This file defines two types of attributes:
   * C23 standard attributes.  These have macro names that do not begin with
     'ATTRIBUTE_'.
   * Selected GCC attributes; see:
     https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html
     https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html
     https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html
     These names begin with 'ATTRIBUTE_' to avoid name clashes.  */


/* This file uses _GL_ATTRIBUTE_ALLOC_SIZE, _GL_ATTRIBUTE_ALWAYS_INLINE,
   _GL_ATTRIBUTE_ARTIFICIAL, _GL_ATTRIBUTE_COLD, _GL_ATTRIBUTE_CONST,
   _GL_ATTRIBUTE_COUNTED_BY, _GL_ATTRIBUTE_DEALLOC, _GL_ATTRIBUTE_DEPRECATED,
   _GL_ATTRIBUTE_ERROR, _GL_ATTRIBUTE_WARNING, _GL_ATTRIBUTE_EXTERNALLY_VISIBLE,
   _GL_ATTRIBUTE_FALLTHROUGH, _GL_ATTRIBUTE_FORMAT, _GL_ATTRIBUTE_LEAF,
   _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_MAY_ALIAS, _GL_ATTRIBUTE_MAYBE_UNUSED,
   _GL_ATTRIBUTE_NODISCARD, _GL_ATTRIBUTE_NOINLINE, _GL_ATTRIBUTE_NONNULL,
   _GL_ATTRIBUTE_NONNULL_IF_NONZERO, _GL_ATTRIBUTE_NONSTRING,
   _GL_ATTRIBUTE_NOTHROW, _GL_ATTRIBUTE_PACKED, _GL_ATTRIBUTE_PURE,
   _GL_ATTRIBUTE_REPRODUCIBLE, _GL_ATTRIBUTE_RETURNS_NONNULL,
   _GL_ATTRIBUTE_SENTINEL, _GL_ATTRIBUTE_UNSEQUENCED, _GL_UNNAMED.  */


/* =============== Attributes for specific kinds of functions =============== */

/* Attributes for functions that should not be used.  */

/* Warn if the entity is used.  */
/* Applies to:
     - function, variable,
     - struct, union, struct/union member,
     - enumeration, enumeration item,
     - typedef,
   in C++ also: namespace, class, template specialization.  */

/* If a function call is not optimized way, warn with MSG.  */
/* Applies to: functions.  */

/* If a function call is not optimized way, report an error with MSG.  */
/* Applies to: functions.  */


/* Attributes for memory-allocating functions.  */

/* The function returns a pointer to freshly allocated memory.  */
/* Applies to: functions.  */

/* ATTRIBUTE_ALLOC_SIZE ((N)) - The Nth argument of the function
   is the size of the returned memory block.
   ATTRIBUTE_ALLOC_SIZE ((M, N)) - Multiply the Mth and Nth arguments
   to determine the size of the returned memory block.  */
/* Applies to: functions, pointer to functions, function types.  */

/* ATTRIBUTE_DEALLOC (F, I) declares that the function returns pointers
   that can be freed by passing them as the Ith argument to the
   function F.
   ATTRIBUTE_DEALLOC_FREE declares that the function returns pointers that
   can be freed via 'free'; it can be used only after declaring 'free'.  */
/* Applies to: functions.  Cannot be used on inline functions.  */

/* Attributes for variadic functions.  */

/* The variadic function expects a trailing NULL argument.
   ATTRIBUTE_SENTINEL () - The last argument is NULL (requires C99).
   ATTRIBUTE_SENTINEL ((N)) - The (N+1)st argument from the end is NULL.  */
/* Applies to: functions.  */


/* ================== Attributes for compiler diagnostics ================== */

/* Attributes that help the compiler diagnose programmer mistakes.
   Some of them may also help for some compiler optimizations.  */

/* ATTRIBUTE_FORMAT ((ARCHETYPE, STRING-INDEX, FIRST-TO-CHECK)) -
   The STRING-INDEXth function argument is a format string of style
   ARCHETYPE, which is one of:
     printf, gnu_printf
     scanf, gnu_scanf,
     strftime, gnu_strftime,
     strfmon,
   or the same thing prefixed and suffixed with '__'.
   If FIRST-TO-CHECK is not 0, arguments starting at FIRST-TO_CHECK
   are suitable for the format string.  */
/* Applies to: functions.  */

/* ATTRIBUTE_NONNULL ((N1, N2,...)) - Arguments N1, N2,... must not be NULL.
   ATTRIBUTE_NONNULL () - All pointer arguments must not be null.  */
/* Applies to: functions.  */

/* ATTRIBUTE_NONNULL_IF_NONZERO (NP, NI) - Argument NP (a pointer)
   must not be NULL if the argument NI (an integer) is != 0.  */
/* Applies to: functions.  */


/* The function's return value is a non-NULL pointer.  */
/* Applies to: functions.  */

/* Warn if the caller does not use the return value,
   unless the caller uses something like ignore_value.  */
/* Applies to: function, enumeration, class.  */


/* Attributes that disable false alarms when the compiler diagnoses
   programmer "mistakes".  */

/* Do not warn if the entity is not used.  */
/* Applies to:
     - function, variable,
     - struct, union, struct/union member,
     - enumeration, enumeration item,
     - typedef,
   in C++ also: class.  */

/* The contents of a character array is not meant to be NUL-terminated.  */
/* Applies to: struct/union members and variables that are arrays of element
   type '[[un]signed] char'.  */

/* Do not warn if control flow falls through to the immediately
   following 'case' or 'default' label.  */
/* Applies to: Empty statement (;), inside a 'switch' statement.  */


/* =================== Attributes for runtime diagnostics =================== */

/* Attributes that provide information to the undefined-behaviour sanitizer
   (UBSAN).  */

/* COUNTED_BY (C) declares that the number of elements of the field is given
   by C, which must be another field in the same struct.
   The programmer is responsible for guaranteeing some invariants; see
   <https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html> for details.  */
/* Applies to struct fields of type array or pointer (to data).  */


/* ================== Attributes for debugging information ================== */

/* Attributes regarding debugging information emitted by the compiler.  */

/* Omit the function from stack traces when debugging.  */
/* Applies to: functions.  */

/* Make the entity visible to debuggers etc., even with '-fwhole-program'.  */
/* Applies to: functions, variables.  */


/* ========== Attributes that mainly direct compiler optimizations ========== */

/* The function does not throw exceptions.  */
/* Applies to: functions.  */
/* After a function's parameter list, this attribute must come first, before
   other attributes.  */

/* Do not inline the function.  */
/* Applies to: functions.  */

/* Always inline the function, and report an error if the compiler
   cannot inline.  */
/* Applies to: functions.  */

/* It is OK for a compiler to move a call, or omit a duplicate call
   and reuse a cached return value, even if the state changes between calls.
   It is also OK to omit a call if the result is not used.
   This attribute is safe if the function does not change observable state,
   returns a value determined solely by its arguments' values
   without examining state, and always returns exactly once -
   e.g., does not raise an exception, call longjmp, or loop forever.
   (This attribute is stricter than _GL_ATTRIBUTE_PURE because the
   function cannot observe state.  Unlike _GL_ATTRIBUTE_UNSEQUENCED
   the function must return exactly once and cannot access state
   addressed by its pointer arguments or that happens to have the same
   value for all calls to the function, but the function is allowed to
   return a pointer to storage that can be modified later.  */
/* Applies to: functions.  */

/* It is OK for a compiler to move a call, or omit a duplicate call
   and reuse a cached value returned either directly or indirectly via
   a pointer, if the state addressed by its pointer arguments is the same;
   however, pointer arguments cannot alias.
   This attribute is safe for a function that is effectless, idempotent,
   stateless, and independent; see ISO C 23 § 6.7.13.8 for a definition of
   these terms.
   (This attribute is stricter than _GL_ATTRIBUTE_REPRODUCIBLE because
   the function must be stateless and independent.  Unlike
   _GL_ATTRIBUTE_CONST the function need not return exactly once, and
   can depend on state accessed via its pointer arguments or that
   happens to have the same value for all calls to the function, but
   the function cannot return a pointer to storage whose contents
   change later.)
   See also <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2956.htm> and
   <https://stackoverflow.com/questions/76847905/>.  */
/* Applies to: functions, pointer to functions, function type.  */

/* It is OK for a compiler to move a call, or omit a duplicate call
   and reuse a cached return value, if observable state is the same.
   It is also OK to omit a call if the return value is not used.
   This attribute is safe if the function does not change observable state,
   returns a value determined solely by its arguments's values
   together with observable state, and always returns exactly once.
   (This attribute is looser than _GL_ATTRIBUTE_CONST because the function
   can depend on observable state.
   Unlike _GL_ATTRIBUTE_REPRODUCIBLE the function must return exactly
   once and cannot change state addressed by its arguments, but the
   function can return a pointer to storage whose contents change later.)  */
/* Applies to: functions.  */

/* It is OK for a compiler to move a call, or omit a duplicate call
   and reuse a cached value returned either directly or indirectly via
   a pointer, if other observable state is the same;
   however, pointer arguments cannot alias.
   This attribute is safe for a function that is effectless and idempotent;
   see ISO C 23 § 6.7.13.8 for a definition of these terms.
   (This attribute is looser than _GL_ATTRIBUTE_UNSEQUENCED because
   the function need not be stateless or independent.
   Unlike _GL_ATTRIBUTE_PURE the function need not return exactly once
   and can change state addressed by its pointer arguments, but the
   function cannot return a pointer to storage whose contents change later.)
   See also <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2956.htm> and
   <https://stackoverflow.com/questions/76847905/>.  */
/* Applies to: functions, pointer to functions, function type.  */

/* The function is rarely executed.  */
/* Applies to: functions.  */

/* If called from some other compilation unit, the function executes
   code from that unit only by return or by exception handling,
   letting the compiler optimize that unit more aggressively.  */
/* Applies to: functions.  */

/* For struct members: The member has the smallest possible alignment.
   For struct, union, class: All members have the smallest possible alignment,
   minimizing the memory required.  */
/* Applies to: struct members, struct, union,
   in C++ also: class.  */


/* ================ Attributes that make invalid code valid ================ */

/* Attributes that prevent fatal compiler optimizations for code that is not
   fully ISO C compliant.  */

/* Pointers to the type may point to the same storage as pointers to
   other types, thus disabling strict aliasing optimization.  */
/* Applies to: types.  */


/* ==================== Unnamed function parameters ======================== */

/* Although UNNAMED is not an attribute, it is related to MAYBE_UNUSED
   and so is defined here for convenience.  */

/* UNNAMED (ID) is the "name" of an unnamed function parameter.
   Each of the function's unnamed parameters should have a unique "name".
   The "name" cannot be used.  This ports both to C17 and earlier, which
   lack unnamed parameters, and to C++ and later C, which have them.  */
/* Applies to:
     - function parameters.  */




/* True stack allocation is not implemented by x86-cc yet.  Keep the
 * standard extension visible so uses become an explicit compiler/runtime
 * requirement instead of an accidental missing-header failure.
 */
void *alloca(size_t size);


int isalpha(int c);
int isdigit(int c);
int isalnum(int c);
int isspace(int c);
int isupper(int c);
int islower(int c);
int toupper(int c);
int tolower(int c);


/* Commonly used file permission combination.  */




/* Define PATH_MAX somehow.  Requires sys/types.h.
   Copyright (C) 1992, 1999, 2001, 2003, 2005, 2009-2026 Free Software
   Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* POSIX:2008 defines PATH_MAX to be the maximum number of bytes in a filename,
   including the terminating NUL byte.
   <https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/limits.h.html>
   PATH_MAX is not defined on systems which have no limit on filename length,
   such as GNU/Hurd.

   This file does *not* define PATH_MAX always.  Programs that use this file
   can handle the GNU/Hurd case in several ways:
     - Either with a package-wide handling, or with a per-file handling,
     - Either through a
         #ifdef PATH_MAX
       or through a fallback like
         #ifndef PATH_MAX
         #define PATH_MAX 8192
         #endif
       or through a fallback like
         #ifndef PATH_MAX
         #define PATH_MAX pathconf ("/", _PC_PATH_MAX)
         #endif
 */

/* This file uses HAVE_SYS_PARAM_H.  */




/* Don't include sys/param.h if it already has been.  */






struct timeval { long tv_sec; long tv_usec; };
int gettimeofday(struct timeval *tv, void *tz);

/* Since major is a function on SVR4, we can't use 'ifndef major'.  */



/* stdckdint.h -- checked integer arithmetic

   Copyright 2022-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

@PRAGMA_COLUMNS@

/* Copyright 2025-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2025.  */

typedef unsigned short char16_t;

/* Some systems don't define this; POSIX mentions it but says it is
   obsolete.  gnulib defines it, but only on native Windows systems,
   and there only because MSVC 10 does.  */

/* Return true if ERRNUM indicates that a file disappeared during a
   directory traversal.  */
static inline bool
ignorable_traversal_errno (int errnum) { return errnum == 2; }

extern char const *Version;

/* Exit statuses for programs like 'env' that exec other programs.  */
enum
{
  EXIT_TIMEDOUT = 124, /* Time expired before child completed.  */
  EXIT_CANCELED = 125, /* Internal error prior to exec attempt.  */
  EXIT_CANNOT_INVOKE = 126, /* Program located, but not usable.  */
  EXIT_ENOENT = 127 /* Could not find program to exec.  */
};

/* Failure exit status

   Copyright (C) 2002, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



extern int volatile exit_failure;



/* Set exit_failure to STATUS if that's not the default already.  */
static inline void
initialize_exit_failure (int status)
{
  if (status != 1)
    exit_failure = status;
}

int open(const char *path, int flags, ...);
enum { O_PATHSEARCH = 0 };

struct dirent { ino_t d_ino; unsigned char d_type; char d_name[49]; };
typedef struct __blackjack_DIR DIR;
DIR *opendir(const char *path);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

enum
{
  NOT_AN_INODE_NUMBER = 0
};

/* Some systems don't have inodes, so fake them to avoid lots of ifdefs.  */

/* include here for SIZE_MAX.  */

/* Redirection and wildcarding when done by the utility itself.
   Generally a noop, but used in particular for OS/2.  */

/* stat-related macros

   Copyright (C) 1993-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation, either version 3 of the License,
   or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* All the mode bits that can be affected by chmod.  */

/* timespec -- System time interface

   Copyright (C) 2000, 2002, 2004-2005, 2007, 2009-2026 Free Software
   Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* Convert a possibly-signed character to an unsigned character.  This is
   a bit safer than casting to unsigned char, since it catches some type
   errors that the cast doesn't.  */
static inline unsigned char to_uchar (char ch) { return ch; }

/* Return non zero if a non breaking space.  */

static inline int
c32isnbspace (char32_t wc)
{
  return wc == 0x00A0 || wc == 0x2007 || wc == 0x202F || wc == 0x2060;
}


static inline int
c32isvertspace (char32_t wc)
{
  return    wc == 0x000A || wc == 0x000B || wc == 0x000C || wc == 0x000D
         || wc == 0x2028 || wc == 0x2029;
}


/* c32isblank() is too variable on non GLIBC platforms.
   E.g., does not include \u3000 ideographic space on musl.
   E.g., does include non-breaking space on Solaris and NetBSD.
   This equivalent is more consistent across systems.  */

static inline bool
c32issep (char32_t wc)
{
  return c32isspace (wc) && ! c32isvertspace (wc) && ! c32isnbspace (wc);
}

/* Return true if the current charset is UTF-8.  */
static inline bool
is_utf8_charset (void)
{
  static int is_utf8 = -1;
  if (is_utf8 == -1)
    {
      char32_t w;
      mbstate_t mbs; mbszero (&mbs);
      is_utf8 = mbrtoc32 (&w, "\xe2\x9f\xb8", 3, &mbs) == 3 && w == 0x27F8;
    }
  return is_utf8;
}


/* Take care of NLS matters.  */

/* Convenience header for conditional use of GNU <libintl.h>.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



/* Return a value that pluralizes the same way that N does, in all
   languages we know of.  */
static inline unsigned long int
select_plural (uintmax_t n)
{
  /* Reduce by a power of ten, but keep it away from zero.  The
     gettext manual says 1000000 should be safe.  */
  enum { PLURAL_REDUCER = 1000000 };
  return (n <= ULONG_MAX ? n : n % PLURAL_REDUCER + PLURAL_REDUCER);
}


/* Just like strncmp, but the second argument must be a literal string
   and you don't specify the length;  that comes from the literal.  */






/* Interix has replacements for getgr{gid,nam,ent}, that don't
   query the domain controller for group members when not required.
   This speeds up the calls tremendously (<1 ms vs. >3 s). */
/* To protect any system that could provide _nomembers functions
   other than interix, check for HAVE_SETGROUPS, as interix is
   one of the very few (the only?) platform that lacks it */


/* A type for indices and sizes.
   Copyright (C) 2020-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */



/* IDX_MAX is the maximum value of an idx_t.  */

/* The type 'idx_t' holds an (array) index or an (object) size.
   Its implementation promotes to a signed integer type,
   which can hold the values
     0..2^63-1 (on 64-bit platforms) or
     0..2^31-1 (on 32-bit platforms).

   Why a signed integer type?

     * Security: Signed types can be checked for overflow via
       '-fsanitize=undefined', but unsigned types cannot.

     * Comparisons without surprises: ISO C99 § 6.3.1.8 specifies a few
       surprising results for comparisons, such as

           (int) -3 < (unsigned long) 7  =>  false
           (int) -3 < (unsigned int) 7   =>  false
       and on 32-bit machines:
           (long) -3 < (unsigned int) 7  =>  false

       This is surprising because the natural comparison order is by
       value in the realm of infinite-precision signed integers (ℤ).

       The best way to get rid of such surprises is to use signed types
       for numerical integer values, and use unsigned types only for
       bit masks and enums.

   Why not use 'size_t' directly?

     * Because 'size_t' is an unsigned type, and a signed type is better.
       See above.

   Why not use 'ssize_t'?

     * 'ptrdiff_t' is more portable; it is standardized by ISO C
       whereas 'ssize_t' is standardized only by POSIX.

     * 'ssize_t' is not required to be as wide as 'size_t', and some
       now-obsolete POSIX platforms had 'size_t' wider than 'ssize_t'.

     * Conversely, some now-obsolete platforms had 'ptrdiff_t' wider
       than 'size_t', which can be a win and conforms to POSIX.

   Won't this cause a problem with objects larger than PTRDIFF_MAX?

     * Typical modern or large platforms do not allocate such objects,
       so this is not much of a problem in practice; for example, you
       can safely write 'idx_t len = strlen (s);'.  To port to older
       small platforms where allocations larger than PTRDIFF_MAX could
       in theory be a problem, you can use Gnulib's ialloc module, or
       functions like ximalloc in Gnulib's xalloc module.

   Why not use 'ptrdiff_t' directly?

     * Maintainability: When reading and modifying code, it helps to know that
       a certain variable cannot have negative values.  For example, when you
       have a loop

         int n = ...;
         for (int i = 0; i < n; i++) ...

       or

         ptrdiff_t n = ...;
         for (ptrdiff_t i = 0; i < n; i++) ...

       you have to ask yourself "what if n < 0?".  Whereas in

         idx_t n = ...;
         for (idx_t i = 0; i < n; i++) ...

       you know that this case cannot happen.

       Similarly, when a programmer writes

         idx_t = ptr2 - ptr1;

       there is an implied assertion that ptr1 and ptr2 point into the same
       object and that ptr1 <= ptr2.

     * Being future-proof: In the future, range types (integers which are
       constrained to a certain range of values) may be added to C compilers
       or to the C standard.  Several programming languages (Ada, Haskell,
       Common Lisp, Pascal) already have range types.  Such range types may
       help producing good code and good warnings.  The type 'idx_t' could
       then be typedef'ed to a range type that is signed after promotion.  */



/* In the future, idx_t could be typedef'ed to a signed range type.
   The clang "extended integer types", supported in Clang 11 or newer
   <https://clang.llvm.org/docs/LanguageExtensions.html#extended-integer-types>,
   are a special case of range types.  However, these types don't support binary
   operators with plain integer types (e.g. expressions such as x > 1).
   Therefore, they don't behave like signed types (and not like unsigned types
   either).  So, we cannot use them here.  */

/* Use the signed type 'ptrdiff_t'.  */
/* Note: ISO C does not mandate that 'size_t' and 'ptrdiff_t' have the same
   size, but it is so on all platforms we have seen since 1990.  */
/* <stddef.h> already included above.  */
typedef ptrdiff_t idx_t;

/* So far no need has been found for an IDX_WIDTH macro.
   Perhaps there should be another macro IDX_VALUE_BITS that does not
   count the sign bit and is therefore one less than PTRDIFF_WIDTH.  */



/* xalloc.h -- malloc with out-of-memory checking

   Copyright (C) 1990-2000, 2003-2004, 2006-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_INLINE_HEADER_BEGIN, _GL_INLINE, _Noreturn,
   _GL_ATTRIBUTE_ALLOC_SIZE, _GL_ATTRIBUTE_MALLOC,
   _GL_ATTRIBUTE_RETURNS_NONNULL.  */



_GL_INLINE_HEADER_BEGIN











_GL_INLINE_HEADER_END

/* Compile-time assert-like macros.

   Copyright (C) 2005-2006, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert, Bruno Haible, and Jim Meyering.  */

/* Prefer faster, non-thread-safe stdio functions if available.

   Copyright (C) 2001-2004, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering.  */


/* These are wrappers for functions/macros from the GNU C library, and
   from other C libraries supporting POSIX's optional thread-safe functions.

   The standard I/O functions are thread-safe.  These *_unlocked ones are
   more efficient but not thread-safe.  That they're not thread-safe is
   fine since all of the applications in this package are single threaded.

   Also, some code that is shared with the GNU C library may invoke
   the *_unlocked functions directly.  On hosts that lack those
   functions, invoke the non-thread-safe versions instead.  */

/* This file uses HAVE_DECL_*_UNLOCKED.  */



















/* Determine whether two stat buffers are known to refer to the same file.

   Copyright (C) 2006, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_INLINE_HEADER_BEGIN, _GL_INLINE.  */


_GL_INLINE_HEADER_BEGIN



/* True if A and B point to structs with st_dev and st_ino members
   that are known to represent the same file.

   Use | and ^ to shorten generated code, and to lessen the
   probability of screwups if st_ino is an array.  */

  /* POSIX.  */

/* True if struct objects A and B are known to represent the same file.  */


/* True if *A and *B represent the same file.  Unlike PSAME_INODE,
   args are evaluated once and must point to struct stat,
   and this function works even on POSIX platforms where fstat etc. do
   not return useful st_dev and st_ino values for shared memory
   objects and typed memory objects.  */

static inline bool
psame_inode (struct stat const *a, struct stat const *b)
{
  return (! (S_TYPEISSHM (a) | S_TYPEISTMO (a)               | S_TYPEISSHM (b) | S_TYPEISTMO (b))            && (! (((a)->st_dev ^ (b)->st_dev)                                | ((a)->st_ino ^ (b)->st_ino))));
}



_GL_INLINE_HEADER_END


/* Take file names apart into directory and base names.

   Copyright (C) 1998, 2001, 2003-2006, 2009-2026 Free Software Foundation,
   Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_PURE,
   _GL_ATTRIBUTE_RETURNS_NONNULL.  */

/* Basic filename support macros.
   Copyright (C) 2001-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* From Paul Eggert and Jim Meyering.  */





/* Filename support.
   ISSLASH(C)                  tests whether C is a directory separator
                               character.
   HAS_DEVICE(Filename)        tests whether Filename contains a device
                               specification.
   FILE_SYSTEM_PREFIX_LEN(Filename)  length of the device specification
                                     at the beginning of Filename,
                                     index of the part consisting of
                                     alternating components and slashes.
   FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
                               1 when a non-empty device specification
                               can be followed by an empty or relative
                               part,
                               0 when a non-empty device specification
                               must be followed by a slash,
                               0 when device specification don't exist.
   IS_ABSOLUTE_FILE_NAME(Filename)
                               tests whether Filename is independent of
                               any notion of "current directory".
   IS_RELATIVE_FILE_NAME(Filename)
                               tests whether Filename may be concatenated
                               to a directory filename to yield the name
                               of a file relative to that directory.
                               Watch out: IS_RELATIVE_FILE_NAME ("") is 1
                               even though "" is not a relative file name.
   Note: On native Windows, OS/2, DOS, "c:" is neither an absolute nor a
   relative file name!
   IS_FILE_NAME_WITH_DIR(Filename)  tests whether Filename contains a device
                                    or directory specification.
 */
  /* Unix */

/* Deprecated macros.  For backward compatibility with old users of the
   'filename' module.  */



/* Extract the last component (base name) of a file name.

   Copyright (C) 1998, 2001, 2003-2006, 2009-2026 Free Software Foundation,
   Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* This file uses _GL_ATTRIBUTE_PURE.  */





/* Return the address of the last file name component of FILENAME.
   If FILENAME has some trailing slash(es), they are considered to be
   part of the last component.
   If FILENAME has no relative file name components because it is a file
   system root, return the empty string.
   Examples:
              FILENAME      RESULT
              "foo.c"       "foo.c"
              "foo/bar.c"   "bar.c"
              "/foo/bar.c"  "bar.c"
              "foo/bar/"    "bar/"
              "foo/bar//"   "bar//"
              "/"           ""
              "//"          ""
              ""            ""
   The return value is a tail of the given FILENAME; do NOT free() it!  */

/* This function was traditionally called 'basename', but we avoid this
   function name because
     * Various platforms have different functions in their libc.
       In particular, the glibc basename(), defined in <string.h>, does
       not consider trailing slashes to be part of the component:
              FILENAME      RESULT
              "foo/bar/"    ""
              "foo/bar//"   ""
     * The 'basename' command eliminates trailing slashes and for a root
       produces a non-empty result:
              FILENAME      RESULT
              "foo/bar/"    "bar"
              "foo/bar//"   "bar"
              "/"           "/"
              "//"          "/"
 */
extern char *last_component (char const *filename) ;

/* Return the length of the basename FILENAME.
   Typically FILENAME is the value returned by base_name or last_component.
   Act like strlen (FILENAME), except omit all trailing slashes.  */
extern size_t base_len (char const *filename) ;







char *mdir_name (char const *file)
   _GL_ATTRIBUTE_DEALLOC_FREE;
size_t dir_len (char const *file) ;

bool strip_trailing_slashes (char *file);


/* provide a replacement openat function
   Copyright (C) 2004-2006, 2008-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* written by Jim Meyering */


/* This file uses _GL_INLINE_HEADER_BEGIN, _GL_INLINE, _Noreturn,
   _GL_ATTRIBUTE_DEPRECATED, HAVE_OPENAT.  */



_GL_INLINE_HEADER_BEGIN






_Noreturn void openat_restore_fail (int);
_Noreturn void openat_save_fail (int);

/* Using these function names makes application code
   slightly more readable than it would be with
   fchownat (..., 0) or fchownat (..., AT_SYMLINK_NOFOLLOW).  */




/* For now, there are no wrappers named laccessat or leuidaccessat,
   since gnulib doesn't support faccessat(,AT_SYMLINK_NOFOLLOW) and
   since access rights on symlinks are of limited utility.  Likewise,
   wrappers are not provided for accessat or euidaccessat, so as to
   avoid dragging in -lgen on some platforms.  */



_GL_INLINE_HEADER_END


static inline bool
dot_or_dotdot (char const *file_name)
{
  if (file_name[0] == '.')
    {
      char sep = file_name[(file_name[1] == '.') + 1];
      return (! sep || ((sep) == '/'));
    }
  else
    return false;
}

/* A wrapper for readdir so that callers don't see entries for '.' or '..'.  */
static inline struct dirent const *
readdir_ignoring_dot_and_dotdot (DIR *dirp)
{
  while (true)
    {
      struct dirent const *dp = readdir (dirp);
      if (dp == 0 || ! dot_or_dotdot (dp->d_name))
        return dp;
    }
}

/* Return -1 if DIR is an empty directory,
   0 if DIR is a nonempty directory,
   and a positive error number if there was trouble determining
   whether DIR is an empty or nonempty directory.  */
enum {
    DS_UNKNOWN = -2,
    DS_EMPTY = -1,
    DS_NONEMPTY = 0,
};
static inline int
directory_status (int fd_cwd, char const *dir)
{
  DIR *dirp;
  bool no_direntries;
  int saved_errno;
  int fd = openat (fd_cwd, dir,                    (0 | O_DIRECTORY                     | O_NOCTTY | O_NOFOLLOW | O_NONBLOCK));

  if (fd < 0)
    return errno;

  dirp = fdopendir (fd);
  if (dirp == 0)
    {
      saved_errno = errno;
      close (fd);
      return saved_errno;
    }

  errno = 0;
  no_direntries = !readdir_ignoring_dot_and_dotdot (dirp);
  saved_errno = errno;
  closedir (dirp);
  return no_direntries && saved_errno == 0 ? DS_EMPTY : saved_errno;
}

/* Factor out some of the common --help and --version processing code.  */

/* These enum values cannot possibly conflict with the option values
   ordinarily used by commands, including CHAR_MAX + 1, etc.  Avoid
   CHAR_MIN - 1, as it may equal -1, the getopt end-of-options value.  */
enum
{
  GETOPT_HELP_CHAR = (CHAR_MIN - 2),
  GETOPT_VERSION_CHAR = (CHAR_MIN - 3)
};



/* Program_name must be a literal string.
   Usually it is just PROGRAM_NAME.  */


/* Close standard input, rewinding seekable stdin if necessary.

   Copyright (C) 2007, 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



void close_stdin_set_file_name (const char *file);
void close_stdin (void);


/* Close standard output and standard error.

   Copyright (C) 1998, 2000, 2003-2004, 2006, 2008-2026 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



void close_stdout_set_file_name (const char *file);
void close_stdout_set_ignore_EPIPE (bool ignore);
void close_stdout (void);



/* Print --version and bug-reporting information in a consistent format.
   Copyright (C) 1999, 2003, 2005, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering. */


/* This file uses _GL_ATTRIBUTE_SENTINEL.  */



extern const char version_etc_copyright[];

/* The three functions below display the --version information in the
   standard way: command and package names, package version, followed
   by a short GPLv3+ notice and a list of up to 10 author names.

   If COMMAND_NAME is NULL, the PACKAGE is assumed to be the name of
   the program.  The formats are therefore:

   PACKAGE VERSION

   or

   COMMAND_NAME (PACKAGE) VERSION.

   The functions differ in the way they are passed author names: */

/* N_AUTHORS names are supplied in array AUTHORS.  */
extern void version_etc_arn (FILE *stream,                               const char *command_name, const char *package,                               const char *version,                               const char * const * authors, size_t n_authors);

/* Names are passed in the NULL-terminated array AUTHORS.  */
extern void version_etc_ar (FILE *stream,                              const char *command_name, const char *package,                              const char *version, const char * const * authors);

/* Names are passed in the NULL-terminated va_list.  */
extern void version_etc_va (FILE *stream,                              const char *command_name, const char *package,                              const char *version, char * authors);

/* Names are passed as separate arguments, with an additional
   NULL argument at the end.  */
extern void version_etc (FILE *stream,                           const char *command_name, const char *package,                           const char *version,                           /* const char *author1, ..., NULL */ ...)
  _GL_ATTRIBUTE_SENTINEL ((0));

/* Display the usual "Report bugs to" stanza.  */
extern void emit_bug_reporting_address (void);



/* Localization of proper names.  -*- coding: utf-8 -*-
   Copyright (C) 2006, 2008-2026 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2006.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* INTRODUCTION

   What do

      Torbjörn Granlund    (coreutils)
      François Pinard      (coreutils)
      Danilo Šegan         (gettext)

   have in common?

   A non-ASCII name. This causes trouble in the --version output. The simple
   "solution" unfortunately mutilates the name.

     $ du --version | grep Granlund
     Écrit par Torbjorn Granlund, David MacKenzie, Paul Eggert et Jim Meyering.

     $ ptx --version | grep Pinard
     Écrit par F. Pinard.

   What is desirable, is to print the full name if the output character set
   allows it, and the ASCIIfied name only as a fallback.

     $ recode-sr-latin --version
     ...
     Written by Danilo Šegan and Bruno Haible.

     $ LC_ALL=C recode-sr-latin --version
     ...
     Written by Danilo Segan and Bruno Haible.

   The 'propername' and 'propername-lite' modules do this. Plus, for
   languages that do not use the Latin alphabet, they allow a translator
   to write the name using that different writing system. In that case the
   propername and propername_utf8 output will look like this:
      <translated name> (<original name in English>)
   whereas the propername_lite output will just be the translated name
   if available, otherwise the original name (in UTF-8 if possible and
   in ASCII if not).

   To use the 'propername' module requires two simple steps:

     1) Add it to the list of gnulib modules to import,

     2) Change the arguments of version_etc(),

          from "Paul Eggert"
          to   proper_name ("Paul Eggert")

          from "Torbjorn Granlund"
          to   proper_name_utf8 ("Torbjorn Granlund", "Torbj\303\266rn Granlund")
          or   proper_name_lite ("Torbjorn Granlund", "Torbj\303\266rn Granlund")

          from "F. Pinard"
          to   proper_name_utf8 ("Franc,ois Pinard", "Fran\303\247ois Pinard")
          or   proper_name_lite ("Franc,ois Pinard", "Fran\303\247ois Pinard")

        In source code, the second argument of proper_name_lite and
        proper_name_utf8 should use octal escapes, not UTF-8 - e.g.,
        "Fran\303\247ois Pinard", not "François Pinard".  Doing it
        this way can avoid mishandling non-ASCII characters if the
        source is recoded to non-UTF-8, or if the compiler does not
        treat UTF-8 as-is in character string contents.

        (Optionally, here you can also add / * TRANSLATORS: ... * / comments
        explaining how the name is written or pronounced.)

   Here is an example in context.

              char const *author_names[2] = {
                / * TRANSLATORS: This is the proper name "Danilo Šegan".
                    In the original Cyrillic it is "Данило Шеган".  * /
                proper_name_utf8 ("Danilo Segan", "Danilo \305\240egan"),
                proper_name ("Bruno Haible")
              };

   Differences between proper_name_utf8 and proper_name_lite:
   * proper_name_lite uses the localization provided by the translator.
     If there is no localization, it uses the name with Unicode characters
     only in UTF-8 locales, otherwise it uses the original name in English.
   * proper_name_utf8 is more elaborate:
     - It uses the name with Unicode characters also when the locale encoding
       is not UTF-8 but contains the necessary characters (e.g. ISO-8859-x or
       GB18030).
     - If there is a localization, it produces a better result when the
       translator has given a poor localization.
 */




/* Return the localization of NAME.  NAME is written in ASCII.  */
extern const char * proper_name_lite (const char *name, const char *name) /* NOT attribute const */;

/* Return the localization of a name whose original writing is not ASCII.
   NAME_UTF8 is the real name, written in UTF-8 with octal or hexadecimal
   escape sequences.  NAME_ASCII is a fallback written only with ASCII
   characters.  */
extern const char * proper_name_utf8 (const char *name_ascii,                                        const char *name_utf8);

/* Return the localization of the name spelled NAME_ASCII in ASCII,
   and NAME_UTF8 in UTF-8.  This function needs less infrastructure
   than proper_name and proper_name_utf8.  */
extern const char *proper_name_lite (const char *name_ascii,                                       const char *name_utf8);



/* Define away proper_name, since it's not worth the cost of adding ~17KB to
   the x86_64 text size of every single program.  This avoids a 40%
   (almost ~2MB) increase in the file system space utilization for the set
   of the 100 binaries. */

/* Program name management.
   Copyright (C) 2001-2004, 2006, 2009-2026 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2001.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* Programs using this file should do the following in main():
     set_program_name (argv[0]);
 */

/* A C macro for declaring that specific arguments must not be NULL.
   Copyright (C) 2009-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* _GL_ARG_NONNULL((n,...,m)) tells the compiler and static analyzer tools
   that the values passed as arguments n, ..., m must be non-NULL pointers.
   n = 1 stands for the first argument, n = 2 for the second argument etc.  */



/* String containing name the program is called with.  */
extern const char *program_name;

/* Set program_name, based on argv[0].
   argv0 must be a string allocated with indefinite extent, and must not be
   modified after this call.  */
extern void set_program_name (const char *argv0)
  ;







/* MIN, MAX macros.
   Copyright (C) 1995, 1998, 2001, 2003, 2005, 2009-2026 Free Software
   Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* Note: MIN, MAX are also defined in <sys/param.h> on some systems
   (glibc, HP-UX).  Therefore you might get warnings about MIN, MAX
   macro redefinitions on some systems; the workaround is to
   #include this file as the last one among the #include list.  */

/* This file uses HAVE_MINMAX_IN_LIMITS_H, HAVE_MINMAX_IN_SYS_PARAM_H.  */

/* Before we define the following symbols we get the <limits.h> file
   since otherwise we get redefinitions on some systems if <limits.h> is
   included after this file.  Likewise for <sys/param.h>.
   If more than one of these system headers define MIN and MAX, pick just
   one of the headers (because the definitions most likely are the same).  */

/* Note: MIN and MAX should be used with two arguments of the
   same type.  They might not return the minimum and maximum of their two
   arguments, if the arguments have different types or have unusual
   floating-point values.  For example, on a typical host with 32-bit 'int',
   64-bit 'long long', and 64-bit IEEE 754 'double' types:

     MAX (-1, 2147483648) returns 4294967295.
     MAX (9007199254740992.0, 9007199254740993) returns 9007199254740992.0.
     MAX (NaN, 0.0) returns 0.0.
     MAX (+0.0, -0.0) returns -0.0.

   and in each case the answer is in some sense bogus.  */

/* MAX(a,b) returns the maximum of A and B.  */

/* MIN(a,b) returns the minimum of A and B.  */

/* intprops.h -- properties of integer types

   Copyright (C) 2001-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


/* intprops-internal.h -- properties of integer types not visible to users

   Copyright (C) 2001-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */



/* Pacify GCC 13.2 in some calls to _GL_EXPR_SIGNED.  */

/* Nonzero if this compiler has GCC bug 68193 or Clang bug 25764.  See:
   https://gcc.gnu.org/PR68193
   https://github.com/llvm/llvm-project/issues/25764
   For now, assume GCC < 14 and all Clang versions generate bogus
   warnings for _Generic.  This matters only for compilers that
   lack relevant builtins.  */

/* Suppress -Wuseless-cast for, e.g., gcc-14 -std=gnu99.  */

/* Return a value with the common real type of E and V and the value of V.
   Do not evaluate E.  */

/* The extra casts in the following macros work around compiler bugs,
   e.g., in Cray C 5.0.3.0.  */

/* True if the standard integer or standard real type T is signed.  */
/* Pacify -Wuseless-cast, but do not default to the simpler expression;
   see <https://gcc.gnu.org/PR125261>.  */

/* Return 1 if the real expression E, after promotion, has a
   signed or floating type.  Do not evaluate E.  */


/* Minimum and maximum values for integer types and expressions.  */

/* The width in bits of the integer type or expression T.
   Do not evaluate T.  T must not be a bit-field expression.
   Padding bits are not supported; this is checked at compile-time below.  */

/* The maximum and minimum values for the type of the expression E,
   after integer promotion.  E is not evaluated.  */

/* Work around OpenVMS incompatibility with C99.  */

/* This include file assumes that signed types are two's complement without
   padding bits; the above macros have undefined behavior otherwise.
   If this is a problem for you, please let us know how to fix it for your host.
   This assumption is tested by the intprops-tests module.  */

/* Does the __typeof__ keyword work?  This could be done by
   'configure', but for now it's easier to do it by hand.  */

/* Return 1 if the integer type or expression T might be signed.  Return 0
   if it is definitely unsigned.  T must not be a bit-field expression.
   This macro does not evaluate its argument, and expands to an
   integer constant expression.  */

/* Return 1 if - A would overflow in [MIN,MAX] arithmetic.
   A should not have side effects, and A's type should be an
   integer with minimum value MIN and maximum MAX.  */

/* True if __builtin_add_overflow (A, B, P) and __builtin_sub_overflow
   (A, B, P) work when P is non-null.  */

/* True if __builtin_mul_overflow (A, B, P) works when P is non-null.  */

/* True if __builtin_add_overflow_p (A, B, C) works, and similarly for
   __builtin_sub_overflow_p and __builtin_mul_overflow_p.  */


/* Store the low-order bits of A + B, A - B, A * B, respectively, into *R.
   Return 1 if the result overflows.  Arguments should not have side
   effects and A, B and *R can be of any integer type other than char,
   bool, a bit-precise integer type, or an enumeration type.  */

/* Store the low-order bits of A <op> B into *R, where OP specifies
   the operation and OVERFLOW the overflow predicate.  Return 1 if the
   result overflows.  Arguments should not have side effects,
   and A, B and *R can be of any integer type other than char, bool, a
   bit-precise integer type, or an enumeration type.  */
/* Store the low-order bits of A <op> B into *R, where OP specifies
   the operation and OVERFLOW the overflow predicate.  If *R is
   signed, its type is ST with bounds SMIN..SMAX; otherwise its type
   is UT with bounds U..UMAX.  ST and UT are narrower than int.
   Return 1 if the result overflows.  Arguments should not have side
   effects, and A, B and *R can be of any integer type other than
   char, bool, a bit-precise integer type, or an enumeration type.  */


/* Store the low-order bits of A <op> B into *R, where the operation
   is given by OP.  Use the unsigned type UT for calculation to avoid
   overflow problems.  *R's type is T, with extrema TMIN and TMAX.
   T can be any signed integer type other than char, bool, a
   bit-precise integer type, or an enumeration type.
   Return 1 if the result overflows.  */

/* Return 1 if the integer expression -A would overflow.
   Arguments should not have side effects,
   and can be any signed integer type other than char, bool, a
   bit-precise integer type, or an enumeration type.
   These macros are tuned for their last input argument being a constant.  */


/* Return the low-order bits of A <op> B, where the operation is given
   by OP.  Use the unsigned type UT for calculation to avoid undefined
   behavior on signed integer overflow, and convert the result to type T.
   UT is at least as wide as T and is no narrower than unsigned int,
   T is two's complement, and there is no padding or trap representations.
   Assume that converting UT to T yields the low-order bits, as is
   done in all known two's-complement C compilers.  E.g., see:
   https://gcc.gnu.org/onlinedocs/gcc/Integers-implementation.html

   According to the C standard, converting UT to T yields an
   implementation-defined result or signal for values outside T's
   range.  However, code that works around this theoretical problem
   runs afoul of a compiler bug in Oracle Studio 12.3 x86.  See:
   https://lists.gnu.org/r/bug-gnulib/2017-04/msg00049.html
   As the compiler bug is real, don't try to work around the
   theoretical problem.  */


/* Return true if the numeric values A + B, A - B, A * B fall outside
   the range TMIN..TMAX.  Arguments should not have side effects
   and can be any integer type other than char, bool,
   a bit-precise integer type, or an enumeration type.
   TMIN should be signed and nonpositive.
   TMAX should be positive, and should be signed unless TMIN is zero.  */


/* The extra casts in the following macros work around compiler bugs,
   e.g., in Cray C 5.0.3.0.  */

/* True if the arithmetic type T is an integer type.  bool counts as
   an integer.  */
/* Pacify -Wuseless-cast and do not default to the simpler expression;
   see <https://gcc.gnu.org/PR125261>.  */

/* True if the standard integer or standard real type T is signed.  */

/* Return 1 if the real expression E, after promotion, has a
   signed or floating type.  Do not evaluate E.  */

/* The same value as as the arithmetic expression E, but with E's type
   after integer promotions.  For example, if E is of type 'enum {A, B}'
   then 'switch (INT_PROMOTE (E))' pacifies gcc -Wswitch-enum if some
   enum values are deliberately omitted from the switch's cases.
   Here, unary + is safer than a cast or inline function, as unary +
   does only integer promotions and is disallowed on pointers.  */


/* Minimum and maximum values for integer types and expressions.  */

/* The width in bits of the integer type or expression T.
   Do not evaluate T.  T must not be a bit-field expression.
   Padding bits are not supported; this is checked at compile-time below.  */

/* The maximum and minimum values for the standard integer type T.  */
/* Pacify -Wuseless-cast and do not default to the simpler expressions;
   see <https://gcc.gnu.org/PR125261>.  */

/* Bound on length of the string representing an unsigned integer
   value representable in B bits.  log10 (2.0) < 146/485.  The
   smallest value of B where this bound is not tight is 2621.  */

/* Bound on length of the string representing an integer type or expression T.
   T must not be a bit-field expression.

   Subtract 1 for the sign bit if T is signed, and then add 1 more for
   a minus sign if needed.

   Because _GL_SIGNED_TYPE_OR_EXPR sometimes returns 1 when its argument is
   unsigned, this macro may overestimate the true bound by one byte when
   applied to unsigned types of size 2, 4, 16, ... bytes.  */

/* Bound on buffer size needed to represent an integer type or expression T,
   including the terminating null.  T must not be a bit-field expression.  */


/* Range overflow checks.

   The INT_<op>_RANGE_OVERFLOW macros return 1 if the corresponding C
   operators overflow arithmetically when given the same arguments.
   These macros do not rely on undefined or implementation-defined behavior.
   Although their implementations are simple and straightforward,
   they are harder to use and may be less efficient than the
   INT_<op>_WRAPV, INT_<op>_OK, and INT_<op>_OVERFLOW macros described below.

   Example usage:

     long int i = ...;
     long int j = ...;
     if (INT_MULTIPLY_RANGE_OVERFLOW (i, j, LONG_MIN, LONG_MAX))
       printf ("multiply would overflow");
     else
       printf ("product is %ld", i * j);

   Restrictions on *_RANGE_OVERFLOW macros:

   These macros do not check for all possible numerical problems or
   undefined or unspecified behavior: they do not check for division
   by zero, for bad shift counts, or for shifting negative numbers.

   These macros may evaluate their arguments zero or multiple times,
   so the arguments should not have side effects.  The arithmetic
   arguments (including the MIN and MAX arguments) must be of the same
   integer type after the usual arithmetic conversions, and the type
   must have minimum value MIN and maximum MAX.  Unsigned types should
   use a zero MIN of the proper type.

   Because all arguments are subject to integer promotions, these
   macros typically do not work on types narrower than 'int'.

   These macros are tuned for constant MIN and MAX.  For commutative
   operations such as A + B, they are also tuned for constant B.  */

/* Return 1 if A + B would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  */

/* Return 1 if A - B would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  */

/* Return 1 if - A would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  */

/* Return 1 if A * B would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  Avoid && and || as they tickle
   bugs in Sun C 5.11 2010/08/13 and other compilers; see
   <https://lists.gnu.org/r/bug-gnulib/2011-05/msg00401.html>.  */

/* Return 1 if A / B would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  Do not check for division by zero.  */

/* Return 1 if A % B would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  Do not check for division by zero.
   Mathematically, % should never overflow, but on x86-like hosts
   INT_MIN % -1 traps, and the C standard permits this, so treat this
   as an overflow too.  */

/* Return 1 if A << B would overflow in [MIN,MAX] arithmetic.
   See above for restrictions.  Here, MIN and MAX are for A only, and B need
   not be of the same type as the other arguments.  The C standard says that
   behavior is undefined for shifts unless 0 <= B < wordwidth, and that when
   A is negative then A << B has undefined behavior and A >> B has
   implementation-defined behavior, but do not check these other
   restrictions.  */

/* The _GL*_OVERFLOW macros have the same restrictions as the
   *_RANGE_OVERFLOW macros, except that they do not assume that operands
   (e.g., A and B) have the same type as MIN and MAX.  Instead, they assume
   that the result (e.g., A + B) has that type.  */

/* Return a nonzero value if A is a mathematical multiple of B, where
   A is unsigned, B is negative, and MAX is the maximum value of A's
   type.  A's type must be the same as (A % B)'s type.  Normally (A %
   -B == 0) suffices, but things get tricky if -B would overflow.  */

/* Check for integer overflow, and report low order bits of answer.

   The INT_<op>_OVERFLOW macros return 1 if the corresponding C operators
   might not yield numerically correct answers due to arithmetic overflow.
   The INT_<op>_WRAPV macros compute the low-order bits of the sum,
   difference, and product of two C integers, and return 1 if these
   low-order bits are not numerically correct.
   These macros work correctly on all known practical hosts, and do not rely
   on undefined behavior due to signed arithmetic overflow.

   Example usage, assuming A and B are long int:

     if (INT_MULTIPLY_OVERFLOW (a, b))
       printf ("result would overflow\n");
     else
       printf ("result is %ld (no overflow)\n", a * b);

   Example usage with WRAPV flavor:

     long int result;
     bool overflow = INT_MULTIPLY_WRAPV (a, b, &result);
     printf ("result is %ld (%s)\n", result,
             overflow ? "after overflow" : "no overflow");

   Restrictions on these macros:

   These macros do not check for all possible numerical problems or
   undefined or unspecified behavior: they do not check for division
   by zero, for bad shift counts, or for shifting negative numbers.

   These macros may evaluate their arguments zero or multiple times, so the
   arguments should not have side effects.

   The WRAPV macros are not constant expressions.  They support only
   +, binary -, and *.

   Because the WRAPV macros convert the result, they report overflow
   in different circumstances than the OVERFLOW macros do.  For
   example, in the typical case with 16-bit 'short' and 32-bit 'int',
   if A, B and *R are all of type 'short' then INT_ADD_OVERFLOW (A, B)
   returns false because the addition cannot overflow after A and B
   are converted to 'int', whereas INT_ADD_WRAPV (A, B, R) returns
   true or false depending on whether the sum fits into 'short'.

   These macros are tuned for their last input argument being a constant.

   A, B, and *R should be integers; they need not be the same type,
   and they need not be all signed or all unsigned.
   However, none of the integer types should be bit-precise,
   and *R's type should not be char, bool, or an enumeration type.

   Return 1 if the integer expressions A * B, A - B, -A, A * B, A / B,
   A % B, and A << B would overflow, respectively.  */


/* Return 1 if the expression A <op> B would overflow,
   where OP_RESULT_OVERFLOW (A, B, MIN, MAX) does the actual test,
   assuming MIN and MAX are the minimum and maximum for the result type.
   Arguments should be free of side effects.  */

/* Store the low-order bits of A + B, A - B, A * B, respectively, into *R.
   Return 1 if the result overflows.  See above for restrictions.  */

/* The following macros compute A + B, A - B, and A * B, respectively.
   If no overflow occurs, they set *R to the result and return 1;
   otherwise, they return 0 and may modify *R.

   Example usage:

     long int result;
     if (INT_ADD_OK (a, b, &result))
       printf ("result is %ld\n", result);
     else
       printf ("overflow\n");

   A, B, and *R should be integers; they need not be the same type,
   and they need not be all signed or all unsigned.
   However, none of the integer types should be bit-precise,
   and *R's type should not be char, bool, or an enumeration type.

   These macros work correctly on all known practical hosts, and do not rely
   on undefined behavior due to signed arithmetic overflow.

   These macros are not constant expressions.

   These macros may evaluate their arguments zero or multiple times, so the
   arguments should not have side effects.

   These macros are tuned for B being a constant.  */









/* Use this to suppress gcc warnings.  */

/* main_exit should be called only from the main function.  It is
   equivalent to 'exit'.  When checking for lint it calls 'exit', to
   pacify gcc -fsanitize=lint which would otherwise have false alarms
   for pointers in the main function's activation record.  Otherwise
   it simply returns from 'main'; this used to be what gcc's static
   checking preferred and may yet be again.  */





/* Compute the greatest common divisor of U and V using Euclid's
   algorithm.  U and V must be nonzero.  */

_GL_ATTRIBUTE_CONST
static inline size_t
gcd (size_t u, size_t v)
{
  do
    {
      size_t t = u % v;
      u = v;
      v = t;
    }
  while (v);

  return u;
}

/* Compute the least common multiple of U and V.  U and V must be
   nonzero.  There is no overflow checking, so callers should not
   specify outlandish sizes.  */

_GL_ATTRIBUTE_CONST
static inline size_t
lcm (size_t u, size_t v)
{
  return u * (v / gcd (u, v));
}

/* Return PTR, aligned upward to the next multiple of ALIGNMENT.
   ALIGNMENT must be nonzero.  The caller must arrange for ((char *)
   PTR) through ((char *) PTR + ALIGNMENT - 1) to be addressable
   locations.  */

static inline void *
ptr_align (void const *ptr, size_t alignment)
{
  char const *p0 = ptr;
  char const *p1 = p0 + alignment - 1;
  return (void *) (p1 - (size_t) p1 % alignment);
}

/* Return whether the buffer consists entirely of NULs.
   Based on memeqzero in CCAN by Rusty Russell under CC0 (Public domain).  */


static inline bool
is_nul (void const *buf, size_t length)
{
  const unsigned char *p = buf;
/* Using possibly unaligned access for the first 16 bytes
   saves about 30-40 cycles, though it is strictly undefined behavior
   and so would need __attribute__ ((__no_sanitize_undefined__))
   to avoid -fsanitize=undefined warnings.
   Considering coreutils is mainly concerned with relatively
   large buffers, we'll just use the defined behavior.  */
  unsigned char word;

  if (! length)
    return true;

  /* Check len bytes not aligned on a word.  */
  while ((length & (sizeof word - 1)))
    {
      if (*p)
        return false;
      p++;
      length--;
      if (! length)
        return true;
   }

  /* Check up to 16 bytes a word at a time.  */
  for (;;)
    {
      memcpy (&word, p, sizeof word);
      if (word)
        return false;
      p += sizeof word;
      length -= sizeof word;
      if (! length)
        return true;
      if ((length & 15) == 0)
        break;
   }

  /* Now we know first 16 bytes are NUL, memeq with self.  */
  return memeq (buf, p, length);
}

/* Set Accum = 10*Accum + Digit_val and return true, where Accum is an
   integer object and Digit_val an integer expression.  However, if
   the result overflows, set Accum to an unspecified value and return
   false.  Accum and Digit_val may be evaluated multiple times.  */



/* Output --option descriptions;
   formatted with ANSI format and hyperlink codes.
   Any postprocessors like help2man etc. are expected to handle this,
   though it can be disabled in edge cases with the TERM=dumb env var.  */

static inline void
oputs_ (_GL_ATTRIBUTE_MAYBE_UNUSED char const *program, char const *option)
{
  static int help_no_sgr =
    -1;  /* Lookup.  */
  if (help_no_sgr == -1)
    {
      /* Note we don't consult isatty() since usually you
         would want markup when piping to grep/less etc.  */
      char const *term = getenv ("TERM");
      help_no_sgr = (!term || !*term || streq (term, "dumb"));
    }
  if (help_no_sgr)
    {
      fputs (option, stdout);
      return;
    }

  bool double_space = true;
  char const *first_word = option + strspn (option, " \t\n");
  char const *option_text = strchr (option, '-');
  if (!option_text)                    /* for dd(1) option syntax.  */
    {
      option_text = first_word;
      /* Just match first word to support single spaced
         translated dd "foo=bar description" format.  */
      double_space = false;
    }
  else if (option_text != first_word)  /* for test(1) option syntax.  */
    {
      /* Ensure only a single space encountered before '-', to avoid
         matching within descriptions for translated dd option syntax.  */
      char const *s = first_word;
      size_t spaces = 0;
      while (s < option_text && spaces < 2)
        spaces += !!isspace (*s++);
      if (spaces == 2)
        {
          /* Probably mismatched dd format.  */
          option_text = first_word;
          double_space = false;
        }
    }

  size_t anchor_len = strcspn (option_text, ",=[ \n");

  /* Set highlighted text up to spacing after the full option text.
     Any single space is included in highlighted text,
     double space or TAB or newline terminates the option text.  */
  char const *desc_text = option_text + anchor_len;
  while (*desc_text && *desc_text != '\n')
    {
      if (*desc_text == '-' && *(desc_text + 1) == '-')
        double_space = false;
      if (isspace (*desc_text))
        {
          if (*desc_text == '\t' || isspace (*(desc_text + 1)))
            break;
          /* With long options we restrict the match as some translations
             delimit a long option and description with a single space.  */
          if (!double_space && *(desc_text + 1) != '-')
            break;
        }

      desc_text++;
    }

  /* write spaces before option text. */
  fwrite (option, 1, first_word - option, stdout);

  /* write option text.  */
  /* first_word != option_text for test(1).  */
  fwrite (first_word, 1, desc_text - first_word, stdout);

  /* write description.  */
  fputs (desc_text, stdout);
}

/* If required and possible,
   call oputs with printf formatted message.  */

_GL_ATTRIBUTE_FORMAT ((printf, 2, 3))
static inline void
oprintf_ (char const *program, char const *message, ...)
{
  char * args;
  char *buf;
  int buflen = -1;


  if (buflen < 0)
    {
      vprintf (message, args);
      return;
    }

  oputs_ (program, buf);
  free (buf);
}

static inline void
emit_stdin_note (void)
{
  fputs ((const char *) {("\nWith no FILE, or when FILE is -, read standard input.\n")}, stdout);
}
static inline void
emit_mandatory_arg_note (void)
{
  fputs ((const char *) {("\nMandatory arguments to long options are mandatory for short options too.\n")}, stdout);
}

static inline void
emit_size_note (void)
{
  fputs ((const char *) {("\nThe SIZE argument is an integer and optional unit (example: 10K is 10*1024).\nUnits are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\nBinary prefixes can be used, too: KiB=K, MiB=M, and so on.\n")}, stdout);
}

static inline void
emit_blocksize_note (char const *program)
{
  printf ((const char *) {("\nDisplay values are in units of the first available SIZE from --block-size,\nand the %s_BLOCK_SIZE, BLOCK_SIZE and BLOCKSIZE environment variables.\nOtherwise, units default to 1024 bytes (or 512 if POSIXLY_CORRECT is set).\n")}, program);
}

static inline void
emit_update_parameters_note (void)
{
  fputs ((const char *) {("\nUPDATE controls which existing files in the destination are replaced.\n'all' is the default operation when an --update option is not specified,\nand results in all existing files in the destination being replaced.\n'none' is like the --no-clobber option, in that no files in the\ndestination are replaced, and skipped files do not induce a failure.\n'none-fail' also ensures no files are replaced in the destination,\nbut any skipped files are diagnosed and induce a failure.\n'older' is the default operation when --update is specified, and results\nin files being replaced if they're older than the corresponding source file.\n")}, stdout);
}

static inline void
emit_backup_suffix_note (void)
{
  fputs ((const char *) {("\nThe backup suffix is '~', unless set with --suffix or SIMPLE_BACKUP_SUFFIX.\nThe version control method may be selected via the --backup option or through\nthe VERSION_CONTROL environment variable.  Here are the values:\n\n")}, stdout);
  fputs ((const char *) {("  none, off       never make backups (even if --backup is given)\n  numbered, t     make numbered backups\n  existing, nil   numbered if numbered backups exist, simple otherwise\n  simple, never   always make simple backups\n")}, stdout);
}

static inline void
emit_symlink_recurse_options_ (char const *program, char const *default_opt)
{
      printf ((const char *) {("\nThe following options modify how a hierarchy is traversed when the -R\noption is also specified.  If more than one is specified, only the final\none takes effect. %s is the default.\n\n")}, default_opt);
      oputs_ (program, (const char *) {("  -H\n         if a command line argument is a symlink to a directory, traverse it\n")});
      oputs_ (program, (const char *) {("  -L\n         traverse every symbolic link to a directory encountered\n")});
      oputs_ (program, (const char *) {("  -P\n         do not traverse any symbolic links\n\n")});
}

static inline void
emit_exec_status (char const *program)
{
      printf ((const char *) {("\nExit status:\n  125  if the %s command itself fails\n  126  if COMMAND is found but cannot be invoked\n  127  if COMMAND cannot be found\n  -    the exit status of COMMAND otherwise\n")}, program);
}

static inline void
emit_ancillary_info (char const *program)
{
  struct infomap { char const *program; char const *node; } const infomap[] = {
    { "[", "test invocation" },
    { "coreutils", "Multi-call invocation" },
    { "sha224sum", "sha2 utilities" },
    { "sha256sum", "sha2 utilities" },
    { "sha384sum", "sha2 utilities" },
    { "sha512sum", "sha2 utilities" },
    { 0, 0 }
  };

  char const *node = program;
  struct infomap const *map_prog = infomap;

  while (map_prog->program && ! streq (program, map_prog->program))
    map_prog++;

  if (map_prog->node)
    node = map_prog->node;

  emit_bug_reporting_address ();

  /* .htaccess on the coreutils web site maps programs to the appropriate page,
     however we explicitly handle "[" -> "test" here as the "[" is not
     recognized as part of a URL by default in terminals.  */
  char const *url_program = streq (program, "[") ? "test" : program;
  printf ((const char *) {("Full documentation <%s%s>\n")},           PACKAGE_URL, url_program);
  printf ((const char *) {("or available locally via: info '(coreutils) %s%s'\n")},           node, node == program ? " invocation" : "");
}

/* Use a macro rather than an inline function, as this references
   the global program_name, which causes dynamic linking issues
   in libstdbuf.so on some systems where unused functions
   are not removed by the linker.  */

/* inttostr.h -- convert integers to printable strings

   Copyright (C) 2001-2006, 2009-2026 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert */

/* This file uses _GL_ATTRIBUTE_NODISCARD.  */


/* intprops.h -- properties of integer types

   Copyright (C) 2001-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */




 char *imaxtostr (intmax_t, char *);
 char *inttostr (int, char *);
 char *offtostr (off_t, char *);
 char *uinttostr (unsigned int, char *);
 char *umaxtostr (uintmax_t, char *);



static inline char *
timetostr (time_t t, char *buf)
{
  return ((_Generic ((time_t) {0},               bool: 0, char: CHAR_MIN < 0, signed char: 1, unsigned char: 0,               short int: 1, unsigned short int: 0, int: 1, unsigned int: 0,               long int: 1, unsigned long int: 0, long long int: 1, unsigned long long int: 0,               float: 1, double: 1, long double: 1))           ? imaxtostr (t, buf)           : umaxtostr (t, buf));
}

static inline char *
bad_cast (char const *s)
{
  return (char *) s;
}

/* Return a boolean indicating whether SB->st_size is defined.  */
static inline bool
usable_st_size (struct stat const *sb)
{
  return ((((sb->st_mode) & 0170000) == 0100000) || S_ISLNK (sb->st_mode)           || S_TYPEISSHM (sb) || S_TYPEISTMO (sb));
}

_Noreturn void usage (int status);


extern unsigned int error_message_count;
extern int error_one_per_line;
void error(int status, int errnum, const char *format, ...);
void error_at_line(int status, int errnum, const char *filename,                    unsigned int linenum, const char *format, ...);


/* Like error(0, 0, ...), but without an implicit newline.
   Also a noop unless the global DEV_DEBUG is set.  */


/* exit with a _single_ "write error" diagnostic.  */

static inline void
write_error (void)
{
  int saved_errno = errno;
  fflush (stdout);    /* Last attempt to write any buffered data.  */
  fpurge (stdout);    /* Ensure nothing buffered that might induce an error. */
  clearerr (stdout);  /* Avoid extraneous diagnostic from close_stdout.  */
  error (1, saved_errno, (const char *) {("write error")});
}

/* Like stpncpy, but do ensure that the result is NUL-terminated,
   and do not NUL-pad out to LEN.  I.e., when strnlen (src, len) == len,
   this function writes a NUL byte into dest[len].  Thus, the length
   of the destination buffer must be at least LEN + 1.
   The DEST and SRC buffers must not overlap.  */
static inline char *
stzncpy (char *restrict dest, char const *restrict src, size_t len)
{
  for (size_t i = 0; i < len && *src; i++)
    *dest++ = *src++;
  *dest = 0;
  return dest;
}

/* Return true if ERR is ENOTSUP or EOPNOTSUPP, otherwise false.
   This wrapper function avoids the redundant 'or'd comparison on
   systems like Linux for which they have the same value.  It also
   avoids the gcc warning to that effect.  */
static inline bool
is_ENOTSUP (int err)
{
  return err == EOPNOTSUPP || (95 != EOPNOTSUPP && err == 95);
}


/* How coreutils quotes filenames, to minimize use of outer quotes,
   but also provide better support for copy and paste when used.  */
/* quotearg.h - quote arguments for output

   Copyright (C) 1998-2002, 2004, 2006, 2008-2026 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Paul Eggert <eggert@twinsun.com> */


/* This file uses _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_RETURNS_NONNULL.  */




/* Basic quoting styles.  For each style, an example is given on the
   input strings "simple", "\0 \t\n'\"\033?""?/\\", and "a:b", using
   quotearg_buffer, quotearg_mem, and quotearg_colon_mem with that
   style and the default flags and quoted characters.  Note that the
   examples are shown here as valid C strings rather than what
   displays on a terminal (with "??/" as a trigraph for "\\").  */
enum quoting_style
  {
    /* Output names as-is (ls --quoting-style=literal).  Can result in
       embedded null bytes if QA_ELIDE_NULL_BYTES is not in
       effect.

       quotearg_buffer:
       "simple", "\0 \t\n'\"\033??/\\", "a:b"
       quotearg:
       "simple", " \t\n'\"\033??/\\", "a:b"
       quotearg_colon:
       "simple", " \t\n'\"\033??/\\", "a:b"
    */
    literal_quoting_style,

    /* Quote names for the shell if they contain shell metacharacters
       or would cause ambiguous output (ls --quoting-style=shell).
       Can result in embedded null bytes if QA_ELIDE_NULL_BYTES is not
       in effect.

       quotearg_buffer:
       "simple", "'\0 \t\n'\\''\"\033??/\\'", "a:b"
       quotearg:
       "simple", "' \t\n'\\''\"\033??/\\'", "a:b"
       quotearg_colon:
       "simple", "' \t\n'\\''\"\033??/\\'", "'a:b'"
    */
    shell_quoting_style,

    /* Quote names for the shell, even if they would normally not
       require quoting (ls --quoting-style=shell-always).  Can result
       in embedded null bytes if QA_ELIDE_NULL_BYTES is not in effect.
       Behaves like shell_quoting_style if QA_ELIDE_OUTER_QUOTES is in
       effect.

       quotearg_buffer:
       "'simple'", "'\0 \t\n'\\''\"\033??/\\'", "'a:b'"
       quotearg:
       "'simple'", "' \t\n'\\''\"\033??/\\'", "'a:b'"
       quotearg_colon:
       "'simple'", "' \t\n'\\''\"\033??/\\'", "'a:b'"
    */
    shell_always_quoting_style,

    /* Quote names for the shell if they contain shell metacharacters
       or other problematic characters (ls --quoting-style=shell-escape).
       Non printable characters are quoted using the $'...' syntax
       <https://www.gnu.org/software/bash/manual/html_node/ANSI_002dC-Quoting.html>,
       which originated in ksh93 and is widely supported by most shells,
       and proposed for inclusion in POSIX.

       quotearg_buffer:
       "simple", "''$'\\0'' '$'\\t\\n'\\''\"'$'\\033''??/\\'", "a:b"
       quotearg:
       "simple", "''$'\\0'' '$'\\t\\n'\\''\"'$'\\033''??/\\'", "a:b"
       quotearg_colon:
       "simple", "''$'\\0'' '$'\\t\\n'\\''\"'$'\\033''??/\\'", "'a:b'"
    */
    shell_escape_quoting_style,

    /* Quote names for the shell even if they would normally not
       require quoting (ls --quoting-style=shell-escape).
       Non printable characters are quoted using the $'...' syntax
       <https://www.gnu.org/software/bash/manual/html_node/ANSI_002dC-Quoting.html>,
       which originated in ksh93 and is widely supported by most shells,
       and proposed for inclusion in POSIX.  Behaves like
       shell_escape_quoting_style if QA_ELIDE_OUTER_QUOTES is in effect.

       quotearg_buffer:
       "simple", "''$'\\0'' '$'\\t\\n'\\''\"'$'\\033''??/\'", "a:b"
       quotearg:
       "simple", "''$'\\0'' '$'\\t\\n'\\''\"'$'\\033''??/\'", "a:b"
       quotearg_colon:
       "simple", "''$'\\0'' '$'\\t\\n'\\''\"'$'\\033''??/\'", "'a:b'"
    */
    shell_escape_always_quoting_style,

    /* Quote names as for a C language string (ls --quoting-style=c).
       Behaves like c_maybe_quoting_style if QA_ELIDE_OUTER_QUOTES is
       in effect.  Split into consecutive strings if
       QA_SPLIT_TRIGRAPHS.

       quotearg_buffer:
       "\"simple\"", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a:b\""
       quotearg:
       "\"simple\"", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a:b\""
       quotearg_colon:
       "\"simple\"", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a\\:b\""
    */
    c_quoting_style,

    /* Like c_quoting_style except omit the surrounding double-quote
       characters if no quoted characters are encountered.

       quotearg_buffer:
       "simple", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "a:b"
       quotearg:
       "simple", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "a:b"
       quotearg_colon:
       "simple", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a:b\""
    */
    c_maybe_quoting_style,

    /* Like c_quoting_style except always omit the surrounding
       double-quote characters and ignore QA_SPLIT_TRIGRAPHS
       (ls --quoting-style=escape).

       quotearg_buffer:
       "simple", "\\0 \\t\\n'\"\\033??/\\\\", "a:b"
       quotearg:
       "simple", "\\0 \\t\\n'\"\\033??/\\\\", "a:b"
       quotearg_colon:
       "simple", "\\0 \\t\\n'\"\\033??/\\\\", "a\\:b"
    */
    escape_quoting_style,

    /* Like clocale_quoting_style, but use single quotes in the
       default C locale or if the program does not use gettext
       (ls --quoting-style=locale).  For UTF-8 locales, quote
       characters will use Unicode.

       LC_MESSAGES=C
       quotearg_buffer:
       "'simple'", "'\\0 \\t\\n\\'\"\\033??/\\\\'", "'a:b'"
       quotearg:
       "'simple'", "'\\0 \\t\\n\\'\"\\033??/\\\\'", "'a:b'"
       quotearg_colon:
       "'simple'", "'\\0 \\t\\n\\'\"\\033??/\\\\'", "'a\\:b'"

       LC_MESSAGES=pt_PT.utf8
       quotearg_buffer:
       "\302\253simple\302\273",
       "\302\253\\0 \\t\\n'\"\\033??/\\\\\302\253", "\302\253a:b\302\273"
       quotearg:
       "\302\253simple\302\273",
       "\302\253\\0 \\t\\n'\"\\033??/\\\\\302\253", "\302\253a:b\302\273"
       quotearg_colon:
       "\302\253simple\302\273",
       "\302\253\\0 \\t\\n'\"\\033??/\\\\\302\253", "\302\253a\\:b\302\273"
    */
    locale_quoting_style,

    /* Like c_quoting_style except use quotation marks appropriate for
       the locale and ignore QA_SPLIT_TRIGRAPHS
       (ls --quoting-style=clocale).

       LC_MESSAGES=C
       quotearg_buffer:
       "\"simple\"", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a:b\""
       quotearg:
       "\"simple\"", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a:b\""
       quotearg_colon:
       "\"simple\"", "\"\\0 \\t\\n'\\\"\\033??/\\\\\"", "\"a\\:b\""

       LC_MESSAGES=pt_PT.utf8
       quotearg_buffer:
       "\302\253simple\302\273",
       "\302\253\\0 \\t\\n'\"\\033??/\\\\\302\253", "\302\253a:b\302\273"
       quotearg:
       "\302\253simple\302\273",
       "\302\253\\0 \\t\\n'\"\\033??/\\\\\302\253", "\302\253a:b\302\273"
       quotearg_colon:
       "\302\253simple\302\273",
       "\302\253\\0 \\t\\n'\"\\033??/\\\\\302\253", "\302\253a\\:b\302\273"
    */
    clocale_quoting_style,

    /* Like clocale_quoting_style except use the custom quotation marks
       set by set_custom_quoting.  If custom quotation marks are not
       set, the behavior is undefined.

       left_quote = right_quote = "'"
       quotearg_buffer:
       "'simple'", "'\\0 \\t\\n\\'\"\\033??/\\\\'", "'a:b'"
       quotearg:
       "'simple'", "'\\0 \\t\\n\\'\"\\033??/\\\\'", "'a:b'"
       quotearg_colon:
       "'simple'", "'\\0 \\t\\n\\'\"\\033??/\\\\'", "'a\\:b'"

       left_quote = "(" and right_quote = ")"
       quotearg_buffer:
       "(simple)", "(\\0 \\t\\n'\"\\033??/\\\\)", "(a:b)"
       quotearg:
       "(simple)", "(\\0 \\t\\n'\"\\033??/\\\\)", "(a:b)"
       quotearg_colon:
       "(simple)", "(\\0 \\t\\n'\"\\033??/\\\\)", "(a\\:b)"

       left_quote = ":" and right_quote = " "
       quotearg_buffer:
       ":simple ", ":\\0\\ \\t\\n'\"\\033??/\\\\ ", ":a:b "
       quotearg:
       ":simple ", ":\\0\\ \\t\\n'\"\\033??/\\\\ ", ":a:b "
       quotearg_colon:
       ":simple ", ":\\0\\ \\t\\n'\"\\033??/\\\\ ", ":a\\:b "

       left_quote = "\"'" and right_quote = "'\""
       Notice that this is treated as a single level of quotes or two
       levels where the outer quote need not be escaped within the inner
       quotes.  For two levels where the outer quote must be escaped
       within the inner quotes, you must use separate quotearg
       invocations.
       quotearg_buffer:
       "\"'simple'\"", "\"'\\0 \\t\\n\\'\"\\033??/\\\\'\"", "\"'a:b'\""
       quotearg:
       "\"'simple'\"", "\"'\\0 \\t\\n\\'\"\\033??/\\\\'\"", "\"'a:b'\""
       quotearg_colon:
       "\"'simple'\"", "\"'\\0 \\t\\n\\'\"\\033??/\\\\'\"", "\"'a\\:b'\""
    */
    custom_quoting_style
  };

/* Flags for use in set_quoting_flags.  */
enum quoting_flags
  {
    /* Always elide null bytes from styles that do not quote them,
       even when the length of the result is available to the
       caller.  */
    QA_ELIDE_NULL_BYTES = 0x01,

    /* Omit the surrounding quote characters if no escaped characters
       are encountered.  Note that if no other character needs
       escaping, then neither does the escape character.
       *Attention!*  This flag is unsupported in combination with the styles
       shell_escape_quoting_style and shell_escape_always_quoting_style
       (because in this situation it cannot handle strings that start
       with a non-printable character).  */
    QA_ELIDE_OUTER_QUOTES = 0x02,

    /* In the c_quoting_style and c_maybe_quoting_style, split ANSI
       trigraph sequences into concatenated strings (for example,
       "?""?/" rather than "??/", which could be confused with
       "\\").  */
    QA_SPLIT_TRIGRAPHS = 0x04
  };

/* For now, --quoting-style=literal is the default, but this may change.  */

/* Names of quoting styles and their corresponding values.  */
extern char const *const quoting_style_args[];
extern enum quoting_style const quoting_style_vals[];

struct quoting_options;

/* The functions listed below set and use a hidden variable
   that contains the default quoting style options.  */

/* Allocate a new set of quoting options, with contents initially identical
   to O if O is not null, or to the default if O is null.
   It is the caller's responsibility to free the result.  */
struct quoting_options *clone_quoting_options (struct quoting_options *o)
   _GL_ATTRIBUTE_DEALLOC_FREE
  ;

/* Get the value of O's quoting style.  If O is null, use the default.  */
enum quoting_style get_quoting_style (struct quoting_options const *o);

/* In O (or in the default if O is null),
   set the value of the quoting style to S.  */
void set_quoting_style (struct quoting_options *o, enum quoting_style s);

/* In O (or in the default if O is null),
   set the value of the quoting options for character C to I.
   Return the old value.  Currently, the only values defined for I are
   0 (the default) and 1 (which means to quote the character even if
   it would not otherwise be quoted).  C must never be a digit or a
   letter that has special meaning after a backslash (for example, "\t"
   for tab).  */
int set_char_quoting (struct quoting_options *o, char c, int i);

/* In O (or in the default if O is null),
   set the value of the quoting options flag to I, which can be a
   bitwise combination of enum quoting_flags, or 0 for default
   behavior.  Return the old value.  */
int set_quoting_flags (struct quoting_options *o, int i);

/* In O (or in the default if O is null),
   set the value of the quoting style to custom_quoting_style,
   set the left quote to LEFT_QUOTE, and set the right quote to
   RIGHT_QUOTE.  Each of LEFT_QUOTE and RIGHT_QUOTE must be
   null-terminated and can be the empty string.  Because backslashes are
   used for escaping, it does not make sense for RIGHT_QUOTE to contain
   a backslash.  RIGHT_QUOTE must not begin with a digit or a letter
   that has special meaning after a backslash (for example, "\t" for
   tab).  */
void set_custom_quoting (struct quoting_options *o,                           char const *left_quote,                           char const *right_quote);

/* Place into buffer BUFFER (of size BUFFERSIZE) a quoted version of
   argument ARG (of size ARGSIZE), using O to control quoting.
   If O is null, use the default.
   Terminate the output with a null character, and return the written
   size of the output, not counting the terminating null.
   If BUFFERSIZE is too small to store the output string, return the
   value that would have been returned had BUFFERSIZE been large enough.
   If ARGSIZE is -1, use the string length of the argument for ARGSIZE.
   On output, BUFFER might contain embedded null bytes if ARGSIZE was
   not -1, the style of O does not use backslash escapes, and the
   flags of O do not request elision of null bytes.*/
size_t quotearg_buffer (char *restrict buffer, size_t buffersize,                          char const *arg, size_t argsize,                          struct quoting_options const *o);

/* Like quotearg_buffer, except return the result in a newly allocated
   buffer.  It is the caller's responsibility to free the result.  The
   result will not contain embedded null bytes.  */
char *quotearg_alloc (char const *arg, size_t argsize,                        struct quoting_options const *o)
   _GL_ATTRIBUTE_DEALLOC_FREE
  ;

/* Like quotearg_alloc, except that the length of the result,
   excluding the terminating null byte, is stored into SIZE if it is
   non-NULL.  The result might contain embedded null bytes if ARGSIZE
   was not -1, SIZE was not NULL, the style of O does not use
   backslash escapes, and the flags of O do not request elision of
   null bytes.*/
char *quotearg_alloc_mem (char const *arg, size_t argsize,                            size_t *size, struct quoting_options const *o)
   _GL_ATTRIBUTE_DEALLOC_FREE
  ;

/* Use storage slot N to return a quoted version of the string ARG.
   Use the default quoting options.
   The returned value points to static storage that can be
   reused by the next call to this function with the same value of N.
   N must be nonnegative.  The output of all functions in the
   quotearg_n family are guaranteed to not contain embedded null
   bytes.*/
char *quotearg_n (int n, char const *arg);

/* Equivalent to quotearg_n (0, ARG).  */
char *quotearg (char const *arg);

/* Use storage slot N to return a quoted version of the argument ARG
   of size ARGSIZE.  This is like quotearg_n (N, ARG), except it can
   quote null bytes.  */
char *quotearg_n_mem (int n, char const *arg, size_t argsize);

/* Equivalent to quotearg_n_mem (0, ARG, ARGSIZE).  */
char *quotearg_mem (char const *arg, size_t argsize);

/* Use style S and storage slot N to return a quoted version of the string ARG.
   This is like quotearg_n (N, ARG), except that it uses S with no other
   options to specify the quoting method.  */
char *quotearg_n_style (int n, enum quoting_style s, char const *arg);

/* Use style S and storage slot N to return a quoted version of the
   argument ARG of size ARGSIZE.  This is like quotearg_n_style
   (N, S, ARG), except it can quote null bytes.  */
char *quotearg_n_style_mem (int n, enum quoting_style s,                              char const *arg, size_t argsize);

/* Equivalent to quotearg_n_style (0, S, ARG).  */
char *quotearg_style (enum quoting_style s, char const *arg);

/* Equivalent to quotearg_n_style_mem (0, S, ARG, ARGSIZE).  */
char *quotearg_style_mem (enum quoting_style s,                            char const *arg, size_t argsize);

/* Like quotearg (ARG), except also quote any instances of CH.
   See set_char_quoting for a description of acceptable CH values.  */
char *quotearg_char (char const *arg, char ch);

/* Like quotearg_char (ARG, CH), except it can quote null bytes.  */
char *quotearg_char_mem (char const *arg, size_t argsize, char ch);

/* Equivalent to quotearg_char (ARG, ':').  */
char *quotearg_colon (char const *arg);

/* Like quotearg_colon (ARG), except it can quote null bytes.  */
char *quotearg_colon_mem (char const *arg, size_t argsize);

/* Like quotearg_n_style, except with ':' quoting enabled.  */
char *quotearg_n_style_colon (int n, enum quoting_style s, char const *arg);

/* Like quotearg_n_style (N, S, ARG) but with S as custom_quoting_style
   with left quote as LEFT_QUOTE and right quote as RIGHT_QUOTE.  See
   set_custom_quoting for a description of acceptable LEFT_QUOTE and
   RIGHT_QUOTE values.  */
char *quotearg_n_custom (int n, char const *left_quote,                           char const *right_quote, char const *arg);

/* Like quotearg_n_custom (N, LEFT_QUOTE, RIGHT_QUOTE, ARG) except it
   can quote null bytes.  */
char *quotearg_n_custom_mem (int n, char const *left_quote,                               char const *right_quote,                               char const *arg, size_t argsize);

/* Equivalent to quotearg_n_custom (0, LEFT_QUOTE, RIGHT_QUOTE, ARG).  */
char *quotearg_custom (char const *left_quote, char const *right_quote,                         char const *arg);

/* Equivalent to quotearg_n_custom_mem (0, LEFT_QUOTE, RIGHT_QUOTE, ARG,
                                        ARGSIZE).  */
char *quotearg_custom_mem (char const *left_quote,                             char const *right_quote,                             char const *arg, size_t argsize);

/* Free any dynamically allocated memory.  */
void quotearg_free (void);




/* Use these to shell quote only when necessary,
   when the quoted item is already delimited with colons.  */

/* Use these when there are spaces around the file name,
   in the error message.  */

/* Equivalent to quotearg(), but explicit to avoid syntax checks.  */


static char const G_line[] = { 0 };
enum ls_modes
{
  /* This is for the 'ls' program.  */
  LS_LS,

  /* This is for the 'dir' program.  */
  LS_MULTI_COL,

  /* This is for the 'vdir' program.  */
  LS_LONG_FORMAT
};

extern enum ls_modes ls_mode;
/* statx -> stat conversion functions for coreutils
   Copyright (C) 2019-2026 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */




static int const term_sig[] =
  {
    SIGALRM, /* our timeout.  */
    2,  /* Ctrl-C at terminal for example.  */
    3, /* Ctrl-\ at terminal for example.  */
    SIGHUP,  /* terminal closed for example.  */
    15, /* if terminated, stop monitored proc.  */

    SIGPIPE, SIGUSR1, SIGUSR2,

    SIGILL, SIGTRAP, SIGABRT, SIGBUS, SIGFPE, SIGSEGV,

  };


/* Include <sys/capability.h> last to avoid a clash of <sys/types.h>
   include guards with some premature versions of libcap.
   For more details, see <https://bugzilla.redhat.com/483548>.  */





/* Unix-based readdir implementations have historically returned a dirent.d_ino
   value that is sometimes not equal to the stat-obtained st_ino value for
   that same entry.  This error occurs for a readdir entry that refers
   to a mount point.  readdir's error is to return the inode number of
   the underlying directory -- one that typically cannot be stat'ed, as
   long as a file system is mounted on that directory.  RELIABLE_D_INO
   encapsulates whether we can use the more efficient approach of relying
   on readdir-supplied d_ino values, or whether we must incur the cost of
   calling stat or lstat to obtain each guaranteed-valid inode number.  */




enum filetype
  {
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    normal,
    symbolic_link,
    sock,
    whiteout,
    arg_directory
  };
enum { filetype_cardinality = arg_directory + 1 };

/* Display letters and indicators for each filetype.
   Keep these in sync with enum filetype.  */
static char const filetype_letter[] =
  {'?', 'p', 'c', 'd', 'b', '-', 'l', 's', 'w', 'd'};
static_assert (((size_t) (sizeof (filetype_letter) / sizeof (filetype_letter)[0]              + 0 * 0)) == filetype_cardinality);

/* Map enum filetype to <dirent.h> d_type values.  */
static unsigned char const filetype_d_type[] =
  {
    0, 1, 2, 4, 6, 8, 10, 12,
    14, 4
  };
static_assert (((size_t) (sizeof (filetype_d_type) / sizeof (filetype_d_type)[0]              + 0 * 0)) == filetype_cardinality);

/* Map d_type values to enum filetype.  */
static char const d_type_filetype[255 + 1] =
  {
    [6] = blockdev, [2] = chardev, [4] = directory,
    [1] = fifo, [10] = symbolic_link, [8] = normal,
    [12] = sock, [14] = whiteout
  };

enum acl_type
  {
    ACL_T_NONE,
    ACL_T_UNKNOWN,
    ACL_T_LSM_CONTEXT_ONLY,
    ACL_T_YES
  };

struct fileinfo
  {
    /* The file name.  */
    char *name;

    /* For symbolic link, name of the file linked to, otherwise zero.  */
    char *linkname;

    /* For terminal hyperlinks. */
    char *absolute_name;

    struct stat stat;

    enum filetype filetype;

    /* For symbolic link and long listing, st_mode of file linked to, otherwise
       zero.  */
    mode_t linkmode;

    /* security context.  */
    char *scontext;

    bool stat_ok;

    /* For symbolic link and color printing, true if linked-to file
       exists, otherwise false.  */
    bool linkok;

    /* For long listings, true if the file has an access control list,
       or a security context.  */
    enum acl_type acl_type;

    /* For color listings, true if a regular file has capability info.  */
    bool has_capability;

    /* Whether file name needs quoting. tri-state with -1 == unknown.  */
    int quoted;

    /* Cached screen width (including quoting).  */
    size_t width;
  };

/* Null is a valid character in a color indicator (think about Epson
   printers, for example) so we have to use a length/buffer string
   type.  */

struct bin_str
  {
    size_t len;			/* Number of bytes */
    char const *string;		/* Pointer to the same */
  };


static size_t quote_name (char const *name,                           struct quoting_options const *options,                           int needs_general_quoting,                           const struct bin_str *color,                           bool allow_pad, struct obstack *stack,                           char const *absolute_name);
static size_t quote_name_buf (char **inbuf, size_t bufsize, char *name,                               struct quoting_options const *options,                               int needs_general_quoting, size_t *width,                               bool *pad);
static int decode_switches (int argc, char **argv);
static bool file_ignored (char const *name);
static uintmax_t gobble_file (char const *name, enum filetype type,                               ino_t inode, bool command_line_arg,                               char const *dirname);
static const struct bin_str * get_color_indicator (const struct fileinfo *f,                                                    bool symlink_target);
static bool print_color_indicator (const struct bin_str *ind);
static void put_indicator (const struct bin_str *ind);
static void add_ignore_pattern (char const *pattern);
static void attach (char *dest, char const *dirname, char const *name);
static void clear_files (void);
static void extract_dirs_from_files (char const *dirname,                                      bool command_line_arg);
static bool get_link_name (char const *filename, struct fileinfo *f,                            bool command_line_arg);
static void indent (size_t from, size_t to);
static idx_t calculate_columns (bool by_columns);
static void print_current_files (void);
static void print_dir (char const *name, char const *realname,                        bool command_line_arg);
static size_t print_file_name_and_frills (const struct fileinfo *f,                                           size_t start_col);
static void print_horizontal (void);
static int format_user_width (uid_t u);
static int format_group_width (gid_t g);
static void print_long_format (const struct fileinfo *f);
static void print_many_per_line (void);
static size_t print_name_with_quoting (const struct fileinfo *f,                                        bool symlink_target,                                        struct obstack *stack,                                        size_t start_col);
static void prep_non_filename_text (void);
static bool print_type_indicator (bool stat_ok, mode_t mode,                                   enum filetype type);
static void print_with_separator (char sep);
static void queue_directory (char const *name, char const *realname,                              bool command_line_arg);
static void sort_files (void);
static void parse_ls_color (void);

static size_t quote_name_width (char const *name,                                 struct quoting_options const *options,                                 int needs_general_quoting);

/* Initial size of hash table.
   Most hierarchies are likely to be shallower than this.  */
enum { INITIAL_TABLE_SIZE = 30 };

/* The set of 'active' directories, from the current command-line argument
   to the level in the hierarchy at which files are being listed.
   A directory is represented by its device and inode numbers (struct dev_ino).
   A directory is added to this set when ls begins listing it or its
   entries, and it is removed from the set just after ls has finished
   processing it.  This set is used solely to detect loops, e.g., with
   mkdir loop; cd loop; ln -s ../loop sub; ls -RL  */
static Hash_table *active_dir_set;


/* The table of files in the current directory:

   'cwd_file' points to a vector of 'struct fileinfo', one per file.
   'cwd_n_alloc' is the number of elements space has been allocated for.
   'cwd_n_used' is the number actually in use.  */

/* Address of block containing the files that are described.  */
static struct fileinfo *cwd_file;

/* Length of block that 'cwd_file' points to, measured in files.  */
static idx_t cwd_n_alloc;

/* Index of first unused slot in 'cwd_file'.  */
static idx_t cwd_n_used;

/* Whether files needs may need padding due to quoting.  */
static bool cwd_some_quoted;

/* Whether quoting style _may_ add outer quotes,
   and whether aligning those is useful.  */
static bool align_variable_outer_quotes;

/* Vector of pointers to files, in proper sorted order, and the number
   of entries allocated for it.  */
static void **sorted_file;
static size_t sorted_file_alloc;

/* When true, in a color listing, color each symlink name according to the
   type of file it points to.  Otherwise, color them according to the 'ln'
   directive in LS_COLORS.  Dangling (orphan) symlinks are treated specially,
   regardless.  This is set when 'ln=target' appears in LS_COLORS.  */

static bool color_symlink_as_referent;

static char const *hostname;

/* Mode of appropriate file for coloring.  */
static mode_t
file_or_link_mode (struct fileinfo const *file)
{
  return (color_symlink_as_referent && file->linkok           ? file->linkmode : file->stat.st_mode);
}


/* Record of one pending directory waiting to be listed.  */

struct pending
  {
    char *name;
    /* If the directory is actually the file pointed to by a symbolic link we
       were told to list, 'realname' will contain the name of the symbolic
       link, otherwise zero.  */
    char *realname;
    bool command_line_arg;
    struct pending *next;
  };

static struct pending *pending_dirs;

/* Current time in seconds and nanoseconds since 1970, updated as
   needed when deciding whether a file is recent.  */

static struct timespec current_time;

static bool print_scontext;
static char UNKNOWN_SECURITY_CONTEXT[] = "?";

/* Whether any of the files has an ACL.  This affects the width of the
   mode column.  */

static bool any_has_acl;

/* The number of columns to use for columns containing inode numbers,
   block sizes, link counts, owners, groups, authors, major device
   numbers, minor device numbers, and file sizes, respectively.  */

static int inode_number_width;
static int block_size_width;
static int nlink_width;
static int scontext_width;
static int owner_width;
static int group_width;
static int author_width;
static int major_device_number_width;
static int minor_device_number_width;
static int file_size_width;

/* Option flags */

/* long_format for lots of info, one per line.
   one_per_line for just names, one per line.
   many_per_line for just names, many per line, sorted vertically.
   horizontal for just names, many per line, sorted horizontally.
   with_commas for just names, many per line, separated by commas.

   -l (and other options that imply -l), -1, -C, -x and -m control
   this parameter.  */

enum format
  {
    long_format,		/* -l and other options that imply -l */
    one_per_line,		/* -1 */
    many_per_line,		/* -C */
    horizontal,			/* -x */
    with_commas			/* -m */
  };

static enum format format;

/* 'full-iso' uses full ISO-style dates and times.  'long-iso' uses longer
   ISO-style timestamps, though shorter than 'full-iso'.  'iso' uses shorter
   ISO-style timestamps.  'locale' uses locale-dependent timestamps.  */
enum time_style
  {
    full_iso_time_style,	/* --time-style=full-iso */
    long_iso_time_style,	/* --time-style=long-iso */
    iso_time_style,		/* --time-style=iso */
    locale_time_style		/* --time-style=locale */
  };

static char const *const time_style_args[] =
{
  "full-iso", "long-iso", "iso", "locale", 0
};
static enum time_style const time_style_types[] =
{
  full_iso_time_style, long_iso_time_style, iso_time_style,
  locale_time_style
};
static_assert (((size_t) (sizeof (time_style_args) / sizeof (time_style_args)[0]              + 0 * 0)) == ((size_t) (sizeof (time_style_types) / sizeof (time_style_types)[0]              + 0 * 0)) + 1);

/* Type of time to print or sort by.  Controlled by -c and -u.
   The values of each item of this enum are important since they are
   used as indices in the sort functions array (see sort_files()).  */

enum time_type
  {
    time_mtime = 0,		/* default */
    time_ctime,			/* -c */
    time_atime,			/* -u */
    time_btime,                 /* birth time */
    time_numtypes		/* the number of elements of this enum */
  };

static enum time_type time_type;
static bool explicit_time;

/* The file characteristic to sort by.  Controlled by -t, -S, -U, -X, -v.
   The values of each item of this enum are important since they are
   used as indices in the sort functions array (see sort_files()).  */

enum sort_type
  {
    sort_name = 0,		/* default */
    sort_extension,		/* -X */
    sort_width,
    sort_size,			/* -S */
    sort_version,		/* -v */
    sort_time,			/* -t; must be second to last */
    sort_none,			/* -U; must be last */
    sort_numtypes		/* the number of elements of this enum */
  };

static enum sort_type sort_type;

/* Direction of sort.
   false means highest first if numeric,
   lowest first if alphabetic;
   these are the defaults.
   true means the opposite order in each case.  -r  */

static bool sort_reverse;

/* True means to display owner information.  -g turns this off.  */

static bool print_owner = true;

/* True means to display author information.  */

static bool print_author;

/* True means to display group information.  -G and -o turn this off.  */

static bool print_group = true;

/* True means print the user and group id's as numbers rather
   than as names.  -n  */

static bool numeric_ids;

/* True means mention the size in blocks of each file.  -s  */

static bool print_block_size;

/* Human-readable options for output, when printing block counts.  */
static int human_output_opts;

/* The units to use when printing block counts.  */
static uintmax_t output_block_size;

/* Likewise, but for file sizes.  */
static int file_human_output_opts;
static uintmax_t file_output_block_size = 1;

/* Follow the output with a special string.  Using this format,
   Emacs' dired mode starts up twice as fast, and can handle all
   strange characters in file names.  */
static bool dired;

/* 'none' means don't mention the type of files.
   'slash' means mention directories only, with a '/'.
   'file_type' means mention file types.
   'classify' means mention file types and mark executables.

   Controlled by -F, -p, and --indicator-style.  */

enum indicator_style
  {
    none = 0,	/*     --indicator-style=none (default) */
    slash,	/* -p, --indicator-style=slash */
    file_type,	/*     --indicator-style=file-type */
    classify	/* -F, --indicator-style=classify */
  };

static enum indicator_style indicator_style;

/* Names of indicator styles.  */
static char const *const indicator_style_args[] =
{
  "none", "slash", "file-type", "classify", 0
};
static enum indicator_style const indicator_style_types[] =
{
  none, slash, file_type, classify
};
static_assert (((size_t) (sizeof (indicator_style_args) / sizeof (indicator_style_args)[0]              + 0 * 0)) == ((size_t) (sizeof (indicator_style_types) / sizeof (indicator_style_types)[0]              + 0 * 0)) + 1);

/* True means use colors to mark types.  Also define the different
   colors as well as the stuff for the LS_COLORS environment variable.
   The LS_COLORS variable is now in a termcap-like format.  */

static bool print_with_color;

static bool print_hyperlink;

/* Whether we used any colors in the output so far.  If so, we will
   need to restore the default color later.  If not, we will need to
   call prep_non_filename_text before using color for the first time. */

static bool used_color = false;

enum when_type
  {
    when_never,		/* 0: default or --color=never */
    when_always,	/* 1: --color=always */
    when_if_tty		/* 2: --color=tty */
  };

enum Dereference_symlink
  {
    DEREF_UNDEFINED = 0,		/* default */
    DEREF_NEVER,
    DEREF_COMMAND_LINE_ARGUMENTS,	/* -H */
    DEREF_COMMAND_LINE_SYMLINK_TO_DIR,	/* the default, in certain cases */
    DEREF_ALWAYS			/* -L */
  };

enum indicator_no
  {
    C_LEFT, C_RIGHT, C_END, C_RESET, C_NORM, C_FILE, C_DIR, C_LINK,
    C_FIFO, C_SOCK,
    C_BLK, C_CHR, C_MISSING, C_ORPHAN, C_EXEC, C_DOOR, C_SETUID, C_SETGID,
    C_STICKY, C_OTHER_WRITABLE, C_STICKY_OTHER_WRITABLE, C_CAP, C_MULTIHARDLINK,
    C_CLR_TO_EOL
  };

static char const indicator_name[][2]=
  {
    {'l','c'}, {'r','c'}, {'e','c'}, {'r','s'}, {'n','o'},
    {'f','i'}, {'d','i'}, {'l','n'},
    {'p','i'}, {'s','o'},
    {'b','d'}, {'c','d'}, {'m','i'}, {'o','r'}, {'e','x'},
    {'d','o'}, {'s','u'}, {'s','g'},
    {'s','t'}, {'o','w'}, {'t','w'}, {'c','a'}, {'m','h'},
    {'c','l'}
  };

struct color_ext_type
  {
    struct bin_str ext;		/* The extension we're looking for */
    struct bin_str seq;		/* The sequence to output when we do */
    bool   exact_match;		/* Whether to compare case insensitively */
    struct color_ext_type *next;	/* Next in list */
  };

static struct bin_str color_indicator[] =
  {
    { 2, (char const []) {'\033','['} },/* lc: Left of color sequence */
    { 1, (char const []) {'m'} },	/* rc: Right of color sequence */
    { 0, 0 },			/* ec: End color (replaces lc+rs+rc) */
    { 1, (char const []) {'0'} },	/* rs: Reset to ordinary colors */
    { 0, 0 },			/* no: Normal */
    { 0, 0 },			/* fi: File: default */
    { 5, ((char const [])           {'0','1',';','3','4'}) },	/* di: Directory: bright blue */
    { 5, ((char const [])           {'0','1',';','3','6'}) },	/* ln: Symlink: bright cyan */
    { 2, (char const []) {'3','3'} },		/* pi: Pipe: yellow/brown */
    { 5, ((char const [])           {'0','1',';','3','5'}) },	/* so: Socket: bright magenta */
    { 5, ((char const [])           {'0','1',';','3','3'}) },	/* bd: Block device: bright yellow */
    { 5, ((char const [])           {'0','1',';','3','3'}) },	/* cd: Char device: bright yellow */
    { 0, 0 },			/* mi: Missing file: undefined */
    { 0, 0 },			/* or: Orphaned symlink: undefined */
    { 5, ((char const [])           {'0','1',';','3','2'}) },	/* ex: Executable: bright green */
    { 5, ((char const [])           {'0','1',';','3','5'}) },	/* do: Door: bright magenta */
    { 5, ((char const [])           {'3','7',';','4','1'}) },	/* su: setuid: white on red */
    { 5, ((char const [])           {'3','0',';','4','3'}) },	/* sg: setgid: black on yellow */
    { 5, ((char const [])           {'3','7',';','4','4'}) },	/* st: sticky: black on blue */
    { 5, ((char const [])           {'3','4',';','4','2'}) },	/* ow: other-writable: blue on green */
    { 5, ((char const [])           {'3','0',';','4','2'}) },	/* tw: ow w/ sticky: black on green */
    { 0, 0 },			/* ca: disabled by default */
    { 0, 0 },			/* mh: disabled by default */
    { 3, ((char const [])           {'\033','[','K'}) },		/* cl: clear to end of line */
  };

/* A list mapping file extensions to corresponding display sequence.  */
static struct color_ext_type *color_ext_list = 0;

/* Buffer for color sequences */
static char *color_buf;

/* True means to check for orphaned symbolic link, for displaying
   colors, or to group symlink to directories with other dirs.  */

static bool check_symlink_mode;

/* True means mention the inode number of each file.  -i  */

static bool print_inode;

/* What to do with symbolic links.  Affected by -d, -F, -H, -l (and
   other options that imply -l), and -L.  */

static enum Dereference_symlink dereference;

/* True means when a directory is found, display info on its
   contents.  -R  */

static bool recursive;

/* True means when an argument is a directory name, display info
   on it itself.  -d  */

static bool immediate_dirs;

/* True means that directories are grouped before files. */

static bool directories_first;

/* Which files to ignore.  */

static enum
{
  /* Ignore files whose names start with '.', and files specified by
     --hide and --ignore.  */
  IGNORE_DEFAULT = 0,

  /* Ignore '.', '..', and files specified by --ignore.  */
  IGNORE_DOT_AND_DOTDOT,

  /* Ignore only files specified by --ignore.  */
  IGNORE_MINIMAL
} ignore_mode;

/* A linked list of shell-style globbing patterns.  If a non-argument
   file name matches any of these patterns, it is ignored.
   Controlled by -I.  Multiple -I options accumulate.
   The -B option adds '*~' and '.*~' to this list.  */

struct ignore_pattern
  {
    char const *pattern;
    struct ignore_pattern *next;
  };

static struct ignore_pattern *ignore_patterns;

/* Similar to IGNORE_PATTERNS, except that -a or -A causes this
   variable itself to be ignored.  */
static struct ignore_pattern *hide_patterns;

/* True means output nongraphic chars in file names as '?'.
   (-q, --hide-control-chars)
   qmark_funny_chars and the quoting style (-Q, --quoting-style=WORD) are
   independent.  The algorithm is: first, obey the quoting style to get a
   string representing the file name;  then, if qmark_funny_chars is set,
   replace all nonprintable chars in that string with '?'.  It's necessary
   to replace nonprintable chars even in quoted strings, because we don't
   want to mess up the terminal if control chars get sent to it, and some
   quoting methods pass through control chars as-is.  */
static bool qmark_funny_chars;

/* True means extra replacement of newline with '?'
   in cases where a newline in a file name would be
   ambiguous with newline separators.  */
static bool qmark_newline;

/* Quoting options for file and dir name output.  */

static struct quoting_options *filename_quoting_options;
static struct quoting_options *dirname_quoting_options;

/* The number of chars per hardware tab stop.  Setting this to zero
   inhibits the use of TAB characters for separating columns.  -T */
static size_t tabsize;

/* True means print each directory name before listing it.  */

static bool print_dir_name;

/* The line length to use for breaking lines in many-per-line format.
   Can be set with -w.  If zero, there is no limit.  */

static size_t line_length;

/* The local time zone rules, as per the TZ environment variable.  */

static timezone_t localtz;

/* If true, the file listing format requires that stat be called on
   each file.  */

static bool format_needs_stat;

/* Similar to 'format_needs_stat', but set if only the file type is
   needed.  */

static bool format_needs_type;

/* Like 'format_needs_stat', but set only if capability colors are needed.  */

static bool format_needs_capability;

/* An arbitrary limit on the number of bytes in a printed timestamp.
   This is set to a relatively small value to avoid the need to worry
   about denial-of-service attacks on servers that run "ls" on behalf
   of remote clients.  1000 bytes should be enough for any practical
   timestamp format.  */

enum { TIME_STAMP_LEN_MAXIMUM = ((1000) > ((((((sizeof (time_t) * 8) - 1) * 146 + 484) / 485)    + 1)) ? (1000) : ((((((sizeof (time_t) * 8) - 1) * 146 + 484) / 485)    + 1))) };

/* strftime formats for non-recent and recent files, respectively, in
   -l output.  */

static char const *long_time_format[2] =
  {
    /* strftime format for non-recent files (older than 6 months), in
       -l output.  This should contain the year, month and day (at
       least), in an order that is understood by people in your
       locale's territory.  Please try to keep the number of used
       screen columns small, because many people work in windows with
       only 80 columns.  But make this as wide as the other string
       below, for recent files.  */
    /* TRANSLATORS: ls output needs to be aligned for ease of reading,
       so be wary of using variable width fields from the locale.
       Note %b is handled specially by ls and aligned correctly.
       Note also that specifying a width as in %5b is erroneous as strftime
       will count bytes rather than characters in multibyte locales.  */
    "%b %e  %Y",
    /* strftime format for recent files (younger than 6 months), in -l
       output.  This should contain the month, day and time (at
       least), in an order that is understood by people in your
       locale's territory.  Please try to keep the number of used
       screen columns small, because many people work in windows with
       only 80 columns.  But make this as wide as the other string
       above, for non-recent files.  */
    /* TRANSLATORS: ls output needs to be aligned for ease of reading,
       so be wary of using variable width fields from the locale.
       Note %b is handled specially by ls and aligned correctly.
       Note also that specifying a width as in %5b is erroneous as strftime
       will count bytes rather than characters in multibyte locales.  */
    "%b %e %H:%M"
  };

/* The set of signals that are caught.  */

static sigset_t caught_signals;

/* If nonzero, the value of the pending fatal signal.  */

static sig_atomic_t volatile interrupt_signal;

/* A count of the number of pending stop signals that have been received.  */

static sig_atomic_t volatile stop_signal_count;

/* Desired exit status.  */

static int exit_status;

/* Exit statuses.  */
enum
  {
    /* "ls" had a minor problem.  E.g., while processing a directory,
       ls obtained the name of an entry via readdir, yet was later
       unable to stat that name.  This happens when listing a directory
       in which entries are actively being removed or renamed.  */
    LS_MINOR_PROBLEM = 1,

    /* "ls" had more serious trouble (e.g., memory exhausted, invalid
       option or failure to stat a command line argument.  */
    LS_FAILURE = 2
  };

/* For long options that have no equivalent short option, use a
   non-character as a pseudo short option, starting with CHAR_MAX + 1.  */
enum
{
  AUTHOR_OPTION = CHAR_MAX + 1,
  BLOCK_SIZE_OPTION,
  COLOR_OPTION,
  DEREFERENCE_COMMAND_LINE_SYMLINK_TO_DIR_OPTION,
  FILE_TYPE_INDICATOR_OPTION,
  FORMAT_OPTION,
  FULL_TIME_OPTION,
  GROUP_DIRECTORIES_FIRST_OPTION,
  HIDE_OPTION,
  HYPERLINK_OPTION,
  INDICATOR_STYLE_OPTION,
  QUOTING_STYLE_OPTION,
  SHOW_CONTROL_CHARS_OPTION,
  SI_OPTION,
  SORT_OPTION,
  TIME_OPTION,
  TIME_STYLE_OPTION,
  ZERO_OPTION,
};

static struct option const long_options[] =
{
  {"all", 0, 0, 'a'},
  {"escape", 0, 0, 'b'},
  {"directory", 0, 0, 'd'},
  {"dired", 0, 0, 'D'},
  {"full-time", 0, 0, FULL_TIME_OPTION},
  {"group-directories-first", 0, 0,
   GROUP_DIRECTORIES_FIRST_OPTION},
  {"human-readable", 0, 0, 'h'},
  {"inode", 0, 0, 'i'},
  {"kibibytes", 0, 0, 'k'},
  {"numeric-uid-gid", 0, 0, 'n'},
  {"no-group", 0, 0, 'G'},
  {"hide-control-chars", 0, 0, 'q'},
  {"reverse", 0, 0, 'r'},
  {"size", 0, 0, 's'},
  {"width", 1, 0, 'w'},
  {"almost-all", 0, 0, 'A'},
  {"ignore-backups", 0, 0, 'B'},
  {"classify", 2, 0, 'F'},
  {"file-type", 0, 0, FILE_TYPE_INDICATOR_OPTION},
  {"si", 0, 0, SI_OPTION},
  {"dereference-command-line", 0, 0, 'H'},
  {"dereference-command-line-symlink-to-dir", 0, 0,
   DEREFERENCE_COMMAND_LINE_SYMLINK_TO_DIR_OPTION},
  {"hide", 1, 0, HIDE_OPTION},
  {"ignore", 1, 0, 'I'},
  {"indicator-style", 1, 0, INDICATOR_STYLE_OPTION},
  {"dereference", 0, 0, 'L'},
  {"literal", 0, 0, 'N'},
  {"quote-name", 0, 0, 'Q'},
  {"quoting-style", 1, 0, QUOTING_STYLE_OPTION},
  {"recursive", 0, 0, 'R'},
  {"format", 1, 0, FORMAT_OPTION},
  {"show-control-chars", 0, 0, SHOW_CONTROL_CHARS_OPTION},
  {"sort", 1, 0, SORT_OPTION},
  {"tabsize", 1, 0, 'T'},
  {"time", 1, 0, TIME_OPTION},
  {"time-style", 1, 0, TIME_STYLE_OPTION},
  {"zero", 0, 0, ZERO_OPTION},
  {"color", 2, 0, COLOR_OPTION},
  {"hyperlink", 2, 0, HYPERLINK_OPTION},
  {"block-size", 1, 0, BLOCK_SIZE_OPTION},
  {"context", 0, 0, 'Z'},
  {"author", 0, 0, AUTHOR_OPTION},
  {"help", 0, 0, GETOPT_HELP_CHAR},
  {"version", 0, 0, GETOPT_VERSION_CHAR},
  {0, 0, 0, 0}
};

static char const *const format_args[] =
{
  "verbose", "long", "commas", "horizontal", "across",
  "vertical", "single-column", 0
};
static enum format const format_types[] =
{
  long_format, long_format, with_commas, horizontal, horizontal,
  many_per_line, one_per_line
};
static_assert (((size_t) (sizeof (format_args) / sizeof (format_args)[0]              + 0 * 0)) == ((size_t) (sizeof (format_types) / sizeof (format_types)[0]              + 0 * 0)) + 1);

static char const *const sort_args[] =
{
  "none", "size", "time", "version", "extension",
  "name", "width", 0
};
static enum sort_type const sort_types[] =
{
  sort_none, sort_size, sort_time, sort_version, sort_extension,
  sort_name, sort_width
};
static_assert (((size_t) (sizeof (sort_args) / sizeof (sort_args)[0]              + 0 * 0)) == ((size_t) (sizeof (sort_types) / sizeof (sort_types)[0]              + 0 * 0)) + 1);

static char const *const time_args[] =
{
  "atime", "access", "use",
  "ctime", "status",
  "mtime", "modification",
  "birth", "creation",
  0
};
static enum time_type const time_types[] =
{
  time_atime, time_atime, time_atime,
  time_ctime, time_ctime,
  time_mtime, time_mtime,
  time_btime, time_btime,
};
static_assert (((size_t) (sizeof (time_args) / sizeof (time_args)[0]              + 0 * 0)) == ((size_t) (sizeof (time_types) / sizeof (time_types)[0]              + 0 * 0)) + 1);

static char const *const when_args[] =
{
  /* force and none are for compatibility with another color-ls version */
  "always", "yes", "force",
  "never", "no", "none",
  "auto", "tty", "if-tty", 0
};
static enum when_type const when_types[] =
{
  when_always, when_always, when_always,
  when_never, when_never, when_never,
  when_if_tty, when_if_tty, when_if_tty
};
static_assert (((size_t) (sizeof (when_args) / sizeof (when_args)[0]              + 0 * 0)) == ((size_t) (sizeof (when_types) / sizeof (when_types)[0]              + 0 * 0)) + 1);

/* Information about filling a column.  */
struct column_info
{
  bool valid_len;
  size_t line_len;
  size_t *col_arr;
};

/* Array with information about column fullness.  */
static struct column_info *column_info;

/* Maximum number of columns ever possible for this display.  */
static size_t max_idx;

/* The minimum width of a non-final column is 3: 1 character for the name
   and 2 for the separating white space.  The final column is not padded.  */
enum { MIN_COLUMN_WIDTH = 3 };


/* This zero-based index is for the --dired option.  It is incremented
   for each byte of output generated by this program so that the beginning
   and ending indices (in that output) of every file name can be recorded
   and later output themselves.  */
static off_t dired_pos;

static void
dired_outbyte (char c)
{
  dired_pos++;
  putchar (c);
}

/* Output the buffer S, of length S_LEN, and increment DIRED_POS by S_LEN.  */
static void
dired_outbuf (char const *s, size_t s_len)
{
  dired_pos += s_len;
  fwrite (s, sizeof *s, s_len, stdout);
}

/* Output the string S, and increment DIRED_POS by its length.  */
static void
dired_outstring (char const *s)
{
  dired_outbuf (s, strlen (s));
}

static void
dired_indent (void)
{
  if (dired)
    dired_outstring ("  ");
}

/* With --dired, store pairs of beginning and ending indices of file names.  */
static struct obstack dired_obstack;

/* With --dired, store pairs of beginning and ending indices of any
   directory names that appear as headers (just before 'total' line)
   for lists of directory entries.  Such directory names are seen when
   listing hierarchies using -R and when a directory is listed with at
   least one other command line argument.  */
static struct obstack subdired_obstack;

/* Save the current index on the specified obstack, OBS.  */
static void
push_current_dired_pos (struct obstack *obs)
{
  if (dired)
    ((obs)->temp.tempint = (sizeof dired_pos),					         ((((unsigned int) ((obs)->chunk_limit - (obs)->next_free)) < (obs)->temp.tempint)				         ? (_obstack_newchunk ((obs), (obs)->temp.tempint), 0) : 0),		         memcpy ((obs)->next_free, &dired_pos, (obs)->temp.tempint),			         (obs)->next_free += (obs)->temp.tempint,					         (void) 0);
}

/* With -R, this stack is used to help detect directory cycles.
   The device/inode pairs on this stack mirror the pairs in the
   active_dir_set hash table.  */
static struct obstack dev_ino_obstack;

/* Push a pair onto the device/inode stack.  */
static void
dev_ino_push (dev_t dev, ino_t ino)
{
  void *vdi;
  struct dev_ino *di;
  int dev_ino_size = sizeof *di;
  ((&dev_ino_obstack)->temp.tempint = (dev_ino_size),					         ((((unsigned int) ((&dev_ino_obstack)->chunk_limit - (&dev_ino_obstack)->next_free)) < (&dev_ino_obstack)->temp.tempint)				         ? (_obstack_newchunk ((&dev_ino_obstack), (&dev_ino_obstack)->temp.tempint), 0) : 0),		         ((&dev_ino_obstack)->next_free += ((&dev_ino_obstack)->temp.tempint)),				         (void) 0);
  vdi = ((&dev_ino_obstack)->next_free);
  di = vdi;
  di--;
  di->st_dev = dev;
  di->st_ino = ino;
}

/* Pop a dev/ino struct off the global dev_ino_obstack
   and return that struct.  */
static struct dev_ino
dev_ino_pop (void)
{
  void *vdi;
  struct dev_ino *di;
  int dev_ino_size = sizeof *di;
  ((dev_ino_size <= ((unsigned int) ((&dev_ino_obstack)->next_free - (&dev_ino_obstack)->object_base))) ? (void)0 : abort());
  ((&dev_ino_obstack)->next_free += (-dev_ino_size));
  vdi = ((&dev_ino_obstack)->next_free);
  di = vdi;
  return *di;
}

static void
assert_matching_dev_ino (char const *name, struct dev_ino di)
{
  _GL_ATTRIBUTE_MAYBE_UNUSED struct stat sb;
  ((0 <= stat (name, &sb)) ? (void)0 : abort());
  ((sb.st_dev == di.st_dev) ? (void)0 : abort());
  ((sb.st_ino == di.st_ino) ? (void)0 : abort());
}

static char eolbyte = '\n';

/* Write to standard output PREFIX, followed by the quoting style and
   a space-separated list of the integers stored in OS all on one line.  */

static void
dired_dump_obstack (char const *prefix, struct obstack *os)
{
  size_t n_pos;

  n_pos = ((unsigned int) ((os)->next_free - (os)->object_base)) / sizeof (dired_pos);
  if (n_pos > 0)
    {
      off_t *pos = (((os)->next_free == (os)->object_base					          ? (((os)->maybe_empty_object = 1), 0)				          : 0),								         (os)->temp.tempptr = (os)->object_base,				         (os)->next_free							           = (((os)->object_base) + ((((os)->next_free) - ((os)->object_base) + ((os)->alignment_mask)) & ~((os)->alignment_mask))),				         (os)->object_base = (os)->next_free,					         (os)->temp.tempptr);
      fputs (prefix, stdout);
      for (size_t i = 0; i < n_pos; i++)
        {
          intmax_t p = pos[i];
          printf (" %jd", p);
        }
      putchar ('\n');
    }
}

/* Return the platform birthtime member of the stat structure,
   or fallback to the mtime member, which we have populated
   from the statx structure or reset to an invalid timestamp
   where birth time is not supported.  */
static struct timespec
get_stat_btime (struct stat const *st)
{
  struct timespec btimespec;

  btimespec = get_stat_birthtime (st);

  return btimespec;
}

static int
do_stat (char const *name, struct stat *st)
{
  return stat (name, st);
}

static int
do_lstat (char const *name, struct stat *st)
{
  return lstat (name, st);
}

static int
stat_for_mode (char const *name, struct stat *st)
{
  return stat (name, st);
}

static int
stat_for_ino (char const *name, struct stat *st)
{
  return stat (name, st);
}

static int
fstat_for_ino (int fd, struct stat *st)
{
  return fstat (fd, st);
}

/* Return the address of the first plain %b spec in FMT, or NULL if
   there is no such spec.  %5b etc. do not match, so that user
   widths/flags are honored.  */


static char const *
first_percent_b (char const *fmt)
{
  for (; *fmt; fmt++)
    if (fmt[0] == '%')
      switch (fmt[1])
        {
        case 'b': return fmt;
        case '%': fmt++; break;
        }
  return 0;
}

static char RFC3986[256];
static void
file_escape_init (void)
{
  for (int i = 0; i < 256; i++)
    RFC3986[i] |= c_isalnum (i) || i == '~' || i == '-' || i == '.' || i == '@GUARD_PREFIX@_STDCOUNTOF_H';
}

enum { MBSWIDTH_FLAGS = 1 | 2 };

/* Read the abbreviated month names from the locale, to align them
   and to determine the max width of the field and to truncate names
   greater than our max allowed.
   Note even though this handles multibyte locales correctly
   it's not restricted to them as single byte locales can have
   variable width abbreviated months and also precomputing/caching
   the names was seen to increase the performance of ls significantly.  */

/* abformat[RECENT][MON] is the format to use for timestamps with
   recentness RECENT and month MON.  */
enum { ABFORMAT_SIZE = 128 };
static char abformat[2][12][ABFORMAT_SIZE];
/* True if precomputed formats should be used.  This can be false if
   nl_langinfo fails, if a format or month abbreviation is unusually
   long, or if a month abbreviation contains '%'.  */
static bool use_abformat;

/* Store into ABMON the abbreviated month names, suitably aligned.
   Return true if successful.  */

static bool
abmon_init (char abmon[12][ABFORMAT_SIZE])
{
  return false;
}

/* Initialize ABFORMAT and USE_ABFORMAT.  */

static void
abformat_init (void)
{
  char const *pb[2];
  for (int recent = 0; recent < 2; recent++)
    pb[recent] = first_percent_b (long_time_format[recent]);
  if (! (pb[0] || pb[1]))
    return;

  char abmon[12][ABFORMAT_SIZE];
  if (! abmon_init (abmon))
    return;

  for (int recent = 0; recent < 2; recent++)
    {
      char const *fmt = long_time_format[recent];
      for (int i = 0; i < 12; i++)
        {
          char *nfmt = abformat[recent][i];
          int nbytes;

          if (! pb[recent])
            nbytes = snprintf (nfmt, ABFORMAT_SIZE, "%s", fmt);
          else
            {
              if (! (pb[recent] - fmt <= ((ABFORMAT_SIZE) < (32767) ? (ABFORMAT_SIZE) : (32767))))
                return;
              int prefix_len = pb[recent] - fmt;
              nbytes = snprintf (nfmt, ABFORMAT_SIZE, "%.*s%s%s",                                  prefix_len, fmt, abmon[i], pb[recent] + 2);
            }

          if (! (0 <= nbytes && nbytes < ABFORMAT_SIZE))
            return;
        }
    }

  use_abformat = true;
}

static size_t
dev_ino_hash (void const *x, size_t table_size)
{
  struct dev_ino const *p = x;
  return (uintmax_t) {p->st_ino} % table_size;
}

static bool
dev_ino_compare (void const *x, void const *y)
{
  struct dev_ino const *a = x;
  struct dev_ino const *b = y;
  return (! (((a)->st_dev ^ (b)->st_dev)                                | ((a)->st_ino ^ (b)->st_ino)));
}

static void
dev_ino_free (void *x)
{
  free (x);
}

/* Add the device/inode pair (P->st_dev/P->st_ino) to the set of
   active directories.  Return true if there is already a matching
   entry in the table.  */

static bool
visit_dir (dev_t dev, ino_t ino)
{
  struct dev_ino *ent;
  struct dev_ino *ent_from_table;
  bool found_match;

  ent = xmalloc (sizeof *ent);
  ent->st_ino = ino;
  ent->st_dev = dev;

  /* Attempt to insert this entry into the table.  */
  ent_from_table = hash_insert (active_dir_set, ent);

  if (ent_from_table == 0)
    {
      /* Insertion failed due to lack of memory.  */
      xalloc_die ();
    }

  found_match = (ent_from_table != ent);

  if (found_match)
    {
      /* ent was not inserted, so free it.  */
      free (ent);
    }

  return found_match;
}

static void
free_pending_ent (struct pending *p)
{
  free (p->name);
  free (p->realname);
  free (p);
}

static bool
is_colored (enum indicator_no type)
{
  /* Return true unless the string is "", "0" or "00"; try to be efficient.  */
  size_t len = color_indicator[type].len;
  if (len == 0)
    return false;
  if (2 < len)
    return true;
  char const *s = color_indicator[type].string;
  return (s[0] != '0') | (s[len - 1] != '0');
}

static void
restore_default_color (void)
{
  put_indicator (&color_indicator[C_LEFT]);
  put_indicator (&color_indicator[C_RIGHT]);
}

static void
set_normal_color (void)
{
  if (print_with_color && is_colored (C_NORM))
    {
      put_indicator (&color_indicator[C_LEFT]);
      put_indicator (&color_indicator[C_NORM]);
      put_indicator (&color_indicator[C_RIGHT]);
    }
}

/* An ordinary signal was received; arrange for the program to exit.  */

static void
sighandler (int sig)
{
  if (! interrupt_signal)
    interrupt_signal = sig;
}

/* A SIGTSTP was received; arrange for the program to suspend itself.  */

static void
stophandler (_GL_ATTRIBUTE_MAYBE_UNUSED int sig)
{
  if (! interrupt_signal)
    stop_signal_count++;
}

/* Process any pending signals.  If signals are caught, this function
   should be called periodically.  Ideally there should never be an
   unbounded amount of time when signals are not being processed.
   Signal handling can restore the default colors, so callers must
   immediately change colors after invoking this function.  */

static void
process_signals (void)
{
  while (interrupt_signal || stop_signal_count)
    {
      int sig;
      int stops;
      sigset_t oldset;

      if (used_color)
        restore_default_color ();
      fflush (stdout);

      sigprocmask (0, &caught_signals, &oldset);

      /* Reload interrupt_signal and stop_signal_count, in case a new
         signal was handled before sigprocmask took effect.  */
      sig = interrupt_signal;
      stops = stop_signal_count;

      /* SIGTSTP is special, since the application can receive that signal
         more than once.  In this case, don't set the signal handler to the
         default.  Instead, just raise the uncatchable SIGSTOP.  */
      if (stops)
        {
          stop_signal_count = stops - 1;
          sig = 19;
        }
      else
        signal (sig, ((sighandler_t)0));

      /* Exit or suspend the program.  */
      raise (sig);
      sigprocmask (2, &oldset, 0);

      /* If execution reaches here, then the program has been
         continued (after being suspended).  */
    }
}

/* Setup signal handlers if INIT is true,
   otherwise restore to the default.  */

static void
signal_setup (bool init)
{
  /* The signals that are trapped, and the number of such signals.  */
  static int const stop_sig[] =
    {
      /* This one is handled specially.  */
      20,
    };

  enum { nsigs = ((size_t) (sizeof (term_sig) / sizeof (term_sig)[0]              + 0 * 0)), nstop = ((size_t) (sizeof (stop_sig) / sizeof (stop_sig)[0]              + 0 * 0)) };

  if (init)
    {
      struct sigaction act;

      sigemptyset (&caught_signals);
      for (int j = 0; j < nsigs + nstop; j++)
        {
          int sig = j < nsigs ? term_sig[j]: stop_sig[j - nsigs];
          sigaction (sig, 0, &act);
          if (act.sa_handler != ((sighandler_t)1))
            sigaddset (&caught_signals, sig);
        }

      act.sa_mask = caught_signals;
      act.sa_flags = 0;

      for (int j = 0; j < nsigs + nstop; j++)
        {
          int sig = j < nsigs ? term_sig[j]: stop_sig[j - nsigs];
          if (sigismember (&caught_signals, sig))
            {
              act.sa_handler = j < nsigs ? sighandler : stophandler;
              sigaction (sig, &act, 0);
            }
        }
    }
  else /* restore.  */
    {
      for (int j = 0; j < nsigs + nstop; j++)
        {
          int sig = j < nsigs ? term_sig[j]: stop_sig[j - nsigs];
          if (sigismember (&caught_signals, sig))
            signal (sig, ((sighandler_t)0));
        }
    }
}

static void
signal_init (void)
{
  signal_setup (true);
}

static void
signal_restore (void)
{
  signal_setup (false);
}

int
main (int argc, char **argv)
{
  int i;
  struct pending *thispend;
  int n_files;

  ;
  set_program_name (argv[0]);
  setlocale (0, "");
  ((void) (const char *) {("coreutils")},      (const char *) {("/share/locale")});
  (const char *) {("coreutils")};

  initialize_exit_failure (LS_FAILURE);
  atexit (close_stdout);

  static_assert (((size_t) (sizeof (color_indicator) / sizeof (color_indicator)[0]              + 0 * 0)) == ((size_t) (sizeof (indicator_name) / sizeof (indicator_name)[0]              + 0 * 0)));

  exit_status = 0;
  print_dir_name = true;
  pending_dirs = 0;

  current_time.tv_sec = (_Generic ((time_t) {0},               bool: (bool) 0, char: (char) CHAR_MIN,               signed char: (signed char) -128, unsigned char: (unsigned char) 0,               short int: (short int) SHRT_MIN, unsigned short int: (unsigned short int) 0,               int: -32768, unsigned int: 0u,               long int: LONG_MIN, unsigned long int: 0ul,               long long int: LLONG_MIN, unsigned long long int: 0ull));
  current_time.tv_nsec = -1;

  i = decode_switches (argc, argv);

  if (print_with_color)
    parse_ls_color ();

  /* Test print_with_color again, because the call to parse_ls_color
     may have just reset it -- e.g., if LS_COLORS is invalid.  */

  if (print_with_color)
    {
      /* Don't use TAB characters in output.  Some terminal
         emulators can't handle the combination of tabs and
         color codes on the same line.  */
      tabsize = 0;
    }

  if (directories_first)
    check_symlink_mode = true;
  else if (print_with_color)
    {
      /* Avoid following symbolic links when possible.  */
      if (is_colored (C_ORPHAN)           || (is_colored (C_EXEC) && color_symlink_as_referent)           || (is_colored (C_MISSING) && format == long_format))
        check_symlink_mode = true;
    }

  if (dereference == DEREF_UNDEFINED)
    dereference = ((immediate_dirs                     || indicator_style == classify                     || format == long_format)                    ? DEREF_NEVER                    : DEREF_COMMAND_LINE_SYMLINK_TO_DIR);

  /* When using -R, initialize a data structure we'll use to
     detect any directory cycles.  */
  if (recursive)
    {
      active_dir_set = hash_initialize (INITIAL_TABLE_SIZE, 0,                                         dev_ino_hash,                                         dev_ino_compare,                                         dev_ino_free);
      if (active_dir_set == 0)
        xalloc_die ();

      _obstack_begin ((&dev_ino_obstack), 0, 0,						                        ((void *(*) (long int)) (malloc)),			                        ((void (*) (void *)) (free)));
    }

  localtz = tzalloc (getenv ("TZ"));

  format_needs_stat = ((sort_type == sort_time) | (sort_type == sort_size)                        | (format == long_format)                        | print_block_size | print_hyperlink | print_scontext);
  format_needs_type = ((! format_needs_stat)                        & (recursive | print_with_color | print_scontext                           | directories_first                           | (indicator_style != none)));
  format_needs_capability = print_with_color && is_colored (C_CAP);

  if (dired)
    {
      _obstack_begin ((&dired_obstack), 0, 0,						                        ((void *(*) (long int)) (malloc)),			                        ((void (*) (void *)) (free)));
      _obstack_begin ((&subdired_obstack), 0, 0,						                        ((void *(*) (long int)) (malloc)),			                        ((void (*) (void *)) (free)));
    }

  if (print_hyperlink)
    {
      file_escape_init ();

      hostname = xgethostname ();
      /* The hostname is generally ignored,
         so ignore failures obtaining it.  */
      if (! hostname)
        hostname = "";
    }

  cwd_n_alloc = 100;
  cwd_file = xmalloc (cwd_n_alloc * sizeof *cwd_file);
  cwd_n_used = 0;

  clear_files ();

  n_files = argc - i;

  if (n_files <= 0)
    {
      if (immediate_dirs)
        gobble_file (".", directory, NOT_AN_INODE_NUMBER, true, 0);
      else
        queue_directory (".", 0, true);
    }
  else
    do
      gobble_file (argv[i++], unknown, NOT_AN_INODE_NUMBER, true, 0);
    while (i < argc);

  if (cwd_n_used)
    {
      sort_files ();
      if (!immediate_dirs)
        extract_dirs_from_files (0, true);
      /* 'cwd_n_used' might be zero now.  */
    }

  /* In the following if/else blocks, it is sufficient to test 'pending_dirs'
     (and not pending_dirs->name) because there may be no markers in the queue
     at this point.  A marker may be enqueued when extract_dirs_from_files is
     called with a non-empty string or via print_dir.  */
  if (cwd_n_used)
    {
      print_current_files ();
      if (pending_dirs)
        dired_outbyte ('\n');
    }
  else if (n_files <= 1 && pending_dirs && !pending_dirs->next)
    print_dir_name = false;

  while (pending_dirs)
    {
      thispend = pending_dirs;
      pending_dirs = pending_dirs->next;

      if ((!!active_dir_set))
        {
          if (thispend->name == 0)
            {
              /* thispend->name == NULL means this is a marker entry
                 indicating we've finished processing the directory.
                 Use its dev/ino numbers to remove the corresponding
                 entry from the active_dir_set hash table.  */
              struct dev_ino di = dev_ino_pop ();
              struct dev_ino *found = hash_remove (active_dir_set, &di);
              if (false)
                assert_matching_dev_ino (thispend->realname, di);
              ((found) ? (void)0 : abort());
              dev_ino_free (found);
              free_pending_ent (thispend);
              continue;
            }
        }

      print_dir (thispend->name, thispend->realname,                  thispend->command_line_arg);

      free_pending_ent (thispend);
      print_dir_name = true;
    }

  if (print_with_color && used_color)
    {

      /* Skip the restore when it would be a no-op, i.e.,
         when left is "\033[" and right is "m".  */
      if (!(color_indicator[C_LEFT].len == 2             && memeq (color_indicator[C_LEFT].string, "\033[", 2)             && color_indicator[C_RIGHT].len == 1             && color_indicator[C_RIGHT].string[0] == 'm'))
        restore_default_color ();

      fflush (stdout);

      signal_restore ();

      /* Act on any signals that arrived before the default was restored.
         This can process signals out of order, but there doesn't seem to
         be an easy way to do them in order, and the order isn't that
         important anyway.  */
      for (int j = stop_signal_count; j; j--)
        raise (19);
      int j = interrupt_signal;
      if (j)
        raise (j);
    }

  if (dired)
    {
      /* No need to free these since we're about to exit.  */
      dired_dump_obstack ("//DIRED//", &dired_obstack);
      dired_dump_obstack ("//SUBDIRED//", &subdired_obstack);
      printf ("//DIRED-OPTIONS// --quoting-style=%s\n",               quoting_style_args[get_quoting_style (filename_quoting_options)]);
    }

  if ((!!active_dir_set))
    {
      ((hash_get_n_entries (active_dir_set) == 0) ? (void)0 : abort());
      hash_free (active_dir_set);
    }

  return exit_status;
}

/* Return the line length indicated by the value given by SPEC, or -1
   if unsuccessful.  0 means no limit on line length.  */

static ptrdiff_t
decode_line_length (char const *spec)
{
  uintmax_t val;

  /* Treat too-large values as if they were 0, which is
     effectively infinity.  */
  switch (xstrtoumax (spec, 0, 0, &val, ""))
    {
    case LONGINT_OK:
      return val <= ((PTRDIFF_MAX) < (SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX)) ? val : 0;

    case LONGINT_OVERFLOW:
      return 0;

    case LONGINT_INVALID:
    case LONGINT_INVALID_SUFFIX_CHAR:
    case LONGINT_INVALID_SUFFIX_CHAR_WITH_OVERFLOW:
      return -1;

    default:
      unreachable ();
    }
}

/* Return true if standard output is a tty, caching the result.  */

static bool
stdout_isatty (void)
{
  static signed char out_tty = -1;
  if (out_tty < 0)
    out_tty = isatty (1);
  ((out_tty == 0 || out_tty == 1) ? (void) 0 : /*NOTREACHED*/ (void) 0);
  return out_tty;
}

/* Set all the option flags according to the switches specified.
   Return the index of the first non-option argument.  */

static int
decode_switches (int argc, char **argv)
{
  char *time_style_option = 0;

  /* These variables are false or -1 unless a switch says otherwise.  */
  bool kibibytes_specified = false;
  int format_opt = -1;
  int hide_control_chars_opt = -1;
  int quoting_style_opt = -1;
  int sort_opt = -1;
  ptrdiff_t tabsize_opt = -1;
  ptrdiff_t width_opt = -1;

  while (true)
    {
      int oi = -1;
      int c = getopt_long (argc, argv,                            "abcdfghiklmnopqrstuvw:xABCDFGHI:LNQRST:UXZ1",                            long_options, &oi);
      if (c == -1)
        break;

      switch (c)
        {
        case 'a':
          ignore_mode = IGNORE_MINIMAL;
          break;

        case 'b':
          quoting_style_opt = escape_quoting_style;
          break;

        case 'c':
          time_type = time_ctime;
          explicit_time = true;
          break;

        case 'd':
          immediate_dirs = true;
          break;

        case 'f':
          ignore_mode = IGNORE_MINIMAL; /* enable -a */
          sort_opt = sort_none;         /* enable -U */
          break;

        case FILE_TYPE_INDICATOR_OPTION: /* --file-type */
          indicator_style = file_type;
          break;

        case 'g':
          format_opt = long_format;
          print_owner = false;
          break;

        case 'h':
          file_human_output_opts = human_output_opts =
            human_autoscale | human_SI | human_base_1024;
          file_output_block_size = output_block_size = 1;
          break;

        case 'i':
          print_inode = true;
          break;

        case 'k':
          kibibytes_specified = true;
          break;

        case 'l':
          format_opt = long_format;
          break;

        case 'm':
          format_opt = with_commas;
          break;

        case 'n':
          numeric_ids = true;
          format_opt = long_format;
          break;

        case 'o':  /* Just like -l, but don't display group info.  */
          format_opt = long_format;
          print_group = false;
          break;

        case 'p':
          indicator_style = slash;
          break;

        case 'q':
          hide_control_chars_opt = true;
          break;

        case 'r':
          sort_reverse = true;
          break;

        case 's':
          print_block_size = true;
          break;

        case 't':
          sort_opt = sort_time;
          break;

        case 'u':
          time_type = time_atime;
          explicit_time = true;
          break;

        case 'v':
          sort_opt = sort_version;
          break;

        case 'w':
          width_opt = decode_line_length (optarg);
          if (width_opt < 0)
            error (LS_FAILURE, 0, "%s: %s", (const char *) {("invalid line width")},                    quote (optarg));
          break;

        case 'x':
          format_opt = horizontal;
          break;

        case 'A':
          ignore_mode = IGNORE_DOT_AND_DOTDOT;
          break;

        case 'B':
          add_ignore_pattern ("*~");
          add_ignore_pattern (".*~");
          break;

        case 'C':
          format_opt = many_per_line;
          break;

        case 'D':
          format_opt = long_format;
          print_hyperlink = false;
          dired = true;
          break;

        case 'F':
          {
            int i;
            if (optarg)
              i = ((when_types) [__xargmatch_internal ("--classify", optarg, when_args,                                          (void const *) (when_types),                                       sizeof *(when_types),                                              argmatch_die,                                                   true)]);
            else
              /* Using --classify with no argument is equivalent to using
                 --classify=always.  */
              i = when_always;

            if (i == when_always || (i == when_if_tty && stdout_isatty ()))
              indicator_style = classify;
            break;
          }

        case 'G':		/* inhibit display of group info */
          print_group = false;
          break;

        case 'H':
          dereference = DEREF_COMMAND_LINE_ARGUMENTS;
          break;

        case DEREFERENCE_COMMAND_LINE_SYMLINK_TO_DIR_OPTION:
          dereference = DEREF_COMMAND_LINE_SYMLINK_TO_DIR;
          break;

        case 'I':
          add_ignore_pattern (optarg);
          break;

        case 'L':
          dereference = DEREF_ALWAYS;
          break;

        case 'N':
          quoting_style_opt = literal_quoting_style;
          break;

        case 'Q':
          quoting_style_opt = c_quoting_style;
          break;

        case 'R':
          recursive = true;
          break;

        case 'S':
          sort_opt = sort_size;
          break;

        case 'T':
          tabsize_opt = xnumtoumax (optarg, 0, 0, ((PTRDIFF_MAX) < (SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX)),                                     "", (const char *) {("invalid tab size")}, LS_FAILURE, 0);
          break;

        case 'U':
          sort_opt = sort_none;
          break;

        case 'X':
          sort_opt = sort_extension;
          break;

        case '1':
          /* -1 has no effect after -l.  */
          if (format_opt != long_format)
            format_opt = one_per_line;
          break;

        case AUTHOR_OPTION:
          print_author = true;
          break;

        case HIDE_OPTION:
          {
            struct ignore_pattern *hide = xmalloc (sizeof *hide);
            hide->pattern = optarg;
            hide->next = hide_patterns;
            hide_patterns = hide;
          }
          break;

        case SORT_OPTION:
          sort_opt = ((sort_types) [__xargmatch_internal ("--sort", optarg, sort_args,                                          (void const *) (sort_types),                                       sizeof *(sort_types),                                              argmatch_die,                                                   true)]);
          break;

        case GROUP_DIRECTORIES_FIRST_OPTION:
          directories_first = true;
          break;

        case TIME_OPTION:
          time_type = ((time_types) [__xargmatch_internal ("--time", optarg, time_args,                                          (void const *) (time_types),                                       sizeof *(time_types),                                              argmatch_die,                                                   true)]);
          explicit_time = true;
          break;

        case FORMAT_OPTION:
          format_opt = ((format_types) [__xargmatch_internal ("--format", optarg, format_args,                                          (void const *) (format_types),                                       sizeof *(format_types),                                              argmatch_die,                                                   true)]);
          break;

        case FULL_TIME_OPTION:
          format_opt = long_format;
          time_style_option = (char *) "full-iso";
          break;

        case COLOR_OPTION:
          {
            int i;
            if (optarg)
              i = ((when_types) [__xargmatch_internal ("--color", optarg, when_args,                                          (void const *) (when_types),                                       sizeof *(when_types),                                              argmatch_die,                                                   true)]);
            else
              /* Using --color with no argument is equivalent to using
                 --color=always.  */
              i = when_always;

            print_with_color = (i == when_always                                 || (i == when_if_tty && stdout_isatty ()));
            break;
          }

        case HYPERLINK_OPTION:
          {
            int i;
            if (optarg)
              i = ((when_types) [__xargmatch_internal ("--hyperlink", optarg, when_args,                                          (void const *) (when_types),                                       sizeof *(when_types),                                              argmatch_die,                                                   true)]);
            else
              /* Using --hyperlink with no argument is equivalent to using
                 --hyperlink=always.  */
              i = when_always;

            print_hyperlink = (i == when_always                                || (i == when_if_tty && stdout_isatty ()));
            break;
          }

        case INDICATOR_STYLE_OPTION:
          indicator_style = ((indicator_style_types) [__xargmatch_internal ("--indicator-style", optarg, indicator_style_args,                                          (void const *) (indicator_style_types),                                       sizeof *(indicator_style_types),                                              argmatch_die,                                                   true)]);
          break;

        case QUOTING_STYLE_OPTION:
          quoting_style_opt = ((quoting_style_vals) [__xargmatch_internal ("--quoting-style", optarg, quoting_style_args,                                          (void const *) (quoting_style_vals),                                       sizeof *(quoting_style_vals),                                              argmatch_die,                                                   true)]);
          break;

        case TIME_STYLE_OPTION:
          time_style_option = optarg;
          break;

        case SHOW_CONTROL_CHARS_OPTION:
          hide_control_chars_opt = false;
          break;

        case BLOCK_SIZE_OPTION:
          {
            enum strtol_error e = human_options (optarg, &human_output_opts,                                                  &output_block_size);
            if (e != LONGINT_OK)
              xstrtol_fatal (e, oi, 0, long_options, optarg);
            file_human_output_opts = human_output_opts;
            file_output_block_size = output_block_size;
          }
          break;

        case SI_OPTION:
          file_human_output_opts = human_output_opts =
            human_autoscale | human_SI;
          file_output_block_size = output_block_size = 1;
          break;

        case 'Z':
          print_scontext = true;
          break;

        case ZERO_OPTION:
          eolbyte = 0;
          hide_control_chars_opt = false;
          if (format_opt != long_format)
            format_opt = one_per_line;
          print_with_color = false;
          quoting_style_opt = literal_quoting_style;
          break;

        case GETOPT_HELP_CHAR:			    usage (0);			    break;;

        case GETOPT_VERSION_CHAR:						    version_etc (stdout, (ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), "GNU coreutils", Version, proper_name_lite ("Richard M. Stallman", "Richard M. Stallman"),   proper_name_lite ("David MacKenzie", "David MacKenzie"),	                 (char *) 0);					    exit (0);						    break;;

        default:
          usage (LS_FAILURE);
        }
    }

  if (! output_block_size)
    {
      char const *ls_block_size = getenv ("LS_BLOCK_SIZE");
      human_options (ls_block_size,                      &human_output_opts, &output_block_size);
      if (ls_block_size || getenv ("BLOCK_SIZE"))
        {
          file_human_output_opts = human_output_opts;
          file_output_block_size = output_block_size;
        }
      if (kibibytes_specified)
        {
          human_output_opts = 0;
          output_block_size = 1024;
        }
    }

  format = (0 <= format_opt ? format_opt             : ls_mode == LS_LS ? (stdout_isatty ()                                   ? many_per_line : one_per_line)             : ls_mode == LS_MULTI_COL ? many_per_line             : /* ls_mode == LS_LONG_FORMAT */ long_format);

  /* If the line length was not set by a switch but is needed to determine
     output, go to the work of obtaining it from the environment.  */
  ptrdiff_t linelen = width_opt;
  if (format == many_per_line || format == horizontal || format == with_commas       || print_with_color)
    {
      if (linelen < 0)
        {
          char const *p = getenv ("COLUMNS");
          if (p && *p)
            {
              linelen = decode_line_length (p);
              if (linelen < 0)
                error (0, 0,                        (const char *) {("ignoring invalid width"                          " in environment variable COLUMNS: %s")},                        quote (p));
            }
        }
    }

  line_length = linelen < 0 ? 80 : linelen;

  /* Determine the max possible number of display columns.  */
  max_idx = line_length / MIN_COLUMN_WIDTH;
  /* Account for first display column not having a separator,
     or line_lengths shorter than MIN_COLUMN_WIDTH.  */
  max_idx += line_length % MIN_COLUMN_WIDTH != 0;

  if (format == many_per_line || format == horizontal || format == with_commas)
    {
      if (0 <= tabsize_opt)
        tabsize = tabsize_opt;
      else
        {
          tabsize = 8;
          char const *p = getenv ("TABSIZE");
          if (p)
            {
              uintmax_t tmp;
              if (xstrtoumax (p, 0, 0, &tmp, "") == LONGINT_OK                   && tmp <= SIZE_MAX)
                tabsize = tmp;
              else
                error (0, 0,                        (const char *) {("ignoring invalid tab size"                          " in environment variable TABSIZE: %s")},                        quote (p));
            }
        }
    }

  qmark_funny_chars = (hide_control_chars_opt < 0                        ? ls_mode == LS_LS && stdout_isatty ()                        : hide_control_chars_opt);

  qmark_newline = hide_control_chars_opt != false && eolbyte == '\n'
                  && ((line_length                        && (format == with_commas                            || format == many_per_line || format == horizontal))                       || format == one_per_line || format == long_format);

  int qs = quoting_style_opt;
  if (qs < 0)
    qs = getenv_quoting_style ();
  if (qs < 0)
    qs = (ls_mode == LS_LS           ? (stdout_isatty () ? shell_escape_quoting_style : -1)           : escape_quoting_style);
  if (0 <= qs)
    set_quoting_style (0, qs);
  qs = get_quoting_style (0);
  align_variable_outer_quotes
    = ((format == long_format         || ((format == many_per_line || format == horizontal) && line_length))        && (qs == shell_quoting_style            || qs == shell_escape_quoting_style            || qs == c_maybe_quoting_style));
  filename_quoting_options = clone_quoting_options (0);
  if (qs == escape_quoting_style)
    set_char_quoting (filename_quoting_options, ' ', 1);
  if (file_type <= indicator_style)
    {
      for (char const *p = &"*=>@|"[indicator_style - file_type]; *p; p++)
        set_char_quoting (filename_quoting_options, *p, 1);
    }
  if (format == with_commas       && (qs == shell_quoting_style           || qs == shell_escape_quoting_style           || qs == c_maybe_quoting_style           || qs == escape_quoting_style))
    set_char_quoting (filename_quoting_options, ',', 1);

  dirname_quoting_options = clone_quoting_options (0);
  set_char_quoting (dirname_quoting_options, ':', 1);

  /* --dired implies --format=long (-l) and sans --hyperlink.
     So ignore it if those overridden.  */
  dired &= (format == long_format) & !print_hyperlink;

  if (eolbyte < dired)
    error (LS_FAILURE, 0, (const char *) {("--dired and --zero are incompatible")});

  /* If a time type is explicitly specified (with -c, -u, or --time=)
     and we're not showing a time (-l not specified), then sort by that time,
     rather than by name.  Note this behavior is unspecified by POSIX.  */

  sort_type = (0 <= sort_opt ? sort_opt                : (format != long_format && explicit_time)                ? sort_time : sort_name);

  if (format == long_format)
    {
      char *envstyle = 0;
      char *style = time_style_option;
      if (! style)
        style = envstyle = getenv ("TIME_STYLE");

      if (! style)
        style = (char *) "locale";
      else
        {
          static char const posix_prefix[] = "posix-";
          while ((strncmp (style, posix_prefix, sizeof posix_prefix - 1) == 0) /* sizeof posix_prefix - 1==-1 means unbounded */)
            {
              if (! hard_locale (5))
                return optind;
              style += sizeof posix_prefix - 1;
            }
        }

      if (*style == '+')
        {
          char *p0 = style + 1;
          char *p0nl = strchr (p0, '\n');
          char const *p1 = p0;
          if (p0nl)
            {
              p1 = p0nl + 1;
              if (strchr (p1, '\n'))
                error (LS_FAILURE, 0, (const char *) {("invalid time style format %s")},                        quote (p0));
              if (envstyle)
                p0 = xmemdup0 (p0, p0nl - p0);
              else
                *p0nl = '\0';
            }
          long_time_format[0] = p0;
          long_time_format[1] = p1;
        }
      else
        {
          switch (x_timestyle_match (style, /*allow_posix=*/ true,                                      time_style_args,                                      (char const *) time_style_types,                                      sizeof (*time_style_types), LS_FAILURE))
            {
            case full_iso_time_style:
              long_time_format[0] = long_time_format[1] =
                "%Y-%m-%d %H:%M:%S.%N %z";
              break;

            case long_iso_time_style:
              long_time_format[0] = long_time_format[1] = "%Y-%m-%d %H:%M";
              break;

            case iso_time_style:
              long_time_format[0] = "%Y-%m-%d ";
              long_time_format[1] = "%m-%d %H:%M";
              break;

            case locale_time_style:
              if (hard_locale (5))
                {
                  for (int i = 0; i < 2; i++)
                    long_time_format[i] =
                      ((void) (int) {(5)},        ((void) (const char *) {(0)}, (const char *) {(long_time_format[i])}));
                }
            }
        }

      abformat_init ();
    }

  return optind;
}

/* Parse a string as part of the LS_COLORS variable; this may involve
   decoding all kinds of escape characters.  If equals_end is set an
   unescaped equal sign ends the string, otherwise only a : or \0
   does.  Set *OUTPUT_COUNT to the number of bytes output.  Return
   true if successful.

   The resulting string is *not* null-terminated, but may contain
   embedded nulls.

   Note that both dest and src are char **; on return they point to
   the first free byte after the array and the character that ended
   the input string, respectively.  */

static bool
get_funky_string (char **dest, char const **src, bool equals_end,                   size_t *output_count)
{
  char num;			/* For numerical codes */
  size_t count;			/* Something to count with */
  enum {
    ST_GND, ST_BACKSLASH, ST_OCTAL, ST_HEX, ST_CARET, ST_END, ST_ERROR
  } state;
  char const *p;
  char *q;

  p = *src;			/* We don't want to double-indirect */
  q = *dest;			/* the whole darn time.  */

  count = 0;			/* No characters counted in yet.  */
  num = 0;

  state = ST_GND;		/* Start in ground state.  */
  while (state < ST_END)
    {
      switch (state)
        {
        case ST_GND:		/* Ground state (no escapes) */
          switch (*p)
            {
            case ':':
            case '\0':
              state = ST_END;	/* End of string */
              break;
            case '\\':
              state = ST_BACKSLASH; /* Backslash escape sequence */
              ++p;
              break;
            case '^':
              state = ST_CARET; /* Caret escape */
              ++p;
              break;
            case '=':
              if (equals_end)
                {
                  state = ST_END; /* End */
                  break;
                }
              _GL_ATTRIBUTE_FALLTHROUGH;
            default:
              *(q++) = *(p++);
              ++count;
              break;
            }
          break;

        case ST_BACKSLASH:	/* Backslash escaped character */
          switch (*p)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
              state = ST_OCTAL;	/* Octal sequence */
              num = *p - '0';
              break;
            case 'x':
            case 'X':
              state = ST_HEX;	/* Hex sequence */
              num = 0;
              break;
            case 'a':		/* Bell */
              num = '\a';
              break;
            case 'b':		/* Backspace */
              num = '\b';
              break;
            case 'e':		/* Escape */
              num = 27;
              break;
            case 'f':		/* Form feed */
              num = '\f';
              break;
            case 'n':		/* Newline */
              num = '\n';
              break;
            case 'r':		/* Carriage return */
              num = '\r';
              break;
            case 't':		/* Tab */
              num = '\t';
              break;
            case 'v':		/* Vtab */
              num = '\v';
              break;
            case '?':		/* Delete */
              num = 127;
              break;
            case '@GUARD_PREFIX@_STDCOUNTOF_H':		/* Space */
              num = ' ';
              break;
            case '\0':		/* End of string */
              state = ST_ERROR;	/* Error! */
              break;
            default:		/* Escaped character like \ ^ : = */
              num = *p;
              break;
            }
          if (state == ST_BACKSLASH)
            {
              *(q++) = num;
              ++count;
              state = ST_GND;
            }
          ++p;
          break;

        case ST_OCTAL:		/* Octal sequence */
          if (*p < '0' || *p > '7')
            {
              *(q++) = num;
              ++count;
              state = ST_GND;
            }
          else
            num = (num << 3) + (*(p++) - '0');
          break;

        case ST_HEX:		/* Hex sequence */
          switch (*p)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
              num = (num << 4) + (*(p++) - '0');
              break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
              num = (num << 4) + (*(p++) - 'a') + 10;
              break;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
              num = (num << 4) + (*(p++) - 'A') + 10;
              break;
            default:
              *(q++) = num;
              ++count;
              state = ST_GND;
              break;
            }
          break;

        case ST_CARET:		/* Caret escape */
          state = ST_GND;	/* Should be the next state... */
          if (*p >= '@' && *p <= '~')
            {
              *(q++) = *(p++) & 037;
              ++count;
            }
          else if (*p == '?')
            {
              *(q++) = 127;
              ++count;
            }
          else
            state = ST_ERROR;
          break;

        case ST_END: case ST_ERROR: default:
          ((false) ? (void)0 : abort());
        }
    }

  *dest = q;
  *src = p;
  *output_count = count;

  return state != ST_ERROR;
}

enum parse_state
  {
    PS_START = 1,
    PS_2,
    PS_3,
    PS_4,
    PS_DONE,
    PS_FAIL
  };


/* Check if the content of TERM is a valid name in dircolors.  */

static bool
known_term_type (void)
{
  char const *term = getenv ("TERM");
  if (! term || ! *term)
    return false;

  char const *line = G_line;
  while (line - G_line < sizeof (G_line))
    {
      if (strncmp (line, "" "TERM " "", sizeof ("TERM ") - 1) == 0)
        {
          if (fnmatch (line + 5, term, 0) == 0)
            return true;
        }
      line += strlen (line) + 1;
    }

  return false;
}

static void
parse_ls_color (void)
{
  char const *p;		/* Pointer to character being parsed */
  char *buf;			/* color_buf buffer pointer */
  char label0, label1;		/* Indicator label */
  struct color_ext_type *ext;	/* Extension we are working on */

  if ((p = getenv ("LS_COLORS")) == 0 || *p == '\0')
    {
      /* LS_COLORS takes precedence, but if that's not set then
         honor the COLORTERM and TERM env variables so that
         we only go with the internal ANSI color codes if the
         former is non empty or the latter is set to a known value.  */
      char const *colorterm = getenv ("COLORTERM");
      if (! (colorterm && *colorterm) && ! known_term_type ())
        print_with_color = false;
      return;
    }

  ext = 0;

  /* This is an overly conservative estimate, but any possible
     LS_COLORS string will *not* generate a color_buf longer than
     itself, so it is a safe way of allocating a buffer in
     advance.  */
  buf = color_buf = xstrdup (p);

  enum parse_state state = PS_START;
  while (true)
    {
      switch (state)
        {
        case PS_START:		/* First label character */
          switch (*p)
            {
            case ':':
              ++p;
              break;

            case '*':
              /* Allocate new extension block and add to head of
                 linked list (this way a later definition will
                 override an earlier one, which can be useful for
                 having terminal-specific defs override global).  */

              ext = xmalloc (sizeof *ext);
              ext->next = color_ext_list;
              color_ext_list = ext;
              ext->exact_match = false;

              ++p;
              ext->ext.string = buf;

              state = (get_funky_string (&buf, &p, true, &ext->ext.len)                        ? PS_4 : PS_FAIL);
              break;

            case '\0':
              state = PS_DONE;	/* Done! */
              goto done;

            default:	/* Assume it is file type label */
              label0 = *p++;
              state = PS_2;
              break;
            }
          break;

        case PS_2:		/* Second label character */
          if (*p)
            {
              label1 = *p++;
              state = PS_3;
            }
          else
            state = PS_FAIL;	/* Error */
          break;

        case PS_3:		/* Equal sign after indicator label */
          state = PS_FAIL;	/* Assume failure...  */
          if (*(p++) == '=')/* It *should* be...  */
            {
              for (int i = 0; i < ((size_t) (sizeof (indicator_name) / sizeof (indicator_name)[0]              + 0 * 0)); i++)
                {
                  if ((label0 == indicator_name[i][0])                       && (label1 == indicator_name[i][1]))
                    {
                      color_indicator[i].string = buf;
                      state = (get_funky_string (&buf, &p, false,                                                  &color_indicator[i].len)                                ? PS_START : PS_FAIL);
                      break;
                    }
                }
              if (state == PS_FAIL)
                error (0, 0, (const char *) {("unrecognized prefix: %s")},                        quote ((char []) {label0, label1, '\0'}));
            }
          break;

        case PS_4:		/* Equal sign after *.ext */
          if (*(p++) == '=')
            {
              ext->seq.string = buf;
              state = (get_funky_string (&buf, &p, false, &ext->seq.len)                        ? PS_START : PS_FAIL);
            }
          else
            state = PS_FAIL;
          break;

        case PS_FAIL:
          goto done;

        case PS_DONE: default:
          ((false) ? (void)0 : abort());
        }
    }
 done:

  if (state == PS_FAIL)
    {
      error (0, 0,              (const char *) {("unparsable value for LS_COLORS environment variable")});
      free (color_buf);
      for (struct color_ext_type *e = color_ext_list; e != 0;            /* empty */)
        {
          struct color_ext_type *e2 = e;
          e = e->next;
          free (e2);
        }
      print_with_color = false;
      return;
    }
  else
    {
      /* Postprocess list to set EXACT_MATCH on entries where there are
         different cased extensions with separate sequences defined.
         Also set ext.len to SIZE_MAX on any entries that can't
         match due to precedence, to avoid redundant string compares.  */
      for (struct color_ext_type *e1 = color_ext_list; e1 != 0;            e1 = e1->next)
        {
          bool case_ignored = false;

          for (struct color_ext_type *e2 = e1->next; e2 != 0;                e2 = e2->next)
            {
              if (e2->ext.len < SIZE_MAX && e1->ext.len == e2->ext.len)
                {
                  if (memeq (e1->ext.string, e2->ext.string, e1->ext.len))
                    e2->ext.len = SIZE_MAX; /* Ignore */
                  else if (c_strncasecmp (e1->ext.string, e2->ext.string,                                           e1->ext.len) == 0)
                    {
                      if (case_ignored)
                        {
                          e2->ext.len = SIZE_MAX; /* Ignore */
                        }
                      else if (e1->seq.len == e2->seq.len                                && memeq (e1->seq.string, e2->seq.string,                                          e1->seq.len))
                        {
                          e2->ext.len = SIZE_MAX; /* Ignore */
                          case_ignored = true;    /* Ignore all subsequent */
                        }
                      else
                        {
                          e1->exact_match = true;
                          e2->exact_match = true;
                        }
                    }
                }
            }
        }
    }

  if (color_indicator[C_LINK].len == 6       && !strncmp (color_indicator[C_LINK].string, "" "target" "", sizeof ("target") - 1))
    color_symlink_as_referent = true;
}

/* Set the exit status to report a failure.  If SERIOUS, it is a
   serious failure; otherwise, it is merely a minor problem.  */

static void
set_exit_status (bool serious)
{
  if (serious)
    exit_status = LS_FAILURE;
  else if (exit_status == 0)
    exit_status = LS_MINOR_PROBLEM;
}

/* Assuming a failure is serious if SERIOUS, use the printf-style
   MESSAGE to report the failure to access a file named FILE.  Assume
   errno is set appropriately for the failure.  */

static void
file_failure (bool serious, char const *message, char const *file)
{
  error (0, errno, message, quotearg_style (shell_escape_always_quoting_style, file));
  set_exit_status (serious);
}

/* Request that the directory named NAME have its contents listed later.
   If REALNAME is nonzero, it will be used instead of NAME when the
   directory name is printed.  This allows symbolic links to directories
   to be treated as regular directories but still be listed under their
   real names.  NAME == NULL is used to insert a marker entry for the
   directory named in REALNAME.
   If NAME is non-null, we use its dev/ino information to save
   a call to stat -- when doing a recursive (-R) traversal.
   COMMAND_LINE_ARG means this directory was mentioned on the command line.  */

static void
queue_directory (char const *name, char const *realname, bool command_line_arg)
{
  struct pending *new = xmalloc (sizeof *new);
  new->realname = realname ? xstrdup (realname) : 0;
  new->name = name ? xstrdup (name) : 0;
  new->command_line_arg = command_line_arg;
  new->next = pending_dirs;
  pending_dirs = new;
}

/* Read directory NAME, and list the files in it.
   If REALNAME is nonzero, print its name instead of NAME;
   this is used for symbolic links to directories.
   COMMAND_LINE_ARG means this directory was mentioned on the command line.  */

static void
print_dir (char const *name, char const *realname, bool command_line_arg)
{
  DIR *dirp;
  struct dirent *next;
  uintmax_t total_blocks = 0;
  static bool first = true;

  errno = 0;
  dirp = opendir (name);
  if (!dirp)
    {
      if (command_line_arg || ! ignorable_traversal_errno (errno))
        file_failure (command_line_arg, (const char *) {("cannot open directory %s")}, name);
      return;
    }

  if ((!!active_dir_set))
    {
      struct stat dir_stat;
      int fd = dirfd (dirp);

      /* If dirfd failed, endure the overhead of stat'ing by path  */
      if ((0 <= fd            ? fstat_for_ino (fd, &dir_stat)            : stat_for_ino (name, &dir_stat)) < 0)
        {
          if (! ignorable_traversal_errno (errno))
            file_failure (command_line_arg,                           (const char *) {("cannot determine device and inode of %s")}, name);
          closedir (dirp);
          return;
        }

      /* If we've already visited this dev/inode pair, warn that
         we've found a loop, and do not process this directory.  */
      if (visit_dir (dir_stat.st_dev, dir_stat.st_ino))
        {
          error (0, 0, (const char *) {("%s: not listing already-listed directory")},                  quotearg_n_style_colon (0, shell_escape_quoting_style, name));
          closedir (dirp);
          set_exit_status (true);
          return;
        }

      dev_ino_push (dir_stat.st_dev, dir_stat.st_ino);
    }

  clear_files ();

  if (recursive || print_dir_name)
    {
      if (!first)
        dired_outbyte ('\n');
      first = false;
      dired_indent ();

      char *absolute_name = 0;
      if (print_hyperlink)
        {
          absolute_name = canonicalize_filename_mode (name, CAN_MISSING);
          if (! absolute_name               && ! ignorable_traversal_errno (errno))
            file_failure (command_line_arg,                           (const char *) {("error canonicalizing %s")}, name);
        }
      quote_name (realname ? realname : name, dirname_quoting_options, -1,                   0, true, &subdired_obstack, absolute_name);

      free (absolute_name);

      dired_outstring (":\n");
    }

  /* Read the directory entries, and insert the subfiles into the 'cwd_file'
     table.  */

  while (true)
    {
      /* Set errno to zero so we can distinguish between a readdir failure
         and when readdir simply finds that there are no more entries.  */
      errno = 0;
      next = readdir (dirp);
      if (next)
        {
          if (! file_ignored (next->d_name))
            {
              enum filetype type;
              type = unknown;
              total_blocks += gobble_file (next->d_name, type,                                            NOT_AN_INODE_NUMBER,                                            false, name);

              /* In this narrow case, print out each name right away, so
                 ls uses constant memory while processing the entries of
                 this directory.  Useful when there are many (millions)
                 of entries in a directory.  */
              if (format == one_per_line && sort_type == sort_none                       && !print_block_size && !recursive)
                {
                  /* We must call sort_files in spite of
                     "sort_type == sort_none" for its initialization
                     of the sorted_file vector.  */
                  sort_files ();
                  print_current_files ();
                  clear_files ();
                }
            }
        }
      else
        {
          int err = errno;
          if (err == 0)
            break;
          /* Ignore errors indicating that the directory was removed.  */
          if (ignorable_traversal_errno (err))
            break;
          file_failure (command_line_arg, (const char *) {("reading directory %s")}, name);
          if (err != EOVERFLOW)
            break;
        }

      /* When processing a very large directory, and since we've inhibited
         interrupts, this loop would take so long that ls would be annoyingly
         uninterruptible.  This ensures that it handles signals promptly.  */
      process_signals ();
    }

  if (closedir (dirp) != 0)
    {
      file_failure (command_line_arg, (const char *) {("closing directory %s")}, name);
      /* Don't return; print whatever we got.  */
    }

  /* Sort the directory contents.  */
  sort_files ();

  /* If any member files are subdirectories, perhaps they should have their
     contents listed rather than being mentioned here as files.  */

  if (recursive)
    extract_dirs_from_files (name, false);

  if (format == long_format || print_block_size)
    {
      char buf[((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 3];
      char *p = human_readable (total_blocks, buf + 1, human_output_opts,                                 512, output_block_size);
      char *pend = p + strlen (p);
      *--p = ' ';
      *pend++ = eolbyte;
      dired_indent ();
      dired_outstring ((const char *) {("total")});
      dired_outbuf (p, pend - p);
    }

  if (cwd_n_used)
    print_current_files ();
}

/* Add 'pattern' to the list of patterns for which files that match are
   not listed.  */

static void
add_ignore_pattern (char const *pattern)
{
  struct ignore_pattern *ignore;

  ignore = xmalloc (sizeof *ignore);
  ignore->pattern = pattern;
  /* Add it to the head of the linked list.  */
  ignore->next = ignore_patterns;
  ignore_patterns = ignore;
}

/* Return true if one of the PATTERNS matches FILE.  */

static bool
patterns_match (struct ignore_pattern const *patterns, char const *file)
{
  for (struct ignore_pattern const *p = patterns; p; p = p->next)
    if (fnmatch (p->pattern, file, 0x04) == 0)
      return true;
  return false;
}

/* Return true if FILE should be ignored.  */

static bool
file_ignored (char const *name)
{
  return ((ignore_mode != IGNORE_MINIMAL            && name[0] == '.'            && (ignore_mode == IGNORE_DEFAULT || ! name[1 + (name[1] == '.')]))           || (ignore_mode == IGNORE_DEFAULT               && patterns_match (hide_patterns, name))           || patterns_match (ignore_patterns, name));
}

/* POSIX requires that a file size be printed without a sign, even
   when negative.  Assume the typical case where negative sizes are
   actually positive values that have wrapped around.  */

static uintmax_t
unsigned_file_size (off_t size)
{
  return size + (size < 0) * ((uintmax_t) (_Generic ((off_t) {0},               bool: (bool) 1, char: (char) CHAR_MAX,               signed char: (signed char) 127, unsigned char: (unsigned char) -1,               short int: (short int) SHRT_MAX, unsigned short int: (unsigned short int) -1,               int: 32767, unsigned int: -1u,               long int: LONG_MAX, unsigned long int: -1ul,               long long int: LLONG_MAX, unsigned long long int: -1ull)) - (_Generic ((off_t) {0},               bool: (bool) 0, char: (char) CHAR_MIN,               signed char: (signed char) -128, unsigned char: (unsigned char) 0,               short int: (short int) SHRT_MIN, unsigned short int: (unsigned short int) 0,               int: -32768, unsigned int: 0u,               long int: LONG_MIN, unsigned long int: 0ul,               long long int: LLONG_MIN, unsigned long long int: 0ull)) + 1);
}

static bool
has_capability (_GL_ATTRIBUTE_MAYBE_UNUSED char const *name)
{
  errno = 95;
  return false;
}

/* Enter and remove entries in the table 'cwd_file'.  */

static void
free_ent (struct fileinfo *f)
{
  free (f->name);
  free (f->linkname);
  free (f->absolute_name);
  if (f->scontext != UNKNOWN_SECURITY_CONTEXT)
    ((void) 0);
}

/* Empty the table of files.  */
static void
clear_files (void)
{
  for (idx_t i = 0; i < cwd_n_used; i++)
    {
      struct fileinfo *f = sorted_file[i];
      free_ent (f);
    }

  cwd_n_used = 0;
  cwd_some_quoted = false;
  any_has_acl = false;
  inode_number_width = 0;
  block_size_width = 0;
  nlink_width = 0;
  owner_width = 0;
  group_width = 0;
  author_width = 0;
  scontext_width = 0;
  major_device_number_width = 0;
  minor_device_number_width = 0;
  file_size_width = 0;
}

/* Cache file_has_aclinfo failure, when it's trivial to do.
   Like file_has_aclinfo, but when F's st_dev says it's on a file
   system lacking ACL support, return 0 with ENOTSUP immediately.  */
static int
file_has_aclinfo_cache (char const *file, struct fileinfo *f,                         struct aclinfo *ai, int flags)
{
  /* If UNSUPPORTED_SCONTEXT, these variables hold the
     st_dev and associated info for the most recently processed device
     for which file_has_aclinfo failed indicating lack of support.  */
  static int unsupported_return;
  static char *unsupported_scontext;
  static int unsupported_scontext_err;
  static dev_t unsupported_device;

  if (f->stat_ok && unsupported_scontext       && f->stat.st_dev == unsupported_device)
    {
      ai->buf = ai->u._gl_acl_ch;
      ai->size = 0;
      ai->scontext = unsupported_scontext;
      ai->scontext_err = unsupported_scontext_err;
      errno = 95;
      return unsupported_return;
    }

  errno = 0;
  int n = file_has_aclinfo (file, ai, flags);
  int err = errno;
  if (f->stat_ok && n <= 0 && !acl_errno_valid (err)       && (!(flags & ACL_GET_SCONTEXT) || !acl_errno_valid (ai->scontext_err)))
    {
      unsupported_return = n;
      unsupported_scontext = ai->scontext;
      unsupported_scontext_err = ai->scontext_err;
      unsupported_device = f->stat.st_dev;
    }
  return n;
}

/* Cache has_capability failure, when it's trivial to do.
   Like has_capability, but when F's st_dev says it's on a file
   system lacking capability support, return 0 with ENOTSUP immediately.  */
static bool
has_capability_cache (char const *file, struct fileinfo *f)
{
  /* If UNSUPPORTED_CACHED, UNSUPPORTED_DEVICE is the cached
     st_dev of the most recently processed device for which we've
     found that has_capability fails indicating lack of support.  */
  static bool unsupported_cached;
  static dev_t unsupported_device;

  if (f->stat_ok && unsupported_cached && f->stat.st_dev == unsupported_device)
    {
      errno = 95;
      return 0;
    }

  bool b = has_capability (file);
  if (f->stat_ok && !b && !acl_errno_valid (errno))
    {
      unsupported_cached = true;
      unsupported_device = f->stat.st_dev;
    }
  return b;
}

static bool
needs_quoting (char const *name)
{
  char test[2];
  size_t len = quotearg_buffer (test, sizeof test , name, -1,                                 filename_quoting_options);
  return *name != *test || strlen (name) != len;
}

/* Add a file to the current table of files.
   Verify that the file exists, and print an error message if it does not.
   Return the number of blocks that the file occupies.  */
static uintmax_t
gobble_file (char const *name, enum filetype type, ino_t inode,              bool command_line_arg, char const *dirname)
{
  uintmax_t blocks = 0;
  struct fileinfo *f;

  /* An inode value prior to gobble_file necessarily came from readdir,
     which is not used for command line arguments.  */
  ((! command_line_arg || inode == NOT_AN_INODE_NUMBER) ? (void)0 : abort());

  if (cwd_n_used == cwd_n_alloc)
    cwd_file = xpalloc (cwd_file, &cwd_n_alloc, 1, -1, sizeof *cwd_file);

  f = &cwd_file[cwd_n_used];
  memset (f, '\0', sizeof *f);
  f->stat.st_ino = inode;
  f->filetype = type;
  f->scontext = UNKNOWN_SECURITY_CONTEXT;

  f->quoted = -1;
  if ((! cwd_some_quoted) && align_variable_outer_quotes)
    {
      /* Determine if any quoted for padding purposes.  */
      f->quoted = needs_quoting (name);
      if (f->quoted)
        cwd_some_quoted = 1;
    }

  bool check_stat =
     (command_line_arg       || print_hyperlink       || format_needs_stat       || (format_needs_type && type == unknown)       /* When coloring a directory, stat it to indicate
         sticky and/or other-writable attributes.  */       || ((type == directory || type == unknown) && print_with_color           && (is_colored (C_OTHER_WRITABLE)               || is_colored (C_STICKY)               || is_colored (C_STICKY_OTHER_WRITABLE)))       /* When dereferencing symlinks, the inode and type must come from
         stat, but readdir provides the inode and type of lstat.  */       || ((print_inode || format_needs_type)           && (type == symbolic_link || type == unknown)           && (dereference == DEREF_ALWAYS               || color_symlink_as_referent || check_symlink_mode))       /* Command line dereferences are already taken care of by the above
         assertion that the inode number is not yet known.  */       || (print_inode && inode == NOT_AN_INODE_NUMBER)       /* --indicator-style=classify (aka -F) requires statting each
         regular file to see whether it's executable.  */       || ((type == normal || type == unknown)           && (indicator_style == classify               /* This is so that --color ends up highlighting files with these
                 mode bits set even when options like -F are not specified.  */               || (print_with_color && (is_colored (C_EXEC)                                        || is_colored (C_SETUID)                                        || is_colored (C_SETGID))))));

  /* Absolute name of this file, if needed.  */
  char const *full_name = name;
  if (check_stat | print_scontext | format_needs_capability       && name[0] != '/' && dirname)
    {
      char *p = alloca (strlen (name) + strlen (dirname) + 2);
      attach (p, dirname, name);
      full_name = p;
    }

  bool do_deref;

  if (!check_stat)
    do_deref = dereference == DEREF_ALWAYS;
  else
    {
      int err;

      if (print_hyperlink)
        {
          f->absolute_name = canonicalize_filename_mode (full_name,                                                          CAN_MISSING);
          if (! f->absolute_name               && (command_line_arg                   || ! ignorable_traversal_errno (errno)))
            file_failure (command_line_arg,                           (const char *) {("error canonicalizing %s")}, full_name);
        }

      switch (dereference)
        {
        case DEREF_ALWAYS:
          err = do_stat (full_name, &f->stat);
          do_deref = true;
          break;

        case DEREF_COMMAND_LINE_ARGUMENTS:
        case DEREF_COMMAND_LINE_SYMLINK_TO_DIR:
          if (command_line_arg)
            {
              bool need_lstat;
              err = do_stat (full_name, &f->stat);
              do_deref = true;

              if (dereference == DEREF_COMMAND_LINE_ARGUMENTS)
                break;

              need_lstat = (err < 0                             ? (errno == 2 || errno == 40)                             : ! (((f->stat.st_mode) & 0170000) == 0040000));
              if (!need_lstat)
                break;

              /* stat failed because of ENOENT || ELOOP, maybe indicating a
                 non-traversable symlink.  Or stat succeeded,
                 FULL_NAME does not refer to a directory,
                 and --dereference-command-line-symlink-to-dir is in effect.
                 Fall through so that we call lstat instead.  */
            }
          _GL_ATTRIBUTE_FALLTHROUGH;

        case DEREF_NEVER:
          err = do_lstat (full_name, &f->stat);
          do_deref = false;
          break;

        case DEREF_UNDEFINED: default:
          ((false) ? (void)0 : abort());
        }

      if (err != 0)
        {
          if (! command_line_arg && ignorable_traversal_errno (errno))
            {
              int stat_errno = errno;
              struct stat linkstat;
              bool dangling_link = (do_deref                                     && (type == symbolic_link                                         || type == unknown)                                     && do_lstat (full_name, &linkstat) == 0);
              errno = stat_errno;
              if (! dangling_link)
                {
                  free_ent (f);
                  return 0;
                }
            }

          /* Failure to stat a command line argument leads to
             an exit status of 2.  For other files, stat failure
             provokes an exit status of 1.  */
          file_failure (command_line_arg,                         (const char *) {("cannot access %s")}, full_name);

          if (command_line_arg)
            {
              free_ent (f);
              return 0;
            }

          f->name = xstrdup (name);
          cwd_n_used++;

          return 0;
        }

      f->stat_ok = true;
      f->filetype = type = d_type_filetype[IFTODT (f->stat.st_mode)];
    }

  if (type == directory && command_line_arg && !immediate_dirs)
    f->filetype = type = arg_directory;

  bool get_scontext = (format == long_format) | print_scontext;
  bool check_capability = format_needs_capability & (type == normal);

  if (get_scontext | check_capability)
    {
      struct aclinfo ai;
      int aclinfo_flags = ((do_deref ? ACL_SYMLINK_FOLLOW : 0)                            | (get_scontext ? ACL_GET_SCONTEXT : 0)                            | filetype_d_type[type]);
      int n = file_has_aclinfo_cache (full_name, f, &ai, aclinfo_flags);
      bool have_acl = 0 < n;
      bool have_scontext = !ai.scontext_err;

      /* Let the user know via '?' if errno is EACCES, which can
         happen with Linux kernel 6.12 on an NFS file system.
         That's better than a long-winded diagnostic.

         Similarly, ignore ENOENT which may happen on some versions
         of cygwin when processing dangling symlinks for example.
         Also if a file is removed while we're reading ACL info,
         ACL_T_UNKNOWN is sufficient indication for that edge case.  */
      bool cannot_access_acl = n < 0
           && (errno == 13                || ignorable_traversal_errno (errno));

      f->acl_type = (!have_scontext && !have_acl                      ? (cannot_access_acl ? ACL_T_UNKNOWN : ACL_T_NONE)                      : (have_scontext && !have_acl                         ? ACL_T_LSM_CONTEXT_ONLY                         : ACL_T_YES));
      any_has_acl |= f->acl_type != ACL_T_NONE;

      if (format == long_format && n < 0 && !cannot_access_acl)
        error (0, errno, "%s", quotearg_n_style_colon (0, shell_escape_quoting_style, full_name));
      else
        {
          /* When requesting security context information, don't make
             ls fail just because the file (even a command line argument)
             isn't on the right type of file system.  I.e., a getfilecon
             failure isn't in the same class as a stat failure.  */
          if (print_scontext && ai.scontext_err               && ! ignorable_traversal_errno (ai.scontext_err)               && (! (is_ENOTSUP (ai.scontext_err)                      || ai.scontext_err == (-1))))
            error (0, ai.scontext_err, "%s", quotearg_n_style_colon (0, shell_escape_quoting_style, full_name));
        }

      /* has_capability adds around 30% runtime to 'ls --color',
         so call it only if really needed.  Note capability coloring
         is disabled in the default color config.  */
      if (check_capability && false)
        f->has_capability = has_capability_cache (full_name, f);

      f->scontext = ai.scontext;
      ai.scontext = 0;
      ((void) 0);
    }

  if ((type == symbolic_link)       & ((format == long_format) | check_symlink_mode))
    {
      struct stat linkstats;

      if (! get_link_name (full_name, f, command_line_arg))
        {
          free_ent (f);
          return 0;
        }

      /* Use the slower quoting path for this entry, though
         don't update CWD_SOME_QUOTED since alignment not affected.  */
      if (f->linkname && f->quoted == 0 && needs_quoting (f->linkname))
        f->quoted = -1;

      /* Avoid following symbolic links when possible, i.e., when
         they won't be traced and when no indicator is needed.  */
      if (f->linkname           && (file_type <= indicator_style || check_symlink_mode)           && stat_for_mode (full_name, &linkstats) == 0)
        {
          f->linkok = true;
          f->linkmode = linkstats.st_mode;
        }
    }

  blocks = ((&f->stat)->st_blocks);
  if (format == long_format || print_block_size)
    {
      char buf[((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1];
      int len = gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (human_readable (blocks, buf, human_output_opts,                                           512, output_block_size),                           MBSWIDTH_FLAGS);
      if (block_size_width < len)
        block_size_width = len;
    }

  if (format == long_format)
    {
      if (print_owner)
        {
          int len = format_user_width (f->stat.st_uid);
          if (owner_width < len)
            owner_width = len;
        }

      if (print_group)
        {
          int len = format_group_width (f->stat.st_gid);
          if (group_width < len)
            group_width = len;
        }

      if (print_author)
        {
          int len = format_user_width (f->stat.st_author);
          if (author_width < len)
            author_width = len;
        }
    }

  if (print_scontext)
    {
      int len = strlen (f->scontext);
      if (scontext_width < len)
        scontext_width = len;
    }

  if (format == long_format)
    {
      char b[((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)];
      int b_len = strlen (umaxtostr (f->stat.st_nlink, b));
      if (nlink_width < b_len)
        nlink_width = b_len;

      if ((type == chardev) | (type == blockdev))
        {
          char buf[((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)];
          int len = strlen (umaxtostr ((((f->stat.st_rdev) >> 8) & 0xff), buf));
          if (major_device_number_width < len)
            major_device_number_width = len;
          len = strlen (umaxtostr (((f->stat.st_rdev) & 0xff), buf));
          if (minor_device_number_width < len)
            minor_device_number_width = len;
          len = major_device_number_width + 2 + minor_device_number_width;
          if (file_size_width < len)
            file_size_width = len;
        }
      else
        {
          char buf[((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1];
          uintmax_t size = unsigned_file_size (f->stat.st_size);
          int len = gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (human_readable (size, buf,                                               file_human_output_opts,                                               1, file_output_block_size),                               MBSWIDTH_FLAGS);
          if (file_size_width < len)
            file_size_width = len;
        }
    }

  if (print_inode)
    {
      char buf[((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)];
      int len = strlen (umaxtostr (f->stat.st_ino, buf));
      if (inode_number_width < len)
        inode_number_width = len;
    }

  f->name = xstrdup (name);
  cwd_n_used++;

  return blocks;
}

/* Return true if F refers to a directory.  */
static bool
is_directory (const struct fileinfo *f)
{
  return f->filetype == directory || f->filetype == arg_directory;
}

/* Return true if F refers to a (symlinked) directory.  */
static bool
is_linked_directory (const struct fileinfo *f)
{
  return f->filetype == directory || f->filetype == arg_directory
         || (((f->linkmode) & 0170000) == 0040000);
}

/* Put the name of the file that FILENAME is a symbolic link to
   into the LINKNAME field of 'f'.  COMMAND_LINE_ARG indicates whether
   FILENAME is a command-line argument.  */

static bool
get_link_name (char const *filename, struct fileinfo *f, bool command_line_arg)
{
  f->linkname = areadlink_with_size (filename, f->stat.st_size);
  if (f->linkname == 0)
    {
      if (! command_line_arg           && ignorable_traversal_errno (errno))
        return false;
      file_failure (command_line_arg, (const char *) {("cannot read symbolic link %s")},                     filename);
    }
  return true;
}

/* Return true if the last component of NAME is '.' or '..'
   This is so we don't try to recurse on '././././. ...' */

static bool
basename_is_dot_or_dotdot (char const *name)
{
  char const *base = last_component (name);
  return dot_or_dotdot (base);
}

/* Remove any entries from CWD_FILE that are for directories,
   and queue them to be listed as directories instead.
   DIRNAME is the prefix to prepend to each dirname
   to make it correct relative to ls's working dir;
   if it is null, no prefix is needed and "." and ".." should not be ignored.
   If COMMAND_LINE_ARG is true, this directory was mentioned at the top level,
   This is desirable when processing directories recursively.  */

static void
extract_dirs_from_files (char const *dirname, bool command_line_arg)
{
  idx_t i, j;
  bool ignore_dot_and_dot_dot = (dirname != 0);

  if (dirname && (!!active_dir_set))
    {
      /* Insert a marker entry first.  When we dequeue this marker entry,
         we'll know that DIRNAME has been processed and may be removed
         from the set of active directories.  */
      queue_directory (0, dirname, false);
    }

  /* Queue the directories last one first, because queueing reverses the
     order.  */
  for (i = cwd_n_used; 0 < i; )
    {
      i--;
      struct fileinfo *f = sorted_file[i];

      if (is_directory (f)           && (! ignore_dot_and_dot_dot               || ! basename_is_dot_or_dotdot (f->name)))
        {
          if (!dirname || f->name[0] == '/')
            queue_directory (f->name, f->linkname, command_line_arg);
          else
            {
              char *name = file_name_concat (dirname, f->name, 0);
              queue_directory (name, f->linkname, command_line_arg);
              free (name);
            }
          if (f->filetype == arg_directory)
            free_ent (f);
        }
    }

  /* Now delete the directories from the table, compacting all the remaining
     entries.  */

  for (i = 0, j = 0; i < cwd_n_used; i++)
    {
      struct fileinfo *f = sorted_file[i];
      sorted_file[j] = f;
      j += (f->filetype != arg_directory);
    }
  cwd_n_used = j;
}

/* Use strcoll to compare strings in this locale.  If an error occurs,
   report an error and longjmp to failed_strcoll.  */

static jmp_buf failed_strcoll;

static int
xstrcoll (char const *a, char const *b)
{
  int diff;
  errno = 0;
  diff = strcoll (a, b);
  if (errno)
    {
      error (0, errno, (const char *) {("cannot compare file names %s and %s")},              quote_n (0, a), quote_n (1, b));
      set_exit_status (false);
      longjmp (failed_strcoll, 1);
    }
  return diff;
}

/* Comparison routines for sorting the files.  */

typedef void const *V;

/* Used below in DEFINE_SORT_FUNCTIONS for _df_ sort function variants.  */
static int
dirfirst_check (struct fileinfo const *a, struct fileinfo const *b,                 int (*cmp) (V, V))
{
  int diff = is_linked_directory (b) - is_linked_directory (a);
  return diff ? diff : cmp (a, b);
}

/* Define the 8 different sort function variants required for each sortkey.
   KEY_NAME is a token describing the sort key, e.g., ctime, atime, size.
   KEY_CMP_FUNC is a function to compare records based on that key, e.g.,
   ctime_cmp, atime_cmp, size_cmp.  Append KEY_NAME to the string,
   '[rev_][x]str{cmp|coll}[_df]_', to create each function name.  */

static int
cmp_ctime (struct fileinfo const *a, struct fileinfo const *b,            int (*cmp) (char const *, char const *))
{
  int diff = timespec_cmp (get_stat_ctime (&b->stat),                            get_stat_ctime (&a->stat));
  return diff ? diff : cmp (a->name, b->name);
}

static int
cmp_mtime (struct fileinfo const *a, struct fileinfo const *b,            int (*cmp) (char const *, char const *))
{
  int diff = timespec_cmp (get_stat_mtime (&b->stat),                            get_stat_mtime (&a->stat));
  return diff ? diff : cmp (a->name, b->name);
}

static int
cmp_atime (struct fileinfo const *a, struct fileinfo const *b,            int (*cmp) (char const *, char const *))
{
  int diff = timespec_cmp (get_stat_atime (&b->stat),                            get_stat_atime (&a->stat));
  return diff ? diff : cmp (a->name, b->name);
}

static int
cmp_btime (struct fileinfo const *a, struct fileinfo const *b,            int (*cmp) (char const *, char const *))
{
  int diff = timespec_cmp (get_stat_btime (&b->stat),                            get_stat_btime (&a->stat));
  return diff ? diff : cmp (a->name, b->name);
}

static int
off_cmp (off_t a, off_t b)
{
  return _GL_CMP (a, b);
}

static int
cmp_size (struct fileinfo const *a, struct fileinfo const *b,           int (*cmp) (char const *, char const *))
{
  int diff = off_cmp (b->stat.st_size, a->stat.st_size);
  return diff ? diff : cmp (a->name, b->name);
}

static int
cmp_name (struct fileinfo const *a, struct fileinfo const *b,           int (*cmp) (char const *, char const *))
{
  return cmp (a->name, b->name);
}

/* Compare file extensions.  Files with no extension are 'smallest'.
   If extensions are the same, compare by file names instead.  */

static int
cmp_extension (struct fileinfo const *a, struct fileinfo const *b,                int (*cmp) (char const *, char const *))
{
  char const *base1 = strrchr (a->name, '.');
  char const *base2 = strrchr (b->name, '.');
  int diff = cmp (base1 ? base1 : "", base2 ? base2 : "");
  return diff ? diff : cmp (a->name, b->name);
}

/* Return the (cached) screen width,
   for the NAME associated with the passed fileinfo F.  */

static size_t
fileinfo_name_width (struct fileinfo const *f)
{
  return f->width
         ? f->width
         : quote_name_width (f->name, filename_quoting_options, f->quoted);
}

static int
cmp_width (struct fileinfo const *a, struct fileinfo const *b,           int (*cmp) (char const *, char const *))
{
  int diff = fileinfo_name_width (a) - fileinfo_name_width (b);
  return diff ? diff : cmp (a->name, b->name);
}

/* direct, non-dirfirst versions */					  static int xstrcoll_ctime (V a, V b)				  { return cmp_ctime (a, b, xstrcoll); }				   static int strcmp_ctime (V a, V b)		  { return cmp_ctime (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_ctime (V a, V b)				  { return cmp_ctime (b, a, xstrcoll); }				   static int rev_strcmp_ctime (V a, V b)	  { return cmp_ctime (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_ctime (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_ctime); }		   static int strcmp_df_ctime (V a, V b)		  { return dirfirst_check (a, b, strcmp_ctime); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_ctime (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_ctime); }		   static int rev_strcmp_df_ctime (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_ctime); }
/* direct, non-dirfirst versions */					  static int xstrcoll_mtime (V a, V b)				  { return cmp_mtime (a, b, xstrcoll); }				   static int strcmp_mtime (V a, V b)		  { return cmp_mtime (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_mtime (V a, V b)				  { return cmp_mtime (b, a, xstrcoll); }				   static int rev_strcmp_mtime (V a, V b)	  { return cmp_mtime (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_mtime (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_mtime); }		   static int strcmp_df_mtime (V a, V b)		  { return dirfirst_check (a, b, strcmp_mtime); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_mtime (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_mtime); }		   static int rev_strcmp_df_mtime (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_mtime); }
/* direct, non-dirfirst versions */					  static int xstrcoll_atime (V a, V b)				  { return cmp_atime (a, b, xstrcoll); }				   static int strcmp_atime (V a, V b)		  { return cmp_atime (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_atime (V a, V b)				  { return cmp_atime (b, a, xstrcoll); }				   static int rev_strcmp_atime (V a, V b)	  { return cmp_atime (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_atime (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_atime); }		   static int strcmp_df_atime (V a, V b)		  { return dirfirst_check (a, b, strcmp_atime); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_atime (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_atime); }		   static int rev_strcmp_df_atime (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_atime); }
/* direct, non-dirfirst versions */					  static int xstrcoll_btime (V a, V b)				  { return cmp_btime (a, b, xstrcoll); }				   static int strcmp_btime (V a, V b)		  { return cmp_btime (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_btime (V a, V b)				  { return cmp_btime (b, a, xstrcoll); }				   static int rev_strcmp_btime (V a, V b)	  { return cmp_btime (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_btime (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_btime); }		   static int strcmp_df_btime (V a, V b)		  { return dirfirst_check (a, b, strcmp_btime); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_btime (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_btime); }		   static int rev_strcmp_df_btime (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_btime); }
/* direct, non-dirfirst versions */					  static int xstrcoll_size (V a, V b)				  { return cmp_size (a, b, xstrcoll); }				   static int strcmp_size (V a, V b)		  { return cmp_size (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_size (V a, V b)				  { return cmp_size (b, a, xstrcoll); }				   static int rev_strcmp_size (V a, V b)	  { return cmp_size (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_size (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_size); }		   static int strcmp_df_size (V a, V b)		  { return dirfirst_check (a, b, strcmp_size); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_size (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_size); }		   static int rev_strcmp_df_size (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_size); }
/* direct, non-dirfirst versions */					  static int xstrcoll_name (V a, V b)				  { return cmp_name (a, b, xstrcoll); }				   static int strcmp_name (V a, V b)		  { return cmp_name (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_name (V a, V b)				  { return cmp_name (b, a, xstrcoll); }				   static int rev_strcmp_name (V a, V b)	  { return cmp_name (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_name (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_name); }		   static int strcmp_df_name (V a, V b)		  { return dirfirst_check (a, b, strcmp_name); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_name (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_name); }		   static int rev_strcmp_df_name (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_name); }
/* direct, non-dirfirst versions */					  static int xstrcoll_extension (V a, V b)				  { return cmp_extension (a, b, xstrcoll); }				   static int strcmp_extension (V a, V b)		  { return cmp_extension (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_extension (V a, V b)				  { return cmp_extension (b, a, xstrcoll); }				   static int rev_strcmp_extension (V a, V b)	  { return cmp_extension (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_extension (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_extension); }		   static int strcmp_df_extension (V a, V b)		  { return dirfirst_check (a, b, strcmp_extension); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_extension (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_extension); }		   static int rev_strcmp_df_extension (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_extension); }
/* direct, non-dirfirst versions */					  static int xstrcoll_width (V a, V b)				  { return cmp_width (a, b, xstrcoll); }				   static int strcmp_width (V a, V b)		  { return cmp_width (a, b, strcmp); }				                                                                          /* reverse, non-dirfirst versions */					  static int rev_xstrcoll_width (V a, V b)				  { return cmp_width (b, a, xstrcoll); }				   static int rev_strcmp_width (V a, V b)	  { return cmp_width (b, a, strcmp); }				                                                                          /* direct, dirfirst versions */					  static int xstrcoll_df_width (V a, V b)				  { return dirfirst_check (a, b, xstrcoll_width); }		   static int strcmp_df_width (V a, V b)		  { return dirfirst_check (a, b, strcmp_width); }			                                                                          /* reverse, dirfirst versions */					  static int rev_xstrcoll_df_width (V a, V b)			  { return dirfirst_check (a, b, rev_xstrcoll_width); }		   static int rev_strcmp_df_width (V a, V b)	  { return dirfirst_check (a, b, rev_strcmp_width); }

/* Compare file versions.
   Unlike the other compare functions, cmp_version does not fail
   because filevercmp and strcmp do not fail; cmp_version uses strcmp
   instead of xstrcoll because filevercmp is locale-independent so
   strcmp is its appropriate secondary.

   All the other sort options need xstrcoll and strcmp variants,
   because they all use xstrcoll (either as the primary or secondary
   sort key), and xstrcoll has the ability to do a longjmp if strcoll fails for
   locale reasons.  */
static int
cmp_version (struct fileinfo const *a, struct fileinfo const *b)
{
  int diff = filevercmp (a->name, b->name);
  return diff ? diff : strcmp (a->name, b->name);
}

static int
xstrcoll_version (V a, V b)
{
  return cmp_version (a, b);
}
static int
rev_xstrcoll_version (V a, V b)
{
  return cmp_version (b, a);
}
static int
xstrcoll_df_version (V a, V b)
{
  return dirfirst_check (a, b, xstrcoll_version);
}
static int
rev_xstrcoll_df_version (V a, V b)
{
  return dirfirst_check (a, b, rev_xstrcoll_version);
}


/* We have 2^3 different variants for each sort-key function
   (for 3 independent sort modes).
   The function pointers stored in this array must be dereferenced as:

    sort_variants[sort_key][use_strcmp][reverse][dirs_first]

   Note that the order in which sort keys are listed in the function pointer
   array below is defined by the order of the elements in the time_type and
   sort_type enums!  */


static qsortFunc const sort_functions[][2][2][2] =
  {
    {                                                                     {                                                                     { xstrcoll_name, xstrcoll_df_name },                    { rev_xstrcoll_name, rev_xstrcoll_df_name },          },                                                                  {                                                                     { strcmp_name, strcmp_df_name },                        { rev_strcmp_name, rev_strcmp_df_name },              }                                                                 },
    {                                                                     {                                                                     { xstrcoll_extension, xstrcoll_df_extension },                    { rev_xstrcoll_extension, rev_xstrcoll_df_extension },          },                                                                  {                                                                     { strcmp_extension, strcmp_df_extension },                        { rev_strcmp_extension, rev_strcmp_df_extension },              }                                                                 },
    {                                                                     {                                                                     { xstrcoll_width, xstrcoll_df_width },                    { rev_xstrcoll_width, rev_xstrcoll_df_width },          },                                                                  {                                                                     { strcmp_width, strcmp_df_width },                        { rev_strcmp_width, rev_strcmp_df_width },              }                                                                 },
    {                                                                     {                                                                     { xstrcoll_size, xstrcoll_df_size },                    { rev_xstrcoll_size, rev_xstrcoll_df_size },          },                                                                  {                                                                     { strcmp_size, strcmp_df_size },                        { rev_strcmp_size, rev_strcmp_df_size },              }                                                                 },

    {
      {
        { xstrcoll_version, xstrcoll_df_version },
        { rev_xstrcoll_version, rev_xstrcoll_df_version },
      },

      /* We use NULL for the strcmp variants of version comparison
         since as explained in cmp_version definition, version comparison
         does not rely on xstrcoll, so it will never longjmp, and never
         need to try the strcmp fallback. */
      {
        { 0, 0 },
        { 0, 0 },
      }
    },

    /* last are time sort functions */
    {                                                                     {                                                                     { xstrcoll_mtime, xstrcoll_df_mtime },                    { rev_xstrcoll_mtime, rev_xstrcoll_df_mtime },          },                                                                  {                                                                     { strcmp_mtime, strcmp_df_mtime },                        { rev_strcmp_mtime, rev_strcmp_df_mtime },              }                                                                 },
    {                                                                     {                                                                     { xstrcoll_ctime, xstrcoll_df_ctime },                    { rev_xstrcoll_ctime, rev_xstrcoll_df_ctime },          },                                                                  {                                                                     { strcmp_ctime, strcmp_df_ctime },                        { rev_strcmp_ctime, rev_strcmp_df_ctime },              }                                                                 },
    {                                                                     {                                                                     { xstrcoll_atime, xstrcoll_df_atime },                    { rev_xstrcoll_atime, rev_xstrcoll_df_atime },          },                                                                  {                                                                     { strcmp_atime, strcmp_df_atime },                        { rev_strcmp_atime, rev_strcmp_df_atime },              }                                                                 },
    {                                                                     {                                                                     { xstrcoll_btime, xstrcoll_df_btime },                    { rev_xstrcoll_btime, rev_xstrcoll_df_btime },          },                                                                  {                                                                     { strcmp_btime, strcmp_df_btime },                        { rev_strcmp_btime, rev_strcmp_df_btime },              }                                                                 }
  };

/* The number of sort keys is calculated as the sum of
     the number of elements in the sort_type enum (i.e., sort_numtypes)
     -2 because neither sort_time nor sort_none use entries themselves
     the number of elements in the time_type enum (i.e., time_numtypes)
   This is because when sort_type==sort_time, we have up to
   time_numtypes possible sort keys.

   This line verifies at compile-time that the array of sort functions has been
   initialized for all possible sort keys. */
static_assert (((size_t) (sizeof (sort_functions) / sizeof (sort_functions)[0]              + 0 * 0)) == sort_numtypes - 2 + time_numtypes);

/* Set up SORTED_FILE to point to the in-use entries in CWD_FILE, in order.  */

static void
initialize_ordering_vector (void)
{
  for (idx_t i = 0; i < cwd_n_used; i++)
    sorted_file[i] = &cwd_file[i];
}

/* Cache values based on attributes global to all files.  */

static void
update_current_files_info (void)
{
  /* Cache screen width of name, if needed multiple times.  */
  if (sort_type == sort_width       || (line_length && (format == many_per_line || format == horizontal)))
    {
      for (idx_t i = 0; i < cwd_n_used; i++)
        {
          struct fileinfo *f = sorted_file[i];
          f->width = fileinfo_name_width (f);
        }
    }
}

/* Sort the files now in the table.  */

static void
sort_files (void)
{
  bool use_strcmp;

  if (sorted_file_alloc < cwd_n_used + (cwd_n_used >> 1))
    {
      free (sorted_file);
      sorted_file = xinmalloc (cwd_n_used, 3 * sizeof *sorted_file);
      sorted_file_alloc = 3 * cwd_n_used;
    }

  initialize_ordering_vector ();

  update_current_files_info ();

  if (sort_type == sort_none)
    return;

  /* Try strcoll.  If it fails, fall back on strcmp.  We can't safely
     ignore strcoll failures, as a failing strcoll might be a
     comparison function that is not a total order, and if we ignored
     the failure this might cause qsort to dump core.  */

  if (! setjmp (failed_strcoll))
    use_strcmp = false;      /* strcoll() succeeded */
  else
    {
      use_strcmp = true;
      ((sort_type != sort_version) ? (void)0 : abort());
      initialize_ordering_vector ();
    }

  /* When sort_type == sort_time, use time_type as subindex.  */
  mpsort ((void const **) sorted_file, cwd_n_used,           sort_functions[sort_type + (sort_type == sort_time ? time_type : 0)]                         [use_strcmp][sort_reverse]                         [directories_first]);
}

/* List all the files now in the table.  */

static void
print_current_files (void)
{
  switch (format)
    {
    case one_per_line:
      for (idx_t i = 0; i < cwd_n_used; i++)
        {
          print_file_name_and_frills (sorted_file[i], 0);
          putchar (eolbyte);
        }
      break;

    case many_per_line:
      if (! line_length)
        print_with_separator (' ');
      else
        print_many_per_line ();
      break;

    case horizontal:
      if (! line_length)
        print_with_separator (' ');
      else
        print_horizontal ();
      break;

    case with_commas:
      print_with_separator (',');
      break;

    case long_format:
      for (idx_t i = 0; i < cwd_n_used; i++)
        {
          set_normal_color ();
          print_long_format (sorted_file[i]);
          dired_outbyte (eolbyte);
        }
      break;
    }
}

/* Replace the first %b with precomputed aligned month names.
   Note on glibc-2.7 at least, this speeds up the whole 'ls -lU'
   process by around 17%, compared to letting strftime() handle the %b.  */

static ptrdiff_t
align_nstrftime (char *buf, size_t size, bool recent, struct tm const *tm,                  timezone_t tz, int ns)
{
  char const *nfmt = (use_abformat                       ? abformat[recent][tm->tm_mon]                       : long_time_format[recent]);
  return nstrftime (buf, size, nfmt, tm, tz, ns);
}

/* Return the expected number of columns in a long-format timestamp,
   or zero if it cannot be calculated.  */

static int
long_time_expected_width (void)
{
  static int width = -1;

  if (width < 0)
    {
      time_t epoch = 0;
      struct tm tm;
      char buf[TIME_STAMP_LEN_MAXIMUM + 1];

      /* In case you're wondering if localtime_rz can fail with an input time_t
         value of 0, let's just say it's very unlikely, but not inconceivable.
         The TZ environment variable would have to specify a time zone that
         is 2**31-1900 years or more ahead of UTC.  This could happen only on
         a 64-bit system that blindly accepts e.g., TZ=UTC+20000000000000.
         However, this is not possible with Solaris 10 or glibc-2.3.5, since
         their implementations limit the offset to 167:59 and 24:00, resp.  */
      if (localtime_rz (localtz, &epoch, &tm))
        {
          ptrdiff_t len = align_nstrftime (buf, sizeof buf, false,                                            &tm, localtz, 0);
          if (len > 0)
            width = mbsnwidth (buf, len, MBSWIDTH_FLAGS);
        }

      if (width < 0)
        width = 0;
    }

  return width;
}

/* Print the user or group name NAME, with numeric id ID, using a
   print width of WIDTH columns.  */

static void
format_user_or_group (char const *name, uintmax_t id, int width)
{
  if (name)
    {
      int name_width = gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (name, MBSWIDTH_FLAGS);
      int width_gap = name_width < 0 ? 0 : width - name_width;
      int pad = ((0) > (width_gap) ? (0) : (width_gap));
      dired_outstring (name);

      do
        dired_outbyte (' ');
      while (pad--);
    }
  else
    dired_pos += printf ("%*ju ", width, id);
}

/* Print the name or id of the user with id U, using a print width of
   WIDTH.  */

static void
format_user (uid_t u, int width, bool stat_ok)
{
  format_user_or_group (! stat_ok ? "?" :                         (numeric_ids ? 0 : getuser (u)), u, width);
}

/* Likewise, for groups.  */

static void
format_group (gid_t g, int width, bool stat_ok)
{
  format_user_or_group (! stat_ok ? "?" :                         (numeric_ids ? 0 : getgroup (g)), g, width);
}

/* Return the number of columns that format_user_or_group will print,
   or -1 if unknown.  */

static int
format_user_or_group_width (char const *name, uintmax_t id)
{
  return (name           ? gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (name, MBSWIDTH_FLAGS)           : snprintf (0, 0, "%ju", id));
}

/* Return the number of columns that format_user will print,
   or -1 if unknown.  */

static int
format_user_width (uid_t u)
{
  return format_user_or_group_width (numeric_ids ? 0 : getuser (u), u);
}

/* Likewise, for groups.  */

static int
format_group_width (gid_t g)
{
  return format_user_or_group_width (numeric_ids ? 0 : getgroup (g), g);
}

/* Return a pointer to a formatted version of F->stat.st_ino,
   possibly using buffer, which must be at least
   INT_BUFSIZE_BOUND (uintmax_t) bytes.  */
static char *
format_inode (char buf[((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)],               const struct fileinfo *f)
{
  return (f->stat_ok && f->stat.st_ino != NOT_AN_INODE_NUMBER           ? umaxtostr (f->stat.st_ino, buf)           : (char *) "?");
}

/* Print information about F in long format.  */
static void
print_long_format (const struct fileinfo *f)
{
  char modebuf[12];
  char buf
    [((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1		/* inode */
     + ((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1	/* size in blocks */
     + sizeof (modebuf) - 1 + 1		/* mode string */
     + ((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)	/* st_nlink */
     + ((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 2	/* major device number */
     + ((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1	/* minor device number */
     + TIME_STAMP_LEN_MAXIMUM + 1	/* max length of time/date */
     ];
  ptrdiff_t s;
  char *p;
  struct timespec when_timespec;
  struct tm when_local;
  bool btime_ok = true;

  /* Compute the mode string, except remove the trailing space if no
     file in this directory has an ACL or security context.  */
  if (f->stat_ok)
    filemodestring (&f->stat, modebuf);
  else
    {
      modebuf[0] = filetype_letter[f->filetype];
      memset (modebuf + 1, '?', 10);
      modebuf[11] = '\0';
    }
  if (! any_has_acl)
    modebuf[10] = '\0';
  else if (f->acl_type == ACL_T_LSM_CONTEXT_ONLY)
    modebuf[10] = '.';
  else if (f->acl_type == ACL_T_YES)
    modebuf[10] = '+';
  else if (f->acl_type == ACL_T_UNKNOWN)
    modebuf[10] = '?';

  switch (time_type)
    {
    case time_ctime:
      when_timespec = get_stat_ctime (&f->stat);
      break;
    case time_mtime:
      when_timespec = get_stat_mtime (&f->stat);
      break;
    case time_atime:
      when_timespec = get_stat_atime (&f->stat);
      break;
    case time_btime:
      when_timespec = get_stat_btime (&f->stat);
      if (when_timespec.tv_sec == -1 && when_timespec.tv_nsec == -1)
        btime_ok = false;
      break;
    case time_numtypes: default:
      unreachable ();
    }

  p = buf;

  if (print_inode)
    {
      char hbuf[((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)];
      p += sprintf (p, "%*s ", inode_number_width, format_inode (hbuf, f));
    }

  if (print_block_size)
    {
      char hbuf[((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1];
      char const *blocks =
        (! f->stat_ok          ? "?"          : human_readable (((&f->stat)->st_blocks), hbuf, human_output_opts,                            512, output_block_size));
      int blocks_width = gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (blocks, MBSWIDTH_FLAGS);
      for (int pad = blocks_width < 0 ? 0 : block_size_width - blocks_width;            0 < pad; pad--)
        *p++ = ' ';
      while ((*p++ = *blocks++))
        continue;
      p[-1] = ' ';
    }

  /* The last byte of the mode string is the POSIX
     "optional alternate access method flag".  */
  {
    char hbuf[((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)];
    p += sprintf (p, "%s %*s ", modebuf, nlink_width,                   ! f->stat_ok ? "?" : umaxtostr (f->stat.st_nlink, hbuf));
  }

  dired_indent ();

  if (print_owner || print_group || print_author || print_scontext)
    {
      dired_outbuf (buf, p - buf);

      if (print_owner)
        format_user (f->stat.st_uid, owner_width, f->stat_ok);

      if (print_group)
        format_group (f->stat.st_gid, group_width, f->stat_ok);

      if (print_author)
        format_user (f->stat.st_author, author_width, f->stat_ok);

      if (print_scontext)
        format_user_or_group (f->scontext, 0, scontext_width);

      p = buf;
    }

  if (f->stat_ok       && (S_ISCHR (f->stat.st_mode) || S_ISBLK (f->stat.st_mode)))
    {
      int blanks_width = (file_size_width                           - (major_device_number_width + 2                              + minor_device_number_width));
      p += sprintf (p, "%*ju, %*ju ",                     major_device_number_width + ((0) > (blanks_width) ? (0) : (blanks_width)),                     (uintmax_t) (((f->stat.st_rdev) >> 8) & 0xff),                     minor_device_number_width,                     (uintmax_t) ((f->stat.st_rdev) & 0xff));
    }
  else
    {
      char hbuf[((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1];
      char const *size =
        (! f->stat_ok          ? "?"          : human_readable (unsigned_file_size (f->stat.st_size),                            hbuf, file_human_output_opts, 1,                            file_output_block_size));
      int size_width = gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (size, MBSWIDTH_FLAGS);
      for (int pad = size_width < 0 ? 0 : file_size_width - size_width;            0 < pad; pad--)
        *p++ = ' ';
      while ((*p++ = *size++))
        continue;
      p[-1] = ' ';
    }

  s = -1;

  if (f->stat_ok && btime_ok       && localtime_rz (localtz, &when_timespec.tv_sec, &when_local))
    {
      struct timespec six_months_ago;
      bool recent;

      /* If the file appears to be in the future, update the current
         time, in case the file happens to have been modified since
         the last time we checked the clock.  */
      if (timespec_cmp (current_time, when_timespec) < 0)
        gettime (&current_time);

      /* Consider a time to be recent if it is within the past six months.
         A Gregorian year has 365.2425 * 24 * 60 * 60 == 31556952 seconds
         on the average.  Write this value as an integer constant to
         avoid floating point hassles.  */
      six_months_ago.tv_sec = current_time.tv_sec - 31556952 / 2;
      six_months_ago.tv_nsec = current_time.tv_nsec;

      recent = (timespec_cmp (six_months_ago, when_timespec) < 0                 && timespec_cmp (when_timespec, current_time) < 0);

      /* We assume here that all time zones are offset from UTC by a
         whole number of seconds.  */
      s = align_nstrftime (p, TIME_STAMP_LEN_MAXIMUM + 1, recent,                            &when_local, localtz, when_timespec.tv_nsec);
    }

  if (0 <= s)
    {
      p += s;
      *p++ = ' ';
    }
  else
    {
      /* The time cannot be converted using the desired format, so
         print it as a huge integer number of seconds.  */
      char hbuf[((((((sizeof (intmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)];
      p += sprintf (p, "%*s ", long_time_expected_width (),                     (! f->stat_ok || ! btime_ok                      ? "?"                      : timetostr (when_timespec.tv_sec, hbuf)));
      /* FIXME: (maybe) We discarded when_timespec.tv_nsec. */
    }

  dired_outbuf (buf, p - buf);
  size_t w = print_name_with_quoting (f, false, &dired_obstack, p - buf);

  if (f->filetype == symbolic_link)
    {
      if (f->linkname)
        {
          dired_outstring (" -> ");
          print_name_with_quoting (f, true, 0, (p - buf) + w + 4);
          if (indicator_style != none)
            print_type_indicator (true, f->linkmode, unknown);
        }
    }
  else if (indicator_style != none)
    print_type_indicator (f->stat_ok, f->stat.st_mode, f->filetype);
}

/* Write to *BUF a quoted representation of the file name NAME, if non-null,
   using OPTIONS to control quoting.  *BUF is set to NAME if no quoting
   is required.  *BUF is allocated if more space required (and the original
   *BUF is not deallocated).
   Store the number of screen columns occupied by NAME's quoted
   representation into WIDTH, if non-null.
   Store into PAD whether an initial space is needed for padding.
   Return the number of bytes in *BUF.  */

static size_t
quote_name_buf (char **inbuf, size_t bufsize, char *name,                 struct quoting_options const *options,                 int needs_general_quoting, size_t *width, bool *pad)
{
  char *buf = *inbuf;
  size_t displayed_width /* empty */;
  size_t len = 0;
  bool quoted;

  enum quoting_style qs = get_quoting_style (options);
  bool partial_quoting = qs == shell_quoting_style
                         || qs == shell_always_quoting_style
                         || qs == literal_quoting_style;
  bool needs_further_quoting = qmark_funny_chars && partial_quoting;

  /* Note we provide extra protection only for newline separators.
     I.e., we don't bother protecting "double space" or "comma space"
     separated entries, as for interactive output, shell escape quoting
     is best to disambiguate, and for programmatic, --zero is best.
     Extra processing to mark ', ' and '  ' would be overkill
     as interactively there will still be ambiguities with multi-byte spaces,
     and marked characters impact programmatic processing anyway.  */
  bool extra_newline_protection = (!needs_further_quoting                                    && qmark_newline && partial_quoting                                    && !dired && strchr (name, '\n'));

  if (needs_general_quoting != 0)
    {
      len = quotearg_buffer (buf, bufsize, name, -1, options);
      if (bufsize <= len)
        {
          buf = xmalloc (len + 1);
          quotearg_buffer (buf, len + 1, name, -1, options);
        }

      quoted = (*name != *buf) || strlen (name) != len;
    }
  else if (needs_further_quoting || extra_newline_protection)
    {
      len = strlen (name);
      if (bufsize <= len)
        buf = xmalloc (len + 1);
      memcpy (buf, name, len + 1);

      quoted = false;
    }
  else
    {
      len = strlen (name);
      buf = name;
      quoted = false;
    }

  /* It's safe to replace newlines without multi-byte iteration, as newlines
     do not appear as part of any multi-byte encoded character.  */
  if (extra_newline_protection)
    for (char *p = buf; p < buf + len; p++)
      if (eolbyte && *p == '\n')
        *p = '?';

  if (needs_further_quoting)
    {
      if (MB_CUR_MAX > 1)
        {
          char const *p = buf;
          char const *plimit = buf + len;
          char *q = buf;
          displayed_width = 0;

          while (p < plimit)
            switch (*p)
              {
                case ' ': case '!': case '"': case '#': case '%':
                case '&': case '\'': case '(': case ')': case '*':
                case '+': case ',': case '-': case '.': case '/':
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                case ':': case ';': case '<': case '=': case '>':
                case '?':
                case 'A': case 'B': case 'C': case 'D': case 'E':
                case 'F': case 'G': case 'H': case 'I': case 'J':
                case 'K': case 'L': case 'M': case 'N': case 'O':
                case 'P': case 'Q': case 'R': case 'S': case 'T':
                case 'U': case 'V': case 'W': case 'X': case 'Y':
                case 'Z':
                case '[': case '\\': case ']': case '^': case '@GUARD_PREFIX@_STDCOUNTOF_H':
                case 'a': case 'b': case 'c': case 'd': case 'e':
                case 'f': case 'g': case 'h': case 'i': case 'j':
                case 'k': case 'l': case 'm': case 'n': case 'o':
                case 'p': case 'q': case 'r': case 's': case 't':
                case 'u': case 'v': case 'w': case 'x': case 'y':
                case 'z': case '{': case '|': case '}': case '~':
                  /* These characters are printable ASCII characters.  */
                  *q++ = *p++;
                  displayed_width += 1;
                  break;
                default:
                  /* If we have a multibyte sequence, copy it until we
                     reach its end, replacing each non-printable multibyte
                     character with a single question mark.  */
                  {
                    mbstate_t mbstate; mbszero (&mbstate);
                    do
                      {
                        char32_t wc;
                        size_t bytes;
                        int w;

                        bytes = mbrtoc32 (&wc, p, plimit - p, &mbstate);

                        if (bytes == (size_t) -1)
                          {
                            /* An invalid multibyte sequence was
                               encountered.  Skip one input byte, and
                               put a question mark.  */
                            p++;
                            *q++ = '?';
                            displayed_width += 1;
                            break;
                          }

                        if (bytes == (size_t) -2)
                          {
                            /* An incomplete multibyte character
                               at the end.  Replace it entirely with
                               a question mark.  */
                            p = plimit;
                            *q++ = '?';
                            displayed_width += 1;
                            break;
                          }

                        if (bytes == 0)
                          /* A null wide character was encountered.  */
                          bytes = 1;

                        w = c32width (wc);
                        if (w >= 0)
                          {
                            /* A printable multibyte character.
                               Keep it.  */
                            for (; bytes > 0; --bytes)
                              *q++ = *p++;
                            displayed_width += w;
                          }
                        else
                          {
                            /* An nonprintable multibyte character.
                               Replace it entirely with a question
                               mark.  */
                            p += bytes;
                            *q++ = '?';
                            displayed_width += 1;
                          }
                      }
                    while (! mbsinit (&mbstate));
                  }
                  break;
              }

          /* The buffer may have shrunk.  */
          len = q - buf;
        }
      else
        {
          char *p = buf;
          char const *plimit = buf + len;

          while (p < plimit)
            {
              if (! isprint (to_uchar (*p)))
                *p = '?';
              p++;
            }
          displayed_width = len;
        }
    }
  else if (width != 0)
    {
      if (MB_CUR_MAX > 1)
        {
          displayed_width = mbsnwidth (buf, len, MBSWIDTH_FLAGS);
          displayed_width = ((0) > (displayed_width) ? (0) : (displayed_width));
        }
      else
        {
          char const *p = buf;
          char const *plimit = buf + len;

          displayed_width = 0;
          while (p < plimit)
            {
              if (isprint (to_uchar (*p)))
                displayed_width++;
              p++;
            }
        }
    }

  /* Set padding to better align quoted items,
     and also give a visual indication that quotes are
     not actually part of the name.  */
  *pad = (align_variable_outer_quotes && cwd_some_quoted && ! quoted);

  if (width != 0)
    *width = displayed_width;

  *inbuf = buf;

  return len;
}

static size_t
quote_name_width (char const *name, struct quoting_options const *options,                   int needs_general_quoting)
{
  char smallbuf[BUFSIZ];
  char *buf = smallbuf;
  size_t width;
  bool pad;

  quote_name_buf (&buf, sizeof smallbuf, (char *) name, options,                   needs_general_quoting, &width, &pad);

  if (buf != smallbuf && buf != name)
    free (buf);

  width += pad;

  return width;
}

/* %XX escape any input out of range as defined in RFC3986,
   and also if PATH, convert all path separators to '/'.  */
static char *
file_escape (char const *str, bool path)
{
  char *esc = xnmalloc (3, strlen (str) + 1);
  char *p = esc;
  while (*str)
    {
      if (path && ((*str) == '/'))
        {
          *p++ = '/';
          str++;
        }
      else if (RFC3986[to_uchar (*str)])
        *p++ = *str++;
      else
        p += sprintf (p, "%%%02x", to_uchar (*str++));
    }
  *p = '\0';
  return esc;
}

static size_t
quote_name (char const *name, struct quoting_options const *options,             int needs_general_quoting, const struct bin_str *color,             bool allow_pad, struct obstack *stack, char const *absolute_name)
{
  char smallbuf[BUFSIZ];
  char *buf = smallbuf;
  size_t len;
  bool pad;

  len = quote_name_buf (&buf, sizeof smallbuf, (char *) name, options,                         needs_general_quoting, 0, &pad);

  if (pad && allow_pad)
    dired_outbyte (' ');

  if (color)
    print_color_indicator (color);

  /* If we're padding, then don't include the outer quotes in
     the --hyperlink, to improve the alignment of those links.  */
  bool skip_quotes = false;

  if (absolute_name)
    {
      if (align_variable_outer_quotes && cwd_some_quoted && ! pad)
        {
          skip_quotes = true;
          putchar (*buf);
        }
      char *h = file_escape (hostname, /* path= */ false);
      char *n = file_escape (absolute_name, /* path= */ true);
      /* TODO: It would be good to be able to define parameters
         to give hints to the terminal as how best to render the URI.
         For example since ls is outputting a dense block of URIs
         it would be best to not underline by default, and only
         do so upon hover etc.  */
      printf ("\033]8;;file://%s%s%s\033\\", h, *n == '/' ? "" : "/", n);
      free (h);
      free (n);
    }

  if (stack)
    push_current_dired_pos (stack);

  fwrite (buf + skip_quotes, 1, len - (skip_quotes * 2), stdout);

  dired_pos += len;

  if (stack)
    push_current_dired_pos (stack);

  if (absolute_name)
    {
      fputs ("\033]8;;\033\\", stdout);
      if (skip_quotes)
        putchar (*(buf + len - 1));
    }

  if (buf != smallbuf && buf != name)
    free (buf);

  return len + pad;
}

static size_t
print_name_with_quoting (const struct fileinfo *f,                          bool symlink_target,                          struct obstack *stack,                          size_t start_col)
{
  char const *name = symlink_target ? f->linkname : f->name;

  const struct bin_str *color
    = print_with_color ? get_color_indicator (f, symlink_target) : 0;

  bool used_color_this_time = (print_with_color                                && (color || is_colored (C_NORM)));

  size_t len = quote_name (name, filename_quoting_options, f->quoted,                            color, !symlink_target, stack, f->absolute_name);

  process_signals ();
  if (used_color_this_time)
    {
      prep_non_filename_text ();

      /* We use the byte length rather than display width here as
         an optimization to avoid accurately calculating the width,
         because we only output the clear to EOL sequence if the name
         _might_ wrap to the next line.  This may output a sequence
         unnecessarily in multi-byte locales for example,
         but in that case it's inconsequential to the output.  */
      if (line_length           && (start_col / line_length != (start_col + len - 1) / line_length))
        put_indicator (&color_indicator[C_CLR_TO_EOL]);
    }

  return len;
}

static void
prep_non_filename_text (void)
{
  if (color_indicator[C_END].string != 0)
    put_indicator (&color_indicator[C_END]);
  else
    {
      put_indicator (&color_indicator[C_LEFT]);
      put_indicator (&color_indicator[C_RESET]);
      put_indicator (&color_indicator[C_RIGHT]);
    }
}

/* Print the file name of 'f' with appropriate quoting.
   Also print file size, inode number, and filetype indicator character,
   as requested by switches.  */

static size_t
print_file_name_and_frills (const struct fileinfo *f, size_t start_col)
{
  char buf[((((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1) > (((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)) ? (((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1) : (((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)))];

  set_normal_color ();

  if (print_inode)
    printf ("%*s ", format == with_commas ? 0 : inode_number_width,             format_inode (buf, f));

  if (print_block_size)
    {
      char const *blocks =
        (! f->stat_ok          ? "?"          : human_readable (((&f->stat)->st_blocks), buf, human_output_opts,                            512, output_block_size));
      int blocks_width = gnu_mbswidth  /* avoid clash with UnixWare 7.1.1 function */ (blocks, MBSWIDTH_FLAGS);
      int pad = 0;
      if (0 <= blocks_width && block_size_width && format != with_commas)
        pad = block_size_width - blocks_width;
      printf ("%*s%s ", pad, "", blocks);
    }

  if (print_scontext)
    printf ("%*s ", format == with_commas ? 0 : scontext_width, f->scontext);

  size_t width = print_name_with_quoting (f, false, 0, start_col);

  if (indicator_style != none)
    width += print_type_indicator (f->stat_ok, f->stat.st_mode, f->filetype);

  return width;
}

/* Given these arguments describing a file, return the single-byte
   type indicator, or 0.  */
static char
get_type_indicator (bool stat_ok, mode_t mode, enum filetype type)
{
  char c;

  if (stat_ok ? (((mode) & 0170000) == 0100000) : type == normal)
    {
      if (stat_ok && indicator_style == classify && (mode & S_IXUGO))
        c = '*';
      else
        c = 0;
    }
  else
    {
      if (stat_ok ? (((mode) & 0170000) == 0040000) : type == directory || type == arg_directory)
        c = '/';
      else if (indicator_style == slash)
        c = 0;
      else if (stat_ok ? S_ISLNK (mode) : type == symbolic_link)
        c = '@';
      else if (stat_ok ? S_ISFIFO (mode) : type == fifo)
        c = '|';
      else if (stat_ok ? S_ISSOCK (mode) : type == sock)
        c = '=';
      else if (stat_ok && S_ISDOOR (mode))
        c = '>';
      else
        c = 0;
    }
  return c;
}

static bool
print_type_indicator (bool stat_ok, mode_t mode, enum filetype type)
{
  char c = get_type_indicator (stat_ok, mode, type);
  if (c)
    dired_outbyte (c);
  return !!c;
}

/* Returns if color sequence was printed.  */
static bool
print_color_indicator (const struct bin_str *ind)
{
  if (ind)
    {
      /* Need to reset so not dealing with attribute combinations */
      if (is_colored (C_NORM))
        restore_default_color ();
      put_indicator (&color_indicator[C_LEFT]);
      put_indicator (ind);
      put_indicator (&color_indicator[C_RIGHT]);
    }

  return ind != 0;
}

/* Returns color indicator or NULL if none.  */

static const struct bin_str *
get_color_indicator (const struct fileinfo *f, bool symlink_target)
{
  enum indicator_no type;
  struct color_ext_type *ext;	/* Color extension */
  size_t len;			/* Length of name */

  char const *name;
  mode_t mode;
  int linkok;
  if (symlink_target)
    {
      name = f->linkname;
      mode = f->linkmode;
      linkok = f->linkok ? 0 : -1;
    }
  else
    {
      name = f->name;
      mode = file_or_link_mode (f);
      linkok = f->linkok;
    }

  /* Is this a nonexistent file?  If so, linkok == -1.  */

  if (linkok == -1 && is_colored (C_MISSING))
    type = C_MISSING;
  else if (!f->stat_ok)
    {
      static enum indicator_no const filetype_indicator[] =
        {
          C_ORPHAN, C_FIFO, C_CHR, C_DIR, C_BLK, C_FILE,
          C_LINK, C_SOCK, C_FILE, C_DIR
        };
      static_assert (((size_t) (sizeof (filetype_indicator) / sizeof (filetype_indicator)[0]              + 0 * 0)) == filetype_cardinality);
      type = filetype_indicator[f->filetype];
    }
  else
    {
      if ((((mode) & 0170000) == 0100000))
        {
          type = C_FILE;

          if ((mode & S_ISUID) != 0 && is_colored (C_SETUID))
            type = C_SETUID;
          else if ((mode & S_ISGID) != 0 && is_colored (C_SETGID))
            type = C_SETGID;
          else if (f->has_capability)
            type = C_CAP;
          else if ((mode & S_IXUGO) != 0 && is_colored (C_EXEC))
            type = C_EXEC;
          else if ((1 < f->stat.st_nlink) && is_colored (C_MULTIHARDLINK))
            type = C_MULTIHARDLINK;
        }
      else if ((((mode) & 0170000) == 0040000))
        {
          type = C_DIR;

          if ((mode & S_ISVTX) && (mode & S_IWOTH)               && is_colored (C_STICKY_OTHER_WRITABLE))
            type = C_STICKY_OTHER_WRITABLE;
          else if ((mode & S_IWOTH) != 0 && is_colored (C_OTHER_WRITABLE))
            type = C_OTHER_WRITABLE;
          else if ((mode & S_ISVTX) != 0 && is_colored (C_STICKY))
            type = C_STICKY;
        }
      else if (S_ISLNK (mode))
        type = C_LINK;
      else if (S_ISFIFO (mode))
        type = C_FIFO;
      else if (S_ISSOCK (mode))
        type = C_SOCK;
      else if (S_ISBLK (mode))
        type = C_BLK;
      else if (S_ISCHR (mode))
        type = C_CHR;
      else if (S_ISDOOR (mode))
        type = C_DOOR;
      else
        {
          /* Classify a file of some other type as C_ORPHAN.  */
          type = C_ORPHAN;
        }
    }

  /* Check the file's suffix only if still classified as C_FILE.  */
  ext = 0;
  if (type == C_FILE)
    {
      /* Test if NAME has a recognized suffix.  */

      len = strlen (name);
      name += len;		/* Pointer to final \0.  */
      for (ext = color_ext_list; ext != 0; ext = ext->next)
        {
          if (ext->ext.len <= len)
            {
              if (ext->exact_match)
                {
                  if ((strncmp (name - ext->ext.len, ext->ext.string, ext->ext.len) == 0) /* ext->ext.len==-1 means unbounded */)
                    break;
                }
              else
                {
                  if (c_strncasecmp (name - ext->ext.len, ext->ext.string,                                      ext->ext.len) == 0)
                    break;
                }
            }
        }
    }

  /* Adjust the color for orphaned symlinks.  */
  if (type == C_LINK && !linkok)
    {
      if (color_symlink_as_referent || is_colored (C_ORPHAN))
        type = C_ORPHAN;
    }

  const struct bin_str *const s
    = ext ? &(ext->seq) : &color_indicator[type];

  return s->string ? s : 0;
}

/* Output a color indicator (which may contain nulls).
   Note we don't update dired_pos here as emacs can be configured
   to handle color codes by stripping/converting them.  */
static void
put_indicator (const struct bin_str *ind)
{
  if (! used_color)
    {
      used_color = true;

      /* If the standard output is a controlling terminal, watch out
         for signals, so that the colors can be restored to the
         default state if "ls" is suspended or interrupted.  */

      if (0 <= tcgetpgrp (1))
        signal_init ();

      prep_non_filename_text ();
    }

  fwrite (ind->string, ind->len, 1, stdout);
}

static size_t
length_of_file_name_and_frills (const struct fileinfo *f)
{
  size_t len = 0;
  char buf[((((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1) > (((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)) ? (((2 * sizeof (uintmax_t) * 8 * 146 / 485 + 1) * (MB_LEN_MAX + 1)    - MB_LEN_MAX + 1 + 3) + 1) : (((((((sizeof (uintmax_t) * 8) - 1) * 146 + 484) / 485)    + 1) + 1)))];

  if (print_inode)
    len += 1 + (format == with_commas                 ? strlen (umaxtostr (f->stat.st_ino, buf))                 : inode_number_width);

  if (print_block_size)
    len += 1 + (format == with_commas                 ? strlen (! f->stat_ok ? "?"                           : human_readable (((&f->stat)->st_blocks), buf,                                             human_output_opts, 512,                                             output_block_size))                 : block_size_width);

  if (print_scontext)
    len += 1 + (format == with_commas ? strlen (f->scontext) : scontext_width);

  len += fileinfo_name_width (f);

  if (indicator_style != none)
    {
      char c = get_type_indicator (f->stat_ok, f->stat.st_mode, f->filetype);
      len += (c != 0);
    }

  return len;
}

static void
print_many_per_line (void)
{
  idx_t cols = calculate_columns (true);
  struct column_info const *line_fmt = &column_info[cols - 1];

  /* Calculate the number of rows that will be in each column except possibly
     for a short column on the right.  */
  idx_t rows = cwd_n_used / cols + (cwd_n_used % cols != 0);

  for (idx_t row = 0; row < rows; row++)
    {
      size_t col = 0;
      idx_t filesno = row;
      size_t pos = 0;

      /* Print the next row.  */
      while (true)
        {
          struct fileinfo const *f = sorted_file[filesno];
          size_t name_length = length_of_file_name_and_frills (f);
          size_t max_name_length = line_fmt->col_arr[col++];
          print_file_name_and_frills (f, pos);

          if (cwd_n_used - rows <= filesno)
            break;
          filesno += rows;

          indent (pos + name_length, pos + max_name_length);
          pos += max_name_length;
        }
      putchar (eolbyte);
    }
}

static void
print_horizontal (void)
{
  size_t pos = 0;
  idx_t cols = calculate_columns (false);
  struct column_info const *line_fmt = &column_info[cols - 1];
  struct fileinfo const *f = sorted_file[0];
  size_t name_length = length_of_file_name_and_frills (f);
  size_t max_name_length = line_fmt->col_arr[0];

  /* Print first entry.  */
  print_file_name_and_frills (f, 0);

  /* Now the rest.  */
  for (idx_t filesno = 1; filesno < cwd_n_used; filesno++)
    {
      idx_t col = filesno % cols;

      if (col == 0)
        {
          putchar (eolbyte);
          pos = 0;
        }
      else
        {
          indent (pos + name_length, pos + max_name_length);
          pos += max_name_length;
        }

      f = sorted_file[filesno];
      print_file_name_and_frills (f, pos);

      name_length = length_of_file_name_and_frills (f);
      max_name_length = line_fmt->col_arr[col];
    }
  putchar (eolbyte);
}

/* Output name + SEP + ' '.  */

static void
print_with_separator (char sep)
{
  size_t pos = 0;

  for (idx_t filesno = 0; filesno < cwd_n_used; filesno++)
    {
      struct fileinfo const *f = sorted_file[filesno];
      size_t len = line_length ? length_of_file_name_and_frills (f) : 0;

      if (filesno != 0)
        {
          char separator;
          size_t next_pos = 2 + (sep == ',' && filesno < cwd_n_used - 1);

          if (! line_length               || (! ckd_add (&next_pos, next_pos, pos)                   && ! ckd_add (&next_pos, next_pos, len)                   && next_pos <= line_length))
            {
              pos += 2;
              separator = ' ';
            }
          else
            {
              pos = 0;
              separator = eolbyte;
            }

          putchar (sep);
          putchar (separator);
        }

      print_file_name_and_frills (f, pos);
      pos += len;
    }
  putchar (eolbyte);
}

/* Assuming cursor is at position FROM, indent up to position TO.
   Use a TAB character instead of two or more spaces whenever possible.  */

static void
indent (size_t from, size_t to)
{
  while (from < to)
    {
      if (tabsize != 0 && to / tabsize > (from + 1) / tabsize)
        {
          putchar ('\t');
          from += tabsize - from % tabsize;
        }
      else
        {
          putchar (' ');
          from++;
        }
    }
}

/* Put DIRNAME/NAME into DEST, handling '.' and '/' properly.  */
/* FIXME: maybe remove this function someday.  See about using a
   non-malloc'ing version of file_name_concat.  */

static void
attach (char *dest, char const *dirname, char const *name)
{
  char const *dirnamep = dirname;

  /* Copy dirname if it is not ".".  */
  if (dirname[0] != '.' || dirname[1] != 0)
    {
      while (*dirnamep)
        *dest++ = *dirnamep++;
      /* Add '/' if 'dirname' doesn't already end with it.  */
      if (dirnamep > dirname && dirnamep[-1] != '/')
        *dest++ = '/';
    }
  while (*name)
    *dest++ = *name++;
  *dest = 0;
}

/* Allocate enough column info suitable for the current number of
   files and display columns, and initialize the info to represent the
   narrowest possible columns.  */

static void
init_column_info (idx_t max_cols)
{
  /* Currently allocated columns in column_info.  */
  static idx_t column_info_alloc;

  if (column_info_alloc < max_cols)
    {
      idx_t old_column_info_alloc = column_info_alloc;
      column_info = xpalloc (column_info, &column_info_alloc,                              max_cols - column_info_alloc, -1,                              sizeof *column_info);

      /* Allocate the new size_t objects by computing the triangle
         formula n * (n + 1) / 2, except that we don't need to
         allocate the part of the triangle that we've already
         allocated.  Check for address arithmetic overflow.  */
      idx_t column_info_growth = column_info_alloc - old_column_info_alloc, s;
      if (ckd_add (&s, old_column_info_alloc + 1, column_info_alloc)           || ckd_mul (&s, s, column_info_growth))
        xalloc_die ();
      size_t *p = xinmalloc (s >> 1, sizeof *p);

      /* Grow the triangle by parceling out the cells just allocated.  */
      for (idx_t i = old_column_info_alloc; i < column_info_alloc; i++)
        {
          column_info[i].col_arr = p;
          p += i + 1;
        }
    }

  for (idx_t i = 0; i < max_cols; ++i)
    {
      column_info[i].valid_len = true;
      column_info[i].line_len = i * MIN_COLUMN_WIDTH + 1;
      for (idx_t j = 0; j < i; ++j)
        column_info[i].col_arr[j] = MIN_COLUMN_WIDTH;
      column_info[i].col_arr[i] = 1;
    }
}

/* Calculate the number of columns needed to represent the current set
   of files in the current display width.  */

static idx_t
calculate_columns (bool by_columns)
{
  /* Normally the maximum number of columns is determined by the
     screen width.  But if few files are available this might limit it
     as well.  */
  idx_t max_cols = 0 < max_idx && max_idx < cwd_n_used ? max_idx : cwd_n_used;

  init_column_info (max_cols);

  /* Compute the maximum number of possible columns.  */
  for (idx_t filesno = 0; filesno < cwd_n_used; ++filesno)
    {
      struct fileinfo const *f = sorted_file[filesno];
      size_t name_length = length_of_file_name_and_frills (f);

      for (idx_t i = 0; i < max_cols; ++i)
        {
          if (column_info[i].valid_len)
            {
              idx_t idx = (by_columns                            ? filesno / ((cwd_n_used + i) / (i + 1))                            : filesno % (i + 1));
              size_t real_length = name_length + (idx == i ? 0 : 2);

              if (column_info[i].col_arr[idx] < real_length)
                {
                  column_info[i].line_len += (real_length                                               - column_info[i].col_arr[idx]);
                  column_info[i].col_arr[idx] = real_length;
                  column_info[i].valid_len = (column_info[i].line_len                                               <= line_length);
                }
            }
        }
    }

  /* Find maximum allowed columns.  */
  idx_t cols;
  for (cols = max_cols; 1 < cols; --cols)
    {
      if (column_info[cols - 1].valid_len)
        break;
    }

  return cols;
}

void
usage (int status)
{
  if (status != 0)
    do     {       fprintf (stderr, (const char *) {("Try '%s --help' for more information.\n")},                program_name);     }   while (0);
  else
    {
      printf ((const char *) {("Usage: %s [OPTION]... [FILE]...\n")}, program_name);
      fputs ((const char *) {("List information about the FILEs (the current directory by default).\nSort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n")}, stdout);

      emit_mandatory_arg_note ();

      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -a, --all\n         do not ignore entries starting with .\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -A, --almost-all\n         do not list implied . and ..\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --author\n         with -l, print the author of each file\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -b, --escape\n         print C-style escapes for nongraphic characters\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --block-size=SIZE\n         with -l, scale sizes by SIZE when printing them;\n         e.g., '--block-size=M'; see SIZE format below\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -B, --ignore-backups\n         do not list implied entries ending with ~\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -c\n         with -lt: sort by, and show, ctime\n           (time of last change of file status information);\n         with -l: show ctime and sort by name;\n         otherwise: sort by ctime, newest first\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -C\n         list entries by columns\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --color[=WHEN]\n         color the output WHEN; more info below\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -d, --directory\n         list directories themselves, not their contents\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -D, --dired\n         generate output designed for Emacs' dired mode\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -f\n         same as -a -U\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -F, --classify[=WHEN]\n         append indicator (one of */=>@|) to entries WHEN\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --file-type\n         like -F, except do not append '*'\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --format=WORD\n         across,horizontal (-x), commas (-m), long (-l),\n         single-column (-1), verbose (-l), vertical (-C)\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --full-time\n         like -l --time-style=full-iso\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -g\n         like -l, but do not list owner\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --group-directories-first\n         group directories before files\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -G, --no-group\n         in a long listing, don't print group names\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -h, --human-readable\n         with -l and -s, print sizes like 1K 234M 2G etc.\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --si\n         likewise, but use powers of 1000 not 1024\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -H, --dereference-command-line\n         follow symbolic links listed on the command line\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --dereference-command-line-symlink-to-dir\n         follow each command line symbolic link that points to a directory\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --hide=PATTERN\n         do not list implied entries matching shell PATTERN\n         (overridden by -a or -A)\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --hyperlink[=WHEN]\n         hyperlink file names WHEN\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --indicator-style=WORD\n         append indicator with style WORD to entry names:\n           none (default), slash (-p), file-type (--file-type), classify (-F)\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -i, --inode\n         print the index number of each file\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -I, --ignore=PATTERN\n         do not list implied entries matching shell PATTERN\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -k, --kibibytes\n         default to 1024-byte blocks for file system usage;\n         used only with -s and per directory totals\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -l\n         use a long listing format\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -L, --dereference\n         when showing file information for a symbolic link,\n         show information for the file the link references\n         rather than for the link itself\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -m\n         fill width with a comma separated list of entries\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -n, --numeric-uid-gid\n         like -l, but list numeric user and group IDs\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -N, --literal\n         print entry names without quoting\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -o\n         like -l, but do not list group information\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -p, --indicator-style=slash\n         append / indicator to directories\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -q, --hide-control-chars\n         print ? instead of nongraphic characters\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --show-control-chars\n         show nongraphic characters as-is;\n         the default, unless program is 'ls' and output is a terminal\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -Q, --quote-name\n         enclose entry names in double quotes\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --quoting-style=WORD\n         use quoting style WORD for entry names:\n           literal, locale, shell, shell-always,\n           shell-escape, shell-escape-always, c, escape\n         (overrides QUOTING_STYLE environment variable)\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -r, --reverse\n         reverse order while sorting\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -R, --recursive\n         list subdirectories recursively\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -s, --size\n         print the allocated size of each file, in blocks\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -S\n         sort by file size, largest first\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --sort=WORD\n         change default 'name' sort to WORD:\n           none (-U), size (-S), time (-t),\n           version (-v), extension (-X), name, width\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --time=WORD\n         select which timestamp used to display or sort;\n           access time (-u): atime, access, use;\n           metadata change time (-c): ctime, status;\n           modified time (default): mtime, modification;\n           birth time: birth, creation;\n         with -l, WORD determines which time to show;\n         with --sort=time, sort by WORD (newest first)\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --time-style=TIME_STYLE\n         time/date format with -l; see TIME_STYLE below\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -t\n         sort by time, newest first; see --time\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -T, --tabsize=COLS\n         assume tab stops at each COLS instead of 8\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -u\n         with -lt: sort by, and show, access time;\n         with -l: show access time and sort by name;\n         otherwise: sort by access time, newest first\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -U\n         do not sort directory entries\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -v\n         natural sort of (version) numbers within text\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -w, --width=COLS\n         set output width to COLS.  0 means no limit\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -x\n         list entries by lines instead of by columns\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -X\n         sort alphabetically by entry extension\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -Z, --context\n         print any security context of each file\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --zero\n         end each output line with NUL, not newline\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("  -1\n         list one file per line\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --help\n         display this help and exit\n")});
      oputs_ ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")), (const char *) {("      --version\n         output version information and exit\n")});
      emit_size_note ();
      fputs ((const char *) {("\nThe TIME_STYLE argument can be full-iso, long-iso, iso, locale, or +FORMAT.\nFORMAT is interpreted like in date(1).  If FORMAT is FORMAT1<newline>FORMAT2,\nthen FORMAT1 applies to non-recent files and FORMAT2 to recent files.\nTIME_STYLE prefixed with 'posix-' takes effect only outside the POSIX locale.\nAlso the TIME_STYLE environment variable sets the default style to use.\n")}, stdout);
      fputs ((const char *) {("\nThe WHEN argument defaults to 'always' and can also be 'auto' or 'never'.\n")}, stdout);
      fputs ((const char *) {("\nUsing color to distinguish file types is disabled both by default and\nwith --color=never.  With --color=auto, ls emits color codes only when\nstandard output is connected to a terminal.  The LS_COLORS environment\nvariable can change the settings.  Use the dircolors(1) command to set it.\n")}, stdout);
      fputs ((const char *) {("\nExit status:\n 0  if OK,\n 1  if minor problems (e.g., cannot access subdirectory),\n 2  if serious trouble (e.g., cannot access command-line argument).\n")}, stdout);
      emit_ancillary_info ((ls_mode == LS_LS ? "ls"                       : (ls_mode == LS_MULTI_COL                          ? "dir" : "vdir")));
    }
  exit (status);
}

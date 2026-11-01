/* Exit with a status code indicating success.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.

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


/* Commonly used file permission combination.  */




ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
int chdir(const char *path);
int isatty(int fd);
char *getcwd(char *buf, size_t size);
ssize_t readlink(const char *path, char *buf, size_t size);



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


/* The include_next requires a split double-inclusion guard.  */


/* Do nothing but include the system header if it works properly.  */
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
typedef unsigned short char16_t;

extern int errno;



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

struct lconv { char *decimal_point; };
char *setlocale(int category, const char *locale);
struct lconv *localeconv(void);

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

enum true_modes
{
  /* This is for the 'true' program.  */
  TRUE_TRUE,

  /* This is for the 'false' program.  */
  TRUE_FALSE
};

extern enum true_modes true_mode;



void
usage (int status)
{
  printf ((const char *) {("Usage: %s [ignored command line arguments]\n  or:  %s OPTION\n")},           program_name, program_name);
  printf ("%s\n\n",           (const char *) {((true_mode != TRUE_TRUE) == 0             ? "Exit with a status code indicating success."             : "Exit with a status code indicating failure.")});
  oputs_ ((true_mode == TRUE_TRUE ? "true" : "false"), (const char *) {("      --help\n         display this help and exit\n")});
  oputs_ ((true_mode == TRUE_TRUE ? "true" : "false"), (const char *) {("      --version\n         output version information and exit\n")});
  printf ((const char *) {("\n" "Your shell may have its own version of %s, which usually supersedes\n" "the version described here.  Please refer to your shell's documentation\n" "for details about the options it supports.\n")}, (true_mode == TRUE_TRUE ? "true" : "false"));
  emit_ancillary_info ((true_mode == TRUE_TRUE ? "true" : "false"));
  exit (status);
}

int
main (int argc, char **argv)
{
  /* Recognize --help or --version only if it's the only command-line
     argument.  */
  if (argc == 2)
    {
      ;
      set_program_name (argv[0]);
      setlocale (0, "");
      ((void) (const char *) {("coreutils")},      (const char *) {("/share/locale")});
      (const char *) {("coreutils")};

      /* Note true(1) will return EXIT_FAILURE in the
         edge case where writes fail with GNU specific options.  */
      atexit (close_stdout);

      if (streq (argv[1], "--help"))
        usage ((true_mode != TRUE_TRUE));

      if (streq (argv[1], "--version"))
        version_etc (stdout, (true_mode == TRUE_TRUE ? "true" : "false"), "GNU coreutils", Version, proper_name_lite ("Jim Meyering", "Jim Meyering"),                      (char *) 0);
    }

  return (true_mode != TRUE_TRUE);
}

/* Blackjack/x86 target configuration for source-compatibility work.
 * This is deliberately small and truthful: define capabilities only when
 * the Blackjack target/runtime provides them.
 */
#ifndef BLACKJACK_CONFIG_H
#define BLACKJACK_CONFIG_H

#define PACKAGE "coreutils"
#define PACKAGE_NAME "GNU coreutils"
#define PACKAGE_VERSION "blackjack"
#define VERSION "blackjack"

/* Target model. */
#define BLACKJACK 1
#define __unix__ 1
#define STDC_HEADERS 1

/* Facilities not presently supplied by Blackjack.  Keep these numeric so
 * upstream #if HAVE_* expressions select their portable/fallback paths. */
#define HAVE_STROPTS_H 0
#define HAVE_LANGINFO_CODESET 0
#define HAVE_SELINUX_SELINUX_H 0
#define HAVE_SYS_ACL_H 0
#define HAVE_SYS_XATTR_H 0
#define HAVE_PTHREAD_H 0

/* Gnulib normally derives these through extern-inline.m4/configure.
 * x86-cc accepts inline declarations; use the conservative static-inline
 * form for header helpers on the Blackjack target. */
#define _GL_INLINE static inline
#define _GL_EXTERN_INLINE static inline

/* Gnulib's generated config normally supplies compiler-attribute wrappers.
 * x86-cc does not implement GCC attributes yet, so the semantically safe
 * compatibility form for pure is an empty annotation. */
#define _GL_ATTRIBUTE_PURE
#define _GL_ATTRIBUTE_NODISCARD
#define _GL_ATTRIBUTE_MALLOC
#define _GL_ATTRIBUTE_RETURNS_NONNULL
#define _GL_ATTRIBUTE_DEPRECATED
#define _GL_ATTRIBUTE_REPRODUCIBLE
#define _GL_ATTRIBUTE_UNSEQUENCED
#define _GL_ATTRIBUTE_DEALLOC(func, arg)

/* No gettext/NLS layer yet. */
#define ENABLE_NLS 0

#endif

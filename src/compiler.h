#ifndef MODEL_COMPILER_H
#define MODEL_COMPILER_H

#include "bug.h"

/*
 * __has_builtin is supported on gcc >= 10, clang >= 3 and icc >= 21.
 * In the meantime, to support gcc < 10, we implement __has_builtin
 * by hand.
 */
#ifndef __has_builtin
#define __has_builtin(x) (0)
#endif

#if !__has_builtin(__builtin_unreachable)
#define __builtin_unreachable() (void)(0)
#endif

/* clang-format off */
#define BITS_PER(x) (\
    (sizeof(x) == 8 ? 64U :\
    (sizeof(x) == 7 ? 48U :\
    (sizeof(x) == 6 ? 56U :\
    (sizeof(x) == 5 ? 40U :\
    (sizeof(x) == 4 ? 32U :\
    (sizeof(x) == 3 ? 24U :\
    (sizeof(x) == 2 ? 16U :\
    (sizeof(x) == 1 ? 8U : BUILD_BUG_ON_ZERO(0))))))))))

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MEMBER_REF(var, member) ((__typeof__(var) *)0)->member
#define MEMBER_SIZE(var, member) sizeof(MEMBER_REF((var), member))
#define ARRAY_SIZE_OF(var, member) ARRAY_SIZE(MEMBER_REF((var), member))

#define __STRINGIFY(n) #n
#define LOCAL(n) __FILE__ ":" __STRINGIFY(n)

/* Are two types/vars the same type (ignoring qualifiers)? */
#define same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define __ARRSIZE(x) (sizeof(x) / sizeof(x[0]))
#define __STRSIZE(x) (__ARRSIZE(x) - 1)
#define __STRADDR(x) ((char const *)(char const(*)[__ARRSIZE(x)]){&(x)})

#endif

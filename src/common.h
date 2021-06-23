#ifndef __COMMON_H
#define __COMMON_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

static inline u32 next_pow2_32(u32 x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x;
}

static inline u64 next_pow2_64(u64 x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x;
}

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define container_of(ptr, type, member)                                        \
	({                                                                     \
		const typeof(((type *)0)->member) *__mptr = (ptr);             \
		(type *)((char *)__mptr - offsetof(type, member));             \
	})

#define min(x, y)                                                              \
	({                                                                     \
		typeof(x) __x = (x);                                           \
		typeof(y) __y = (y);                                           \
		(void)(&__x == &__y);                                          \
		__x < __y ? __x : __y;                                         \
	})

#define max(x, y)                                                              \
	({                                                                     \
		typeof(x) __x = (x);                                           \
		typeof(y) __y = (y);                                           \
		(void)(&__x == &__y);                                          \
		__x > __y ? __x : __y;                                         \
	})

#define roundup(x, y)                                                          \
	({                                                                     \
		const typeof(y) __y = y;                                       \
		(((x) + (__y - 1)) / __y) * __y;                               \
	})

#endif
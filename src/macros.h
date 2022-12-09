#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define null NULL

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef uint8_t byte;

typedef char *String;


#define BIT(x)          (1<<(x))
#define BIT_SET(x, p)     ((x)|(1<<(p)))
#define BIT_CLEAR(x, p)   ((x)&(~(1<<(p))))
#define BIT_AT(x, p)     (((x)>>(p))&1)
#define BIT_TOGGLE(x, p)  ((x)^(1<<(p)))

#define STR_(s)             #s
#define STR(s)              STR_(s)
#define CAT(str1, str2)      (str1 "" str2)
#define PASTE_(a, b)         a##b
#define PASTE(a, b)          PASTE_(a,b)
#define PRINT_TOKEN(token)  printf(#token " is %d", token)

#define PI                  3.141592654
#define RAD2DEG(x)          ((x)/PI*180)
#define DEG2RAD(x)          ((x)*PI/180)
#define ALIGNB(x, align)    (((x) + ((align) - 1)) & ~((align) - 1))
#define ALIGN(x, align)     ((((x) + ((align) - 1)) / (align)) * (align))
#define FLOORB(x, align)    ((x) & ~((align) - 1))
#define FLOOR(x, align)     (((x) / (align)) * (align))
#define CEILB(x, align)     ALIGNB(x, align)
#define CEIL(x, align)      ALIGN(x, align)
#define CLIP(x, min, max)   (((x) < (min)) ? (min) : (((x) > (max)) ? (max) : (x)))
#define UCLIP(x, max)       (((x) > (max)) ? (max) : (x))
#define LCLIP(x, min)       (((x) < (min)) ? (min) : (x))
#define MIN(x, y)           (((x) < (y)) ?  (x) : (y))
#define MAX(x, y)           (((x) > (y)) ?  (x) : (y))
#define ABS(x)              (((x) <  0) ? -(x) : (x))
#define DIFF(a, b)           ABS((a)-(b))
#define IS_NAN(x)            ((x) != (x))
#define IMPLIES(x, y)       (!(x) || (y))
#define SWAP(a, b)          do { a ^= b; b ^= a; a ^= b; } while ( 0 )
#define SORT(a, b)          do { if ((a) > (b)) SWAP((a), (b)); } while (0)
#define COMPARE(x, y)       (((x) > (y)) - ((x) < (y)))
#define SIGN(x)             COMPARE(x, 0)
#define IS_ODD(num)       ((num) & 1)
#define IS_EVEN(num)      (!IS_ODD( (num) ))
#define IS_BETWEEN(n, L, H)   ((unsigned char)((n) >= (L) && (n) <= (H)))

#define LOG(x, fmt, ...)    if(x){printf("%s:%d: " fmt "\n",__FILE__, __LINE__,__VA_ARGS__);}
#define TRY(x, s)            if(!(x)){printf("%s:%d:%s",__FILE__, __LINE__,s);}
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)           if(!(n)) { \
                            printf("%s - Failed ",#n); \
                            printf("On %s ",__DATE__); \
                            printf("At %s ",__TIME__); \
                            printf("In File %s ",__FILE__); \
                            printf("At Line %d\n",__LINE__); \
                            exit(-1);}
#endif


#define VEC(T) typedef struct { u32 size; u32 capacity; T *items;  } PASTE(Vec_, T)

#define VEC_INIT(v, cap) \
memset((v), 0, sizeof(*(v))); \
(v)->capacity = (cap) == 0 ? 16 : (cap);                         \
(v)->items = calloc((cap), sizeof((v)->items[0]));       \
ASSERT((v)->items != null)

#define VEC_DESTROY(v) free((v)->items); (v)->items=null

#define VEC_ADD(v, e) \
if ((v)->size == (v)->capacity) { \
  (v)->items = realloc((v)->items, (v)->capacity * 2 * sizeof((v)->items[0])); \
  ASSERT((v)->items != null);\
  (v)->capacity *= 2; \
}                      \
(v)->items[(v)->size++] = e

#define VEC_AT(v, i) (v)->items[(i)]

#define VEC_SORT(v, cmp) (qsort((v)->items, (v)->size, sizeof(*(v)->items), cmp))

#define VEC_POP(v) ASSERT((v)->size > 0); (v)->size--

#define VEC_DELETE_AT(v, i) ASSERT(i >= 0 && i < (v)->capacity); (v)->items[i] = (v)->items[--(v)->size]

VEC(u32);
VEC(u64);
VEC(i64);
VEC(i32);
VEC(f32);
VEC(f64);
VEC(String);


#endif //C_DATA_STRUCTURE_LIBS_H

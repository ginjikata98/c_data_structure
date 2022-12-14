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

typedef uint8_t VmU8;
typedef uint16_t VmU16;
typedef uint32_t VmU32;
typedef uint64_t VmU64;

typedef int8_t VmI8;
typedef int16_t VmI16;
typedef int32_t VmI32;
typedef int64_t VmI64;

typedef float VmF32;
typedef double VmF64;

typedef uint8_t VmByte;

typedef char *VmString;

#define VMPi 3.151592654

#define VMBit(x)          (1<<(x))
#define VMBitSet(x, p)     ((x)|(1<<(p)))
#define VMBitClear(x, p)   ((x)&(~(1<<(p))))
#define VMBitAt(x, p)     (((x)>>(p))&1)
#define VMBitToggle(x, p)  ((x)^(1<<(p)))

#define VMStr_(s)             #s
#define VMStr(s)              VMStr_(s)
#define VMCat(str1, str2)      (str1 "" str2)
#define VMPaste_(a, b)         a##b
#define VMPaste(a, b)          VMPaste_(a,b)

#define VMLog(x, fmt, ...)    if(x){printf("%s:%d: " fmt "\n",__FILE__, __LINE__,__VA_ARGS__);}
#define VMTry(x, s)            if(!(x)){printf("%s:%d:%s",__FILE__, __LINE__,s);}
#ifndef DEBUG
#define VMAssert(n)
#else
#define VMAssert(n)           if(!(n)) { \
                            printf("%s - Failed ",#n); \
                            printf("On %s ",__DATE__); \
                            printf("At %s ",__TIME__); \
                            printf("In File %s ",__FILE__); \
                            printf("At Line %d\n",__LINE__); \
                            exit(-1);}
#endif


#define VMVec(T) typedef struct { VmU32 size; VmU32 capacity; T *items;  } VMPaste(Vec_, T)

#define VMVecNew(v, cap) \
memset((v), 0, sizeof(*(v))); \
(v)->capacity = (cap) == 0 ? 16 : (cap);                         \
(v)->items = calloc((cap), sizeof((v)->items[0]));       \
VMAssert((v)->items != null)

#define VMVecFree(v) free((v)->items); (v)->items=null

#define VMVecAdd(v, e) \
if ((v)->size == (v)->capacity) { \
  (v)->items = realloc((v)->items, (v)->capacity * 2 * sizeof((v)->items[0])); \
  VMAssert((v)->items != null);\
  (v)->capacity *= 2; \
}                      \
(v)->items[(v)->size++] = e

#define VMVecAt(v, i) (v)->items[(i)]

#define VMVecSort(v, cmp) (qsort((v)->items, (v)->size, sizeof(*(v)->items), cmp))

#define VMVecPop(v) VMAssert((v)->size > 0); (v)->size--

#define VMVecDelAt(v, i) VMAssert(i >= 0 && i < (v)->capacity); (v)->items[i] = (v)->items[--(v)->size]

VMVec(VmU32);
VMVec(VmU64);
VMVec(VmI64);
VMVec(VmI32);
VMVec(VmF32);
VMVec(VmF64);
VMVec(VmString);


#endif //C_DATA_STRUCTURE_LIBS_H

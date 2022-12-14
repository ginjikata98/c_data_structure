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

#define FN_PREFIX vm
#define STRUCT_PREFIX Vm

#define FN_NAME_(name) VMPaste(FN_PREFIX, name)
#define FN_NAME(name) FN_NAME_(name)

#define STRUCT_NAME_(name) VMPaste(STRUCT_PREFIX, name)
#define STRUCT_NAME(name) STRUCT_NAME_(name)

#define VMMalloc_(v, s) malloc(s); assert(v != null)
#define VMMalloc(v, s) VMMalloc_(v, s)

#define VMFree_(p) if (p != null) { free(p); p = null; }
#define VMFree(p) VMFree_(p)

#define VMCalloc_(v, l, s) calloc(l, s); assert(v != null)
#define VMCalloc(v, l, s) VMCalloc_(v, l, s)

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



#define VMVec(T, name) typedef struct STRUCT_NAME(name) STRUCT_NAME(name); \
STRUCT_NAME(name) *VMPaste(FN_NAME(name), New) (VmU32 cap);\

#define VMVecDef(T, name) struct VMPaste(Vm, name) { VmU32 size; VmU32 capacity; T *items;  }; \
STRUCT_NAME(name) *VMPaste(FN_NAME(name), New) (VmU32 cap) {\
STRUCT_NAME(name) *a = VMMalloc(a, sizeof(STRUCT_NAME(name)));\
a->capacity = cap > 0 ? cap : 16;\
a->size = 0;\
a->items = VMCalloc(a->items, a->capacity, sizeof(STRUCT_NAME(name)));\
return a;\
}

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

VMVec(VmU32, VecU32);
VMVec(VmU64, VecU64);
VMVec(VmI64, VecI64);
VMVec(VmI32, VecI32);
VMVec(VmF32, VecF32);
VMVec(VmF64, VecF64);
VMVec(VmString, VecString);

#endif //C_DATA_STRUCTURE_LIBS_H

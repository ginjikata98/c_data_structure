#ifndef MAIN_MACRO_H
#define MAIN_MACRO_H

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
#include <unistd.h>
#include <stdarg.h>

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

typedef char *string;

typedef size_t size;

#define FN_PREFIX f
#define STRUCT_PREFIX s

#define mFnName_(name) mPaste(FN_PREFIX, name)
#define mFnName(name) mFnName_(name)

#define mStructName_(name) mPaste(STRUCT_PREFIX, name)
#define mStructName(name) mStructName_(name)

#define mMalloc_(v, s) malloc(s); assert(v != null)
#define mMalloc(v, s) mMalloc_(v, s)

#define mRealloc_(v, s) realloc(v, s); assert(v != null)
#define mRealloc(v, s) mRealloc_(v, s)

#define mFree_(p) if (p != null) { free(p); p = null; }
#define mFree(p) mFree_(p)

#define mCalloc_(v, l, s) calloc(l, s); assert(v != null)
#define mCalloc(v, l, s) mCalloc_(v, l, s)

#define mPi 3.151592654
#define mBit(x)          (1<<(x))
#define mBitSet(x, p)     ((x)|(1<<(p)))
#define mBitClear(x, p)   ((x)&(~(1<<(p))))
#define mBitAt(x, p)     (((x)>>(p))&1)
#define mBitToggle(x, p)  ((x)^(1<<(p)))

#define mStr_(s)             #s
#define mStr(s)              mStr_(s)
#define mCat(str1, str2)      (str1 "" str2)
#define mPaste_(a, b)         a##b
#define mPaste(a, b)          mPaste_(a,b)

#define mLog(x, fmt, ...)    if(x){printf("%s:%d: " fmt "\n",__FILE__, __LINE__,__VA_ARGS__);}
#define mTry(x, s)            if(!(x)){printf("%s:%d:%s",__FILE__, __LINE__,s);}
#ifndef DEBUG
#define mAssert(n)
#else
#define mAssert(n)           if(!(n)) { \
                            printf("%s - Failed ",#n); \
                            printf("On %s ",__DATE__); \
                            printf("At %s ",__TIME__); \
                            printf("In File %s ",__FILE__); \
                            printf("At Line %d\n",__LINE__); \
                            exit(-1);}
#endif

#define mFor(i, len) for (u64 i = 0; i < len; i++)
#define mLoopBack(i, len) for (i64 i = len - 1; i >=; i--)
#define loop for (;;)

#define mArr(T, ...) (T[]) {__VA_ARGS__}

#define mMax(a, b) ((a) > (b) ? (a) : (b))
#define mMin(a, b) ((a) < (b) ? (a) : (b))

#endif //MAIN_MACRO_H

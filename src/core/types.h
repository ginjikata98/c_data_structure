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

typedef u8 byte;

typedef char* string;

typedef size_t size;

#define ai_m_malloc_(v, s) malloc(s); assert(v != null)
#define ai_m_malloc(v, s) ai_m_malloc_(v, s)

#define ai_m_realloc_(v, s) realloc(v, s); assert(v != null)
#define ai_m_realloc(v, s) ai_m_realloc_(v, s)

#define ai_m_free_(p) if (p != null) { free(p); p = null; }
#define ai_m_free(p) ai_m_free_(p)

#define ai_m_calloc_(v, l, s) calloc(l, s); assert(v != null)
#define ai_m_calloc(v, l, s) ai_m_calloc_(v, l, s)

#define ai_m_str_(s)             #s
#define ai_m_str(s)              ai_m_str_(s)
#define ai_m_cat(str1, str2)      (str1 "" str2)
#define ai_m_paste_(a, b)         a##b
#define ai_m_paste(a, b)          ai_m_paste_(a,b)

#define ai_m_log(x, fmt, ...)    if(x){printf("%s:%d: " fmt "\n",__FILE__, __LINE__,__VA_ARGS__);}
#define ai_m_try(x, s)            if(!(x)){printf("%s:%d:%s",__FILE__, __LINE__,s);}

#define loop for (;;)

#define ai_m_vec(T, ...) (T[]) {__VA_ARGS__}

#define ai_m_max(a, b) ((a) > (b) ? (a) : (b))
#define ai_m_min(a, b) ((a) < (b) ? (a) : (b))

#define ai_m_to_byte(a) ((byte*)&(a))
#define ai_m_pointer_to_byte(a) ((byte*)(a))
#define ai_m_from_byte(a, T) ( (T*) (a) )

u64 ai_std_hash(void* input);


#endif //MAIN_MACRO_H

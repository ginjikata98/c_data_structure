#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include "types.h"
#include "string.h"
#include "vec.h"

typedef struct {
  ai_string_ai string;
  ai_vec_api vec;

  u64 (* hash)(void* input, i32);

} ai_std_api;


void* fMemClone(void* src, size s);
void fMemCopy(void* src, void* dest, size s);
f64 track(void (* fn)(void));

#define ai_m_std_module {\
    .vec = ai_m_vec_module,\
    .hash = ai_std_hash,\
}\

#define ai_m_import_std(alias) ai_std_api alias = ai_m_std_module


#endif //C_DATA_STRUCTURE_LIBS_H

#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include "types.h"
#include "string.h"
#include "vec.h"

typedef struct {
  ai_string_ai string;
  ai_vec_api vec;
} ai_std_api;

#define ai_m_std_module {\
    .vec = ai_m_vec_module,\
}\

#define ai_m_import_std(alias) ai_std_api alias = ai_m_std_module


void* fMemClone(void* src, size s);
void fMemCopy(void* src, void* dest, size s);
f64 track(void (* fn)(void));

#endif //C_DATA_STRUCTURE_LIBS_H

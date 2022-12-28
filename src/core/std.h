#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include "types.h"
#include "string.h"

typedef struct {
  ai_string_ai string;
} ai_std_api;

//ai_std_api aa = {
//};

#define ai_m_import_std(alias)


void *fMemClone(void *src, size s);
void fMemCopy(void *src, void *dest, size s);
f64 track(void (*fn)(void));

#endif //C_DATA_STRUCTURE_LIBS_H

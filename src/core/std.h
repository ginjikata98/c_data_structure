#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include "types.h"

void *fMemClone(void *src, size s);
void fMemCopy(void *src, void *dest, size s);
f64 track(void (*fn)(void));

#endif //C_DATA_STRUCTURE_LIBS_H

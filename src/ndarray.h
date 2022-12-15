#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sArray sArray;

#define mShape(...) (u32[]) {__VA_ARGS__}

sArray *fArrayNew(f64 *data, u32 nd, u32 *dimensions);
sArray *fArrayOnes(u32 nd, u32 *dimensions);
sArray *fArrayZeros(u32 nd, u32 *dimensions);
sArray *fArrayArrange(i32 start, i32 end);
void *fArrayReshape(u32 nd, u32 *dimensions);
void fArrayPrint(sArray *arr);
f64 fArrayGet(sArray *arr, u32 *ind);


#endif //MAIN_NDARRAY_H

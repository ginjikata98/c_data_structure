#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sArray sArray;

f64 fArrayGet(sArray *arr, u32 *ind);
u32 fArrayGetIndex(sArray *arr, u32 *ind);
u32 *fArrayGetCord(sArray *arr, u32 idx);
sArray *fArrayNew(f64 *data, u32 nd, u32 *dims);
sArray *fArrayOnes(u32 nd, u32 *dims);
sArray *fArrayZeros(u32 nd, u32 *dims);
sArray *fArrayUniform(u32 nd, u32 *dims);
sArray *fArrayNormal(u32 nd, u32 *dims);
sArray *fArrayArrange(f64 start, f64 end, f64 step);
void fArrayReshape(sArray *arr, u32 nd, const u32 *dims);
void fArrayPrint(sArray *arr);

#endif //MAIN_NDARRAY_H

#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sArray {
  f64 *data;
  u32 nd;
  u32 *dims;
  u32 *strides;
  u32 len;
} sArray;

// Creating and Getting
f64 fArrayGet(sArray *arr, u32 *ind);
u32 fArrayGetIndex(sArray *arr, u32 *ind);
u32 *fArrayGetCord(sArray *arr, u32 idx);
sArray *fArrayNew(f64 *data, u32 nd, u32 *dims);
void fArrayFree(sArray *arr);
sArray *fArrayClone(sArray *arr);
sArray *fArrayOnes(u32 nd, u32 *dims);
sArray *fArrayZeros(u32 nd, u32 *dims);
sArray *fArrayUniform(u32 nd, u32 *dims);
sArray *fArrayNormal(u32 nd, u32 *dims);
sArray *fArrayArrange(f64 start, f64 end, f64 step);
void fArrayPrint(sArray *arr);

// modifying
void fArrayReshape(sArray *arr, u32 nd, const u32 *dims);
sArray *fArrayTranspose(sArray *in, sArray *out);

// reduce
f64 fArrayMean(sArray *arr, u32 axis);
f64 fArraySum(sArray *arr, u32 axis);
f64 fArrayArgMax(sArray *arr, u32 axis);

// math
void fArrayDot(sArray *in1, sArray *in2, sArray *out);
void fArrayAdd(sArray *in1, sArray *in2, sArray *out);
void fArraySub(sArray *in1, sArray *in2, sArray *out);
void fArrayMul(sArray *in1, sArray *in2, sArray *out);
void fArrayDiv(sArray *in1, sArray *in2, sArray *out);
void fArrayMax(sArray *in1, sArray *in2, sArray *out);
void fArrayMin(sArray *in1, sArray *in2, sArray *out);
void fArrayPow(sArray *in1, sArray *in2, sArray *out);

#endif //MAIN_NDARRAY_H

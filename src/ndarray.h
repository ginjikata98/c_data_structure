#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sArray {
  u32 len;
  u32 nd;
  f64 *data;
  u32 *dims;
  u32 *strides;
} sArray;

// Creating and Getting
f64 fArrayGet(sArray *self, u32 *ind);
u32 fArrayGetIndex(sArray *self, u32 *ind);
u32 *fArrayGetCord(sArray *self, u32 idx);
sArray *fArrayNew(f64 *data, u32 nd, u32 *dims);
void fArrayFree(sArray *self);
sArray *fArrayClone(sArray *self);
sArray *fArrayOnes(u32 nd, u32 *dims);
sArray *fArrayZeros(u32 nd, u32 *dims);
sArray *fArrayUniform(u32 nd, u32 *dims);
sArray *fArrayNormal(u32 nd, u32 *dims);
sArray *fArrayLinspace(f64 start, f64 end, f64 step);
void fArrayPrint(sArray *self);
sArray *fArrayChoice(sArray* arr, u32 size);

// modifying
void fArrayReshape(sArray *self, u32 nd, const u32 *dims);
sArray *fArrayTranspose(sArray *in, sArray *out);
sArray *fArrayShuffle(sArray *in, sArray *out);

// reduce
f64 fArrayMean(sArray *arr);
f64 fArraySum(sArray *arr);
f64 fArrayArgMax(sArray *arr);
sArray *fArrayMeanAxis(sArray *arr, u32 axis);
sArray *fArraySumAxis(sArray *arr, u32 axis);
sArray *fArrayArgMaxAxis(sArray *arr, u32 axis);

// math
void fArrayDot(sArray *in1, sArray *in2, sArray *out);
void fArrayAdd(sArray *in1, sArray *in2, sArray *out);
void fArraySub(sArray *in1, sArray *in2, sArray *out);
void fArrayMul(sArray *in1, sArray *in2, sArray *out);
void fArrayDiv(sArray *in1, sArray *in2, sArray *out);
void fArrayMax(sArray *in1, sArray *in2, sArray *out);
void fArrayMin(sArray *in1, sArray *in2, sArray *out);
void fArrayPow(sArray *in1, sArray *in2, sArray *out);
void fArrayCompare(sArray *in1, sArray *in2, sArray *out);
void fArrayAddScalar(sArray *in1, f64 in2, sArray *out);
void fArraySubScalar(sArray *in1, f64 in2, sArray *out);
void fArrayMulScalar(sArray *in1, f64 in2, sArray *out);
void fArrayDivScalar(sArray *in1, f64 in2, sArray *out);
void fArrayMaxScalar(sArray *in1, f64 in2, sArray *out);
void fArrayMinScalar(sArray *in1, f64 in2, sArray *out);
void fArrayPowScalar(sArray *in1, f64 in2, sArray *out);
void fArrayCompareScalar(sArray *in1, f64 in2, sArray *out);

#endif //MAIN_NDARRAY_H

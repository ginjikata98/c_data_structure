#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sTensor {
  u32 len;
  u32 nd;
  f64 *data;
  u32 *dims;
  u32 *strides;
} sTensor;

// Creating and Getting
f64 fTensorGet(sTensor *self, u32 *ind);
u32 fTensorGetIndex(sTensor *self, u32 *ind);
u32 *fTensorGetCord(sTensor *self, u32 idx);
sTensor *fTensorNew(f64 *data, u32 nd, u32 *dims);
void fTensorFree(sTensor *self);
sTensor *fTensorClone(sTensor *self);
sTensor *fTensorOnes(u32 nd, u32 *dims);
sTensor *fTensorZeros(u32 nd, u32 *dims);
sTensor *fTensorUniform(u32 nd, u32 *dims);
sTensor *fTensorNormal(u32 nd, u32 *dims);
sTensor *fTensorLinspace(f64 start, f64 end, f64 step);
void fTensorPrint(sTensor *self);
sTensor *fTensorChoice(sTensor* arr, u32 size);

// modifying
void fTensorReshape(sTensor *self, u32 nd, const u32 *dims);
sTensor *fTensorTranspose(sTensor *in, sTensor *out);
sTensor *fTensorShuffle(sTensor *in, sTensor *out);

// reduce
f64 fTensorMean(sTensor *arr);
f64 fTensorSum(sTensor *arr);
f64 fTensorArgMax(sTensor *arr);
sTensor *fTensorMeanAxis(sTensor *arr, u32 axis);
sTensor *fTensorSumAxis(sTensor *arr, u32 axis);
sTensor *fTensorArgMaxAxis(sTensor *arr, u32 axis);

// math
void fTensorDot(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorAdd(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorSub(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorMul(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorDiv(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorMax(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorMin(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorPow(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorCompare(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorAddScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorSubScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorMulScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorDivScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorMaxScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorMinScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorPowScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorCompareScalar(sTensor *in1, f64 in2, sTensor *out);

#endif //MAIN_NDARRAY_H

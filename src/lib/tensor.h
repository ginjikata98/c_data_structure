#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sTensor {
  i32 len;
  i32 nd;
  f64 *data;
  i32 *dims;
  i32 *strides;
} sTensor;

// Creating and Getting
sTensor *fTensorNew(f64 *data, i32 nd, i32 *dims);
void fTensorFree(sTensor *self);
f64 fTensorGet(sTensor *self, i32 *ind);
i32 fTensorGetIndex(sTensor *self, i32 *ind);
i32 *fTensorGetCord(sTensor *self, i32 idx);
sTensor *fTensorClone(sTensor *self);
sTensor *fTensorOnes(i32 nd, i32 *dims);
sTensor *fTensorZeros(i32 nd, i32 *dims);
sTensor *fTensorUniform(i32 nd, i32 *dims);
sTensor *fTensorNormal(i32 nd, i32 *dims);
sTensor *fTensorLinspace(f64 start, f64 end, f64 step);
void fTensorPrint(sTensor *self);
sTensor *fTensorChoice(sTensor* arr, i32 size);

// modifying
void fTensorReshape(sTensor *self, i32 nd, const i32 *dims);
sTensor *fTensorTranspose(sTensor *in, sTensor *out);
sTensor *fTensorShuffle(sTensor *in, sTensor *out);

// reduce
f64 fTensorMean(sTensor *arr);
f64 fTensorSum(sTensor *arr);
f64 fTensorArgMax(sTensor *arr);
sTensor *fTensorMeanAxis(sTensor *arr, i32 axis);
sTensor *fTensorSumAxis(sTensor *arr, i32 axis);
sTensor *fTensorArgMaxAxis(sTensor *arr, i32 axis);

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

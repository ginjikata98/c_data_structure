//#include "tensor.h"
//#include "rand.h"
//
//i32 prod(i32 nd, const i32 *dims) {
//  i32 n = 1;
//  mLoopUp(i, nd) {
//    n *= dims[i];
//  }
//  return n;
//}
//
//sTensor *fTensorNew(f64 *data, i32 nd, i32 *dims) {
//  assert(nd > 0);
//
//  sTensor *arr = malloc(sizeof(sTensor));
//  arr->data = data;
//  arr->strides = ai_m_malloc(arr->strides, sizeof(i32) * nd);
//  arr->dims = ai_m_malloc(arr->dims, sizeof(i32) * nd);
//  arr->nd = nd;
//
//  fTensorReshape(arr, nd, dims);
//  return arr;
//}
//
//sTensor *fTensorOnes(i32 nd, i32 *dims) {
//  i32 idx = prod(nd, dims);
//
//  f64 *data = ai_m_malloc(data, idx * sizeof(f64));
//
//  mLoopUp(i, idx) {
//    data[i] = 1;
//  }
//
//  return fTensorNew(data, nd, dims);
//}
//
//sTensor *fTensorZeros(i32 nd, i32 *dims) {
//  i32 idx = prod(nd, dims);
//  f64 *data = ai_m_calloc(data, idx, sizeof(f64));
//
//  return fTensorNew(data, nd, dims);
//}
//
//sTensor *fTensorUniform(i32 nd, i32 *dims) {
//  i32 idx = prod(nd, dims);
//  f64 *data = ai_m_malloc(data, idx * sizeof(f64));
//  mLoopUp(i, idx) {
//    data[i] = ai_random_uniform();
//  }
//
//  return fTensorNew(data, nd, dims);
//}
//
//sTensor *fTensorNormal(i32 nd, i32 *dims) {
//  i32 idx = prod(nd, dims);
//  f64 *data = ai_m_malloc(data, idx * sizeof(f64));
//  mLoopUp(i, idx) {
//    data[i] = ai_random_normal();
//  }
//
//  return fTensorNew(data, nd, dims);
//}
//
//sTensor *fTensorLinspace(f64 start, f64 end, f64 step) {
//  assert(end > start);
//  i32 idx = (i32) ((end - start) / step);
//
//  f64 *data = malloc(idx * sizeof(*data));
//  f64 v = start;
//  for (i32 i = 0; i < idx; ++i) {
//    data[i] = v;
//    v += step;
//  }
//
//  return fTensorNew(data, 2, ai_m_vec(i32, 1, idx));
//}
//
//void fTensorReshape(sTensor *self, i32 nd, const i32 *dims) {
//  assert(self);
//  assert(dims);
//  assert(nd > 0);
//
//  if (self->nd != nd) {
//    self->nd = nd;
//    self->dims = ai_m_realloc(self->dims, sizeof(i32) * nd);
//  }
//
//  mLoopUp(i, nd) {
//    self->dims[i] = dims[i];
//  }
//
//  self->idx = 1;
//  for (i32 i = self->nd - 1; i >= 0; i--) {
//    assert(dims[i] > 0);
//    self->idx *= dims[i];
//    if (i == self->nd - 1) {
//      self->strides[i] = 1;
//      continue;
//    }
//    self->strides[i] = self->strides[i + 1] * self->dims[i + 1];
//  }
//}
//
//f64 fTensorGet(sTensor *self, i32 *ind) {
//  assert(self);
//  i32 n = self->nd;
//  i32 *strides = self->strides;
//  f64 *ptr = self->data;
//
//  mLoopUp(i, n) {
//    ptr += (*strides++) * (*ind++);
//  }
//
//  return *ptr;
//}
//
//i32 fTensorGetIndex(sTensor *self, i32 *ind) {
//  assert(self);
//  return 0;
//}
//
//i32 *fTensorGetCord(sTensor *self, i32 idx) {
//  assert(self);
//
//  return null;
//}
//
//void fTensorPrint(sTensor *self) {
//  assert(self);
//  if (!self->data) { return; }
//  printf("[strides]: [");
//  mLoopUp(i, self->nd) {
//    printf("%d,", self->strides[i]);
//  }
//  printf("], [dims]: [");
//  mLoopUp(i, self->nd) {
//    printf("%d,", self->dims[i]);
//  }
//  printf("], [data]: [");
//  mLoopUp(i, self->idx) {
//    printf("%.4f,", self->data[i]);
//  }
//  printf("]\n");
//}
//
//void fTensorFree(sTensor *self) {
//  assert(self);
//  ai_m_free(self->data);
//  ai_m_free(self->dims);
//  ai_m_free(self->strides);
//  ai_m_free(self);
//}
//
//sTensor *fTensorClone(sTensor *self) {
//  assert(self);
//  f64 *data = fMemClone(self->data, self->idx * sizeof(f64));
//  return fTensorNew(data, self->nd, self->dims);
//}
//
//sTensor *fTensorChoice(sTensor* arr, i32 size);
//sTensor *fTensorTranspose(sTensor *in, sTensor *out);
//sTensor *fTensorShuffle(sTensor *in, sTensor *out);
//
//// reduce
//f64 fTensorMean(sTensor *arr);
//f64 fTensorSum(sTensor *arr);
//f64 fTensorArgMax(sTensor *arr);
//sTensor *fTensorMeanAxis(sTensor *arr, i32 axis);
//sTensor *fTensorSumAxis(sTensor *arr, i32 axis);
//sTensor *fTensorArgMaxAxis(sTensor *arr, i32 axis);
//
//// math
//void fTensorDot(sTensor *in1, sTensor *in2, sTensor *out);
//
//static void fAssertEleWiseParams(sTensor *in1, sTensor *in2, sTensor *out) {
//  assert(in1 && in2 && out);
//  assert(in1->idx == in2->idx && in1->nd == in2->nd);
//  assert(in1->idx == out->idx && in1->nd == out->nd);
//}
//
//void fTensorAdd(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = in1->data[i] + in2->data[i];
//  }
//}
//
//void fTensorSub(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = in1->data[i] - in2->data[i];
//  }
//}
//
//void fTensorMul(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = in1->data[i] * in2->data[i];
//  }
//}
//
//void fTensorDiv(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = in1->data[i] / in2->data[i];
//  }
//}
//
//void fTensorMax(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = ai_m_max(in1->data[i], in2->data[i]);
//  }
//}
//
//void fTensorMin(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = ai_m_min(in1->data[i], in2->data[i]);
//  }
//}
//
//void fTensorPow(sTensor *in1, sTensor *in2, sTensor *out) {
//  fAssertEleWiseParams(in1, in2, out);
//  mLoopUp(i, out->idx) {
//    out->data[i] = pow(in1->data[i], in2->data[i]);
//  }
//}
//
//void fTensorAddScalar(sTensor *in1, f64 in2, sTensor *out);
//void fTensorSubScalar(sTensor *in1, f64 in2, sTensor *out);
//void fTensorMulScalar(sTensor *in1, f64 in2, sTensor *out);
//void fTensorDivScalar(sTensor *in1, f64 in2, sTensor *out);
//void fTensorMaxScalar(sTensor *in1, f64 in2, sTensor *out);
//void fTensorMinScalar(sTensor *in1, f64 in2, sTensor *out);
//void fTensorPowScalar(sTensor *in1, f64 in2, sTensor *out);
//
//void fTensorCompare(sTensor *in1, sTensor *in2, sTensor *out);
//void fTensorCompareScalar(sTensor *in1, f64 in2, sTensor *out);
//

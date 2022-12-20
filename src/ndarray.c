#include "ndarray.h"
#include "rand.h"

u32 prod(u32 nd, const u32 *dims) {
  u32 n = 1;
  mFor(i, nd) {
    n *= dims[i];
  }
  return n;
}

sTensor *fTensorNew(f64 *data, u32 nd, u32 *dims) {
  assert(nd > 0);

  sTensor *arr = malloc(sizeof(sTensor));
  arr->data = data;
  arr->strides = mMalloc(arr->strides, sizeof(u32) * nd);
  arr->dims = mMalloc(arr->dims, sizeof(u32) * nd);
  arr->nd = nd;

  fTensorReshape(arr, nd, dims);
  return arr;
}

sTensor *fTensorOnes(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);

  f64 *data = mMalloc(data, len * sizeof(f64));

  mFor(i, len) {
    data[i] = 1;
  }

  return fTensorNew(data, nd, dims);
}

sTensor *fTensorZeros(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);
  f64 *data = mCalloc(data, len, sizeof(f64));

  return fTensorNew(data, nd, dims);
}

sTensor *fTensorUniform(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);
  f64 *data = mMalloc(data, len * sizeof(f64));
  mFor(i, len) {
    data[i] = fRandUniform();
  }

  return fTensorNew(data, nd, dims);
}

sTensor *fTensorNormal(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);
  f64 *data = mMalloc(data, len * sizeof(f64));
  mFor(i, len) {
    data[i] = fRandNormal();
  }

  return fTensorNew(data, nd, dims);
}

sTensor *fTensorLinspace(f64 start, f64 end, f64 step) {
  assert(end > start);
  u32 len = (u32) ((end - start) / step);

  f64 *data = malloc(len * sizeof(*data));
  f64 v = start;
  for (u32 i = 0; i < len; ++i) {
    data[i] = v;
    v += step;
  }

  return fTensorNew(data, 2, mArr(u32, 1, len));
}

void fTensorReshape(sTensor *self, u32 nd, const u32 *dims) {
  assert(self);
  assert(dims);
  assert(nd > 0);

  if (self->nd != nd) {
    self->nd = nd;
    self->dims = mRealloc(self->dims, sizeof(u32) * nd);
  }

  mFor(i, nd) {
    self->dims[i] = dims[i];
  }

  self->len = 1;
  for (i32 i = self->nd - 1; i >= 0; i--) {
    assert(dims[i] > 0);
    self->len *= dims[i];
    if (i == self->nd - 1) {
      self->strides[i] = 1;
      continue;
    }
    self->strides[i] = self->strides[i + 1] * self->dims[i + 1];
  }
}

f64 fTensorGet(sTensor *self, u32 *ind) {
  assert(self);
  u32 n = self->nd;
  u32 *strides = self->strides;
  f64 *ptr = self->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

u32 fTensorGetIndex(sTensor *self, u32 *ind) {
  assert(self);
  return 0;
}

u32 *fTensorGetCord(sTensor *self, u32 idx) {
  assert(self);

  return null;
}

void fTensorPrint(sTensor *self) {
  assert(self);
  if (!self->data) { return; }
  printf("[strides]: [");
  mFor(i, self->nd) {
    printf("%d,", self->strides[i]);
  }
  printf("], [dims]: [");
  mFor(i, self->nd) {
    printf("%d,", self->dims[i]);
  }
  printf("], [data]: [");
  mFor(i, self->len) {
    printf("%.4f,", self->data[i]);
  }
  printf("]\n");
}

void fTensorFree(sTensor *self) {
  assert(self);
  mFree(self->data);
  mFree(self->dims);
  mFree(self->strides);
  mFree(self);
}

sTensor *fTensorClone(sTensor *self) {
  assert(self);
  f64 *data = fMemClone(self->data, self->len * sizeof(f64));
  return fTensorNew(data, self->nd, self->dims);
}

sTensor *fTensorChoice(sTensor* arr, u32 size);
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

static void fAssertEleWiseParams(sTensor *in1, sTensor *in2, sTensor *out) {
  assert(in1 && in2 && out);
  assert(in1->len == in2->len && in1->nd == in2->nd);
  assert(in1->len == out->len && in1->nd == out->nd);
}

void fTensorAdd(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] + in2->data[i];
  }
}

void fTensorSub(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] - in2->data[i];
  }
}

void fTensorMul(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] * in2->data[i];
  }
}

void fTensorDiv(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] / in2->data[i];
  }
}

void fTensorMax(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = mMax(in1->data[i], in2->data[i]);
  }
}

void fTensorMin(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = mMin(in1->data[i], in2->data[i]);
  }
}

void fTensorPow(sTensor *in1, sTensor *in2, sTensor *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = pow(in1->data[i], in2->data[i]);
  }
}

void fTensorAddScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorSubScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorMulScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorDivScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorMaxScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorMinScalar(sTensor *in1, f64 in2, sTensor *out);
void fTensorPowScalar(sTensor *in1, f64 in2, sTensor *out);

void fTensorCompare(sTensor *in1, sTensor *in2, sTensor *out);
void fTensorCompareScalar(sTensor *in1, f64 in2, sTensor *out);


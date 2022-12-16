#include "ndarray.h"
#include "rand.h"

u32 prod(u32 nd, const u32 *dims) {
  u32 n = 1;
  mFor(i, nd) {
    n *= dims[i];
  }
  return n;
}

sArray *fArrayNew(f64 *data, u32 nd, u32 *dims) {
  assert(nd > 0);

  sArray *arr = malloc(sizeof(sArray));
  arr->data = data;
  arr->strides = mMalloc(arr->strides, sizeof(u32) * nd);
  arr->dims = mMalloc(arr->dims, sizeof(u32) * nd);
  arr->nd = nd;

  fArrayReshape(arr, nd, dims);
  return arr;
}

sArray *fArrayOnes(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);

  f64 *data = mMalloc(data, len * sizeof(f64));

  mFor(i, len) {
    data[i] = 1;
  }

  return fArrayNew(data, nd, dims);
}

sArray *fArrayZeros(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);
  f64 *data = mCalloc(data, len, sizeof(f64));

  return fArrayNew(data, nd, dims);
}

sArray *fArrayUniform(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);
  f64 *data = mMalloc(data, len * sizeof(f64));
  mFor(i, len) {
    data[i] = fRandUniform(0, 1);
  }

  return fArrayNew(data, nd, dims);
}

sArray *fArrayNormal(u32 nd, u32 *dims) {
  u32 len = prod(nd, dims);
  f64 *data = mMalloc(data, len * sizeof(f64));
  mFor(i, len) {
    data[i] = fRandNormal();
  }

  return fArrayNew(data, nd, dims);
}

sArray *fArrayLinspace(f64 start, f64 end, f64 step) {
  assert(end > start);
  u32 len = (u32) ((end - start) / step);

  f64 *data = malloc(len * sizeof(*data));
  f64 v = start;
  for (u32 i = 0; i < len; ++i) {
    data[i] = v;
    v += step;
  }

  return fArrayNew(data, 2, mArr(u32, 1, len));
}

void fArrayReshape(sArray *self, u32 nd, const u32 *dims) {
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

f64 fArrayGet(sArray *self, u32 *ind) {
  assert(self);
  u32 n = self->nd;
  u32 *strides = self->strides;
  f64 *ptr = self->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

u32 fArrayGetIndex(sArray *self, u32 *ind) {
  assert(self);
  return 0;
}

u32 *fArrayGetCord(sArray *self, u32 idx) {
  assert(self);

  return null;
}

void fArrayPrint(sArray *self) {
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

void fArrayFree(sArray *self) {
  assert(self);
  mFree(self->data);
  mFree(self->dims);
  mFree(self->strides);
  mFree(self);
}

sArray *fArrayClone(sArray *self) {
  assert(self);
  f64 *data = fMemClone(self->data, self->len * sizeof(f64));
  return fArrayNew(data, self->nd, self->dims);
}

sArray *fArrayChoice(sArray* arr, u32 size);
sArray *fArrayTranspose(sArray *in, sArray *out);

// reduce
f64 fArrayMean(sArray *arr);
f64 fArraySum(sArray *arr);
f64 fArrayArgMax(sArray *arr);
sArray *fArrayMeanAxis(sArray *arr, u32 axis);
sArray *fArraySumAxis(sArray *arr, u32 axis);
sArray *fArrayArgMaxAxis(sArray *arr, u32 axis);

// math
void fArrayDot(sArray *in1, sArray *in2, sArray *out);

static void fAssertEleWiseParams(sArray *in1, sArray *in2, sArray *out) {
  assert(in1 && in2 && out);
  assert(in1->len == in2->len && in1->nd == in2->nd);
  assert(in1->len == out->len && in1->nd == out->nd);
}

void fArrayAdd(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] + in2->data[i];
  }
}

void fArraySub(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] - in2->data[i];
  }
}

void fArrayMul(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] * in2->data[i];
  }
}

void fArrayDiv(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = in1->data[i] / in2->data[i];
  }
}

void fArrayMax(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = mMax(in1->data[i], in2->data[i]);
  }
}

void fArrayMin(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = mMin(in1->data[i], in2->data[i]);
  }
}

void fArrayPow(sArray *in1, sArray *in2, sArray *out) {
  fAssertEleWiseParams(in1, in2, out);
  mFor(i, out->len) {
    out->data[i] = pow(in1->data[i], in2->data[i]);
  }
}

void fArrayAddScalar(sArray *in1, f64 in2, sArray *out);
void fArraySubScalar(sArray *in1, f64 in2, sArray *out);
void fArrayMulScalar(sArray *in1, f64 in2, sArray *out);
void fArrayDivScalar(sArray *in1, f64 in2, sArray *out);
void fArrayMaxScalar(sArray *in1, f64 in2, sArray *out);
void fArrayMinScalar(sArray *in1, f64 in2, sArray *out);
void fArrayPowScalar(sArray *in1, f64 in2, sArray *out);

void fArrayCompare(sArray *in1, sArray *in2, sArray *out);
void fArrayCompareScalar(sArray *in1, f64 in2, sArray *out);


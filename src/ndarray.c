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

sArray *fArrayArrange(f64 start, f64 end, f64 step) {
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

void fArrayReshape(sArray *arr, u32 nd, const u32 *dims) {
  assert(arr);
  assert(dims);
  assert(nd > 0);

  if (arr->nd != nd) {
    arr->nd = nd;
    arr->dims = mRealloc(arr->dims, sizeof(u32) * nd);
  }

  mFor(i, nd) {
    arr->dims[i] = dims[i];
  }

  arr->len = 1;
  for (i32 i = arr->nd - 1; i >= 0; i--) {
    assert(dims[i] > 0);
    arr->len *= dims[i];
    if (i == arr->nd - 1) {
      arr->strides[i] = 1;
      continue;
    }
    arr->strides[i] = arr->strides[i + 1] * arr->dims[i + 1];
  }
}

f64 fArrayGet(sArray *arr, u32 *ind) {
  assert(arr);
  u32 n = arr->nd;
  u32 *strides = arr->strides;
  f64 *ptr = arr->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

u32 fArrayGetIndex(sArray *arr, u32 *ind) {
  assert(arr);
  return 0;
}

u32 *fArrayGetCord(sArray *arr, u32 idx) {
  assert(arr);

  return null;
}

void fArrayPrint(sArray *arr) {
  assert(arr);
  if (!arr->data) { return; }
  printf("[strides]: [");
  mFor(i, arr->nd) {
    printf("%d,", arr->strides[i]);
  }
  printf("], [dims]: [");
  mFor(i, arr->nd) {
    printf("%d,", arr->dims[i]);
  }
  printf("], [data]: [");
  mFor(i, arr->len) {
    printf("%.4f,", arr->data[i]);
  }
  printf("]\n");
}

void fArrayFree(sArray *arr) {
  assert(arr);
  mFree(arr->data);
  mFree(arr->dims);
  mFree(arr->strides);
  mFree(arr);
}

sArray *fArrayClone(sArray *arr) {
  assert(arr);
  f64 *data = fMemClone(arr->data, arr->len * sizeof(f64));
  return fArrayNew(data, arr->nd, arr->dims);
}


// reduce
f64 fArrayMean(sArray *arr, u32 axis);
f64 fArraySum(sArray *arr, u32 axis);
f64 fArrayArgMax(sArray *arr, u32 axis);

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


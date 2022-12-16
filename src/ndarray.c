#include "ndarray.h"
#include "rand.h"

struct sArray {
  f64 *data;
  u32 nd;
  u32 *dims;
  u32 *strides;
  u32 size;
};

static u32 prod(u32 nd, u32 *dims) {
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

  return fArrayNew(data, 2, mArr(u32,1, len));
}

void fArrayReshape(sArray *arr, u32 nd, const u32 *dims) {
  if (arr->nd != nd) {
    arr->nd = nd;
    arr->dims = mRealloc(arr->dims, sizeof(u32) * nd);
  }

  mFor(i, nd) {
    arr->dims[i] = dims[i];
  }

  arr->size = 1;
  for (i32 i = arr->nd - 1; i >= 0; i--) {
    assert(dims[i] > 0);
    arr->size *= dims[i];
    if (i == arr->nd - 1) {
      arr->strides[i] = 1;
      continue;
    }
    arr->strides[i] = arr->strides[i + 1] * arr->dims[i + 1];
  }
}

f64 fArrayGet(sArray *arr, u32 *ind) {
  u32 n = arr->nd;
  u32 *strides = arr->strides;
  f64 *ptr = arr->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

u32 fArrayGetIndex(sArray *arr, u32 *ind) {
  return 0;
}

u32 *fArrayGetCord(sArray *arr, u32 idx) {
  return null;
}

void fArrayPrint(sArray *arr) {
  printf("[strides]: [");
  mFor(i, arr->nd) {
    printf("%d,", arr->strides[i]);
  }
  printf("], [dims]: [");
  mFor(i, arr->nd) {
    printf("%d,", arr->dims[i]);
  }
  printf("], [data]: [");
  mFor(i, arr->size) {
    printf("%.4f,", arr->data[i]);
  }
  printf("]\n");
}

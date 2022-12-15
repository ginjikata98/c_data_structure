#include "ndarray.h"

struct sArray {
    f64 *data;
    u32 ndims;
    u32 *shapes;
    u32 *strides;
    u32 size;
};

sArray *fArrayNew(f64 *data, u32 nd, u32 *dimensions) {
  assert(nd > 0);

  sArray *arr = malloc(sizeof(sArray));
  arr->data = data;
  arr->strides = malloc(sizeof(size) * nd);

  fArrayReshape(arr, nd, dimensions);
  return arr;
}

sArray *fArrayOnes(u32 nd, u32 *dimensions) {
  u32 len = 1;
  mFor(i, nd) {
    len *= dimensions[i];
  }

  f64 *data = mMalloc(data, len * sizeof(f64));

  mFor(i, len) {
    data[i] = 1;
  }

  return fArrayNew(data, nd, dimensions);
}

sArray *fArrayZeros(u32 nd, u32 *dimensions) {
  u32 len = 1;
  mFor(i, nd) {
    len *= dimensions[i];
  }

  f64 *data = mCalloc(data, len, sizeof(f64));

  return fArrayNew(data, nd, dimensions);
}

sArray *fArrayArrange(i32 start, i32 end) {
  assert(end > start);
  u32 len = end - start;

  f64 *data = malloc(len * sizeof(*data));
  for (u32 i = start; i < end; ++i) {
    data[i - start] = i;
  }

  return fArrayNew(data, 2, mShape(1, len));
}

void fArrayReshape(sArray *arr, u32 nd, u32 *dimensions) {
  arr->size = 1;
  arr->ndims = nd;
  arr->shapes = dimensions;
  for (i32 i = arr->ndims - 1; i >= 0; i--) {
    assert(dimensions[i] > 0);
    arr->size *= dimensions[i];
    if (i == arr->ndims - 1) {
      arr->strides[i] = 1;
      continue;
    }
    arr->strides[i] = arr->strides[i + 1] * arr->shapes[i + 1];
  }
}

f64 fArrayGet(sArray *arr, u32 *ind) {
  u32 n = arr->ndims;
  u32 *strides = arr->strides;
  f64 *ptr = arr->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

void fArrayPrint(sArray *arr) {
  printf("[data]: [");
  mFor(i, arr->size) {
    printf("%.4f,", arr->data[i]);
  }
  printf("], [shape]: [");
  mFor(i, arr->ndims) {
    printf("%d,", arr->shapes[i]);
  }
  printf("], [strides]: [");
  mFor(i, arr->ndims) {
    printf("%d,", arr->strides[i]);
  }
  printf("]\n");
}

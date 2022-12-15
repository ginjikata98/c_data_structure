//
// Created by DUNG.VM on 09/12/2022.
//

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

  sArray *array = malloc(sizeof(sArray));
  array->data = data;
  array->ndims = nd;
  array->shapes = dimensions;
  array->strides = malloc(sizeof(size) * nd);
  array->size = 1;

  for (i32 i = nd - 1; i >= 0; i--) {
    assert(dimensions[i] > 0);
    array->size *= dimensions[i];
    if (i == nd - 1) {
      array->strides[i] = 1;
      continue;
    }
    array->strides[i] = array->strides[i + 1] * dimensions[i + 1];
  }

  return array;
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

void *fArrayReshape(u32 nd, u32 *dimensions) {

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

static void print_(sArray *arr, u32 accumulatedIdx, u32 idx) {
  if (idx == arr->ndims - 1) {
    u32 dim = arr->shapes[idx];
    mFor(i, dim) {
      printf(" %.4f ", arr->data[accumulatedIdx + i]);
    }
    return;
  }

  u32 dim = arr->shapes[idx];
  mFor(i, dim) {
    accumulatedIdx += i * arr->strides[idx];
    printf("[");
    print_(arr, accumulatedIdx, idx + 1);
    printf("]");
  }
}

void fArrayPrint(sArray *arr) {
  printf("[");
  print_(arr, 0, 0);
  printf("]");
}

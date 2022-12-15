//
// Created by DUNG.VM on 09/12/2022.
//

#include "ndarray.h"

struct sArray {
  f64 *data;
  size ndims;
  size *shapes;
  size *strides;
  size size;
};

sArray *fArrayNew(f64 *data, size nd, size *dimensions) {
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

sArray *fArrayOnes(size nd, size *dimensions) {
  size size = 1;
  mFor(i, nd) {
    size *= dimensions[i];
  }

  f64 *data = mMalloc(data, size * sizeof(f64));

  mFor(i, size) {
    data[i] = 1;
  }

  return fArrayNew(data, nd, dimensions);
}

sArray *fArrayZeros(size nd, size *dimensions) {
  size size = 1;
  mFor(i, nd) {
    size *= dimensions[i];
  }

  f64 *data = mCalloc(data, size, sizeof(f64));

  return fArrayNew(data, nd, dimensions);
}

sArray *fArrayArrange(i32 start, i32 end) {
  assert(end > start);
  size len = end-start;

  f64 *data = malloc(len * sizeof(*data));
  for (u32 i = start; i < end; ++i) {
    data[i - start] = i;
  }

  return fArrayNew(data, 2, mShape(1, len));
}

void *fArrayReshape(size nd, size *dimensions) {

}


f64 fArrayGet(sArray *arr, size *ind) {
  size n = arr->ndims;
  size *strides = arr->strides;
  f64 *ptr = arr->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

static void print_(sArray *arr, size accumulatedIdx, size idx) {
  if (idx == arr->ndims - 1) {
    mFor(i, arr->shapes[idx]) {
      printf(" %.4f ", arr->data[accumulatedIdx + i]);
    }
    return;
  }

  mFor(i, arr->shapes[idx]) {
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

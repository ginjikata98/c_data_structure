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


f64 fArrayGet(sArray *arr, size *ind) {
  size n = arr->ndims;
  size *strides = arr->strides;
  f64 *ptr = arr->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

void fArrayPrint(sArray *arr) {
  mFor(i, arr->ndims) {
    mFor(j, arr->shapes[i]) {


    }
  }
}
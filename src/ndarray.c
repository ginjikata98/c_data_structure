//
// Created by DUNG.VM on 09/12/2022.
//

#include "ndarray.h"

struct VmNDArray {
    f64 *data;
    u32 ndims;
    u32 *shapes;
    u32 *strides;
    u32 size;
};

VmNDArray *vmNDArrayNew(f64 *data, u32 nd, u32 *dimensions) {
  assert(nd > 0);

  VmNDArray *array = malloc(sizeof(VmNDArray));
  array->data = data;
  array->ndims = nd;
  array->shapes = dimensions;
  array->strides = malloc(sizeof(f64) * nd);
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

VmNDArray *vmNDArrayOnes(u32 nd, u32 *dimensions) {
  u32 size = 1;
  mFor(i, nd) {
    size *= dimensions[i];
  }

  f64 *data = mMalloc(data, size * sizeof(f64));

  mFor(i, size) {
    data[i] = 1;
  }

  return vmNDArrayNew(data, nd, dimensions);
}


f64 vmNDArrayGet(VmNDArray *arr, u32 *ind) {
  u32 n = arr->ndims;
  u32 *strides = arr->strides;
  f64 *ptr = arr->data;

  mFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

void vmNDArrayPrint(VmNDArray *arr) {
  mFor(i, arr->ndims) {
    mFor(j, arr->shapes[i]) {


    }
  }
}
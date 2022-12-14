//
// Created by DUNG.VM on 09/12/2022.
//

#include "ndarray.h"

struct VmNDArray {
    VmF64 *data;
    VmU32 ndims;
    VmU32 *shapes;
    VmU32 *strides;
    VmU32 size;
};

VmNDArray *vmNDArrayNew(VmF64 *data, VmU32 nd, VmU32 *dimensions) {
  assert(nd > 0);

  VmNDArray *array = malloc(sizeof(VmNDArray));
  array->data = data;
  array->ndims = nd;
  array->shapes = dimensions;
  array->strides = malloc(sizeof(VmF64) * nd);
  array->size = 1;

  for (VmI32 i = nd - 1; i >= 0; i--) {
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

VmNDArray *vmNDArrayOnes(VmU32 nd, VmU32 *dimensions) {
  VmU32 size = 1;
  VMFor(i, nd) {
    size *= dimensions[i];
  }

  VmF64 *data = VMMalloc(data, size * sizeof(VmF64));

  VMFor(i, size) {
    data[i] = 1;
  }

  return vmNDArrayNew(data, nd, dimensions);
}


VmF64 vmNDArrayGet(VmNDArray *arr, VmU32 *ind) {
  VmU32 n = arr->ndims;
  VmU32 *strides = arr->strides;
  VmF64 *ptr = arr->data;

  VMFor(i, n) {
    ptr += (*strides++) * (*ind++);
  }

  return *ptr;
}

void vmNDArrayPrint(VmNDArray *arr) {
  VMFor(i, arr->ndims) {
    VMFor(j, arr->shapes[i]) {


    }
  }
}
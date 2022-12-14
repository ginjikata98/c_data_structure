//
// Created by DUNG.VM on 09/12/2022.
//

#include "ndarray.h"

struct VmNDArray {
  VmF32 *data;
  VmU32 nd;
  VmU32 *dimensions;
  VmU32 *strides;
  VmU32 size;
};

VmNDArray *vmNpInit(VmF32 *data, VmU32 nd, VmU32 *dimensions) {
  assert(nd > 0);

  VmNDArray *array = malloc(sizeof(VmNDArray));
  array->data = data;
  array->nd = nd;
  array->dimensions = dimensions;
  array->strides = malloc(sizeof(VmF32) * nd);
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


VmF32 *vmNpGet(VmNDArray *obj, VmU32 const *ind) {
  VmU32 n = obj->nd;
  VmU32 *strides = obj->strides;
  VmF32 *ptr = obj->data;

  while (n--) {
    ptr += (*strides++) * (*ind++);
  }

  return ptr;
}
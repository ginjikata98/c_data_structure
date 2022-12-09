//
// Created by DUNG.VM on 09/12/2022.
//

#include "ndarray.h"

struct NDArray {
  f32 *data;
  u32 nd;
  u32 *dimensions;
  u32 *strides;
  u32 size;
};

NDArray *NDArray_init(f32 *data, u32 nd, u32 *dimensions) {
  assert(nd > 0);

  NDArray *array = malloc(sizeof(NDArray));
  array->data = data;
  array->nd = nd;
  array->dimensions = dimensions;
  array->strides = malloc(sizeof(f32) * nd);
  array->size = 1;

  for (i32 i = nd - 1; i >= 0; i--) {
    assert(dimensions[i] > 0);
    array->size *= dimensions[i];
    if (i == nd - 1) {
      array->strides[i] = 1;
      continue;
    }
    array->strides[i] = array->strides[i + 1] * dimensions[nd - i - 1];
  }

  return array;
}


f32 *NDArray_get(NDArray *obj, u32 const *ind) {
  u32 n = obj->nd;
  u32 *strides = obj->strides;
  f32 *ptr = obj->data;

  while (n--) {
    ptr += (*strides++) * (*ind++);
  }

  return ptr;
}
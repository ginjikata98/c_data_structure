#include <stdio.h>
#include <stdlib.h>
#include <tensorflow/c/c_api.h>

#define DEBUG
#include "macros.h"

f64 square(f64 x) {
  return x * x * x;
}

f64 grad(f64 (*f)(f64), f64 x) {
  return (f(x + 1e-6) - f(x - 1e-6)) / (2e-6);
}

typedef struct NDArray {
  byte *data;
  u32 numOfDim;
  u32 *dimensions;
  u32 *strides;
} NDArray;


int main(void) {
  Vec_u32 v;
  VEC_INIT(&v, 16);
  for (u32 i = 0; i < 10; ++i) {
    VEC_ADD(&v, i);
  }

  VEC_POP(&v);
  VEC_POP(&v);

  VEC_DELETE_AT(&v, 0);
  VEC_DELETE_AT(&v, 0);

  for (u32 i = 0; i < v.size; ++i) {
    printf("%d\n", VEC_AT(&v, i));
  }

  VEC_DESTROY(&v);

  return 0;
}
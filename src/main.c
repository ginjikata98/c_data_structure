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
  List_f64 a;
  List_init(&a);

  Node_f64 n;
  Node_init(n, Node_f64);


  return 0;
}
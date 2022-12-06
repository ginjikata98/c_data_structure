#include <stdio.h>
#include <stdlib.h>
#include "libs.h"
#include <tensorflow/c/c_api.h>

f64 square(f64 x) {
  return x * x * x;
}

f64 grad(f64 (*f)(f64), f64 x) {
  return (f(x + 1e-6) - f(x - 1e-6)) / (2e-6);
}

int main(void) {
  printf("derivative of f(x) = x2 at 4 = %f", grad(square, 4));
//  printf("Hello from TensorFlow C library version %s\n", TF_Version());
  return 0;

}
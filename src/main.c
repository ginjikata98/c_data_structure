#include "lib/macro.h"

#define DEBUG

int main(void) {
  f64 target = 0.8;
  f64 weight = 0.5;
  f64 input = 0.5;

  for (i32 i = 0; i < 10000; ++i) {
    f64 pred = input * weight;
    f64 err = pow((pred - target), 2);

    printf("err: %.3f, pred: %.3f\n", err, pred);
    if (err < 1e-6) { break; }

    weight -= (pred - target) * input;

  }

  return 0;
}
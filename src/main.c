#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <tensorflow/c/c_api.h>

f64 square(f64 x) {
  return x * x * x;
}

f64 grad(f64 (*f)(f64), f64 x) {
  return (f(x + 1e-6) - f(x - 1e-6)) / (2e-6);
}

#define BIT(x)          (1<<(x))
#define SETBIT(x, p)     ((x)|(1<<(p)))
#define CLEARBIT(x, p)   ((x)&(~(1<<(p))))
#define GETBIT(x, p)     (((x)>>(p))&1)
#define TOGGLEBIT(x, p)  ((x)^(1<<(p)))

int main(void) {
  Vec_u32 v;
  Vec_init(&v, 16);
  for (u32 i = 0; i < 10; ++i) {
    Vec_add(&v, i);
  }

  Vec_pop(&v);
  Vec_pop(&v);

  Vec_deleteAt(&v, 0);
  Vec_deleteAt(&v, 0);

  for (u32 i = 0; i < v.size; ++i) {
    printf("%d\n", Vec_at(&v, i));
  }

  Vec_destroy(&v);
  return 0;
}
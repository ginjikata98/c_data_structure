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
#define SETBIT(x,p)     ((x)|(1<<(p)))
#define CLEARBIT(x,p)   ((x)&(~(1<<(p))))
#define GETBIT(x,p)     (((x)>>(p))&1)
#define TOGGLEBIT(x,p)  ((x)^(1<<(p)))

int main(void) {
  Vec_u32 v;
  Vec_init(&v, 3);
  Vec_add(&v, 10);
  Vec_add(&v, 10);
  Vec_add(&v, 10);
  Vec_add(&v, 10);


  return 0;

}
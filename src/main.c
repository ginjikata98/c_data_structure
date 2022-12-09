#define DEBUG

#include "macros.h"

int main(void) {
  srand(time(null));
  printf("%d\n", rand_int(1, 100));
  printf("%f\n", rand_uniform(1.f, 100.f));
  printf("%f\n", rand_normal());

  return 0;
}
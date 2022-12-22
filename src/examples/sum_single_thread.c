#define DEBUG

#include "../lib/std.h"
#include <time.h>


int main(void) {
  clock_t t;
  t = clock();

  u64 sum = 0;

  for (i32 i = 0; i < 1e9; ++i) {
    sum += i;
  }

  t = clock() - t;
  double time_taken = ((double) t) / CLOCKS_PER_SEC;
  printf("took %f seconds to execute \n", time_taken);

  return 0;
}
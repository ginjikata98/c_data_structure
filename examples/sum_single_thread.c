#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"
#include "executor.h"
#include <time.h>


int main(void) {
  clock_t t;
  t = clock();

  u64 sum = 0;
  mFor(i, 1e9) {
    sum += i;
  }

  t = clock() - t;
  double time_taken = ((double) t) / CLOCKS_PER_SEC;
  printf("took %f seconds to execute \n", time_taken);

  return 0;
}
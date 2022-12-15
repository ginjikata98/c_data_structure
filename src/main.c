#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {

  sArray *a = fArrayOnes(2, mShape(2, 2));

  printf("%f\n", fArrayGet(a, mShape(1, 0)));

  return 0;
}
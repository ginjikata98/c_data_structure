#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {

  sArray *a = fArrayArrange(1, 12);

  fArrayPrint(a);

  return 0;
}
#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {

  sArray *a = fArrayArrange(1, 12);
//  sArray *a = fArrayOnes(3, mShape(2, 2, 2));

  fArrayPrint(a);

  return 0;
}
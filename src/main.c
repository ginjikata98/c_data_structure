#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {

  sArray *a = fArrayArrange(0, 100);
  fArrayPrint(a);
  fArrayReshape(a, 3, mShape(2, 25, 2));
  fArrayPrint(a);


//  sArray *a = fArrayOnes(3, mShape(2, 2, 2));


  return 0;
}
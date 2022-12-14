#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "utils.h"

typedef struct {
  VmU32 kArm;
  VmF32 epsilon;

} Bandit;


int main(void) {
//  srand(time(null));
//  printf("%d\n", vmRandU32(1, 100));
//  printf("%f\n", vmRandUniform(1.f, 100.f));
//  printf("%f\n", vmRandNormal());

  VmF32 data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  VmU32 nd = 3;
  VmU32 dims[] = {2, 3, 2};
  VmNDArray *array = vmNpInit(data, nd, dims);

  VmU32 access[] = {0, 1, 0};
  printf("%f", *vmNpGet(array, access));


  return 0;
}
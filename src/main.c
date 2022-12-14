#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"

typedef struct {
  VmU32 kArm;
  VmF32 epsilon;
} Bandit;


int main(void) {
  srand(time(null));
  printf("%d\n", vmRandU32(1, 100));
  printf("%f\n", vmRandUniform(1.f, 100.f));
  printf("%f\n", vmRandNormal());

  VmF32 data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  VmU32 nd = 3;
  VmU32 dims[] = {2, 3, 2};
  VmNDArray *array = vmNDArrayNew(data, nd, dims);

  VmU32 access[] = {0, 1, 0};
  printf("%f\n", *vmNDArrayGet(array, access));

  VmVecU32 *a = vmVecU32New(16);

  for (int i = 0; i < 100; ++i) {
    vmVecU32Push(a, vmRandU32(1, 100));
  }

  printf("size %ld\n", sizeof(&a));
  printf("at 2 %d\n", *vmVecU32At(a, 2));
  vmVecU32DelAt(a, 5);
  printf("pop %d\n", *vmVecU32Pop(a));
//  vmVecU32Sort(a);
  vmVecU32Free(a);

  return 0;
}
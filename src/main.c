#define DEBUG

#include "macros.h"
#include "ndarray.h"
#include "utils.h"

typedef struct {
  u32 kArm;
  f32 epsilon;

} Bandit;


int main(void) {
//  srand(time(null));
//  printf("%d\n", rand_u32(1, 100));
//  printf("%f\n", rand_uniform(1.f, 100.f));
//  printf("%f\n", rand_normal());

  f32 data[] = {1, 2, 3, 4, 5, 6};
  u32 nd = 2;
  u32 dims[] = {2, 3};
  NDArray *array = NDArray_init(data, nd, dims);

  u32 access[] = {1, 2};
  printf("%f", NDArray_get(array, access));


  return 0;
}
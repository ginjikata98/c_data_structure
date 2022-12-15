#define DEBUG

#include <unistd.h>
#include "std.h"
#include "ndarray.h"
#include "rand.h"
#include "pthread.h"


typedef struct {
    VmU32 kArm;
    VmF32 epsilon;
} Bandit;


void *run(void *arg) {
  sleep(1);
  printf("THREAD: Running thread with arg\n");
  return null;
}

int main(void) {
  srand(time(null));

  VmU32 dim[] = {2, 2, 2};
  VmNDArray *a = vmNDArrayOnes(3, dim);

  VmU32 access[] = {1, 1, 1};
  printf("%f", vmNDArrayGet(a, access));

  vmNDArrayPrint(a);

  pthread_t thread_id;
  printf("Before Thread\n");
  pthread_create(&thread_id, null, run, null);
  pthread_join(thread_id, null);
  printf("After Thread\n");


  return 0;
}
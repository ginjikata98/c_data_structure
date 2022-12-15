#define DEBUG

#include <unistd.h>
#include <stdarg.h>
#include "std.h"
#include "ndarray.h"
#include "rand.h"
#include "pthread.h"


typedef struct {
    VmU32 kArm;
    VmF32 epsilon;
} Bandit;


void *run(void *arg) {
  sleep(vmRandU32(1, 4));
  VmU32 *i = (VmU32 *) arg;
  printf("THREAD %d: running!\n", *i);
  VMFree(i);
  return null;
}

int main(void) {
  srand(time(null));
  VmU32 dim[] = {2, 2, 2};
  VmNDArray *a = vmNDArrayOnes(3, dim);
  VmU32 access[] = {1, 1, 1};
  printf("%f", vmNDArrayGet(a, access));
  vmNDArrayPrint(a);

  pthread_t tasks[10];
  printf("Before Thread\n");


  VMFor(i, 10) {
    VmU32 *ptr = VMMalloc(ptr, sizeof(VmU32));
    *ptr = i;
    pthread_create(&tasks[i], null, run, ptr);
  }


  VMFor(i, 10) {
    pthread_join(tasks[i], null);
    printf("done %d thread\n", i);
  }


//  pthread_mutex_init()
//  pthread_mutex_lock();
//  pthread_mutex_unlock();



  printf("After Thread\n");

  return 0;
}
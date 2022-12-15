#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"
#include "executor.h"

typedef struct {
  VmU32 kArm;
  VmF32 epsilon;
} Bandit;

static const size_t numThreads = 8;
static const size_t numItems = 10;

void task(void *arg) {
  int *val = arg;
  int old = *val;
  *val += 1000;
  printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);
}

int main(void) {
//  srand(time(null));
//  VmU32 dim[] = {2, 2, 2};
//  VmNDArray *a = vmNDArrayOnes(3, dim);
//  VmU32 access[] = {1, 1, 1};
//  printf("%f", vmNDArrayGet(a, access));
//  vmNDArrayPrint(a);

  VmExecutor *executor = vmExecutorNewFixed(numThreads);
  VmU32 *vals = VMCalloc(vals, numItems, sizeof(*vals));

  VMFor(i, numItems) {
    vals[i] = i;
    vmExecutorRun(executor, task, vals + i);
  }

  vmExecutorWait(executor);

  VMFor(i, numItems) {
    printf("after %d\n", vals[i]);
  }

  VMFree(vals);
  vmExecutorFree(executor);
  return 0;
}
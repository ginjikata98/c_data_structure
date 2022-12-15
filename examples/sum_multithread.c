#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"
#include "executor.h"

static const size_t numThreads = 8;
static const size_t numItems = 100;

void task(void *arg) {
  int *val = arg;
  int old = *val;

  VMFor(i, 1e9) {
    *val += 1;
  }

  printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);
}

int main(void) {
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

  printf("freeing\n");
  VMFree(vals);
  vmExecutorFree(executor);
  return 0;
}
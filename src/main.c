#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"
#include "executor.h"

static const size numThreads = 8;
static const size numItems = 10;

void task(void *arg) {
  i32 *val = arg;
  i32 old = *val;

  mFor(i, 1e9) {
    *val += 1;
  }

  printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);
}

int main(void) {
  sExecutor *executor = vmExecutorNewFixed(numThreads);
  u32 *vals = mCalloc(vals, numItems, sizeof(*vals));

  mFor(i, numItems) {
    vals[i] = i;
    vmExecutorRun(executor, task, vals + i);
  }

  vmExecutorWait(executor);

  mFor(i, numItems) {
    printf("after %d\n", vals[i]);
  }

  printf("freeing\n");
  mFree(vals);
  vmExecutorFree(executor);
  return 0;
}
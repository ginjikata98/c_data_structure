#define DEBUG

#include "../lib/std.h"
#include "../lib/tensor.h"
#include "../lib/rand.h"
#include "../lib/executor.h"

static const size numThreads = 8;
static const size numItems = 10;

void task(void *arg) {
  i32 *val = arg;
  i32 old = *val;

  for (int i = 0; i < 1e9; ++i) {
    *val += 1;
  }

  printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);
}

int sum_multithread(void) {
  sExecutor *executor = vmExecutorNewFixed(numThreads);
  u32 *vals = ai_calloc(vals, numItems, sizeof(*vals));

  for (i32 i = 0; i < numItems; ++i) {
    vals[i] = i;
    vmExecutorRun(executor, task, vals + i);
  }

  vmExecutorWait(executor);

  for (i32 i = 0; i < numItems; ++i) {
    printf("after %d\n", vals[i]);
  }

  printf("freeing\n");
  ai_m_free(vals);
  vmExecutorFree(executor);
  return 0;
}
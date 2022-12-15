#include "executor.h"

struct VmExecutorWork {
  VmRunnable runnable;
  void *arg;
  struct VmExecutorWork *next;
};
typedef struct VmExecutorWork VmExecutorWork;

struct VmExecutor {
  VmExecutorWork *workFirst;
  VmExecutorWork *workLast;
  VmMutex workMutex;
  VmCondition workCondition;
  VmU32 workingCount;
  VmU32 threadCount;
  VmBool running;
};
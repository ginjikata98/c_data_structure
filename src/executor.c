#include "executor.h"

struct VmWork {
  VmRunnable runnable;
  void *arg;
  struct VmWork *next;
};
typedef struct VmWork VmWork;

struct VmExecutor {
  VmWork *workFirst;
  VmWork *workLast;
  VmMutex workMutex;
  VmCondition workingCondition;
  VmU32 workingCount;
  VmU32 threadCount;
  VmBool running;
};

static VmWork *vmWorkNew(VmRunnable runnable, void *arg) {
  VmWork *work;

  if (runnable == null) {
    return null;
  }

  work = VMMalloc(work, sizeof(VmWork));
  work->runnable = runnable;
  work->arg = arg;
  work->next = null;
  return work;
}

static void vmWorkFree(VmWork *work) {
  VMFree(work);
}

static VmWork *vmExecutorGetWork(VmExecutor *executor) {
  VmWork *work;
  if (executor == null) {
    return null;
  }

  work = executor->workFirst;
  if (work == null) {
    return null;
  }

  if (work->next == null) {
    executor->workFirst = null;
    executor->workLast = null;
  } else {
    executor->workFirst = work->next;
  }

  return work;
}

static void *vmWorkerRun(void *arg) {
  VmExecutor *executor = arg;
  VmWork *work;

  while (VmTrue) {
    pthread_mutex_lock(&(executor->workMutex));

    while (executor->workFirst == null && executor->running) {
      pthread_cond_wait(&(executor->workingCondition), &(executor->workMutex));
    }

    if (!executor->running) {
      break;
    }

    work = vmExecutorGetWork(executor);
    executor->workingCount++;
    pthread_mutex_unlock(&(executor->workMutex));

    if (work != null) {
      work->runnable(work->arg);
      vmWorkFree(work);
    }

    pthread_mutex_lock(&(executor->workMutex));
    executor->workingCount--;
    if (executor->running && executor->workingCount == 0 && executor->workFirst == null) {
      pthread_cond_signal(&(executor->workingCondition));
    }
    pthread_mutex_unlock(&(executor->workMutex));
  }

  executor->threadCount--;
  pthread_cond_signal(&(executor->workingCondition));
  pthread_mutex_unlock(&(executor->workMutex));
  return null;
}


//VmExecutor *vmExecutorNewFixed(VmU32 size);
//void vmExecutorFree(VmExecutor *);
//VmBool vmExecutorRun(VmExecutor *, VmRunnable, void *arg);
//void vmExecutorWait(VmExecutor *);
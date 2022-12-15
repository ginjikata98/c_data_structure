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
  VmCondition workCondition;
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

static void *vmExecutorWorkerRun(void *arg) {
  VmExecutor *executor = arg;
  VmWork *work;

  while (VmTrue) {
    pthread_mutex_lock(&(executor->workMutex));

    while (executor->workFirst == null && executor->running) {
      pthread_cond_wait(&(executor->workCondition), &(executor->workMutex));
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


VmExecutor *vmExecutorNewFixed(VmU32 size) {
  VmExecutor *executor;
  VmThread thread;

  if (size == 0) {
    size = 4;
  }

  executor = calloc(1, sizeof(*executor));
  executor->threadCount = size;

  pthread_mutex_init(&(executor->workMutex), null);
  pthread_cond_init(&(executor->workingCondition), null);
  pthread_cond_init(&(executor->workCondition), null);

  executor->workFirst = null;
  executor->workLast = null;

  VMFor(i, size) {
    pthread_create(&thread, null, vmExecutorWorkerRun, executor);
    pthread_detach(thread);
  }

  return executor;
}

void vmExecutorFree(VmExecutor *executor) {
  if (executor == null) {
    return;
  }

  VmWork *work;
  VmWork *work2;

  pthread_mutex_lock(&(executor->workMutex));
  work = executor->workFirst;
  while (work != null) {
    work2 = work->next;
    vmWorkFree(work);
    work = work2;
  }
  executor->running = VmFalse;
  pthread_cond_broadcast(&(executor->workCondition));
  pthread_mutex_unlock(&(executor->workMutex));

  vmExecutorWait(executor);

  pthread_mutex_destroy(&(executor->workMutex));
  pthread_cond_destroy(&(executor->workCondition));
  pthread_cond_destroy(&(executor->workingCondition));

  VMFree(executor);
}

VmBool vmExecutorRun(VmExecutor *executor, VmRunnable runnable, void *arg) {
  VmWork *work;

  if (executor == null) {
    return VmFalse;
  }

  work = vmWorkNew(runnable, arg);
  if (work == null) {
    return VmFalse;
  }

  pthread_mutex_lock(&(executor->workMutex));
  if (executor->workFirst == null) {
    executor->workFirst = work;
    executor->workLast = executor->workFirst;
  } else {
    executor->workLast->next = work;
    executor->workLast = work;
  }

  pthread_cond_broadcast(&(executor->workCondition));
  pthread_mutex_unlock(&(executor->workMutex));

  return VmTrue;
}

void vmExecutorWait(VmExecutor *executor) {
  if (executor == null) {
    return;
  }

  pthread_mutex_lock(&(executor->workMutex));
  while (VmTrue) {
    if ((executor->running && executor->workingCount != 0) || (!executor->running && executor->threadCount != 0)) {
      pthread_cond_wait(&(executor->workCondition), &(executor->workMutex));
    }

    break;
  }
  pthread_mutex_unlock(&(executor->workMutex));
}
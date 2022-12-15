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
  VmMutex lock;
  VmCondition workerLoopSignal;
  VmCondition waitLoopSignal;
  VmSize workCount;
  VmSize threadCount;
  VmBool running;
};

static VmWork *vmWorkNew(VmRunnable runnable, void *arg) {
  VmWork *work;

  if (runnable == null) {
    return null;
  }

  work = VMMalloc(work, sizeof(*work));
  work->runnable = runnable;
  work->arg = arg;
  work->next = null;
  return work;
}

static void vmWorkFree(VmWork *work) {
  VMFree(work);
}

static VmWork *vmExecutorGetWork(VmExecutor *executor) {
  if (executor == null) {
    return null;
  }

  VmWork *work = executor->workFirst;
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

static void vmExecutorLock(VmExecutor *executor) {
  pthread_mutex_lock(&(executor->lock));
}

static void vmExecutorUnlock(VmExecutor *executor) {
  pthread_mutex_unlock(&(executor->lock));
}

static void vmExecutorNotifyWorkerLoop(VmExecutor *executor) {
  pthread_cond_broadcast(&(executor->workerLoopSignal));
}

static void vmExecutorNotifyWaitLoop(VmExecutor *executor) {
  pthread_cond_signal(&(executor->waitLoopSignal));
}

static void *vmExecutorWorkerLoop(void *arg) {
  VmExecutor *executor = arg;

  while (VmTrue) {
    vmExecutorLock(executor);

    while (executor->workFirst == null && executor->running) {
      pthread_cond_wait(&(executor->workerLoopSignal), &(executor->lock));
    }

    if (!executor->running) {
      break;
    }

    VmWork *work = vmExecutorGetWork(executor);
    vmExecutorUnlock(executor);

    if (work != null) {
      work->runnable(work->arg);
      vmWorkFree(work);
    }

    vmExecutorLock(executor);
    executor->workCount--;
    if (executor->running && executor->workCount == 0 && executor->workFirst == null) {
      vmExecutorNotifyWaitLoop(executor);
    }
    vmExecutorUnlock(executor);
  }

  executor->threadCount--;
  vmExecutorNotifyWaitLoop(executor);
  vmExecutorUnlock(executor);
  return null;
}


VmExecutor *vmExecutorNewFixed(VmSize size) {
  if (size == 0) {
    size = DEFAULT_THREAD;
  }

  VmExecutor *executor = calloc(1, sizeof(*executor));
  executor->threadCount = size;

  pthread_mutex_init(&(executor->lock), null);
  pthread_cond_init(&(executor->workerLoopSignal), null);
  pthread_cond_init(&(executor->waitLoopSignal), null);

  executor->workFirst = null;
  executor->workLast = null;
  executor->running = VmTrue;

  VmThread thread;
  VMFor(i, size) {
    pthread_create(&thread, null, vmExecutorWorkerLoop, executor);
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

  vmExecutorLock(executor);
  work = executor->workFirst;
  while (work != null) {
    work2 = work->next;
    vmWorkFree(work);
    work = work2;
  }
  executor->running = VmFalse;
  vmExecutorNotifyWorkerLoop(executor);
  vmExecutorUnlock(executor);

  vmExecutorWait(executor);

  pthread_mutex_destroy(&(executor->lock));
  pthread_cond_destroy(&(executor->workerLoopSignal));
  pthread_cond_destroy(&(executor->waitLoopSignal));

  VMFree(executor);
}

VmBool vmExecutorRun(VmExecutor *executor, VmRunnable runnable, void *arg) {
  if (executor == null) {
    return VmFalse;
  }

  VmWork *work = vmWorkNew(runnable, arg);
  if (work == null) {
    return VmFalse;
  }

  vmExecutorLock(executor);
  if (executor->workFirst == null) {
    executor->workFirst = work;
    executor->workLast = executor->workFirst;
  } else {
    executor->workLast->next = work;
    executor->workLast = work;
  }
  executor->workCount++;

  vmExecutorNotifyWorkerLoop(executor);
  vmExecutorUnlock(executor);

  return VmTrue;
}

void vmExecutorWait(VmExecutor *executor) {
  if (executor == null) {
    return;
  }

  vmExecutorLock(executor);
  while (VmTrue) {
    if ((executor->running && executor->workCount != 0) || (!executor->running && executor->threadCount != 0)) {
      pthread_cond_wait(&(executor->waitLoopSignal), &(executor->lock));
    } else {
      break;
    }
  }
  vmExecutorUnlock(executor);
}
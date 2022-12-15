#include "executor.h"

struct sWork {
  sRunnable runnable;
  void *arg;
  struct sWork *next;
};
typedef struct sWork sWork;

struct sExecutor {
  sWork *workFirst;
  sWork *workLast;
  sMutex lock;
  sCondition workerLoopSignal;
  sCondition waitLoopSignal;
  size workCount;
  size threadCount;
  bool running;
};

static sWork *vmWorkNew(sRunnable runnable, void *arg) {
  sWork *work;

  if (runnable == null) {
    return null;
  }

  work = mMalloc(work, sizeof(*work));
  work->runnable = runnable;
  work->arg = arg;
  work->next = null;
  return work;
}

static void vmWorkFree(sWork *work) {
  mFree(work);
}

static sWork *vmExecutorGetWork(sExecutor *executor) {
  if (executor == null) {
    return null;
  }

  sWork *work = executor->workFirst;
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

static void vmExecutorLock(sExecutor *executor) {
  pthread_mutex_lock(&(executor->lock));
}

static void vmExecutorUnlock(sExecutor *executor) {
  pthread_mutex_unlock(&(executor->lock));
}

static void vmExecutorNotifyWorkerLoop(sExecutor *executor) {
  pthread_cond_broadcast(&(executor->workerLoopSignal));
}

static void vmExecutorNotifyWaitLoop(sExecutor *executor) {
  pthread_cond_signal(&(executor->waitLoopSignal));
}

static void *vmExecutorWorkerLoop(void *arg) {
  sExecutor *executor = arg;

  while (true) {
    vmExecutorLock(executor);

    while (executor->workFirst == null && executor->running) {
      pthread_cond_wait(&(executor->workerLoopSignal), &(executor->lock));
    }

    if (!executor->running) {
      break;
    }

    sWork *work = vmExecutorGetWork(executor);
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

sExecutor *vmExecutorNewFixed(size numThreads) {
  if (numThreads == 0) {
    numThreads = DEFAULT_THREAD;
  }

  sExecutor *executor = calloc(1, sizeof(*executor));
  executor->threadCount = numThreads;

  pthread_mutex_init(&(executor->lock), null);
  pthread_cond_init(&(executor->workerLoopSignal), null);
  pthread_cond_init(&(executor->waitLoopSignal), null);

  executor->workFirst = null;
  executor->workLast = null;
  executor->running = true;

  sThread thread;
  mFor(i, numThreads) {
    pthread_create(&thread, null, vmExecutorWorkerLoop, executor);
    pthread_detach(thread);
  }

  return executor;
}

void vmExecutorFree(sExecutor *executor) {
  if (executor == null) {
    return;
  }

  sWork *work;
  sWork *work2;

  vmExecutorLock(executor);
  work = executor->workFirst;
  while (work != null) {
    work2 = work->next;
    vmWorkFree(work);
    work = work2;
  }
  executor->running = false;
  vmExecutorNotifyWorkerLoop(executor);
  vmExecutorUnlock(executor);

  vmExecutorWait(executor);

  pthread_mutex_destroy(&(executor->lock));
  pthread_cond_destroy(&(executor->workerLoopSignal));
  pthread_cond_destroy(&(executor->waitLoopSignal));

  mFree(executor);
}

bool vmExecutorRun(sExecutor *executor, sRunnable runnable, void *arg) {
  if (executor == null) {
    return false;
  }

  sWork *work = vmWorkNew(runnable, arg);
  if (work == null) {
    return false;
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

  return true;
}

void vmExecutorWait(sExecutor *executor) {
  if (executor == null) {
    return;
  }

  vmExecutorLock(executor);
  while (true) {
    if ((executor->running && executor->workCount != 0) || (!executor->running && executor->threadCount != 0)) {
      pthread_cond_wait(&(executor->waitLoopSignal), &(executor->lock));
    } else {
      break;
    }
  }
  vmExecutorUnlock(executor);
}
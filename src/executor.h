#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include "macro.h"
#include "pthread.h"
#define DEFAULT_THREAD 8

typedef pthread_t VmThread;
typedef pthread_mutex_t VmMutex;
typedef pthread_cond_t VmCondition;
typedef struct VmExecutor VmExecutor;
typedef void (*VmRunnable)(void *arg);

VmExecutor *vmExecutorNewFixed(VmSize size);
void vmExecutorFree(VmExecutor *);
VmBool vmExecutorRun(VmExecutor *, VmRunnable, void *arg);
void vmExecutorWait(VmExecutor *);

#endif //MAIN_EXECUTOR_H
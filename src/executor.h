#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include "macro.h"
#include "pthread.h"
#define DEFAULT_THREAD 8

typedef pthread_t sThread;
typedef pthread_mutex_t sMutex;
typedef pthread_cond_t sCondition;
typedef struct sExecutor sExecutor;
typedef void (*sRunnable)(void *arg);

sExecutor *vmExecutorNewFixed(size numThreads);
void vmExecutorFree(sExecutor *);
bool vmExecutorRun(sExecutor *, sRunnable, void *arg);
void vmExecutorWait(sExecutor *);

#endif //MAIN_EXECUTOR_H

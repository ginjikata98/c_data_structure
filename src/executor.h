#ifndef MAIN_EXECUTOR_H
#define MAIN_EXECUTOR_H

#include "macro.h"

typedef struct VmExecutor VmExecutor;
typedef void (*VmRunnable)(void *arg);
VmExecutor *vmExecutorNewFixed(VmU32 size);
void vmExecutorFree(VmExecutor *);
VmBool vmExecutorRun(VmExecutor *, VmRunnable, void *arg);
void vmExecutorWait(VmExecutor *);

#endif //MAIN_EXECUTOR_H

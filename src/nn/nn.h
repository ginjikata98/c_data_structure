#ifndef MAIN_NN_H
#define MAIN_NN_H

#include "../lib/std.h"

struct sModule;
typedef struct sModule sModule;

struct sNetwork;
typedef struct sNetwork sNetwork;

typedef enum {
  emModuleTypeLinear, emModuleTypeSoftmax, emModuleTypeDropout,


  emModuleTypeMaxSize,
} eModuleType;

typedef enum {
  emModuleActivationRelu, emModuleActivationSigmoid, emModuleActivationTanh,

  emModuleActivationMaxSize,
} eModuleActivation;


struct sModule {
  string name;
  eModuleType type;
  eModuleActivation activation;
  void (*forward)(struct sModule, struct sNetwork);
  void (*backward)(struct sModule, struct sNetwork);
  void (*update)(struct sModule);
  void *config;
};

struct sNetwork {
  string name;
  i32 numModules;
  sModule *modules;

  f32 *input;
  f32 *truth;
  f32 *delta;
};


float dot_cpu(int N, float *X, int INCX, float *Y, int INCY);
void axpy_cpu(int N, float ALPHA, float *X, int INCX, float *Y, int INCY);
void copy_cpu(int N, float *X, int INCX, float *Y, int INCY);
void scal_cpu(int N, float ALPHA, float *X, int INCX);
void fill_cpu(int N, float ALPHA, float * X, int INCX);
void normalize_cpu(float *x, float *mean, float *variance, int batch, int filters, int spatial);
void softmax(float *input, int n, float temp, int stride, float *output);


#endif //MAIN_NN_H

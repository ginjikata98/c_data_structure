#ifndef MAIN_NN_H
#define MAIN_NN_H

#include "../lib/std.h"

typedef enum {
  emModuleTypeLinear, emModuleTypeSoftmax, emModuleTypeDropout,

  emModuleTypeMaxSize,
} ai_module_type;

typedef enum {
  emModuleActivationRelu, emModuleActivationSigmoid, emModuleActivationTanh,

  emModuleActivationMaxSize,
} ai_module_activation;

typedef struct ai_module {
  string name;
  ai_module_type type;
  ai_module_activation activation;
  void (*forward)(struct ai_module*);
  void (*backward)(struct ai_module*);
  void (*update)(struct ai_module*);
  void *data;
} ai_module;

typedef ai_module ai_module_linear;

typedef struct {
  i32 batch;
  i32 n_inputs;
  i32 n_outputs;
  f32 *weights;
  f32 *biases;
  f32 *output;
  f32 *delta;
  f32 *weight_updates;
  f32 *bias_updates;
  f32 *input;
} ai_module_linear_config;

typedef struct ai_nn_api {
  ai_module_linear *(*Linear)(i32 batch,
                              i32 n_inputs,
                              i32 n_outputs,
                              ai_module_activation,
                              bool batchNormalize,
                              string name);

} ai_nn_api;

ai_nn_api ai_import_nn();

float dot_cpu(int N, float *X, int INCX, float *Y, int INCY);
void axpy_cpu(int N, float ALPHA, float *X, int INCX, float *Y, int INCY);
void copy_cpu(int N, float *X, int INCX, float *Y, int INCY);
void scal_cpu(int N, float ALPHA, float *X, int INCX);
void fill_cpu(int N, float ALPHA, float *X, int INCX);
void normalize_cpu(float *x, float *mean, float *variance, int batch, int filters, int spatial);
void softmax(float *input, int n, float temp, int stride, float *output);

#endif //MAIN_NN_H

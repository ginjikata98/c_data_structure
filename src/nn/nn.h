#ifndef MAIN_NN_H
#define MAIN_NN_H

#include "../lib/std.h"

typedef enum {
  ai_module_type_linear,
  ai_module_type_softmax,
  ai_module_type_dropout,

  ai_module_type_maxsize,
} ai_module_type;

typedef enum {
  ai_module_activation_relu,
  ai_module_activation_sigmoid,
  ai_module_activation_tanh,

  ai_module_activation_maxsize,
} ai_module_activation;

typedef struct ai_module {
  string name;
  ai_module_type type;
  ai_module_activation activation;
  void *(*forward)(struct ai_module *, void *input);
  void *(*backward)(struct ai_module *);
  void *(*update)(struct ai_module *);
} ai_module;

typedef struct ai_module_linear {
  ai_module *base;
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
} ai_module_linear;

typedef struct ai_nn_api {
  ai_module_linear *(*linear)(i32 batch, i32 n_in, i32 n_out, ai_module_activation, bool batch_normalize, string name);

} ai_nn_api;

ai_module *ai_module_new(string name, ai_module_type, ai_module_activation);

ai_nn_api ai_import_nn();

f32 dot_cpu(i32 N, f32 *X, i32 INCX, f32 *Y, i32 INCY);
void axpy_cpu(i32 N, f32 ALPHA, f32 *X, i32 INCX, f32 *Y, i32 INCY);
void copy_cpu(i32 N, f32 *X, i32 INCX, f32 *Y, i32 INCY);
void scal_cpu(i32 N, f32 ALPHA, f32 *X, i32 INCX);
void fill_cpu(i32 N, f32 ALPHA, f32 *X, i32 INCX);
void normalize_cpu(f32 *x, f32 *mean, f32 *variance, i32 batch, i32 filters, i32 spatial);
void softmax(f32 *input, i32 n, f32 temp, i32 stride, f32 *output);

#endif //MAIN_NN_H

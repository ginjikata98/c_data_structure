#ifndef MAIN_NN_H
#define MAIN_NN_H

#include "../lib/std.h"
#include "../core/object.h"

typedef enum {
  ai_module_type_linear, ai_module_type_softmax, ai_module_type_dropout,

  ai_module_type_maxsize,
} ai_module_type;

typedef enum {
  ai_module_activation_relu, ai_module_activation_sigmoid, ai_module_activation_tanh,

  ai_module_activation_maxsize,
} ai_module_activation;

typedef struct ai_module {
  ai_object base;
  void *(*forward)(struct ai_module *, void *input);
  void *(*backward)(struct ai_module *);
  void *(*update)(struct ai_module *);
  void *(*str)(struct ai_module *);
} ai_module;

typedef struct ai_module_linear {
  ai_module base;
  string name;
  f32 *weights;
  f32 *biases;
  f32 *output;
  f32 *delta;
  f32 *weight_updates;
  f32 *bias_updates;
  f32 *input;
  i32 batch;
  i32 n_inputs;
  i32 n_outputs;
  ai_module_activation activation;
} ai_module_linear;

typedef struct ai_nn_api {
  ai_module_linear *(*linear)(i32 batch, i32 n_in, i32 n_out, ai_module_activation);

} ai_nn_api;

ai_module_linear *ai_module_linear_new(i32 batch, i32 n_in, i32 n_out, ai_module_activation);

#define ai_m_import_nn(alias) ai_nn_api alias = {\
.linear = ai_module_linear_new\
}\


#endif //MAIN_NN_H

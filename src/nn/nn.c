#include "nn.h"
#include "gemm.h"
#include "activation.h"
#include "../lib/rand.h"

void add_bias(float *output, float *biases, int batch, int n, int size) {
  int i, j, b;
  for (b = 0; b < batch; ++b) {
    for (i = 0; i < n; ++i) {
      for (j = 0; j < size; ++j) {
        output[(b * n + i) * size + j] += biases[i];
      }
    }
  }
}

void *ai_module_linear_forward(ai_module *ai_module, void *input) {
  ai_module_linear *module = (ai_module_linear *) ai_module;
  assert(input && module);
  module->input = input;
  fill_cpu(module->n_outputs * module->batch, 0, module->output, 0);

  i32 m = module->batch;
  i32 k = module->n_inputs;
  i32 n = module->n_outputs;
  f32 *a = module->input;
  f32 *b = module->weights;
  f32 *c = module->output;

  gemm(0, 1, m, n, k, 1, a, k, b, k, 1, c, n);
//  if (l.batch_normalize) {
//    forward_batchnorm_layer(l, net);
//  } else {
  add_bias(module->output, module->biases, module->batch, module->n_outputs, 1);
//  }
  activate_array(module->output, module->n_outputs * module->batch, module->base.activation);
  return module->output;
}

static void ai_module_linear_backward(ai_module_linear *module) {

}

static void ai_module_linear_update(ai_module_linear *module) {

}

static ai_module ai_module_new(ai_module_type t, ai_module_activation a) {
  ai_module m = {0};
  m.type = t;
  m.activation = a;
  return m;
}

ai_module_linear *ai_module_linear_new(i32 batch, i32 n_inputs, i32 n_outputs, ai_module_activation activation) {
  ai_module_linear *m = ai_calloc(m, 1, sizeof(ai_module_linear));
  m->base = ai_module_new(ai_module_type_linear, activation);

  m->base.forward = ai_module_linear_forward;
//  m->base->backward = ai_module_linear_backward;
//  m->base->update = ai_module_linear_update;

  m->batch = batch;
  m->n_inputs = n_inputs;
  m->n_outputs = n_outputs;

  m->weights = ai_calloc(m->weights, n_outputs * n_inputs, sizeof(f32));
  m->biases = ai_calloc(m->biases, n_outputs, sizeof(f32));

  m->weight_updates = ai_calloc(m->weight_updates, n_outputs * n_inputs, sizeof(f32));
  m->bias_updates = ai_calloc(m->bias_updates, n_outputs, sizeof(f32));

  m->input = null;
  m->output = ai_calloc(m->output, batch * n_outputs, sizeof(f32));
  m->delta = ai_calloc(m->delta, batch * n_outputs, sizeof(f32));

  f32 scale = (f32) sqrt(2. / n_inputs);
  for (i32 i = 0; i < n_outputs * n_inputs; ++i) {
    m->weights[i] = scale * (f32) fRandUniform();
  }

  return m;
}


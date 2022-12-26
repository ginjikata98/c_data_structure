//
// Created by Tony Vu on 26/12/2022.
//

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

static void ai_module_linear_forward(ai_module_linear *module) {
  ai_module_linear_config *data = module->data;

  fill_cpu(data->n_outputs * data->batch, 0, data->output, 0);

  i32 m = data->batch;
  i32 k = data->n_inputs;
  i32 n = data->n_outputs;
  f32 *a = data->input;
  f32 *b = data->weights;
  f32 *c = data->output;

  gemm(0, 1, m, n, k, 1, a, k, b, k, 1, c, n);
//  if (l.batch_normalize) {
//    forward_batchnorm_layer(l, net);
//  } else {
  add_bias(data->output, data->biases, data->batch, data->n_outputs, 1);
//  }
  activate_array(data->output, data->n_outputs * data->batch, module->activation);
}

static void ai_module_linear_backward(ai_module_linear *module) {

}

static void ai_module_linear_update(ai_module_linear *module) {

}

ai_module_linear *ai_module_linear_new(i32 batch,
                                       i32 n_inputs,
                                       i32 n_outputs,
                                       ai_module_activation activation,
                                       bool batchNormalize,
                                       string name) {
  ai_module_linear *m = ai_calloc(m, 1, sizeof(ai_module_linear));
  m->type = emModuleTypeLinear;
  m->name = name;
  m->activation = activation;

  m->forward = ai_module_linear_forward;
  m->backward = ai_module_linear_backward;
  m->update = ai_module_linear_update;

  ai_module_linear_config *c = ai_calloc(c, 1, sizeof(ai_module_linear_config));
  c->batch = batch;
  c->n_inputs = n_inputs;
  c->n_outputs = n_outputs;

  c->weights = ai_calloc(c->weights, n_outputs * n_inputs, sizeof(f32));
  c->biases = ai_calloc(c->biases, n_outputs, sizeof(f32));

  c->weight_updates = ai_calloc(c->weight_updates, n_outputs * n_inputs, sizeof(f32));
  c->bias_updates = ai_calloc(c->bias_updates, n_outputs, sizeof(f32));

  c->input = ai_calloc(c->input, n_inputs, sizeof(f32));
  c->output = ai_calloc(c->output, batch * n_outputs, sizeof(f32));
  c->delta = ai_calloc(c->delta, batch * n_outputs, sizeof(f32));

  f32 scale = sqrt(2. / n_inputs);
  for (i32 i = 0; i < n_outputs * n_inputs; ++i) {
    c->weights[i] = scale * fRandUniform(-1, 1);
  }

  m->data = c;

  return m;
}

ai_nn_api ai_import_nn() {
  ai_nn_api nn = {0};
  nn.Linear = ai_module_linear_new;
  return nn;
}


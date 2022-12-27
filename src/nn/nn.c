#include "nn.h"
#include "math/gemm.h"
#include "activation.h"
#include "math/blas.h"
#include "../lib/rand.h"
#include "../lib/sds.h"

void *ai_module_linear_forward_(ai_module *ai_module, void *input) {
  ai_module_linear *module = (ai_module_linear *) ai_module;
  assert(input && module);
  module->input = (f32 *) input;
  ai_blas_fill_cpu(module->n_outputs * module->batch, 0, module->output, 0);

  i32 m = module->batch;
  i32 k = module->n_inputs;
  i32 n = module->n_outputs;
  f32 *a = module->input;
  f32 *b = module->weights;
  f32 *c = module->output;

  ai_gemm(0, 1, m, n, k, 1, a, k, b, k, 1, c, n);
  ai_blas_add_bias(module->output, module->biases, module->batch, module->n_outputs, 1);
  activate_array(module->output, module->n_outputs * module->batch, module->activation);
  return (void *) module->output;
}

static void ai_module_linear_backward_(ai_module_linear *module) {

}

static void ai_module_linear_update_(ai_module_linear *module) {

}

static string ai_module_linear_gen_name_() {
  static i32 id = 0;
  sds s;
  s = sdsnew("Linear/");
  s = sdscatprintf(s, "%d", id++);
  return s;
}

static string ai_module_linear_str_(ai_module *ai_module) {
  ai_module_linear *module = (ai_module_linear *) ai_module;
  sds s = sdsempty();
  s = sdscatprintf(s, "%s\t%dx%dx%d", module->name, module->batch, module->n_inputs, module->n_outputs);
  return s;
}

ai_module_linear *ai_module_linear_new(i32 batch, i32 n_inputs, i32 n_outputs, ai_module_activation activation) {
  ai_module_linear *m = ai_m_calloc(m, 1, sizeof(ai_module_linear));
  m->name = ai_module_linear_gen_name_();

  m->base.forward = ai_module_linear_forward_;
  m->base.str = ai_module_linear_str_;
//  m->base->backward = ai_module_linear_backward_;
//  m->base->update = ai_module_linear_update_;

  m->batch = batch;
  m->n_inputs = n_inputs;
  m->n_outputs = n_outputs;

  m->weights = ai_m_calloc(m->weights, n_outputs * n_inputs, sizeof(f32));
  m->biases = ai_m_calloc(m->biases, n_outputs, sizeof(f32));

  m->weight_updates = ai_m_calloc(m->weight_updates, n_outputs * n_inputs, sizeof(f32));
  m->bias_updates = ai_m_calloc(m->bias_updates, n_outputs, sizeof(f32));

  m->input = null;
  m->output = ai_m_calloc(m->output, batch * n_outputs, sizeof(f32));
  m->delta = ai_m_calloc(m->delta, batch * n_outputs, sizeof(f32));

  f32 scale = (f32) sqrt(2. / n_inputs);
  for (i32 i = 0; i < n_outputs * n_inputs; ++i) {
    m->weights[i] = scale * (f32) ai_random_uniform();
  }

  return m;
}


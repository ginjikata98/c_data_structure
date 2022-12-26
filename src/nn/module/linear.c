#include "linear.h"
#include "../../lib/rand.h"
#include "../utils/blas.h"
#include "../utils/gemm.h"
#include "../activation.h"

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

static void fModuleLinearForward(sLinearModule module, sNetwork net) {
  sLinearModuleConfig *config = module.config;

  fill_cpu(config->outputs * config->batch, 0, config->output, 0);

  i32 m = config->batch;
  i32 k = config->inputs;
  i32 n = config->outputs;
  f32 *a = net.input;
  f32 *b = config->weights;
  f32 *c = config->output;

  gemm(0, 1, m, n, k, 1, a, k, b, k, 1, config, n);
//  if (l.batch_normalize) {
//    forward_batchnorm_layer(l, net);
//  } else {
  add_bias(config->output, config->biases, config->batch, config->outputs, 1);
//  }
  activate_array(config->output, config->outputs * config->batch, module.activation);

}


static void fModuleLinearBackward(sLinearModule m, sNetwork net) {

}


static void fModuleLinearUpdate(sLinearModule m) {

}


sModule
fModuleLinear(i32 batch, i32 inputs, i32 outputs, eModuleActivation activation, bool batchNormalize, string name) {
  sModule m = {0};
  m.type = emModuleTypeLinear;
  m.name = name;
  m.activation = activation;

  m.forward = fModuleLinearForward;
  m.backward = fModuleLinearBackward;
  m.update = fModuleLinearUpdate;


  sLinearModuleConfig *c = mCalloc(c, 1, sizeof(sLinearModuleConfig));
  c->batch = batch;
  c->inputs = inputs;
  c->outputs = outputs;

  c->weights = mCalloc(c->weights, outputs * inputs, sizeof(f32));
  c->biases = mCalloc(c->biases, outputs, sizeof(f32));

  c->weightUpdates = mCalloc(c->weightUpdates, outputs * inputs, sizeof(f32));
  c->biasUpdates = mCalloc(c->biasUpdates, outputs, sizeof(f32));

  c->output = mCalloc(c->output, batch * outputs, sizeof(f32));
  c->delta = mCalloc(c->delta, batch * outputs, sizeof(f32));

  f32 scale = sqrt(2. / inputs);
  for (i32 i = 0; i < outputs * inputs; ++i) {
    c->weights[i] = scale * fRandUniform(-1, 1);
  }

  m.config = c;

  return m;
}


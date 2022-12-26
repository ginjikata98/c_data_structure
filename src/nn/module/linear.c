#include "linear.h"
#include "../../lib/rand.h"


static void fModuleLinearForward(sLinearModule m, sNetwork net) {

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


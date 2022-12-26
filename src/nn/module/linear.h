//
// Created by DUNG.VM on 26/12/2022.
//

#ifndef MAIN_LINEAR_H
#define MAIN_LINEAR_H

#include "../nn.h"

typedef sModule sLinearModule;

typedef struct {
  i32 batch;
  i32 inputs;
  i32 outputs;
  f32 *weights;
  f32 *biases;
  f32 *output;
  f32 *delta;
  f32 *weightUpdates;
  f32 *biasUpdates;

} sLinearModuleConfig;

sModule fModuleLinear(i32 batch, i32 inputs, i32 outputs, eModuleActivation, bool batchNormalize, string name);


#endif //MAIN_LINEAR_H

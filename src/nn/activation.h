//
// Created by DUNG.VM on 26/12/2022.
//



#ifndef MAIN_ACTIVATION_H
#define MAIN_ACTIVATION_H

#include "nn.h"

f32 fModuleActivationRelu(f32 x);

f32 activate(f32 x, ai_module_activation a);

void activate_array(f32 *x, const i32 n, const ai_module_activation a);

#endif //MAIN_ACTIVATION_H

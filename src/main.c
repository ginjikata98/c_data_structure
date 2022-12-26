#include "lib/macro.h"
#include "nn/nn.h"

#define DEBUG

int main(void) {
  ai_nn_api nn = ai_import_nn();
  ai_module_linear *m = nn.linear(1, 2, 1, ai_module_activation_relu, false, "sdfsdf");

  f32 *z = m->base->forward(m, mArr(f32, 1, 2));

  ai_module_linear *b = (ai_module_linear *) m;


  return 0;
}
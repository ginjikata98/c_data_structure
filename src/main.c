#include "lib/macro.h"
#include "nn/nn.h"

#define DEBUG

int main(void) {
  ai_nn_api nn = ai_import_nn();

  ai_module *m = nn.Linear(1, 2, 1, emModuleActivationRelu, false, "sdfsdf");
  m->forward(m);

  return 0;
}
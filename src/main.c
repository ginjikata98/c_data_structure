#include "lib/macro.h"
#include "nn/module.h"
#include "nn/network.h"
#include "nn/nn.h"
#include "nn/module/linear.h"

#define DEBUG

int main(void) {

  printf("%zu\n", sizeof(sModule));
  printf("%zu\n", sizeof(sNetwork));

  sNetwork n;
  n.name = "wefwef";
  n.numModules = 2;
  n.modules = mMalloc(n.modules, 2 * sizeof(sModule));

  n.modules[0] = fModuleLinear(1, 3, 4, emModuleActivationRelu, false, "asdfsd");
  n.modules[0] = fModuleLinear(1, 4, 1, emModuleActivationRelu, false, "asdfsd");

  for (int i = 0; i < 2; ++i) {
    n.modules[i].forward(n.modules[i], n);
  }



  return 0;
}
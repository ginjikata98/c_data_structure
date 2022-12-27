#include "lib/macro.h"
#include "nn/nn.h"

#define DEBUG

ai_import_nn(nn);

int main(void) {
  ai_module_linear *m = nn.linear(1, 2, 1, ai_module_activation_relu);

  f32 *z = m->base.forward(m, mArr(f32, 1, 2));

  printf("%f\n", *z);

  ai_module *a2 = ((ai_module*)m);

  printf("%d\n", a2->type);
  printf("%zu\n", sizeof(ai_module_linear));
  printf("%zu\n", sizeof(ai_module));

  return 0;
}
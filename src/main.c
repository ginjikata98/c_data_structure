#include "core/types.h"
#include "nn/nn.h"

ai_m_import_nn(nn);

int main(void) {

  ai_module *m = nn.linear(1, 2, 1, ai_module_activation_relu);

  f32 *z = m->forward(m, ai_m_vec(f32, 1, 2));

  printf("%f\n", *z);

  printf("%zu\n", sizeof(ai_module_linear));
  printf("%zu\n", sizeof(ai_module));

  return 0;
}
#include "core/types.h"
#include "nn/nn.h"
#include "lib/rand.h"

ai_m_import_nn(nn);

f32 fn(f32 x) {
  return 2 * x + 3;
}


int main(void) {

  f32 *features = ai_m_calloc(features, 1000, sizeof(f32));
  f32 *target = ai_m_calloc(target, 1000, sizeof(f32));

  for (i32 i = 0; i < 1000; ++i) {
    features[i] = ((f32) ai_random_normal()) * ((f32) i);
    target[i] = fn(features[i]);
  }
  ai_module *m = nn.linear(1000, 1, 1, ai_module_activation_relu);

  f32 *z = m->forward(m, features);
  printf("%f\n", *z);
  printf("%s\n", m->str(m));

  for (i32 i = 0; i < 1000; ++i) {
    printf("%d %.4f %.4f %.4f %.4f \n", i ,features[i], target[i], z[i],
           ((ai_module_linear *) m)->weights[0] * features[i] + ((ai_module_linear *) m)->biases[0]
           )
           ;
  }

  printf("%f\n", ((ai_module_linear *) m)->weights[0]);
  printf("%f\n", ((ai_module_linear *) m)->biases[0]);

  return 0;
}
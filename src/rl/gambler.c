


#include "../lib/macro.h"

#define cGoal 100
#define cHeadProb 0.4

//int main(void) {
//  f64 stateValues[cGoal + 1] = {0};
//  stateValues[cGoal] = 1.0;
//
//  // value interation
//  for (int i = 0; i < 100; ++i) {
//    for (i32 state = 1; state < cGoal; ++state) {
//      i32 maxAction = mMin(state, cGoal - state) + 1;
//      for (i32 a = 1; a < maxAction; ++a) {
//        f64 actionValue = cHeadProb * stateValues[state + a] + (1 - cHeadProb) * stateValues[state - a];
//        stateValues[state] = mMax(actionValue, stateValues[state]);
//      }
//    }
//  }
//
//  i32 policy[cGoal + 1] = {0};
//  for (i32 state = 1; state < cGoal; ++state) {
//    i32 maxAction = mMin(state, cGoal - state) + 1;
//    f64 maxValue = stateValues[0];
//    i32 bestAction = 0;
//    for (i32 a = 1; a < maxAction; ++a) {
//      f64 actionValue = cHeadProb * stateValues[state + a] + (1 - cHeadProb) * stateValues[state - a];
//      if (actionValue > maxValue) {
//        maxValue = actionValue;
//        bestAction = a;
//      }
//    }
//    policy[state] = bestAction;
//  }
//
//  for (i32 state = 0; state < cGoal + 1; ++state) {
//    printf("state: %d\taction: %d\tvalue: %.2f\n", state, policy[state], stateValues[state]);
//  }
//}
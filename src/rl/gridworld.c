#include "../macro.h"

#define cGridSize 5
#define cNumAction 4
#define cDiscount 0.9

i32 actionChange[cNumAction][2] = {{0,  -1},
                                   {0,  1},
                                   {-1, 0},
                                   {1,  0},};
typedef struct {
  i32 x;
  i32 y;
} sState;

typedef struct {
  sState state;
  i32 reward;
} sTransition;

sTransition step(sState s, u32 a) {
  sState newState;
  i32 reward;
  sTransition transition;

  if (s.x == 0 && s.y == 1) {
    reward = 10;
    newState.x = 4;
    newState.y = 1;
  } else if (s.x == 0 && s.y == 3) {
    reward = 5;
    newState.x = 2;
    newState.y = 3;
  } else {
    newState.x = s.x + actionChange[a][0];
    newState.y = s.y + actionChange[a][1];

    if (newState.x < 0 || newState.x >= cGridSize || newState.y < 0 || newState.y >= cGridSize) {
      reward = -1;
      newState = s;
    } else {
      reward = 0;
    }
  }

  transition.state = newState;
  transition.reward = reward;
  return transition;
}

f64 max(f64 *arr, u32 n) {
  f64 max = arr[0];
  mLoopUp(i, n) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

int main(void) {
  f64 values[cGridSize * cGridSize] = {0};
  f64 actionValueCache[cNumAction] = {0};

  mLoopUp(i, 20) {
    mLoopUp(x, cGridSize) {
      mLoopUp(y, cGridSize) {
        mLoopUp(a, cNumAction) {
          sState s = {x, y};
          sTransition transition = step(s, a);
          sState s_tp1 = transition.state;
          actionValueCache[a] = transition.reward + cDiscount * values[s_tp1.x * cGridSize + s_tp1.y];
        }
        values[x * cGridSize + y] = max(actionValueCache, cNumAction);
      }
    }
  }

  mLoopUp(x, cGridSize) {
    mLoopUp(y, cGridSize) {
      printf("[%.2f]\t", values[x * cGridSize + y]);
    }
    printf("\n");
  }
}
#include "../core/types.h"
#include "../lib/rand.h"


#define cActionHit  1
#define cActionStay  0


i32 fGetCard() {
  i32 card = ai_random_randint(1, 14);
  return ai_m_min(card, 10);
}

i32 fGetCardValue(i32 card) {
  return card == 1 ? 11 : card;
}


void fPlay(i32 playerPolicy[22], i32 dealerPolicy[22]) {
  i32 playerSum = 0;
  bool usableAcePlayer = false;

  i32 dealerCard1 = 0;
  i32 dealerCard2 = 0;
  bool usableAceDealer = false;

  while (playerSum < 12) {
    i32 card = fGetCard();
    playerSum += fGetCardValue(card);

    if (playerSum > 21) {
      assert(playerSum == 22);
      playerSum -= 10;
    } else {
      usableAcePlayer |= (1 == card);
      dealerCard1 = fGetCard();
      dealerCard2 = fGetCard();
    }
  }

  i32 state[] = {usableAcePlayer, playerSum, dealerCard1};

  i32 dealerSum = fGetCardValue(dealerCard1) + fGetCardValue(dealerCard2);
  usableAceDealer = dealerCard1 == 1 || dealerCard2 == 1;

  if (dealerSum > 21) {
    assert(dealerSum == 22);
    dealerSum -= 10;
  }

  assert(dealerSum < 21);
  assert(playerSum < 21);

  while (true) {

  }


}


i32 blackjack(void) {
  i32 actions[2] = {cActionStay, cActionHit};

  i32 dealerPolicy[22] = {0};
  for (i32 i = 12; i < 20; ++i) {
    dealerPolicy[i] = cActionHit;
  }
  dealerPolicy[20] = cActionStay;
  dealerPolicy[21] = cActionStay;


}
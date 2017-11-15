#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "cards.h"

using namespace std;

TitleDeed* Cards::deeds = (TitleDeed*) malloc(sizeof(TitleDeed)*22);
Railroad* Cards::railroads = (Railroad*) malloc(sizeof(Railroad)*4);
Utility* Cards::utilities = (Utility*) malloc(sizeof(Utility)*2)
;
static Cards cards;

int rollDice(int d) {
  return rand() % (d*6) + 1;
}

void init() {
  //srand(time(NULL));

  cards.inputTitleDeeds("titledeeds.cards");
  cards.initRailroads();
  cards.initUtilities();
}

int main() {
  init();

  //cout << Cards::deeds[7].name << ", " << Cards::deeds[7].rent[0];

  return 0;
}

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "cards.h"

using namespace std;

TitleDeed* Cards::deeds = (TitleDeed*) malloc(sizeof(TitleDeed)*22);
Railroad* Cards::railroads = (Railroad*) malloc(sizeof(Railroad)*4);
Utility* Cards::utilities = (Utility*) malloc(sizeof(Utility)*2);
EventCard* Cards::chance = (EventCard*) malloc(sizeof(EventCard)*17);
EventCard* Cards::chest = (EventCard*) malloc(sizeof(EventCard)*17);

static Cards cards;

int rollDice(int d) {
  return rand() % (d*6) + 1;
}

void init() {
  //srand(time(NULL));

  Cards::inputTitleDeeds("titledeeds.cards");
  Cards::inputChanceCards("chance.cards");
  Cards::inputChestCards("chest.cards");
  Cards::initRailroads();
  Cards::initUtilities();
}

int main() {
  init();

  cout << Cards::chance[3].description << endl;
  //cout << Cards::deeds[7].name << ", " << Cards::deeds[7].rent[0];

  return 0;
}

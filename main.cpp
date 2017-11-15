#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "cards.h"
#include "eventcard.h"
#include "board.h"

using namespace std;

TitleDeed* Cards::deeds = (TitleDeed*) malloc(sizeof(TitleDeed)*22);
Railroad* Cards::railroads = (Railroad*) malloc(sizeof(Railroad)*4);
Utility* Cards::utilities = (Utility*) malloc(sizeof(Utility)*2);
EventCard* Cards::chance = (EventCard*) malloc(sizeof(EventCard)*17);
EventCard* Cards::chest = (EventCard*) malloc(sizeof(EventCard)*17);

vector<Board::Tile> Board::map;
stack<EventCard*> Board::chanceCards;
stack<EventCard*> Board::chestCards;

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

  cout << Cards::chance[12].description << endl;
  //cout << Cards::deeds[7].name << ", " << Cards::deeds[7].rent[0];

  return 0;
}

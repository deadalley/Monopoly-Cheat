#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "player.h"
#include "cards.h"
#include "eventcard.h"
#include "board.h"
#include "gamecontroller.h"

#define N_TURNS 50

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
  srand(time(NULL));
  Cards::inputTitleDeeds("titledeeds.cards");
  Cards::inputChanceCards("chance.cards");
  Cards::inputChestCards("chest.cards");
  Cards::initRailroads();
  Cards::initUtilities();

  Board::initBoard();

  Bank::initBank();

  GameController::initGame(4);
}

int main() {
  init();

  int k = 0;
  while(k < N_TURNS) {
    GameController::processTurn();
    k++;
  }

  return 0;
}

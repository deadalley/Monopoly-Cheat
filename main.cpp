#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "player.h"
#include "cards.h"
#include "eventcard.h"
#include "board.h"
#include "gamecontroller.h"

#define N_TURNS 45

using namespace std;

TitleDeed* Cards::deeds = (TitleDeed*) malloc(sizeof(TitleDeed)*22);
Railroad* Cards::railroads = (Railroad*) malloc(sizeof(Railroad)*4);
Utility* Cards::utilities = (Utility*) malloc(sizeof(Utility)*2);
EventCard* Cards::chance = (EventCard*) malloc(sizeof(EventCard)*17);
EventCard* Cards::chest = (EventCard*) malloc(sizeof(EventCard)*17);

vector<Board::Tile> Board::map;
stack<EventCard*> Board::chanceCards;
stack<EventCard*> Board::chestCards;

int INIT_BALANCE;

void init() {
  srand(time(NULL));
  Cards::inputTitleDeeds("titledeeds.cards");
  Cards::inputChanceCards("chance.cards");
  Cards::inputChestCards("chest.cards");
  Cards::initRailroads();
  Cards::initUtilities();

  Board::initBoard();

  Bank::initBank();
  INIT_BALANCE = Bank::Balance.getBalanceValue();
  cout << INIT_BALANCE << endl;

  GameController::initGame(4);
}

int main() {
  init();

  int k = 0;
  while(k < N_TURNS) {
    GameController::processTurn();
    k++;

    int i, v = 0;
    for(i = 0; i < 4; i++) {
      v += GameController::getPlayer(i)->wallet.getBalanceValue();
    }
    v += Bank::Balance.getBalanceValue();
    //cout << "\t\t\t\t\t" << v << endl;
    if(v != INIT_BALANCE)
      cerr << "OH NO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }

  return 0;
}

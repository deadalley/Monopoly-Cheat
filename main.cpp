#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "player.h"
#include "cards.h"
#include "eventcard.h"
#include "board.h"
#include "gamecontroller.h"

#define N_TURNS 200
#define N_PLAYERS 4

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

void checkIntegrity(int k) {
  int i, j, v = 0;

  Bills bills;

  // Check bank integrity
  bills = Bank::Balance.getBalance();
  for(j = 0; j < 7; j++) {
    if(bills[j] < 0) {
      cerr << "ERROR (Bank): Negative bills! (" << k << ")" << endl;
      throw NEGATIVE_BILLS;
    }
  }
  // Check player integrity
  for(i = 0; i < N_PLAYERS; i++) {
    bills = GameController::getPlayer(i)->wallet.getBalance();
    for(j = 0; j < 7; j++) {
      if(bills[j] < 0) {
        cerr << "ERROR: Negative bills! (" << k << ")" << endl;
        throw NEGATIVE_BILLS;
      }
    }
    v += GameController::getPlayer(i)->wallet.getBalanceValue();
  }

  v += Bank::Balance.getBalanceValue();
  if(v != INIT_BALANCE) {
    cerr << "ERROR: Amount of money has changed! (" << k << ")" << endl;
    throw TOTAL_AMOUNT_CHANGED;
  }

}

void init() {
  srand(time(NULL));
  Cards::initCards();

  Board::initBoard();

  Bank::initBank();

  INIT_BALANCE = Bank::Balance.getBalanceValue();
  cout << INIT_BALANCE << endl;

  GameController::initGame(N_PLAYERS);

  checkIntegrity(-1);
}

int main() {
  init();

  int k = 0;
  while(k < N_TURNS) {
    try {
      GameController::processTurn();

      checkIntegrity(k);
    }

    catch(int e) {
      cout << "ERROR: " << e << " (" << k << ")" <<endl;
      abort();
    }

    k++;
  }
  return 0;
}

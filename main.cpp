#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "player.h"
#include "cards.h"
#include "eventcard.h"
#include "board.h"
#include "gamecontroller.h"
#include "agmanager.h"

#define N_PLAYERS 3

using namespace std;

TitleDeed* Cards::deeds = (TitleDeed*) malloc(sizeof(TitleDeed)*N_DEEDS);
Railroad* Cards::railroads = (Railroad*) malloc(sizeof(Railroad)*N_RAILROADS);
Utility* Cards::utilities = (Utility*) malloc(sizeof(Utility)*N_UTILITIES);
EventCard* Cards::chance = (EventCard*) malloc(sizeof(EventCard)*N_EVENT_CARDS);
EventCard* Cards::chest = (EventCard*) malloc(sizeof(EventCard)*N_EVENT_CARDS);

vector<Board::Tile> Board::map;
stack<EventCard*> Board::chanceCards;
stack<EventCard*> Board::chestCards;

int INIT_BALANCE;

void checkIntegrity(int k) {
  int i, j, v = 0;
  int players[N_PLAYERS];

  // Check player integrity
  for(i = 0; i < N_PLAYERS; i++) {
    v += GameController::getPlayer(i)->wallet.getBalance();
    players[i] = 0;
  }

  v += Bank::Balance.getBalance();
  if(v != INIT_BALANCE) {
    cerr << "ERROR: Amount of money has changed! (" << k << ")" << endl;
    throw TOTAL_AMOUNT_CHANGED;
  }

  // Check railroad integrity
  for(i = 0; i < N_RAILROADS; i++) {
    if(Cards::railroads[i].owner != -1)
      players[Cards::railroads[i].owner]++;
  }

  for(i = 0; i < N_PLAYERS; i++) {
    if(players[i] != GameController::getPlayer(i)->getOwnedRailroads())
      throw PROPERTY_MISMATCH;
    players[i] = 0;
  }

  // Check utility integrity
  for(i = 0; i < N_UTILITIES; i++) {
    if(Cards::utilities[i].owner != -1)
      players[Cards::utilities[i].owner]++;
  }

  for(i = 0; i < N_PLAYERS; i++) {
    if(players[i] != GameController::getPlayer(i)->getOwnedUtilities())
      throw PROPERTY_MISMATCH;
  }
}

void init() {
  srand(time(NULL));
  Cards::initCards();

  Board::initBoard();

  Bank::initBank();

  INIT_BALANCE = Bank::Balance.getBalance();
  //cout << INIT_BALANCE << endl;

  GameController::initGame(N_PLAYERS);

  checkIntegrity(-1);
}

bool checkWinner() {
  int i, b = 0;
  for(i = 0; i < N_PLAYERS; i++) {
    Player *p = GameController::getPlayer(i);
    if(!p->isBroke)
      b++;
  }
  return b == 1;
}

void checkGameStage(int k) {
  int ownedProperties = 0;
  int totalProperties = N_DEEDS + N_RAILROADS + N_UTILITIES;

  int i;
  for(i = 0; i < N_DEEDS; i++) {
    if(Cards::deeds[i].owner != -1)
      ownedProperties++;
  }
  for(i = 0; i < N_RAILROADS; i++) {
    if(Cards::railroads[i].owner != -1)
      ownedProperties++;
  }
  for(i = 0; i < N_UTILITIES; i++) {
    if(Cards::utilities[i].owner != -1)
      ownedProperties++;
  }

  // Define LATE GAME: more than 50 rounds
  if(k > 50) {
    AGManager::setGameStage(LATE_GAME);
    return;
  }

  // Define EARLY GAME: less than 80% of properties are owned
  if(ownedProperties < 0.8 * totalProperties)
    AGManager::setGameStage(EARLY_GAME);
  else AGManager::setGameStage(MID_GAME);
}

int main() {
  init();

  int k = 0;
  while(k < N_TURNS) {
    try {
      checkGameStage(k);

      GameController::processTurn();

      checkIntegrity(k);

      if(checkWinner()) {
        cout << "GAME ENDED (" << k << ")" << endl;
        return 0;
      }
    }

    catch(int e) {
      cout << "ERROR: " << e << " (" << k << ")" <<endl;
      abort();
    }

    k++;
  }
  return 0;
}

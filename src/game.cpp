#include "game.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "player.h"
#include "cards.h"
#include "eventcard.h"

void Game::checkIntegrity(int k) {
  int i, j, v = 0;
  int players[N_PLAYERS];

  // Check player integrity
  for(i = 0; i < N_PLAYERS; i++) {
    v += gameController.getPlayer(i)->wallet.getBalance();
    players[i] = 0;
  }

  v += bank.Balance.getBalance();
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
    if(players[i] != gameController.getPlayer(i)->getOwnedRailroads())
      throw PROPERTY_MISMATCH;
    players[i] = 0;
  }

  // Check utility integrity
  for(i = 0; i < N_UTILITIES; i++) {
    if(Cards::utilities[i].owner != -1)
      players[Cards::utilities[i].owner]++;
  }

  for(i = 0; i < N_PLAYERS; i++) {
    if(players[i] != gameController.getPlayer(i)->getOwnedUtilities())
      throw PROPERTY_MISMATCH;
  }
}

void Game::initGame() {
  board.initBoard();

  bank.initBank();

  gameController.setBoard(&this->board);
  gameController.setBank(&this->bank);
  gameController.initGameController(&agController, N_PLAYERS);

  checkIntegrity(-1);
}

bool Game::checkWinner() {
  int i, b = 0;
  for(i = 0; i < N_PLAYERS; i++) {
    Player *p = gameController.getPlayer(i);
    if(!p->isBroke)
      b++;
  }
  return b == 1;
}

void Game::checkGameStage(int k) {
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
    agController.setGameStage(LATE_GAME);
    return;
  }

  // Define EARLY GAME: less than 80% of properties are owned
  if(ownedProperties < 0.8 * totalProperties)
    agController.setGameStage(EARLY_GAME);
  else agController.setGameStage(MID_GAME);
}

Player* Game::getWinner() {
  int i;
  for(i = 0; i < N_PLAYERS; i++) {
    Player *p = gameController.getPlayer(i);
    if(!p->isBroke)
      return p;
  }
}

void Game::runGame() {
  initGame();

  int k = 0;
  while(k < N_TURNS) {
    try {
      checkGameStage(k);

      gameController.processTurn();

      checkIntegrity(k);

      if(checkWinner()) {
        cout << "GAME ENDED (" << k << ")" << endl;
        return;
      }
    }

    catch(int e) {
      cout << "ERROR: " << e << " (" << k << ")" <<endl;
      abort();
    }

    k++;
  }
}

#include "game.h"
#include "player.h"
#include "cards.h"
#include "eventcard.h"
#include "utils.h"

#include <iostream>

Game::~Game() {
  // Disown utilites after end of game
  int i;
  for(i = 0; i < N_UTILITIES; i++)
    Cards::utilities[i].owner = -1;

  for(i = 0; i < N_RAILROADS; i++)
    Cards::railroads[i].owner = -1;

  for(i = 0; i < N_DEEDS; i++)
    Cards::deeds[i].owner = -1;
}

void Game::checkIntegrity(int k) {
  int i, j, v = 0;
  int players[N_PLAYERS];

  // Check player integrity
  if(bank.Balance.getBalance() < 0)
    throw NEGATIVE_VALUE;
  for(i = 0; i < N_PLAYERS; i++) {
    v += gameController.getPlayer(i)->wallet.getBalance();
    players[i] = 0;
  }

  // Check total money amount integrity
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

  agController.setGameStage(EARLY_GAME);
}

bool Game::checkWinner() {
  // If exactly one player is not broke, return true
  int i, b = 0;
  for(i = 0; i < N_PLAYERS; i++) {
    Player *p = gameController.getPlayer(i);
    if(!p->isBroke)
      b++;
  }
  return b == 1;
}

void Game::checkGameStage(int k) {
  /* STAGE CHANGE CONDITIONS
   * EARLY GAME: # rounds less than 3 times # of players
   * MIDDLE GAME: # rounds less than 10 times # of players
   * LATE GAME: else
   */
  if(k <= N_PLAYERS * 3)
    agController.setGameStage(EARLY_GAME);

  else if(k <= N_PLAYERS * 10)
    agController.setGameStage(MID_GAME);

  else agController.setGameStage(LATE_GAME);
}

AGPlayer* Game::getWinner() {
  // Pre-condition: must be only one player not broke
  // Return winner
  int i;
  for(i = 0; i < N_PLAYERS; i++) {
    Player *p = gameController.getPlayer(i);
    if(!p->isBroke)
      return p;
  }
}

void Game::runGame() {
  int k = 0;
  while(k < N_TURNS) {
    try {
      // Change stage
      checkGameStage(k);

      // Process turn for current player
      gameController.processTurn();

      // Check game integrity after player turn
      checkIntegrity(k);

      // Check if there is a winner
      if(checkWinner()) {
        if(_VERBOSE)
          cout << "\tGAME ENDED (" << k << ")" << endl;
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

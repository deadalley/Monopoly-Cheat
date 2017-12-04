#include "agcontroller.h"

void AGController::setGameStage(int stage) {
  // Stage didn't change, don't do anything
  if(stage == gameStage)
    return;

  gameStage = stage;
  cout << "-----> GAME STAGE: " << gameStage << " <-----" << endl;

  vector<AGPlayer*>::iterator it;
  for(it = players->begin(); it != players->end(); it++) {
    setPlayerAttributes(*it);
  }
}

void AGController::setPlayers(vector<AGPlayer*> *players) {
  this->players = players;
}

void AGController::setPlayerAttributes(AGPlayer *player) {
  switch(gameStage) {
    case EARLY_GAME: {
      player->buyingChance = 100;
      player->buildingChance = 100;
      player->payingJailChance = 100;
      player->mortgageChance = 100;
      player->minimumBalance = 50;
      player->tradingChance = 100;
      player->minimumCards = 3;
      break;
    }
    case MID_GAME: {
      break;
    }
    case LATE_GAME: {
      break;
    }
  }
}

void AGController::addPlayer(AGPlayer *player) {
  players->push_back(player);
}

AGPlayer* AGController::getPlayer(int i) {
  return players->at(i);
}

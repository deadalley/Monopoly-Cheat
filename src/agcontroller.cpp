#include "agcontroller.h"

void AGController::setGameStage(int stage) {
  // Stage didn't change, don't do anything
  if(stage == gameStage)
    return;

  gameStage = stage;
  cout << "-----> GAME STAGE: " << gameStage << " <-----" << endl;

  vector<AGPlayer*>::iterator it;
  for(it = players->begin(); it != players->end(); it++) {
    (*it)->setStage(stage);
  }
}

void AGController::setPlayers(vector<AGPlayer*> *players) {
  this->players = players;
}

AGPlayer* AGController::getPlayer(int i) {
  return players->at(i);
}

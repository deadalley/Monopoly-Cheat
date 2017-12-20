#include "agcontroller.h"
#include "utils.h"

#include <iostream>

using namespace std;

void AGController::setGameStage(int stage) {
  // Stage didn't change, don't do anything
  if(stage == gameStage)
    return;

  gameStage = stage;
  if(_VERBOSE)
    cout << "-----> GAME STAGE: " << gameStage << " <-----" << endl;

  // Update stage for each player
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

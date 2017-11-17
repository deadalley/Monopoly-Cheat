#include "gamecontroller.h"
#include "player.h"

vector<Player*> GameController::players;

void GameController::initGame(int n_players) {
  //players = new vector<Player*>(n_players);

  int i;
  for(i = 0; i < n_players; i++) {
    Player *p = new Player("Player " + to_string(i + 1));
    players.push_back(p);
  }
}

Player* GameController::getPlayer(int pos) {
  return players.at(pos);
}

void GameController::payAll(Player *player, int value) {
  int i;
  for(i = 0; i < players.size(); i++) {
    player->wallet.payTo(&players.at(i)->wallet, value);
  }
}

void GameController::receiveFromAll(Player *player, int value) {
  int i;
  for(i = 0; i < players.size(); i++) {
    player->wallet.receiveFrom(&players.at(i)->wallet, value);
  }
}

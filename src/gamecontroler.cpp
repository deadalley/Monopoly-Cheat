#include "gamecontroller.h"
#include "player.h"

vector<Player*> GameController::players;
int GameController::activePlayer;

void GameController::initGame(int n_players) {
  int i;
  for(i = 0; i < n_players; i++) {
    Player *p = new Player(i, "Player " + to_string(i + 1));
    players.push_back(p);
  }

  GameController::activePlayer = 0;
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

void GameController::processTurn() {
  Player *player = players.at(activePlayer);

  cout << "=== Started turn for " << player->getName() << endl;
  cout << "\tIs at position " << player->getPosition() << endl;

  int diceValue = Board::rollDice(2);
  cout << "\t" << player->getName() << " rolled " << diceValue << endl;

  int newPosition = (player->getPosition() + diceValue) % 40;
  player->goTo(newPosition);
  cout << "\tLanded on position " << player->getPosition() << endl;

  Board::Tile *tile = Board::getTile(player->getPosition());
  cout << "\tStepped on tile of type " << tile->getType() << endl;
  player->stepOnTile(tile);

  // Update new active player
  GameController::activePlayer++;
  if (GameController::activePlayer >= GameController::players.size())
    GameController::activePlayer = 0;
}

#include "gamecontroller.h"
#include "player.h"

vector<Player*> GameController::players;
int GameController::activePlayer;
int GameController::sequenceOfTurns;

void GameController::initGame(int n_players) {
  int i;
  for(i = 0; i < n_players; i++) {
    Player *p = new Player(i, "Player " + to_string(i + 1));
    players.push_back(p);
  }

  GameController::activePlayer = 0;
  GameController::sequenceOfTurns = 0;
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

  // Dice roll
  int die1 = Board::rollDice(1);
  int die2 = Board::rollDice(1);
  cout << "\t" << player->getName() << " rolled " << die1 << "," << die2 << endl;

  // Check if player is in jail
  if(player->inJail) {
    player->roundsInJail++;
    cout << "\t" << player->getName() << " is " << player->roundsInJail << " rounds in Jail! (oh no)" << endl;
    // Leave if rolled doubles
    if (die1 == die2){
      cout << "\t" << player->getName() << " rolled " << die1 << ", " << die2 << " and left jail" << endl;
      player->inJail = false;
      player->roundsInJail = 0;
    }

    // Leave if has jail card
    else if(player->hasJailCard) {
      cout << "\t" << player->getName() << " has Jail Card and left jail" << endl;
      player->hasJailCard = false;
      player->inJail = false;
    }

    // Leave if paid before rolling doubles
    else if(player->paidToGetOutOfJail()) {
      cout << "\t" << player->getName() << " paid 50 and got out of jail" << endl;
      player->inJail = false;
      player->roundsInJail = 0;
    }

    // Leave if has been in jail three rounds
    else if(player->roundsInJail == 3) {
      if(player->wallet.payTo(&Bank::Balance, 50)) {
        cout << "\t" << player->getName() << " paid 50 and got out of jail" << endl;
        player->inJail = false;
        player->roundsInJail = 0;
      }
    }

    else {
      // Update new active player
      GameController::activePlayer++;
      GameController::sequenceOfTurns = 0;
      if (GameController::activePlayer >= GameController::players.size())
        GameController::activePlayer = 0;
      return;
    }
  }

  // Collect 200 if pass go
  if(player->getPosition() + die1 + die2 >= 40)
    player->wallet.receiveFrom(&Bank::Balance, 200);

  // Move to position
  int newPosition = (player->getPosition() + die1 + die2) % 40;
  player->goTo(newPosition);
  cout << "\tLanded on position " << player->getPosition() << endl;

  Board::Tile *tile = Board::getTile(player->getPosition());
  cout << "\tStepped on tile of type " << tile->getType() << endl;
  player->stepOnTile(tile);

  player->tryToBuild();

  if(die1 == die2) {
    GameController::sequenceOfTurns++;
    // Check if player has rolled doubles three times in a row
    if(GameController::sequenceOfTurns == 3) {
      cout << "\t" << player->getName() << " has rolled doubles three times and has gone to jail" << endl;
      player->goToJail();
    }
  }

  else {
    // Update new active player
    GameController::activePlayer++;
    GameController::sequenceOfTurns = 0;
    if (GameController::activePlayer >= GameController::players.size())
      GameController::activePlayer = 0;
  }

}

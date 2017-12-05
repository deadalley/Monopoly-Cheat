#include "gamecontroller.h"
#include "player.h"
#include "agcontroller.h"

void GameController::initGameController(AGController *agController, int n_players) {
  int i;
  players.clear();

  for(i = 0; i < n_players; i++) {
    Player *p = new Player(i, *agController->getPlayer(i), this);
    players.push_back(p);
  }

  activePlayer = 0;
  sequenceOfTurns = 0;
}

void GameController::setBoard(Board *board) {
  this->board = board;
}

void GameController::setBank(Bank *bank) {
  this->bank = bank;
}

Board* GameController::getBoard() {
  return this->board;
}

Bank* GameController::getBank() {
  return this->bank;
}

int GameController::getPlayerSize() {
  return players.size();
}

Player* GameController::getPlayer(int pos) {
  return players.at(pos);
}

void GameController::payAll(Player *player, int value) {
  int i;
  for(i = 0; i < players.size(); i++) {

    if(i == player->getLocalId())
      continue;

    if(players[i]->isBroke)
      continue;

    if(!player->wallet.payTo(&players.at(i)->wallet, value)) {
      if(player->tryToMortgage(value)) {
        if(!player->wallet.payTo(&players.at(i)->wallet, value)) {
          if(_VERBOSE)
            cout << "\t" << player->getName() << " could not pay " << value << " to " << players[i]->getName() << endl;
          player->goBroke();
        }
      }
      else {
        if(_VERBOSE)
          cout << "\t" << player->getName() << " could not pay " << value << " to " << players[i]->getName() << endl;
        player->goBroke();
      }
    }
  }
}

void GameController::receiveFromAll(Player *player, int value) {
  int i;
  if(_VERBOSE)
    cout << players.size() << endl;
  for(i = 0; i < players.size(); i++) {

    if(i == player->getLocalId())
      continue;

    if(players[i]->isBroke)
      continue;

    if(!players.at(i)->wallet.payTo(&player->wallet, value)) {
      if(players.at(i)->tryToMortgage(value)) {
        if(!players.at(i)->wallet.payTo(&player->wallet, value)) {
          if(_VERBOSE)
            cout << "\t" << players.at(i)->getName() << " could not pay " << value << " to " << player->getName() << endl;
          players[i]->goBroke();
          break;
        }
      }
      else {
        if(_VERBOSE)
          cout << "\t" << players.at(i)->getName() << " could not pay " << value << " to " << player->getName() << endl;
        players[i]->goBroke();
        break;
      }
    }
  }
}

void GameController::processTurn() {
  Player *player = players.at(activePlayer);

  if(_VERBOSE)
    cout << "=== Started turn for " << player->getName() << endl;
  if(player->isBroke) {
    cout << "\t" << player->getName() << " is broke! " << endl;
    GameController::activePlayer++;
    GameController::sequenceOfTurns = 0;
    if (GameController::activePlayer >= GameController::players.size())
      GameController::activePlayer = 0;
    return;
  }

  if(_VERBOSE) {
    cout << "\t" << player->getName() << " has $" << player->wallet.getBalance() << endl;
    cout << "\tIs at position " << player->getPosition() << endl;
  }

  // Dice roll
  board->rollDice();
  int die1 = board->getDie(0);
  int die2 = board->getDie(1);
  if(_VERBOSE)
    cout << "\t" << player->getName() << " rolled " << die1 << "," << die2 << endl;

  // Check if player is in jail
  if(player->inJail) {
    player->roundsInJail++;
    if(_VERBOSE)
      cout << "\t" << player->getName() << " is " << player->roundsInJail << " rounds in Jail! (oh no)" << endl;
    // Leave if rolled doubles
    if (die1 == die2){
      if(_VERBOSE)
        cout << "\t" << player->getName() << " rolled " << die1 << ", " << die2 << " and left jail" << endl;
      player->inJail = false;
      player->roundsInJail = 0;
    }

    // Leave if has jail card
    else if(player->hasJailCard) {
      if(_VERBOSE)
        cout << "\t" << player->getName() << " has Jail Card and left jail" << endl;
      player->hasJailCard = false;
      player->inJail = false;
    }

    // Leave if paid before rolling doubles
    else if(player->paidToGetOutOfJail()) {
      if(_VERBOSE)
        cout << "\t" << player->getName() << " paid 50 and got out of jail" << endl;
      player->inJail = false;
      player->roundsInJail = 0;
    }

    // Leave if has been in jail three rounds
    else if(player->roundsInJail == 3) {
      if(player->wallet.getBalance() < 50) {
        // TODO: Mortgage
      }
      else if(player->wallet.payTo(&bank->Balance, 50)) {
        if(_VERBOSE)
          cout << "\t" << player->getName() << " paid 50 and got out of jail" << endl;
        player->inJail = false;
        player->roundsInJail = 0;
      }
      else throw PAY_FAILED;
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

  // Move to position
  int newPosition = (player->getPosition() + die1 + die2) % 40;
  player->goTo(newPosition);
  if(_VERBOSE)
    cout << "\tLanded on position " << player->getPosition() << endl;

  // Process tile
  Board::Tile *tile = board->getTile(player->getPosition());
  if(_VERBOSE)
    cout << "\tStepped on tile of type " << tile->getType() << endl;
  player->stepOnTile(tile);

  if(player->isBroke) {
    if(_VERBOSE)
      cout << "\t" << player->getName() << " is broke! " << endl;
    GameController::activePlayer++;
    GameController::sequenceOfTurns = 0;
    if (GameController::activePlayer >= GameController::players.size())
      GameController::activePlayer = 0;
    return;
  }

  // Try to trade
  player->tryToTrade();

  // Try to build after turn is processed
  player->tryToBuild();

  if(_VERBOSE)
    cout << "\t" << player->getName() << " has $" << player->wallet.getBalance() << endl;

  if(die1 == die2) {
    GameController::sequenceOfTurns++;
    // Check if player has rolled doubles three times in a row
    if(GameController::sequenceOfTurns == 3) {
      if(_VERBOSE)
        cout << "\t" << player->getName() << " has rolled doubles three times and has gone to jail" << endl;
      player->goToJail();
    }
    else return;
  }
  // Update new active player
  GameController::activePlayer++;
  GameController::sequenceOfTurns = 0;
  if (GameController::activePlayer >= GameController::players.size())
    GameController::activePlayer = 0;
}

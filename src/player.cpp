#include "player.h"
#include "gamecontroller.h"

Player::Player(string name) {
  this->name = name;
  this->position = GO;

  //this->wallet = 0;

  // Set player's initial balance
  Bills initialBalance;
  initialBalance.ones = 5;
  initialBalance.fives = 1;
  initialBalance.tens = 2;
  initialBalance.twenties = 1;
  initialBalance.fifties = 1;
  initialBalance.one_hundreds = 4;
  initialBalance.five_hundreds = 2;

  if(Bank::Balance.deduct(initialBalance))
    this->wallet.setBalance(initialBalance);
}

string Player::getName() {
  return this->name;
}

void Player::processEventCard(EventCard *card) {
  switch(card->effectType) {
    case Collect:
      this->wallet.receiveFrom(&Bank::Balance, card->value);
      break;
    case Pay:
      this->wallet.payTo(&Bank::Balance, card->value);
      break;
    case GoToTile:
      goTo(card->tile);
      break;
    case GoToUtility:
      //TO DO
      break;
    case GoToRailroad:
      switch(position) {
        case CHANCE_1:
          goTo(PENNSYLVANIA_RR);
          break;
        case CHANCE_2:
          goTo(BO_RR);
          break;
        case CHANCE_3:
          goTo(READING_RR);
          break;
      }
      break;
    case GoBack3:
      goTo(this->position - 3);
      break;
    case GoToJail:
      goToJail();
      break;
    case PayForEach:
      //TO DO
      break;
    case PayToAll:
      GameController::payAll(this, card->value);
      break;
    case ReceiveFromAll:
      GameController::receiveFromAll(this, card->value);
      break;
  }
}

void Player::stepOnTile(Board::Tile tile) {
  cout << "Tile Type: " << tile.getType() << endl;
  switch (tile.getType()){
    case PropertyTile:
      // Implement PropertyTile behavior
      break;
    case ChestTile:
      processEventCard(tile.getEventCard());
      break;
    case ChanceTile:
      processEventCard(tile.getEventCard());
      break;
    case JailTile:
      // nothing to do here
      break;
    case GoToJailTile:
      this->goToJail();
      break;
    case GoTile:
      // nothing to do here
      break;
    case FreeParkingTile:
      // nothing to do here
      break;
    case IncomeTaxTile:
      //this->payBank(200);
      this->wallet.payTo(&Bank::Balance, 200);
      break;
    case LuxuryTaxTile:
      //this->payBank(100);
      this->wallet.payTo(&Bank::Balance, 100);
      break;
  }
}

void Player::goTo(int position) {

}

void Player::goToJail() {

}

#include "player.h"

Player::Player(string name) {
  this->name = name;
  this->position = GO;

  Bills initialBalance;
  initialBalance.ones = 5;
  initialBalance.fives = 1;
  initialBalance.tens = 2;
  initialBalance.twenties = 1;
  initialBalance.fifties = 1;
  initialBalance.one_hundreds = 4;
  initialBalance.five_hundreds = 2;

  this->receive(initialBalance);
}

void Player::stepOnTile(Board::Tile tile) {
  switch (tile.getType()){
    case PropertyTile:
      // Implement PropertyTile behavior
      break;
    case ChestTile: {
      EventCard* chest = tile.getEventCard();
      // Implement Chest Event Card
      break;
    }
    case ChanceTile: {
      EventCard* chance = tile.getEventCard();
      // Implement Chance Event Card
      break;
    }
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
      this->payBank(200);
      break;
    case LuxuryTaxTile:
      this->payBank(100);
      break;
  }
}

void Player::payAll (int value) {

}

void Player::receive (Bills transaction) {

}

void Player::payBank (int value) {

}

void Player::goToJail() {
  
}

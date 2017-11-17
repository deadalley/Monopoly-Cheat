#include "player.h"
#include "gamecontroller.h"

Player::Player(string name) {
  this->name = name;
  this->position = GO;

  // Set player's initial balance
  Bills initialBalance;
  initialBalance.ones = 5;
  initialBalance.fives = 1;
  initialBalance.tens = 2;
  initialBalance.twenties = 1;
  initialBalance.fifties = 1;
  initialBalance.one_hundreds = 4;
  initialBalance.five_hundreds = 2;

  this->wallet.receiveFrom(&Bank::Balance, initialBalance);
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
      switch(position) {
        case CHANCE_1:
          goTo(ELECTRIC_CO);
          break;
        case CHANCE_2:
          goTo(WATER_WORKS);
          break;
        case CHANCE_3:
          goTo(ELECTRIC_CO);
          break;
      }
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
    case GeneralRepairs: {
      int i;
      for(i = 0; i < this->cards.size(); i++) {
        Card *card = this->cards.at(i);
        if(card->getType() == PropertyCard) {
          TitleDeed *property = (TitleDeed*) card;
          this->wallet.payTo(&Bank::Balance, 25*property->n_houses);
          this->wallet.payTo(&Bank::Balance, 100*property->n_hotels);
        }
      }
      break;
    }
    case StreetRepairs: {
      int i;
      for(i = 0; i < this->cards.size(); i++) {
        Card *card = this->cards.at(i);
        if(card->getType() == PropertyCard) {
          TitleDeed *property = (TitleDeed*) card;
          this->wallet.payTo(&Bank::Balance, 40*property->n_houses);
          this->wallet.payTo(&Bank::Balance, 115*property->n_hotels);
        }
      }
      break;
    }
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
  if(position < this->position)
    this->wallet.receiveFrom(&Bank::Balance, 200);

  this->position = position;
}

void Player::goToJail() {

}

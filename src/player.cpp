#include "player.h"
#include "gamecontroller.h"

Player::Player(int id, string name) {
  this->id = id;
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
  this->inJail = false;

  this->buyingChance = 100;
}

string Player::getName() {
  return this->name;
}

void Player::processEventCard(EventCard *card) {
  cout << "\t" << name << " drew " << card->description << endl;
  switch(card->effectType) {
    case Collect:
      this->wallet.receiveFrom(&Bank::Balance, card->value);
      cout << "\t" << name << " collected " << card->value << endl;
      break;
    case Pay:
      if(this->wallet.payTo(&Bank::Balance, card->value))
        cout << "\t" << name << " paid " << card->value << endl;
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

void Player::buy(Card *card) {
  if(wallet.payTo(&Bank::Balance, card->price)) {
    cards.push_back(card);
    card->owner = this->id;
    cout << "\t" << name << " bought " << card->name << endl;
  }

  else cout << "\t" << name << " does not have enough credit to buy " << card->name << endl;
}

void Player::stepOnTile(Board::Tile *tile) {
  //cout << "Tile Type: " << tile->getType() << endl;
  switch (tile->getType()){
    case PropertyTile: {
      Card *card = tile->getCard();
      if(id == card->owner)
        cout << "\t" << name << " already owns " << card->name << endl;
      else {
        if(card->owner != -1)
          cout << "\t" << "Player " << (card->owner+1) << " owns " << card->name << endl;

        else {
          cout << "\t" << name << " has " << buyingChance << "\% chance of buying " << card->name << endl;
          int chance = rand() % 100;
          if(chance <= buyingChance)
            buy(card);
        }
      }
      break;
    }
    case ChestTile:
      processEventCard(tile->getEventCard());
      break;
    case ChanceTile:
      processEventCard(tile->getEventCard());
      break;
    case JailTile:
      // nothing to do here
      cout << "\t" << name << " landed on Jail (no worries!)" << endl;
      break;
    case GoToJailTile:
      cout << "\t" << name << " landed on Go To Jail (oh no!)" << endl;
      this->goToJail();
      break;
    case GoTile:
      // nothing to do here
      cout << "\t" << name << " landed on GO" << endl;
      break;
    case FreeParkingTile:
      // nothing to do here
      cout << "\t" << name << " landed on Free Parking" << endl;
      break;
    case IncomeTaxTile:
      if(this->wallet.payTo(&Bank::Balance, 200))
        cout << "\t" << name << " paid 200 in Income Tax" << endl;
      break;
    case LuxuryTaxTile:
      if(this->wallet.payTo(&Bank::Balance, 100))
        cout << "\t" << name << " paid 100 in Luxury Tax" << endl;
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

int Player::getPosition() {
  return this->position;
}

bool Player::isInJail() {
  return inJail;
}

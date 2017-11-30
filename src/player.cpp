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
  this->hasJailCard = false;
  this->roundsInJail = 0;

  this->buyingChance = 100;
  this->buildingChance = 100;
  this->payingJailChance = 80;
  this->mortgageChance = 30;
  this->minimumBalance = 100;
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
      if(card->tile == GO) {
        cout << "\t" << name << " advanced to Go and collected 200" << endl;
        wallet.receiveFrom(&Bank::Balance, 200);
      }
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
    case GoBack3: {
      int newPosition = this->position - 3;
      if(newPosition < 0)
        newPosition = 40 + newPosition;
      this->position = newPosition;
      //goTo(newPosition);
      break;
    }
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
          if(property->hasHotel)
            this->wallet.payTo(&Bank::Balance, 100);
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
          if(property->hasHotel)
            this->wallet.payTo(&Bank::Balance, 115);
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
    if(card->getType() == PropertyCard) {
      TitleDeed *deed = (TitleDeed*) card;
      colorSets[deed->color]++;
      //cout << "\t\t" << deed->color << ": " << colorSets[deed->color] << endl;
    }
  }

  else cout << "\t" << name << " does not have enough credit to buy " << card->name << endl;
}

void Player::stepOnTile(Board::Tile *tile) {
  switch (tile->getType()){
    case PropertyTile: {
      Card *card = tile->getCard();
      // Player already owns card
      if(id == card->owner)
        cout << "\t" << name << " already owns " << card->name << endl;
      else {
        // Card is owned by another player
        if(card->owner != -1) {
          cout << "\t" << "Player " << (card->owner+1) << " owns " << card->name << endl;
          if(card->isMortgaged)
            break;

          // Pay rent
          if(card->getType() == PropertyCard) {
            Player *otherPlayer = GameController::getPlayer(card->owner);
            TitleDeed *property = (TitleDeed*) card;
            int rent = 0;
            if(property->hasHotel)
              rent = property->rent[5];
            else rent = property->rent[property->n_houses];

            if(wallet.payTo(&otherPlayer->wallet, rent))
              cout << "\t" << name << " paid " << rent << " to " << otherPlayer->getName() << endl;
          }
        }

        // Nobody owns card. Player may buy it
        else {
          if((this->wallet.getBalanceValue() - card->price) < this->minimumBalance) {
            cout << "\t" << name << " is at minimum balance" << endl;
          }
          else {
            cout << "\t" << name << " has " << buyingChance << "\% chance of buying " << card->name << endl;
            int chance = rand() % 100;
            if(chance <= buyingChance)
              buy(card);
          }
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
  this->inJail = true;
  this->position = JAIL;
}

int Player::getPosition() {
  return this->position;
}

void Player::build(TitleDeed *deed) {
  if(deed->hasHotel)
    return;

  if(deed->n_houses == 4) {
    if(this->wallet.payTo(&Bank::Balance, deed->hotel_cost)) {
      deed->n_houses = 0;
      deed->hasHotel = true;
      cout << "\t" << name << " built a hotel on " << deed->name << endl;
      return;
    }
  }

  if(this->wallet.payTo(&Bank::Balance, deed->house_cost)) {
    deed->n_houses++;
    cout << "\t" << name << " built a house on " << deed->name << endl;
  }

  else cout << "\t" << name << " could not build on " << deed->name << endl;
}

void Player::tryToBuild() {
  if((this->wallet.getBalanceValue()) <= this->minimumBalance) {
    cout << "\t" << name << " is at minimum balance" << endl;
    return;
  }

  cout << "\t" << name << " has " << buildingChance << "\% chance of building" << endl;
  int chance = rand() % 100;

  // Check if player has all cards of same color for building
  string colors[8] = {"purple", "cyan", "pink", "orange", "red", "yellow", "green", "blue"};
  if(chance <= buildingChance) {
    cout << "\t" << name << " owns " << endl;
    int i;
    for(i = 0; i < 8; i++) {
      cout << "\t\t" << colors[i] << ": " << colorSets[colors[i]] << endl;
      // If purple or cyan and has two OR has three of any other color
      if( ((i == 0 || i == 7) && colorSets[colors[i]] == 2) ||
           colorSets[colors[i]] == 3) {
        // Find first card of that color for building
        TitleDeed *property;
        int j;
        for(j = 0; j < cards.size(); j++) {
          property = (TitleDeed*) cards[j];
          if(property->color == colors[i])
            this->build(property);
        }
      }
    }
  }
  else {
    cout << "\t" << name << " did not build anything this round" << endl;
  }
}

bool Player::paidToGetOutOfJail() {
  if((this->wallet.getBalanceValue() - 50) < this->minimumBalance) {
    cout << "\t" << name << " is at minimum balance" << endl;
  }

  cout << "\t" << name << " has " << payingJailChance << "\% chance of paying to leave jail" << endl;
  int chance = rand() % 100;

  if(chance <= payingJailChance) {
    return wallet.payTo(&Bank::Balance, 50);
  }

  return false;
}

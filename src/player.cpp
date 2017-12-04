#include "player.h"
#include "utils.h"
#include "gamecontroller.h"

#include <map>

Player::Player(int localId, const AGPlayer &agPlayer, GameController *controller) : AGPlayer(agPlayer){
  this->localId = localId;
  this->name = "Player " + to_string(id + 1);
  this->position = GO;

  this->gameController = controller;

  this->inJail = false;
  this->isBroke = false;
  this->hasJailCard = false;
  this->roundsInJail = 0;
  this->ownedRailroads = 0;
  this->ownedUtilities = 0;

  gameController->getBank()->Balance.payTo(&this->wallet, 1500);
}

string Player::getName() {
  return this->name;
}

int Player::getLocalId() {
  return this->localId;
}

int Player::getPosition() {
  return this->position;
}

int Player::getOwnedUtilities() {
  return ownedUtilities;
}

int Player::getOwnedRailroads() {
  return ownedRailroads;
}

ColorSet* Player::getColorSet(Color color) {
  int i;
  for(i = 0; i < colorsets.size(); i++) {
    if(colorsets[i]->getColor() == color)
      return colorsets[i];
  }
  return NULL;
}

void Player::goTo(int position) {
  if(position < this->position) {
    if(gameController->getBank()->Balance.payTo(&this->wallet, 200)) {
      cout << "\t" << name << " passed GO and received 200 from Bank" << endl;
    }

    else {
      cout << "\t Bank cannot pay $200 to player. Not enough credit in bank." << endl;
    }
  }

  this->position = position;
}

void Player::goToJail() {
  this->inJail = true;
  this->position = JAIL;
}

void Player::stepOnTile(Board::Tile *tile) {
  switch (tile->getType()){
    case PropertyTile: {
      Card *card = tile->getCard();

      // Player already owns card
      if(id == card->owner)
        cout << "\t" << name << " already owns " << card->name << endl;
      // Card is owned by another player
      else if(card->owner != -1) {
        cout << "\t" << "Player " << (card->owner+1) << " owns " << card->name << endl;
        // Don't pay rent if card is mortgaged
        if(card->isMortgaged)
          break;

        Player *otherPlayer = gameController->getPlayer(card->owner);
        int rent = 0;

        // Calculate rent
        switch(card->getType()) {
          case PropertyCard: {
            TitleDeed *property = (TitleDeed*) card;

            if(property->hasHotel)
              rent = property->rent[5];
            else rent = property->rent[property->n_houses];
            break;
          }
          case UtilityCard: {
            if(otherPlayer->getOwnedUtilities() == 1)
              rent = 4 * (gameController->getBoard()->getDie(0) + gameController->getBoard()->getDie(1));

            else if(otherPlayer->getOwnedUtilities() == 2)
              rent = 10 * (gameController->getBoard()->getDie(0) + gameController->getBoard()->getDie(1));
            break;
          }
          case RailroadCard: {
            Railroad *railroad = (Railroad*) card;

            rent = railroad->rent[otherPlayer->getOwnedRailroads() - 1];
            break;
          }
        }

        // Pay rent - OBLIGATORY PAY
        cout << "\t" << name << " is paying " << rent << " to " << otherPlayer->getName() << endl;
        if(wallet.payTo(&otherPlayer->wallet, rent))
          cout << "\t" << name << " paid " << rent << " to " << otherPlayer->getName() << endl;
        else {
          tryToMortgage(rent);
          if(!this->wallet.payTo(&otherPlayer->wallet, rent)) {
            cout << "\t" << name << " could not pay $" << rent << " to " << otherPlayer->getName() << endl;
            goBroke();
          }
        }
      }
      // Nobody owns card. Player may buy it
      else {
        if((this->wallet.getBalance() - card->price) < this->getMinimumBalance())
          cout << "\t" << name << " is at minimum balance. Property not bought." << endl;

        else {
          cout << "\t" << name << " has " << getBuyingChance() << "\% chance of buying " << card->name << endl;
          int chance = rand() % 100;
          if(chance <= getBuyingChance())
            buy(card);
        }
      }
      break;
    }
    case ChestTile:
      processEventCard(gameController->getBoard()->getEventCard(tile->getType()));
      break;
    case ChanceTile:
      processEventCard(gameController->getBoard()->getEventCard(tile->getType()));
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
      // OBLIGATORY PAY
      if(this->wallet.payTo(&gameController->getBank()->Balance, 200))
        cout << "\t" << name << " paid 200 in Income Tax" << endl;
      else {
        tryToMortgage(200);
        if(this->wallet.payTo(&gameController->getBank()->Balance, 200))
          cout << "\t" << name << " paid 200 in Income Tax" << endl;
        else {
          cout << "\t" << name << " could not pay 200 as Income Tax" << endl;
          goBroke();
        }
      }

      break;
    case LuxuryTaxTile:
      // OBLIGATORY PAY
      if(this->wallet.payTo(&gameController->getBank()->Balance, 100))
        cout << "\t" << name << " paid 100 in Luxury Tax" << endl;
      else {
        tryToMortgage(100);
        if(this->wallet.payTo(&gameController->getBank()->Balance, 100))
          cout << "\t" << name << " paid 100 in Luxury Tax" << endl;
        else {
          cout << "\t" << name << " could not pay 100 as Luxury Tax" << endl;
          goBroke();
        }
      }
      break;
  }
}

void Player::processEventCard(EventCard *card) {
  cout << "\t" << name << " drew " << card->description << endl;
  // Switch type of drawn card
  switch(card->effectType) {
    // Receive amount from Bank
    case Collect:
      //this->wallet.receiveFrom(&gameController->getBank()->Balance, card->value);
      gameController->getBank()->Balance.payTo(&this->wallet, card->value);
      cout << "\t" << name << " collected " << card->value << endl;
      break;

    // Pay amount to bank
    case Pay:
      if(this->wallet.payTo(&gameController->getBank()->Balance, card->value))
        cout << "\t" << name << " paid " << card->value << endl;
      break;

    // Move to tile
    case GoToTile:
      goTo(card->tile);
      break;

    // Go to next utility
    case GoToUtility: {
      int destination = -1;
      switch(position) {
        case CHANCE_1:
          destination = ELECTRIC_CO;
          break;
        case CHANCE_2:
          destination = WATER_WORKS;
          break;
        case CHANCE_3:
        destination = ELECTRIC_CO;
          break;
        default:
          throw ANY_ERROR;
          break;
      }

      goTo(destination);

      Utility *utility = (Utility*) gameController->getBoard()->getTile(destination)->getCard();
      // Unowned. Player may buy it
      if(utility->owner == -1) {
        if((this->wallet.getBalance() - utility->price) < this->getMinimumBalance()) {
          cout << "\t" << name << " is at minimum balance. Utility not bought." << endl;
        }
        else {
          cout << "\t" << name << " has " << getBuyingChance() << "\% chance of buying " << utility->name << endl;
          int chance = rand() % 100;
          if(chance <= getBuyingChance())
            buy(utility);
        }
      }

      // Card owned by another player
      else if(utility->owner != id) {
        cout << "\t" << "Player " << (utility->owner+1) << " owns " << utility->name << endl;

        Player *otherPlayer = gameController->getPlayer(utility->owner);

        gameController->getBoard()->rollDice();
        int rent = 10 * (gameController->getBoard()->getDie(0) + gameController->getBoard()->getDie(1));
        if(wallet.payTo(&otherPlayer->wallet, rent))
          cout << "\t" << name << " paid " << rent << " to " << otherPlayer->getName() << endl;
        else if(tryToMortgage(rent)) {
          if(wallet.payTo(&otherPlayer->wallet, rent))
            cout << "\t" << name << " paid " << rent << " to " << otherPlayer->getName() << endl;
          else {
            cout << "\t" << name << " could not pay " << rent << " to " << otherPlayer->getName() << endl;
            goBroke();
          }
        }
      }
      break;
    }

    // Go to next railroad
    case GoToRailroad: {
      int destination = -1;
      switch(position) {
        case CHANCE_1:
          destination = PENNSYLVANIA_RR;
          break;
        case CHANCE_2:
          destination = BO_RR;
          break;
        case CHANCE_3:
          destination = READING_RR;
          break;
        default:
          throw ANY_ERROR;
          break;
      }

      goTo(destination);
      Railroad *railroad = (Railroad*) gameController->getBoard()->getTile(destination)->getCard();

      // Unowned. Player may buy it
      if(railroad->owner == -1) {
        if((this->wallet.getBalance() - railroad->price) < this->getMinimumBalance()) {
          cout << "\t" << name << " is at minimum balance. Railroad not bought." << endl;
        }
        else {
          cout << "\t" << name << " has " << getBuyingChance() << "\% chance of buying " << railroad->name << endl;
          int chance = rand() % 100;
          if(chance <= getBuyingChance())
            buy(railroad);
        }
      }

      // Card owned by another player
      else if(railroad->owner != id) {
        cout << "\t" << "Player " << (railroad->owner+1) << " owns " << railroad->name << endl;

        Player *otherPlayer = gameController->getPlayer(railroad->owner);

        int rent = 2 * railroad->rent[otherPlayer->getOwnedRailroads() - 1];

        // OBLIGATORY PAY
        if(wallet.payTo(&otherPlayer->wallet, rent))
          cout << "\t" << name << " paid " << rent << " to " << otherPlayer->getName() << endl;
        else if(tryToMortgage(rent)){
          if(wallet.payTo(&otherPlayer->wallet, rent))
            cout << "\t" << name << " paid " << rent << " to " << otherPlayer->getName() << endl;
          else {
            cout << "\t" << name << " coult not pay " << rent << " to " << otherPlayer->getName() << endl;
            goBroke();
          }
          //throw PAY_FAILED;
        }
        else goBroke();
      }
      break;
    }

    // Go back 3 spaces
    case GoBack3: {
      int newPosition = this->position - 3;
      if(newPosition < 0)
        newPosition = 40 + newPosition;
      this->position = newPosition;
      //goTo(newPosition);
      break;
    }

    // Go to jail
    case GoToJail:
      goToJail();
      break;

    // Receive get out of jail for free card
    case GetOutJail:
      this->hasJailCard = true;
      break;
      
    // Pay for each house and hotel
    case GeneralRepairs: {
      int i;
      for(i = 0; i < colorsets.size(); i++) {
        int j;
        ColorSet *set = colorsets[i];
        for(j = 0; j < set->getSize(); j++) {
          TitleDeed *property = set->getCard(j);
          // Pay for hotel
          if(property->hasHotel) {
            // OBLIGATORY PAY
            if(!this->wallet.payTo(&gameController->getBank()->Balance, 100)) {
              if(tryToMortgage(100)){
                if(!this->wallet.payTo(&gameController->getBank()->Balance, 100))
                  goBroke();
              }
              else {
                goBroke();
              }
            }
              //throw PAY_FAILED;
          }
          // Pay for houses
          else if(property->n_houses > 0) {
            if(!this->wallet.payTo(&gameController->getBank()->Balance, 25*property->n_houses)) {
              if(tryToMortgage(25*property->n_houses)) {
                if(!this->wallet.payTo(&gameController->getBank()->Balance, 25*property->n_houses))
                  goBroke();
              }
              else goBroke();
            }
              //throw PAY_FAILED;
          }
        }
      }
      break;
    }

    // Pay for each house and hotel
    case StreetRepairs: {
      int i;
      for(i = 0; i < colorsets.size(); i++) {
        int j;
        ColorSet *set = colorsets[i];
        for(j = 0; j < set->getSize(); j++) {
          TitleDeed *property = set->getCard(j);
          // Pay for hotel
          if(property->hasHotel) {
            if(!this->wallet.payTo(&gameController->getBank()->Balance, 115)) {
              if(tryToMortgage(115)) {
                if(!this->wallet.payTo(&gameController->getBank()->Balance, 115))
                  goBroke();
              }
              else goBroke();
            }
              //throw PAY_FAILED;
          }

          else if(property->n_houses > 0) {
            if(!this->wallet.payTo(&gameController->getBank()->Balance, 40*property->n_houses)) {
              if(tryToMortgage(40*property->n_houses)) {
                if(!this->wallet.payTo(&gameController->getBank()->Balance, 40*property->n_houses))
                  goBroke();
              }
              else goBroke();
            }
              //throw PAY_FAILED;
          }
        }
      }
      break;
    }
    case PayToAll:
      gameController->payAll(this, card->value);
      break;
    case ReceiveFromAll:
      gameController->receiveFromAll(this, card->value);
      break;
  }
}

void Player::buy(Card *card) {
  if(wallet.payTo(&gameController->getBank()->Balance, card->price)) {
    card->owner = this->localId;

    cout << "\t" << name << " bought " << card->name << ", " << card->owner << endl;

    switch(card->getType()) {
      // Increase owned of color
      case PropertyCard: {
        TitleDeed *deed = (TitleDeed*) card;
        int i;
        ColorSet *set = NULL;
        // Add card to color set
        for(i = 0; i < colorsets.size(); i++) {
          set = colorsets[i];
          if(set->getColor() == deed->color) {
            set->addCard(deed);
            break;
          }
        }
        // Color set not present
        if(i == colorsets.size()) {
          set = new ColorSet(deed->color);
          set->addCard(deed);
          colorsets.push_back(set);
        }
        break;
      }
      // Increase number of owned utilities
      case UtilityCard:
        ownedUtilities++;
        break;
      // Increase number of owned railroads
      case RailroadCard:
        ownedRailroads++;
        break;
    }
  }

  else {
    cout << "\t" << name << " does not have enough credit to buy " << card->name << endl;
  }
}

void Player::build(TitleDeed *deed) {
  if(deed->hasHotel) {
    cout << "\t" << deed->name << " has hotel. Cannot build anymore." << endl;
    return;
  }

  if(deed->n_houses == 4) {
    cout << "\tBuilding hotel on " << deed->name << " with cost " << deed->hotel_cost << endl;
    if(this->wallet.payTo(&gameController->getBank()->Balance, deed->hotel_cost)) {
      deed->n_houses = 0;
      deed->hasHotel = true;
      cout << "\t" << name << " built a hotel on " << deed->name << endl;
      return;
    }
    else {
      cout << "\t" << name << " could build a hotel on " << deed->name << endl;
      return;
    }
  }

  cout << "\tBuilding house on " << deed->name << " with cost " << deed->house_cost << endl;
  if(this->wallet.payTo(&gameController->getBank()->Balance, deed->house_cost)) {
    deed->n_houses++;
    cout << "\t" << name << " built a house on " << deed->name << endl;
    return;
  }
  else {
    cout << "\t" << name << " could not build a house on " << deed->name << endl;
    return;
  }
}

void Player::trade(Player *otherPlayer, TitleDeed *deed, int offeredPrice) {
  if(!this->wallet.payTo(&otherPlayer->wallet, offeredPrice)) {
    cout << "\t" << name << " does not have enough money to trade with " << otherPlayer->getName() << endl;
    throw PAY_FAILED;
  }

  deed->owner = this->localId;

  getColorSet(deed->color)->addCard(deed);

  otherPlayer->getColorSet(deed->color)->removeCard(deed);
}

void Player::tryToBuild() {
  cout << "\t" << name << " is deciding to build" << endl;
  if(this->wallet.getBalance() <= this->getMinimumBalance()) {
    cout << "\t" << name << " is at minimum balance. Nothing was built." << endl;
    return;
  }

  cout << "\t" << name << " has " << getBuildingChance() << "\% chance of building" << endl;
  int chance = rand() % 100;

  // Check if player has all cards of same color for building
  if(chance <= getBuildingChance()) {
    cout << "\t" << name << " owns:" << endl;
    int i;
    // Iterate color sets
    for(i = 0; i < colorsets.size(); i++) {
      ColorSet *colorset = colorsets[i];
      cout << "\t\t" << colorset->getName() << "(" << colorset->getSize() << "):" << endl;
      // Iterate owned cards of color set
      int j;
      for(j = 0; j < colorset->getSize(); j++) {
        cout << "\t\t\t" << colorset->getCard(j)->name;
        cout << "(" << colorset->getCard(j)->n_houses << "), " << colorset->getCard(j)->hasHotel << endl;
      }

      // Can't build if a card is mortgaged
      if(colorset->hasMortgage())
        continue;

      // If has all cards, build
      if(colorset->hasAllCards()) {
        for(j = 0; j < colorset->getSize(); j++) {
          // Check if number of houses is equal to the minimum of the set
          if(colorset->getCard(j)->n_houses == colorset->getMinHouse())
            build(colorset->getCard(j));
        }
      }
    }
  }
  else cout << "\t" << name << " did not build anything this round" << endl;
}

bool Player::tryToMortgage(int value) {
  // TODO: FIX MORTGAGE
  return false;
  cout << "\t" << name << " is trying to mortgage" << endl;
  int i, m = 5000, minIndexI = -1, minIndexJ = -1;
  // Find the minimum mortgage to cover for debt
  for(i = 0; i < colorsets.size(); i++) {
    ColorSet *set = colorsets[i];
    int j;
    // If there is no improvement, find the lowest mortgage to cover
    if(!set->hasImprovement()) {
      for(j = 0; j < set->getSize(); j++) {
        TitleDeed *deed = set->getCard(j);
        if(deed->price >= value && deed->price < m) {
          m = deed->price;
          minIndexJ = j;
          minIndexI = i;
        }
      }
    }
    // If there are improvement, get min price to mortgage
    else {/*
      int q = 0;
      for(j = 0; j < set->getSize(); j++) {
        TitleDeed *deed = set->getCard(j);
        q += deed->n_houses * (deed->house_cost/2);
        if(deed->price >= value && deed->price < min) {
          min = deed->price;
          minIndex = j;
        }
      }*/
    }
  }
  if(minIndexI != -1 && minIndexJ != -1) {
    TitleDeed *deed = colorsets[minIndexI]->getCard(minIndexJ);
    deed->isMortgaged = true;
    gameController->getBank()->Balance.payTo(&this->wallet, deed->mortgage);
    cout << "\t" << name << " mortgaged " << deed->name << " to the bank" << endl;
    return true;
  }
  return false;
}

void Player::tryToTrade() {
  cout << "\t" << name << " is trying to trade cards" << endl;

  // Check if player needs to acquire any cards this round
  if(colorsToAcquire().size() == 0) {
    cout << "\t" << name << " has no cards and did not trade this round" << endl;
    return;
  }

  int chance = rand() % 100;
  cout << "\t" << name << " has " << getTradingChance() << "\% chance of trading" << endl;

  if(chance <= getTradingChance()) {
    int i;
    // Find player to trade
    for(i = 0; i < gameController->getPlayerSize(); i++) {
      Player *otherPlayer = gameController->getPlayer(i);

      // Skip if it's this player
      if(otherPlayer->getLocalId() == this->localId)
        continue;

      // Skip if player is broke
      if(otherPlayer->isBroke)
        continue;

      // Find colors that players can trade/sell/buy
      vector<Color> colors = matchTrade(otherPlayer);
      vector<Color>::iterator it;
      // Find card to trade
      for(it = colors.begin(); it != colors.end(); it++) {
        // Get set from other player with given color
        ColorSet *set = otherPlayer->getColorSet(*it);

        if(set->getSize() != 1) {
          cout << "\tSet " << set->getColor() << " has size " << set->getSize() << endl;
          throw WRONG_SET_SIZE;
        }

        // Get first (and only) card from set
        TitleDeed *deed = set->getCard(0);
        cout << "\t" << name << " is trying to trade " << deed->name << " with " << otherPlayer->getName() << endl;
        // Check if player has minimum balance to pay for card
        if(wallet.getBalance() - deed->price < getMinimumBalance()) {
          cout << "\t" << name << " does not have enough money to trade" << endl;
          continue;
        }

        // Offer a random price for the card (greater than its price, smaller than double the price)
        int price = getOffer(deed);
        // If player can't cover offer, offer maximum to keep minimum balance
        // TODO: Rethink this strategy
        if(wallet.getBalance() - price < getMinimumBalance()) {
          cout << "\t" << name << " does not have enough money to trade" << endl;
          price = wallet.getBalance() - getMinimumBalance();
        }

        // Get the chance of other player trading this card
        int otherTradingChance = otherPlayer->getTradingChance();
        chance = rand() % 100;
        if(chance <= otherTradingChance) {
          trade(otherPlayer, deed, price);
        }
      }
    }
  }
  else {
    cout << "\t" << name << " did not trade this round" << endl;
  }
}

int Player::getOffer(TitleDeed *deed) {
  int increase = rand() % 100;

  float offerPrice = (1 + (float)increase/100) * deed->price;

  cout << "\t" << deed->name << " costs $" << deed->price << endl;
  cout << "\t" << name << " is offering $" << (int)offerPrice << endl;

  return offerPrice;
}

vector<Color> Player::matchTrade(Player *otherPlayer) {
  vector<Color>::iterator it;
  vector<Color> toAcquire = colorsToAcquire();
  //vector<Color> toTrade = colorsToTrade();

  //vector<Color> otherToAcquire = otherPlayer->colorsToAcquire();
  vector<Color> otherToTrade = otherPlayer->colorsToTrade();

  vector<Color> matchToAcquire(min(toAcquire.size(), otherToTrade.size()));
  //vector<Color> matchToTrade(min(toTrade.size(), otherToAcquire.size()));

  it = set_intersection(toAcquire.begin(), toAcquire.end(),
                        otherToTrade.begin(), otherToTrade.end(),
                        matchToAcquire.begin());

  matchToAcquire.resize(it-matchToAcquire.begin());

  /*it = set_intersection(toTrade.begin(), toTrade.end(),
                        otherToAcquire.begin(), otherToAcquire.end(),
                        matchToTrade.begin());

  matchToTrade.resize(it-matchToTrade.begin());
*/
  /*cout << "\t" << name << " needs: ";
  for(it = toAcquire.begin(); it != toAcquire.end(); it++) {
    cout << *it << ", ";
  }
  cout << endl;
  cout << "\t" << otherPlayer->getName() << " has: ";
  for(it = otherToTrade.begin(); it != otherToTrade.end(); it++) {
    cout << *it << ", ";
  }
  cout << endl;
  cout << "\t" << name << " and " << otherPlayer->getName() << " can trade: ";
  for(it = matchToAcquire.begin(); it != matchToAcquire.end(); it++) {
    cout << *it << ", ";
  }
  cout << endl;
  cout << "\t" << name << " has: ";
  for(it = toTrade.begin(); it != toTrade.end(); it++) {
    cout << *it << ", ";
  }
  cout << endl;
  cout << "\t" << otherPlayer->getName() << " needs: ";
  for(it = otherToAcquire.begin(); it != otherToAcquire.end(); it++) {
    cout << *it << ", ";
  }
  cout << endl;
  cout << "\t" << name << " and " << otherPlayer->getName() << " can trade: ";
  for(it = matchToTrade.begin(); it != matchToTrade.end(); it++) {
    cout << *it << ", ";
  }
  cout << endl;*/

  return matchToAcquire;
  //return matchToAcquire.size() != 0 && matchToTrade.size() != 0;
}

vector<Color> Player::colorsToAcquire() {
  int i;
  vector<Color> colorsToAcquire;
  for(i = 0; i < colorsets.size(); i++) {
    ColorSet *set = colorsets[i];
    if(set->getSize() > 0 && !set->hasAllCards())
      colorsToAcquire.push_back(set->getColor());
  }
  return colorsToAcquire;
}

vector<Color> Player::colorsToTrade() {
  int i, c = 0;
  vector<Color> colorsToTrade;
  for(i = 0; i < colorsets.size(); i++) {
    ColorSet *set = colorsets[i];
    c += set->getSize();
    if(set->getSize() == 1 && !set->hasImprovement())
      colorsToTrade.push_back(set->getColor());
  }
  if(c <= getMinimumCards())
    colorsToTrade.clear();
  return colorsToTrade;
}

bool Player::paidToGetOutOfJail() {
  cout << "\t" << name << " is trying to pay to get out of jail" << endl;
  // If at minimum balance, do not pay
  if((this->wallet.getBalance() - 50) < this->getMinimumBalance()) {
    cout << "\t" << name << " is at minimum balance. Will not pay to exit jail." << endl;
    return false;
  }

  cout << "\t" << name << " has " << getPayingJailChance() << "\% chance of paying to leave jail" << endl;
  int chance = rand() % 100;

  if(chance <= getPayingJailChance()) {
    if(!wallet.payTo(&gameController->getBank()->Balance, 50)) {
      throw PAY_FAILED;
      //cout << "\t" << name << " did not pay to leave jail" << endl;
      //return false;
    }
    else return true;
  }

  else {
    cout << "\t" << name << " did not pay to leave jail" << endl;
    return false;
  }
}

void Player::goBroke() {
  this->isBroke = true;
  // Give funds to bank
  this->wallet.payTo(&gameController->getBank()->Balance, this->wallet.getBalance());

  int i;
  // Return deeds to bank
  for(i = 0; i < colorsets.size(); i++) {
    int j;
    for(j = 0; j < colorsets[i]->getSize(); j++) {
      TitleDeed *deed = colorsets[i]->getCard(j);
      deed->owner = -1;
      deed->n_houses = 0;
      deed->hasHotel = false;
      deed->isMortgaged = false;
    }
    free(colorsets[i]);
  }
  // Return utilities to bank
  for(i = 0; i < N_UTILITIES; i++) {
    if(Cards::utilities[i].owner == this->localId)
      Cards::utilities[i].owner = -1;
  }
  // Return railroads to bank
  for(i = 0; i < N_RAILROADS; i++) {
    if(Cards::railroads[i].owner == this->localId)
      Cards::railroads[i].owner = -1;
  }
  ownedRailroads = 0;
  ownedUtilities = 0;
  cout << "\t" << name << " went broke! (oh no)" << endl;
}

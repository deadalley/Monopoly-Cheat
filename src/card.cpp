#include "card.h"

Card::Card() {
  this->isMortgaged = false;
  this->owner = -1;
}

Card::Card(string name, int price, int mortgage) : Card() {
  this->name = name;
  this->price = price;
  this->mortgage = mortgage;
}

CardType Card::getType() {
  return type;
}

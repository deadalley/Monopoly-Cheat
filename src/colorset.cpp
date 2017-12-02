#include "colorset.h"

ColorSet::ColorSet(Color color) {
  this->color = color;
  switch(color) {
    case Purple:
      this->name = "Purple";
      break;
    case Cyan:
      this->name = "Cyan";
      break;
    case Pink:
      this->name = "Pink";
      break;
    case Orange:
      this->name = "Orange";
      break;
    case Red:
      this->name = "Red";
      break;
    case Yellow:
      this->name = "Yellow";
      break;
    case Green:
      this->name = "Green";
      break;
    case Blue:
      this->name = "Blue";
      break;
  }
}

Color ColorSet::getColor() {
  return this->color;
}

string ColorSet::getName() {
  return this->name;
}

TitleDeed* ColorSet::getCard(int pos) {
  return cards[pos];
}

int ColorSet::getSize() {
  return cards.size();
}

void ColorSet::addCard(TitleDeed *card) {
  cards.push_back(card);
}

bool ColorSet::hasMortgage() {
  int i;
  for(i = 0; i < cards.size(); i++){
    TitleDeed *deed = cards.at(i);
    if(deed->isMortgaged)
      return true;
  }
  return false;
}

bool ColorSet::hasImprovement() {
  int i;
  for(i = 0; i < cards.size(); i++) {
    TitleDeed *deed = cards.at(i);
    if(deed->hasHotel || deed->n_houses > 0)
      return true;
  }
  return false;
}

bool ColorSet::hasAllCards() {
  if((color == Purple || color == Blue) && cards.size() == 2)
    return true;
  return cards.size() == 3;
}

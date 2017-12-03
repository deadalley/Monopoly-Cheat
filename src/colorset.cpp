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

int ColorSet::getMinHouse() {
  int i, m = 200;
  for(i = 0; i < cards.size(); i++) {
    m = min(cards[i]->n_houses, m);
  }
  return m;
}

void ColorSet::addCard(TitleDeed *card) {
  cards.push_back(card);
}

void ColorSet::removeCard(TitleDeed *card) {
  vector<TitleDeed*>::iterator it;
  for(it = cards.begin(); it != cards.end(); it++) {
    cout << "Card: " << (*it)->name << endl;
    if(*it == card) {
      break;
    }
  }
  cout << "Removing (colorset): " << (*it)->name << endl;
  cards.erase(it);
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

#include "eventcard.h"

EventCard::EventCard(string description, bool type) {
  this->description = description;
  this->type = type;
  this->value = 0;
  //this->tile = NULL;
}

/*void EventCard::effect(Player *player) {
  switch(effectType) {
    case Collect:
      //player->receive(value);
      break;
    case Pay:
      //player->payBank(value);
      break;
  }
}*/

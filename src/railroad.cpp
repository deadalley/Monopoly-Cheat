#include "railroad.h"

Railroad::Railroad(string name) : Card(name, 200, 100) {
  this->type = RailroadCard;
  //Card(name, 200, 100);
  //this->name = name;
  //this->price = 200;
  //this->mortgage = 100;
  //Card();
  //this->owner = -1;
  //this->isMortgaged = false;

  rent[0] = 25;
  rent[1] = 50;
  rent[2] = 100;
  rent[3] = 200;
}

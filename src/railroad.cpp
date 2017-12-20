#include "railroad.h"

Railroad::Railroad(string name) : Card(name, 200, 100) {
  this->type = RailroadCard;

  rent[0] = 25;
  rent[1] = 50;
  rent[2] = 100;
  rent[3] = 200;
}

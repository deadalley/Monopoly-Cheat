#include "railroad.h"

Railroad::Railroad(string name) {
  this->name = name;
  rent[0] = 25;
  rent[1] = 50;
  rent[2] = 100;
  rent[3] = 200;
  mortgage = 100;
  price = 200;
}

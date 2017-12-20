#include "utility.h"

Utility::Utility(string name) : Card(name, 150, 10) {
  this->type = UtilityCard;
}

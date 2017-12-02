#include "titledeed.h"

TitleDeed::TitleDeed() : Card() {
  this->type = PropertyCard;
  this->n_houses = 0;
  this->hasHotel = false;
}

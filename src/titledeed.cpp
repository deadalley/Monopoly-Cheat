#include "titledeed.h"

TitleDeed::TitleDeed() : Card() {
  this->type = PropertyCard;
  this->n_houses = 0;
  this->hasHotel = false;
}

TitleDeed::TitleDeed(
  string name,
  string color,
  int price,
  int rent[6],
  int mortgage,
  int house_cost,
  int hotel_cost
) {
  this->type = PropertyCard;
  this->color = color;

  Card(name, price, mortgage);

  int i;
  for(i = 0; i < 6; i++)
    this->rent[i] = rent[i];
  this->house_cost = house_cost;
  this->hotel_cost = hotel_cost;

  this->n_houses = 0;
  this->hasHotel = false;
}

#include "titledeed.h"

TitleDeed::TitleDeed() {
  this->type = PropertyCard;
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
  this->name = name;
  this->color = color;

  this->price = price;
  int i;
  for(i = 0; i < 6; i++)
    this->rent[i] = rent[i];
  this->mortgage = mortgage;
  this->house_cost = house_cost;
  this->hotel_cost = hotel_cost;

  this->n_houses = this->n_hotels = 0;
}

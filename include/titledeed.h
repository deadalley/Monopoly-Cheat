#ifndef H_TITLE_DEED
#define H_TITLE_DEED

#include <string>
#include "card.h"

using namespace std;

class TitleDeed : public Card {
  public:
    //string name;
    string color;

    //int price;
    int rent[6];
    //int mortgage;
    int house_cost;
    int hotel_cost;

    int n_houses;
    int n_hotels;

    TitleDeed();
    TitleDeed(
      string name,
      string color,
      int price,
      int rent[6],
      int mortgage,
      int house_cost,
      int hotel_cost
    );
};

#endif

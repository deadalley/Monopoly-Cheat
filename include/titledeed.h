#ifndef H_TITLE_DEED
#define H_TITLE_DEED

#include "card.h"
#include "color.h"

using namespace std;

class TitleDeed : public Card {
  public:
    Color color;
    int rent[6];
    int house_cost;
    int hotel_cost;

    int n_houses;
    bool hasHotel;

    TitleDeed();
};

#endif

#ifndef H_RAILROAD
#define H_RAILROAD

#include <string>
#include "card.h"

using namespace std;

class Railroad : public Card {
  public:
    //string name;
    int rent[4];
    //int mortgage;
    //int price;

    Railroad(string);
};

#endif

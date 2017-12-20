#ifndef H_RAILROAD
#define H_RAILROAD

#include <string>

#include "card.h"

using namespace std;

class Railroad : public Card {
  public:
    int rent[4];

    Railroad(string);
};

#endif

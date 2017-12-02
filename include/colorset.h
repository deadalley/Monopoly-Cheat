#ifndef H_COLORSET
#define H_COLORSET

#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include "titledeed.h"

using namespace std;

class ColorSet {
  private:
    string name;
    Color color;
    vector<TitleDeed*> cards;

  public:
    ColorSet(Color);

    Color getColor();
    string getName();
    TitleDeed* getCard(int);
    int getSize();

    void addCard(TitleDeed*);
    bool hasMortgage();
    bool hasImprovement();
    bool hasAllCards();
};

#endif

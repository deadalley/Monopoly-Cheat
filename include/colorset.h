#ifndef H_COLORSET
#define H_COLORSET

#include <string>
#include <vector>

#include "color.h"
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
    int getMinHouse();

    void addCard(TitleDeed*);
    void removeCard(TitleDeed*);
    bool hasMortgage();
    bool hasImprovement();
    bool hasAllCards();
};

#endif

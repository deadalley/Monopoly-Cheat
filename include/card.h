#ifndef H_CARD
#define H_CARD

#include <string>

using namespace std;

enum CardType {
  PropertyCard,
  UtilityCard,
  RailroadCard
};

class Card {
  protected:
    int id;
    CardType type;

  public:
    string name;
    int price;
    int mortgage;
    int position;
    int owner;
    bool isMortgaged;

    Card();
    Card(string, int, int);
    int getId();
    CardType getType();

    void setId(int);
};

#endif

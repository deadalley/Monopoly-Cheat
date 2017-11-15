#ifndef H_BOARD
#define H_BOARD

#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>

#include "card.h"
#include "cards.h"
#include "eventcard.h"

using namespace std;

#define GO 0
#define MEDITERRANEAN_AV 1
#define CHEST_1 2
#define BALTIC_AV 3
#define INCOME_TAX 4
#define READING_RR 5
#define ORIENTAL_AV 6
#define CHANCE_1 7
#define VERMONT_AV 8
#define CONNECTICUT_AV 9
#define JAIL 10
#define ST_CHARLES_PLACE 11
#define ELECTRIC_CO 12
#define STATES_AV 13
#define VIRGINIA_AV 14
#define PENNSYLVANIA_RR 15
#define ST_JAMES_PLACE 16
#define CHEST_2 17
#define TENNESSEE_AV 18
#define NEW_YORK_AV 19
#define FREE_PARKING 20
#define KENTUCKY_AV 21
#define CHANCE_2 22
#define INDIANA_AV 23
#define ILLINOIS_AV 24
#define BO_RR 25
#define ATLANTIC_AV 26
#define VENTNOR_AV 27
#define WATER_WORKS 28
#define MARVIN_GARDENS 29
#define GO_TO_JAIL 30
#define PACIFIC_AV 31
#define NORTH_CAROLINA_AV 32
#define CHEST_3 33
#define PENNSYLVANIA_AV 34
#define SHORT_LINE 35
#define CHANCE_3 36
#define PARK_PLACE 37
#define LUXURY_TAX 38
#define BOARDWALK 39

enum TileType {
  PropertyTile,
  ChestTile,
  ChanceTile,
  JailTile,
  GoToJailTile,
  GoTile,
  FreeParkingTile,
  IncomeTaxTile,
  LuxuryTaxTile,
};

class Board {

  public:
    class Tile;

  private:
    static vector<Tile> map;

  public:
    static stack<EventCard*> chanceCards;
    static stack<EventCard*> chestCards;
    static Tile* getTile(int);
};

class Board::Tile {
  private:
    TileType type;
    Card* card;                 // Stores card if the tile is a PropertyTile

  public:
    TileType getType();
    Card* getCard();
    EventCard* getEventCard();  // Draws a chance or chest card
    int rollDice(int);

};

#endif

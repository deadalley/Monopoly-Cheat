#ifndef H_BOARD
#define H_BOARD

#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>

#include "bank.h"
#include "card.h"
#include "cards.h"
#include "eventcard.h"

using namespace std;

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
    static void initBoard();
    static stack<EventCard*> chanceCards;
    static stack<EventCard*> chestCards;
    static Tile* getTile(int);
    static int rollDice(int);
};

class Board::Tile {
  private:
    TileType type;
    Card* card;                 // Stores card if the tile is a PropertyTile

  public:
    TileType getType();
    Card* getCard();
    EventCard* getEventCard();  // Draws a chance or chest card
};

#endif

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
    static stack<EventCard*> chanceCards;
    static stack<EventCard*> chestCards;
    static int dice[2];

  public:
    static void initBoard();
    static Tile* getTile(int);
    static void rollDice();
    static int getDie(int);
    static EventCard* getEventCard(TileType);  // Draws a chance or chest card
};

class Board::Tile {
  private:
    TileType type;
    Card* card;                 // Stores card if the tile is a PropertyTile
    int position;

  public:
    Tile(TileType, int, Card*);
    TileType getType();
    Card* getCard();
    void setCard(Card*);
    int getPos();
};

#endif

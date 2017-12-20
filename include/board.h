#ifndef H_BOARD
#define H_BOARD

#include <stack>
#include <vector>

#include "card.h"
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

class Tile;

class Board {

  public:
    class Tile;

  private:
    vector<Tile> map;
    stack<EventCard*> chanceCards;
    stack<EventCard*> chestCards;
    int dice[2];

  public:
    void initBoard();
    Tile* getTile(int);
    void rollDice();
    int getDie(int);
    EventCard* getEventCard(TileType);  // Draws a chance or chest card
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

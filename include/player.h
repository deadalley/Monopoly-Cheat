#ifndef H_PLAYER
#define H_PLAYER

#include <string>

#include "board.h"
#include "card.h"
#include "tile.h"

using namespace std;

class Player {
  private:
    string name;

  public:
    string getName();

    /* Trigger the action of the tile stepped on */
    void stepOnTile(Board::Tile);

    /* Pay all players */
    void payAll(int);

    /* Receive money from all players */
    void receiveFromAll(int);

    /* Pay rent */
    void payRent(Card);

    /* Pay bank */
    void payBank();

    /* Receive money from bank */
    void receive();
};

#endif

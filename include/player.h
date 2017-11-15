#ifndef H_PLAYER
#define H_PLAYER

#include <string>

#include "board.h"
#include "card.h"
#include "utils.h"

using namespace std;

class Player {
  private:
    string name;
    int position;
    Bills wallet;

  public:
    string getName();

    /* Player constructor */
    Player (string);

    /* Trigger the action of the tile stepped on */
    void stepOnTile(Board::Tile);

    /* Pay all players */
    void payAll(int);

    /* Receive money from all players */
    void receiveFromAll(int);

    /* Pay rent */
    void payRent(Card);

    /* Pay bank */
    void payBank(int);

    /* Receive money from bank */
    void receive(int);

    /* Receive money from bank with specific bills*/
    void receive(Bills);

    /* Moves player to designated tile */
    void goTo(int);

    /* Sends player to jail */
    void goToJail();
};

#endif

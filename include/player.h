#ifndef H_PLAYER
#define H_PLAYER

#include <string>

#include "utils.h"
#include "board.h"
#include "wallet.h"

using namespace std;

class Player {
  private:
    string name;
    int position;

    void processEventCard(EventCard *card);

  public:
    Wallet wallet;

    Player(string);
    string getName();

    /* Trigger the action of the tile stepped on */
    void stepOnTile(Board::Tile);

    /* Moves player to designated tile */
    void goTo(int);

    /* Sends player to jail */
    void goToJail();
};

#endif

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
    int id;
    int position;
    vector<Card *> cards;
    bool inJail;

    void processEventCard(EventCard*);
    void buy(Card*);

    /* AG */
    int buyingChance;       // Chance of buying property, 0 < b < 100;

  public:
    Wallet wallet;

    Player(int, string);
    string getName();

    /* Trigger the action of the tile stepped on */
    void stepOnTile(Board::Tile*);

    /* Moves player to designated tile */
    void goTo(int);

    /* Sends player to jail */
    void goToJail();

    int getPosition();

    bool isInJail();
};

#endif

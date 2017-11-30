#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <map>

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
    map<string, int> colorSets;

    void processEventCard(EventCard*);
    void buy(Card*);
    void build(TitleDeed*);

    /* AG */
    int buyingChance;       // Chance of buying property, 0 < b < 100
    int buildingChance;     // Chance of building house/hotel
    int payingJailChance;   // Chance to pay to leave jail
    int mortgageChance;     // Chance to mortgage something
    int minimumBalance;     // Minium balance the player withholds

  public:
    Wallet wallet;

    bool inJail;
    bool hasJailCard;
    int roundsInJail;

    Player(int, string);
    string getName();

    /* Trigger the action of the tile stepped on */
    void stepOnTile(Board::Tile*);

    /* Moves player to designated tile */
    void goTo(int);

    /* Sends player to jail */
    void goToJail();

    int getPosition();

    /* Player decides to build houses or hotels */
    void tryToBuild();

    bool paidToGetOutOfJail();
};

#endif

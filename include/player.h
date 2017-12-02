#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <map>

#include "utils.h"
#include "board.h"
#include "wallet.h"
#include "colorset.h"

using namespace std;

class Player {
  private:
    string name;
    int id;
    int position;
    vector<Card*> cards;
    vector<ColorSet*> colorsets;
    //map<string, int> colorSets;
    int ownedUtilities;
    int ownedRailroads;

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

    bool isBroke;
    bool inJail;
    bool hasJailCard;
    int roundsInJail;

    Player(int, string);

    int getId();
    string getName();
    int getPosition();
    int getOwnedUtilities();
    int getOwnedRailroads();

    void goTo(int);
    void goToJail();

    void stepOnTile(Board::Tile*);
    void tryToBuild();
    bool tryToMortgage(int);

    bool paidToGetOutOfJail();
    void goBroke();
};

#endif

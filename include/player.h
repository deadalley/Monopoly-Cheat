#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <map>

#include "agplayer.h"
#include "board.h"
#include "wallet.h"
#include "colorset.h"

using namespace std;

class Player : public AGPlayer {
  private:
    string name;
    int id;
    int position;
    //vector<Card*> cards;
    vector<ColorSet*> colorsets;
    int ownedUtilities;
    int ownedRailroads;

    void processEventCard(EventCard*);
    void buy(Card*);
    void build(TitleDeed*);
    void trade(Player*, TitleDeed*, int);

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
    ColorSet* getColorSet(Color);
    int getOffer(TitleDeed*);

    vector<Color> colorsToAcquire();
    vector<Color> colorsToTrade();

    void stepOnTile(Board::Tile*);

    void goTo(int);
    void goToJail();
    void goBroke();

    void tryToBuild();
    bool tryToMortgage(int);
    void tryToTrade();

    vector<Color> matchTrade(Player*);

    bool paidToGetOutOfJail();
};

#endif

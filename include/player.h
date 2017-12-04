#ifndef H_PLAYER
#define H_PLAYER

#include <string>

#include "agplayer.h"
#include "board.h"
#include "wallet.h"
#include "colorset.h"

using namespace std;

class GameController;

class Player : public AGPlayer {
  private:
    GameController *gameController;

    string name;
    int id;
    int position;
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

    Player(int, string, GameController*);

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

    void tryToBuild();          // Check conditions and chances for building
    bool tryToMortgage(int);    // Find minimum mortgage to cover for value
    void tryToTrade();          // Try to trade cards

    vector<Color> matchTrade(Player*);  // Return colors that another player has to offer that match colors of interest

    bool paidToGetOutOfJail();
};

#endif

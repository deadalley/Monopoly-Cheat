#ifndef H_EVENTCARD
#define H_EVENTCARD

#include <string>
//#include "board.h"

using namespace std;

enum EventCardEffect {
  Collect,
  Pay,
  GoToTile,
  GoToUtility,
  GoToRailroad,
  GoBack3,
  GoToJail,
  GetOutJail,
  PayForEach,
  PayToAll,
  ReceiveFromAll
};

class EventCard {
  public:

    string description;         // Card text

    bool type;                  // Chance (0) or Community chest (1)

    EventCardEffect effectType; // Expected event caused by the card

    int value;                  // Value to be paid or collected

    size_t tile;                // Destination tile

    EventCard(string description, bool type);
    //void effect(Player *player, Board *board);
};

#endif

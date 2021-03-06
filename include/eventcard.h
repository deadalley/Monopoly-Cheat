#ifndef H_EVENTCARD
#define H_EVENTCARD

#include <string>

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
  StreetRepairs,
  GeneralRepairs,
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

    EventCard(string, bool);

};

#endif

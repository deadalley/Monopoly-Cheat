#ifndef H_AGMANAGER
#define H_AGMANAGER

#include <vector>
#include "game.h"

#define MAX_PLAYERS 5
#define PLAYERS_PER_ROUND 2

using namespace std;

class AGManager {
  private:
    static vector<AGPlayer*> players;

  public:
    static void initPlayers();
    static void simulateGeneration();
};

#endif

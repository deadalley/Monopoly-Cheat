#ifndef H_AGMANAGER
#define H_AGMANAGER

#include <iostream>
#include <vector>
#include "agplayer.h"

using namespace std;

#define N_TURNS 300
#define EARLY_GAME 0
#define MID_GAME 1
#define LATE_GAME 2

class AGManager {
  private:
    static int gameStage;
    static vector<AGPlayer*> players;

    static void setPlayerAttributes(AGPlayer*);

  public:
    static void setGameStage(int);
    static void addPlayer(AGPlayer*);
};

#endif

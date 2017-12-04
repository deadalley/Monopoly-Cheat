#ifndef H_AGCONTROLLER
#define H_AGCONTROLLER

#include <iostream>
#include <vector>
#include "agplayer.h"

using namespace std;

#define N_TURNS 300
#define EARLY_GAME 0
#define MID_GAME 1
#define LATE_GAME 2

class AGController {
  private:
    int gameStage;
    vector<AGPlayer*> *players;

    void setPlayerAttributes(AGPlayer*);

  public:
    void setGameStage(int);
    void setPlayers(vector<AGPlayer*>*);
    void addPlayer(AGPlayer*);
    AGPlayer* getPlayer(int);
};

#endif

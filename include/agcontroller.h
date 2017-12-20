#ifndef H_AGCONTROLLER
#define H_AGCONTROLLER

#include <vector>

#include "agplayer.h"

using namespace std;

#define N_TURNS 300     // Max turns. If no winner found, game is to be discarded
#define EARLY_GAME 0
#define MID_GAME 1
#define LATE_GAME 2

class AGController {
  private:
    int gameStage;
    vector<AGPlayer*> *players;

  public:
    void setGameStage(int);
    void setPlayers(vector<AGPlayer*>*);
    AGPlayer* getPlayer(int);
};

#endif

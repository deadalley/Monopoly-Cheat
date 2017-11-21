#ifndef H_GAMECONTROLLER
#define H_GAMECONTROLLER

#include "player.h"

class GameController {
  private:
    static vector<Player*> players;
    static int activePlayer;

  public:
    static void initGame(int);

    static Player* getPlayer(int);

    static void payAll(Player*, int);
    static void receiveFromAll(Player*, int);
    static void processTurn();
};

#endif

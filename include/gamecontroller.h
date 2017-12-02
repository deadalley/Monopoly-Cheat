#ifndef H_GAMECONTROLLER
#define H_GAMECONTROLLER

#include "player.h"

class GameController {
  private:
    static vector<Player*> players;
    static int sequenceOfTurns;     // Counts how many times the same player has been the active player
    static int activePlayer;        // Player id of current turn

  public:
    static void initGame(int);

    static int getPlayerSize();
    static Player* getPlayer(int);

    static void payAll(Player*, int);
    static void receiveFromAll(Player*, int);
    static void processTurn();
};

#endif

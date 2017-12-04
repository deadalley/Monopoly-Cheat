#ifndef H_GAME
#define H_GAME

#include "gamecontroller.h"
#include "agcontroller.h"
#include "board.h"
#include "bank.h"

class Game {
  private:
    AGController agController;
    GameController gameController;
    Bank bank;
    Board board;

  public:
    void initGame();
    void runGame();
    void checkGameStage(int);
    void checkIntegrity(int);
    bool checkWinner();
    Player* getWinner();
};

#endif

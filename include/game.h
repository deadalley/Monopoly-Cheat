#ifndef H_GAME
#define H_GAME

#include "gamecontroller.h"
#include "agcontroller.h"
#include "board.h"
#include "bank.h"

class Game {
  public:
    int N_PLAYERS;
    AGController agController;
    GameController gameController;
    Bank bank;
    Board board;

    void initGame();
    void runGame();
    void checkGameStage(int);
    void checkIntegrity(int);
    bool checkWinner();
    Player* getWinner();

    ~Game();
};

#endif

#ifndef H_GAMECONTROLLER
#define H_GAMECONTROLLER

#include "player.h"
#include "agcontroller.h"

class Board;
class Bank;

class GameController {
  private:
    vector<Player*> players;
    int sequenceOfTurns;     // Counts how many times the same player has been the active player
    int activePlayer;        // Player id of current turn
    Board *board;
    Bank *bank;

  public:
    void initGameController(AGController*, int);

    void setBoard(Board*);
    void setBank(Bank*);

    Board* getBoard();
    Bank* getBank();

    int getPlayerSize();
    Player* getPlayer(int);

    void payAll(Player*, int);
    void receiveFromAll(Player*, int);
    void processTurn();
};

#endif

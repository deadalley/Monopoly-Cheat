#include "agmanager.h"

vector<AGPlayer*> AGManager::players;

void AGManager::initPlayers() {
  int i, chance;
  for(i = 0; i < MAX_PLAYERS; i++) {
    AGPlayer *p = new AGPlayer(i);
    //p->id = i;  DEBUG

    chance = rand() % 101;
    p->setBuyingChance(chance);
    chance = rand() % 101;
    p->setBuildingChance(chance);
    chance = rand() % 101;
    p->setPayingJailChance(chance);
    chance = rand() % 101;
    p->setMortgageChance(chance);
    chance = rand() % 101;
    p->setTradingChance(chance);

    chance = rand() % 501;
    p->setMinimumBalance(chance);

    chance = rand() % 6;
    p->setMinimumCards(chance);

    players.push_back(p);
  }
}

void AGManager::simulateGeneration() {
  // Iterate players and create games
  vector<AGPlayer*>::iterator first_it;
  for(first_it = players.begin(); first_it != players.end()-PLAYERS_PER_ROUND+1; first_it++) {

    vector<AGPlayer*>::iterator second_it;
    for(second_it = first_it + 1; second_it != (players.end()-PLAYERS_PER_ROUND+2); second_it++) {

      vector<AGPlayer*> roundPlayers(second_it, second_it+(PLAYERS_PER_ROUND-1));
      roundPlayers.push_back(*first_it);

      sort(roundPlayers.begin(), roundPlayers.end(), [](AGPlayer *p1, AGPlayer *p2) {
        return p1->getId() < p2->getId();
      });

      int i;
      cout << "========= STARTING ROUND FOR =========" << endl;
      for(i = 0; i < roundPlayers.size(); i++){
        cout << "\tPlayer " << roundPlayers[i]->getId() << endl;
      }
      cout << "======================================" << endl;

      Game *newGame = new Game();
      newGame->N_PLAYERS = PLAYERS_PER_ROUND;
      newGame->agController.setPlayers(&roundPlayers)  ;
      newGame->initGame();
      newGame->runGame();

      cout << "============= GAME ENDED =============" << endl;
      if(!newGame->checkWinner()) {
        cout << "\tThere were no winners!" << endl;
      }

      delete newGame;

      cin.get();
    }
  }
}

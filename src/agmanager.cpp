#include "agmanager.h"
#include "utils.h"
#include "game.h"
#include "color.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<AGPlayer*> AGManager::players;
int AGManager::generation = 0;

void AGManager::initPlayers() {
  // Initialize players (individuals)
  int i;
  for(i = 0; i < MAX_PLAYERS; i++) {
    AGPlayer *p = new AGPlayer(i);
    players.push_back(p);
  }

  // Set random starting chances for each player
  int stage, chance, j;
  for(stage = 0; stage < 3; stage++) {
    for(i = 0; i < MAX_PLAYERS; i++) {
      AGPlayer *p = players[i];
      p->setStage(stage);

      for(j = 0; j < N_DEEDS+N_UTILITIES+N_RAILROADS; j++) {
        chance = rand() % 101;
        p->setBuyingChance(j, chance);
      }

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
    }
  }
  // Log initial conditions
  logInitPlayers();
}

void AGManager::logInitPlayers() {
  ofstream file;
  file.open("results/init_values.log", ios::app);
  if(!file)
    cerr << "Unable to open file init_values.log" << endl;

  if(generation == 1) {
    file << N_GENERATIONS << endl;
    file << MAX_PLAYERS << endl;
  }

  int i, stage;
  for(i = 0; i < MAX_PLAYERS; i++) {
    AGPlayer *p = players[i];
    file << "P" << p->getId()+1 << endl;

    for(stage = 0; stage < 3; stage++) {
      p->setStage(stage);

      int j;
      for(j = 0; j < N_DEEDS+N_UTILITIES+N_RAILROADS; j++) {
        file << p->getBuyingChance(j) << ",";
      }
      file << p->getBuildingChance() << ",";
      file << p->getPayingJailChance() << ",";
      //file << p->getMortgageChance() << ",";
      file << p->getTradingChance() << ",";
      file << p->getMinimumBalance() << ",";
      file << p->getMinimumCards() << ",";
    }
    file << endl;
  }
  file.close();
}

void AGManager::runAG() {
  // Run Y games for N_GENERATIONS
  for(generation = 1; generation <= N_GENERATIONS; generation++) {
    // Simulate generation and get generation's best
    AGPlayer *best = simulateGeneration();
    // Log features for the best of generation
    logBestFeatures(best);
    // Rest win count for best
    best->resetWinCount();
    //cin.get();
    // Cross features
    crossover(best);
    // Mutate
    mutate(best);
  }
}

void AGManager::logBestFeatures(AGPlayer *best) {
  ofstream file;
  file.open("results/best.log", ios::app);
  if(!file)
    cerr << "Unable to open file best.log" << endl;

  if(generation == 1) {
    file << N_GENERATIONS << endl;
    file << MAX_PLAYERS << endl;
  }

  if(best == NULL)
    return;

  //b << "Generation: " << generation << endl;
  file << "Best: P" << best->getId()+1 << endl;
  file << best->getWinCount() << endl;

  vector<Card*>* ownedProperties = best->getOwnedProperties();
  vector<Card*>::iterator it;
  int colors[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int builtProperties = 0;
  for(it = ownedProperties->begin(); it != ownedProperties->end(); it++) {
    file << (*it)->name << ",";

    if((*it)->getType() == PropertyCard) {
      TitleDeed *deed = (TitleDeed*) (*it);
      colors[(int)deed->color]++;

      builtProperties += deed->n_houses;
      if(deed->hasHotel)
        builtProperties++;
    }
  }
  file << endl;

  int i;
  for(i = 0; i < 8; i++) {
    file << colors[i] << ",";
  }
  file << endl;

  file << builtProperties << endl;

  int stage;
  for(stage = 0; stage < 3; stage++) {
    best->setStage(stage);

    int j;
    for(j = 0; j < N_DEEDS+N_UTILITIES+N_RAILROADS; j++) {
      file << best->getBuyingChance(j) << ",";
    }
    file << best->getBuildingChance() << ",";
    file << best->getPayingJailChance() << ",";
    //file << best->getMortgageChance() << ",";
    file << best->getTradingChance() << ",";
    file << best->getMinimumBalance() << ",";
    file << best->getMinimumCards() << ",";
  }
  file << endl;
  file.close();
}

AGPlayer* AGManager::simulateGeneration() {
  if(_VERBOSE)
    cout << "========= ****GENERATION**** =========" << endl;
  /* Iterate players and create games
   * Games are created as a combination between players
   * Given 5 players playing rounds of 3 players, the possible combinations are
   * 1, 2, 3; 1, 3, 4; 1, 4, 5; 2, 3, 4; 2, 4, 5; 3, 4, 5
   */

  // Iterate players
  vector<AGPlayer*>::iterator first_it;
  for(first_it = players.begin(); first_it != players.end()-PLAYERS_PER_ROUND+1; first_it++) {

    vector<AGPlayer*>::iterator second_it;
    for(second_it = first_it + 1; second_it != (players.end()-PLAYERS_PER_ROUND+2); second_it++) {

      // Create vector of players for current game
      vector<AGPlayer*> roundPlayers(second_it, second_it+(PLAYERS_PER_ROUND-1));
      roundPlayers.push_back(*first_it);

      // Sort players
      sort(roundPlayers.begin(), roundPlayers.end(), [](AGPlayer *p1, AGPlayer *p2) {
        return p1->getId() < p2->getId();
      });

      // Print players in current game
      int i;
      if(_VERBOSE) {
        cout << "========= STARTING GAME FOR ==========" << endl;
        for(i = 0; i < roundPlayers.size(); i++){
          cout << "\tPlayer " << roundPlayers[i]->getId() << endl;
        }
        cout << "======================================" << endl;
      }

      // Create new game and run it
      Game *newGame = new Game();
      newGame->N_PLAYERS = PLAYERS_PER_ROUND;
      newGame->agController.setPlayers(&roundPlayers)  ;
      newGame->initGame();
      newGame->runGame();

      // Check if there is a winner
      if(!newGame->checkWinner()) {
        if(_VERBOSE) {
          cout << "\tThere were no winners!" << endl;
          cout << "======================================" << endl;
        }
        // Run again if no winner found (# of rounds exceeded maximum)
        newGame->runGame();
      }

      // Get winner, increase win count and get properties owned
      AGPlayer *winner = newGame->getWinner();
      if(_VERBOSE)
        cout << "\tWINNER: Player " << winner->getId() + 1 << endl;
      players[winner->getId()]->increaseWinCount();
      players[winner->getId()]->setOwnedProperties(winner->getOwnedProperties());

      delete newGame;
    }
  }

  if(_VERBOSE)
    cout << "============= SCORE BOARD ============" << endl;
  AGPlayer *best = players[0];
  for(first_it = players.begin(); first_it != players.end(); first_it++) {
    if(_VERBOSE)
      cout << "\tPlayer " << (*first_it)->getId() + 1 << ": "<< (*first_it)->getWinCount() << endl;

    if((*first_it)->getWinCount () > best->getWinCount())
      best = (*first_it);
  }
  if(_VERBOSE)
    cout << "\tBest of #" << generation << ": Player " << best->getId() + 1 << endl;

  return best;
}

void AGManager::crossover(AGPlayer *best) {
  vector<AGPlayer*>::iterator it;
  for(it = players.begin(); it != players.end(); it++) {
    if((*it)->getId() == best->getId())
      continue;

    AGPlayer *newPlayer = new AGPlayer((*it)->getId());
    int stage;
    for(stage = 0; stage < 3; stage++) {
      newPlayer->setStage(stage);
      (*it)->setStage(stage);
      best->setStage(stage);

      // Cross features with features from best player
      int j;
      for(j = 0; j < N_DEEDS+N_UTILITIES+N_RAILROADS; j++) {
        newPlayer->setBuyingChance(j,min(100,crossFeature((*it)->getBuyingChance(j), best->getBuyingChance(j))));
      }
      newPlayer->setBuildingChance(min(100,crossFeature((*it)->getBuildingChance(), best->getBuildingChance())));
      newPlayer->setPayingJailChance(min(100,crossFeature((*it)->getPayingJailChance(), best->getPayingJailChance())));
      newPlayer->setMortgageChance(min(100,crossFeature((*it)->getMortgageChance(), best->getMortgageChance())));
      newPlayer->setMinimumBalance(crossFeature((*it)->getMinimumBalance(), best->getMinimumBalance()));
      newPlayer->setTradingChance(min(100,crossFeature((*it)->getTradingChance(), best->getTradingChance())));
      newPlayer->setMinimumCards(crossFeature((*it)->getMinimumCards(), best->getMinimumCards()));
    }

    players.at((*it)->getId()) = newPlayer;
  }
}

int AGManager::crossFeature(int v1, int v2) {
  return (v1+v2) / 2;
}

void AGManager::mutate(AGPlayer *best) {
  int i, stage, chance, sig;
  float mutatedValue;
  for(stage = 0; stage < 3; stage++) {
    for(i = 0; i < MAX_PLAYERS; i++) {
      AGPlayer *p = players[i];
      if(p->getId() == best->getId())
        continue;
      p->setStage(stage);

      /* Given a mutation rate MUTATION, a certain feature f can be mutate to
       * [1-MUTATION/100 * f, 1+MUTATION/100 * f]
       * If f = 80, mutated f can be [72, 88] for MUTATION = 10
       */
      int j;
      for(j = 0; j < N_DEEDS+N_UTILITIES+N_RAILROADS; j++) {
        chance = rand() % (2*MUTATION+1) - MUTATION;
        mutatedValue = max(0.0f,min(100.0f,p->getBuyingChance(j) * (1 + (float)chance/100)));
        p->setBuyingChance(j, round(mutatedValue));
      }
      chance = rand() % (2*MUTATION+1) - MUTATION;
      mutatedValue = max(0.0f,min(100.0f,p->getBuildingChance() * (1 + (float)chance/100)));
      p->setBuildingChance(mutatedValue);
      chance = rand() % (2*MUTATION+1) - MUTATION;
      mutatedValue = max(0.0f,min(100.0f,p->getPayingJailChance() * (1 + (float)chance/100)));
      p->setPayingJailChance(mutatedValue);
      chance = rand() % (2*MUTATION+1) - MUTATION;
      mutatedValue = max(0.0f,min(100.0f,p->getMortgageChance() * (1 + (float)chance/100)));
      p->setMortgageChance(mutatedValue);
      chance = rand() % (2*MUTATION+1) - MUTATION;
      mutatedValue = max(0.0f,min(100.0f,p->getTradingChance() * (1 + (float)chance/100)));
      p->setTradingChance(mutatedValue);

      chance = rand() % (2*MUTATION+1) - MUTATION;
      mutatedValue = max(0.0f,p->getMinimumBalance() * (1 + (float)chance/100));
      p->setMinimumBalance(mutatedValue);

      chance = rand() % (2*MUTATION+1) - MUTATION;
      mutatedValue = max(0.0f,p->getMinimumCards() * (1 + (float)chance/100));
      p->setMinimumCards(mutatedValue);
    }
  }
}

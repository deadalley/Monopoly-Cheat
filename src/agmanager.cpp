#include "agmanager.h"

vector<AGPlayer*> AGManager::players;
int AGManager::generation = 0;

void AGManager::initPlayers() {
  int i;
  for(i = 0; i < MAX_PLAYERS; i++) {
    AGPlayer *p = new AGPlayer(i);
    players.push_back(p);
  }

  int stage, chance;
  for(stage = 0; stage < 3; stage++) {
    for(i = 0; i < MAX_PLAYERS; i++) {
      AGPlayer *p = players[i];
      p->setStage(stage);

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
    }
  }
}

void AGManager::runAG() {
  //logResults(NULL);
  for(generation = 1; generation <= N_GENERATIONS; generation++) {
    AGPlayer *best = simulateGeneration();
    //logResults();
    logBestFeatures(best);
    best->resetWinCount();
    //cin.get();
    crossover(best);
    mutate();
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

  if(best != NULL) {
    //b << "Generation: " << generation << endl;
    file << "Best: P" << best->getId()+1 << endl;
    int stage;
    for(stage = 0; stage < 3; stage++) {
      best->setStage(stage);

      file << best->getBuyingChance() << ",";
      file << best->getBuildingChance() << ",";
      file << best->getPayingJailChance() << ",";
      //file << best->getMortgageChance() << ",";
      file << best->getTradingChance() << ",";
      file << best->getMinimumBalance() << ",";
      file << best->getMinimumCards() << ",";
    }
    file << endl;
  }
  file.close();
}

void AGManager::logResults() {
  ofstream file;

  //ofstream **files = (ofstream**)malloc(sizeof(ofstream*)*6);
/*
  int k;
  for(k = 0; k < 6; k++) {
    ofstream *f = new ofstream();

    string name = "results/feat" + to_string(k+1) + ".txt";
    f->open(name, ios::app);

    if(!f)
      cerr << "Unable to open file " << name << endl;

    files[k] = f;
    *files[k] << "#" << generation << endl;
  }
*/
  file.open("results/results.log", ios::app);


  if(!file)
    cerr << "Unable to open file results.log" << endl;

  file << "#" << generation << endl;

  int i, stage, chance;

  for(i = 0; i < MAX_PLAYERS; i++) {
    AGPlayer *p = players[i];
    //for(k = 0; k < 6; k++)
      //*files[k] << p->getId() << ",";

    file << "P" << p->getId()+1 << endl;

    for(stage = 0; stage < 3; stage++) {
      p->setStage(stage);

      //*files[0] << p->getBuyingChance() << ",";
      file << p->getBuyingChance() << ",";
      //*files[1] << p->getBuildingChance() << ",";
      file << p->getBuildingChance() << ",";
      //*files[2] << p->getPayingJailChance() << ",";
      file << p->getPayingJailChance() << ",";
      //file << p->getMortgageChance() << ",";
      //*files[3] << p->getTradingChance() << ",";
      file << p->getTradingChance() << ",";
      //*files[4] << p->getMinimumBalance() << ",";
      file << p->getMinimumBalance() << ",";
      //*files[5] << p->getMinimumCards() << ",";
      file << p->getMinimumCards() << ",";
    }
    file << endl;
  }/*
  for(k = 0; k < 6; k++) {
    *files[k] << endl;
    files[k]->close();
    delete files[k];
  }
  free(files);*/
  file.close();
}

AGPlayer* AGManager::simulateGeneration() {
  cout << "========= ****GENERATION**** =========" << endl;
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

      if(!newGame->checkWinner()) {
        cout << "\tThere were no winners!" << endl;
        cout << "======================================" << endl;
        newGame->runGame();
      }

      AGPlayer *winner = newGame->getWinner();
      cout << "\tWINNER: Player " << winner->getId() + 1 << endl;
      players[winner->getId()]->increaseWinCount();

      delete newGame;
    }
  }

  cout << "============= SCORE BOARD ============" << endl;
  AGPlayer *best = players[0];
  for(first_it = players.begin(); first_it != players.end(); first_it++) {

    cout << "\tPlayer " << (*first_it)->getId() + 1 << ": "<< (*first_it)->getWinCount() << endl;

    if((*first_it)->getWinCount () > best->getWinCount())
      best = (*first_it);
  }
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

      newPlayer->setBuyingChance(crossFeature((*it)->getBuyingChance(), best->getBuyingChance()));
      newPlayer->setBuildingChance(crossFeature((*it)->getBuildingChance(), best->getBuildingChance()));
      newPlayer->setPayingJailChance(crossFeature((*it)->getPayingJailChance(), best->getPayingJailChance()));
      newPlayer->setMortgageChance(crossFeature((*it)->getMortgageChance(), best->getMortgageChance()));
      newPlayer->setMinimumBalance(crossFeature((*it)->getMinimumBalance(), best->getMinimumBalance()));
      newPlayer->setTradingChance(crossFeature((*it)->getTradingChance(), best->getTradingChance()));
      newPlayer->setMinimumCards(crossFeature((*it)->getMinimumCards(), best->getMinimumCards()));
    }

    players.at((*it)->getId()) = newPlayer;

  }
}

int AGManager::crossFeature(int v1, int v2) {
  return (v1+v2) / 2;
}

void AGManager::mutate() {
  int i, stage, chance;
  float mutatedValue;
  for(stage = 0; stage < 3; stage++) {
    for(i = 0; i < MAX_PLAYERS; i++) {
      AGPlayer *p = players[i];
      p->setStage(stage);

      chance = rand() % MUTATION;
      mutatedValue = p->getBuyingChance() * (1 + (float)chance/100);
      p->setBuyingChance(round(mutatedValue));
      chance = rand() % MUTATION;
      mutatedValue = p->getBuildingChance() * (1 + (float)chance/100);
      p->setBuildingChance(chance);
      chance = rand() % MUTATION;
      mutatedValue = p->getPayingJailChance() * (1 + (float)chance/100);
      p->setPayingJailChance(chance);
      chance = rand() % MUTATION;
      mutatedValue = p->getMortgageChance() * (1 + (float)chance/100);
      p->setMortgageChance(chance);
      chance = rand() % MUTATION;
      mutatedValue = p->getTradingChance() * (1 + (float)chance/100);
      p->setTradingChance(chance);

      chance = rand() % MUTATION;
      mutatedValue = p->getMinimumBalance() * (1 + (float)chance/100);
      p->setMinimumBalance(chance);

      chance = rand() % MUTATION;
      mutatedValue = p->getMinimumCards() * (1 + (float)chance/100);
      p->setMinimumCards(chance);
    }
  }
}

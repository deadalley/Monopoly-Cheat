#ifndef H_AGMANAGER
#define H_AGMANAGER

#include <vector>
#include <string>
#include <fstream>
#include "game.h"

#define MAX_PLAYERS 50
#define PLAYERS_PER_ROUND 3
#define N_GENERATIONS 300
#define MUTATION 50

using namespace std;

class AGManager {
  private:
    static int generation;
    static int mutation;
    static vector<AGPlayer*> players;
    static int crossFeature(int, int);

  public:
    static void initPlayers();
    static void runAG();
    static AGPlayer* simulateGeneration();
    static void crossover(AGPlayer*);
    static void mutate(AGPlayer*);
    static void logBestFeatures(AGPlayer*);
    static void logResults();
    static void logInitPlayers();
};

#endif

#ifndef H_AGMANAGER
#define H_AGMANAGER

#include <vector>
#include <string>
#include <fstream>
#include "game.h"
#include "color.h"

#define MAX_PLAYERS 50
#define PLAYERS_PER_ROUND 1
#define N_GENERATIONS 250
#define MUTATION 2

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

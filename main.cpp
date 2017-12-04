#include "game.h"

using namespace std;

#include "cards.h"
#include "agmanager.h"

int main() {
  srand(time(NULL));
  Cards::initCards();

  AGManager::initPlayers();
  AGManager::simulateGeneration();
  return 0;
}

#include "game.h"

using namespace std;

#include "cards.h"
#include "agmanager.h"

int main() {
  //_VERBOSE = false;
  srand(time(NULL));
  Cards::initCards();

  AGManager::initPlayers();
  AGManager::runAG();
  return 0;
}

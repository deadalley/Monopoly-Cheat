#include "agmanager.h"

void AGManager::initPlayer(AGPlayer *player) {
  player->buyingChance = 100;
  player->buildingChance = 100;
  player->payingJailChance = 100;
  player->mortgageChance = 100;
  player->minimumBalance = 50;
  player->tradingChance = 100;
  player->minimumCards = 3;
}

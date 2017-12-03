#include "agplayer.h"
#include "utils.h"

void AGPlayer::setBuyingChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  buyingChance = c;
}

void AGPlayer::setBuildingChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  buildingChance = c;
}

void AGPlayer::setPayingJailChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  payingJailChance = c;
}

void AGPlayer::setMortgageChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  mortgageChance = c;
}

void AGPlayer::setMinimumBalance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  minimumBalance = c;
}

void AGPlayer::setTradingChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  tradingChance = c;
}

int AGPlayer::getTradingChance() {
  return tradingChance;
}

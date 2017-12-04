#include "agplayer.h"
#include "utils.h"

AGPlayer::AGPlayer(int id) {
  this->id = id;
}

AGPlayer::AGPlayer(const AGPlayer &p) {
  this->id = p.id;
  this->buyingChance = p.buyingChance;
  this->buildingChance = p.buildingChance;
  this->payingJailChance = p.payingJailChance;
  this->mortgageChance = p.mortgageChance;
  this->minimumBalance = p.minimumBalance;
  this->tradingChance = p.tradingChance;
  this->minimumCards = p.minimumCards;
}

void AGPlayer::setId(int id) {
  this->id = id;
}

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

void AGPlayer::setMinimumCards(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  minimumCards = c;
}

int AGPlayer::getId() {
  return id;
}

int AGPlayer::getTradingChance() {
  return tradingChance;
}

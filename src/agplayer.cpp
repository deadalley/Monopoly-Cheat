#include "agplayer.h"
#include "utils.h"
#include <cstring>
#include <iostream>

using namespace std;

AGPlayer::AGPlayer(int id) {
  this->winCount = 0;
  this->id = id;
}

AGPlayer::AGPlayer(const AGPlayer &p) {
  this->id = p.id;
  this->winCount = p.winCount;
  this->stage = p.stage;
  memcpy(this->buyingChance, p.buyingChance, sizeof(this->buyingChance));
  memcpy(this->buildingChance, p.buildingChance, sizeof(this->buildingChance));
  memcpy(this->payingJailChance, p.payingJailChance, sizeof(this->payingJailChance));
  memcpy(this->mortgageChance, p.mortgageChance, sizeof(this->mortgageChance));
  memcpy(this->minimumBalance, p.minimumBalance, sizeof(this->minimumBalance));
  memcpy(this->tradingChance, p.tradingChance, sizeof(this->tradingChance));
  memcpy(this->minimumCards, p.minimumCards, sizeof(this->minimumCards));
}

int AGPlayer::getId() {
  return id;
}

int AGPlayer::getWinCount() {
  return winCount;
}

void AGPlayer::setStage(int stage) {
  this->stage = stage;
}

void AGPlayer::setId(int id) {
  this->id = id;
}

void AGPlayer::setBuyingChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  buyingChance[stage] = c;
}

void AGPlayer::setBuildingChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  buildingChance[stage] = c;
}

void AGPlayer::setPayingJailChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  payingJailChance[stage] = c;
}

void AGPlayer::setMortgageChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  mortgageChance[stage] = c;
}

void AGPlayer::setMinimumBalance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  minimumBalance[stage] = c;
}

void AGPlayer::setTradingChance(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  tradingChance[stage] = c;
}

void AGPlayer::setMinimumCards(int c) {
  if(c < 0)
    throw NEGATIVE_VALUE;
  minimumCards[stage] = c;
}

int AGPlayer::getBuyingChance() {
  return buyingChance[stage];
}

int AGPlayer::getBuildingChance() {
  return buildingChance[stage];
}

int AGPlayer::getPayingJailChance() {
  return payingJailChance[stage];
}

int AGPlayer::getMortgageChance() {
  return mortgageChance[stage];
}

int AGPlayer::getMinimumBalance() {
  return minimumBalance[stage];
}

int AGPlayer::getTradingChance() {
  return tradingChance[stage];
}

int AGPlayer::getMinimumCards() {
  return minimumCards[stage];
}

void AGPlayer::increaseWinCount() {
  winCount = winCount +1;
}

void AGPlayer::resetWinCount() {
  winCount = 0;
}

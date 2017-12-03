#include "bank.h"
#include "gamecontroller.h"

Wallet Bank::Balance;

void Bank::initBank() {
  Balance.setBalance(20580);
}

#include "bank.h"
#include "gamecontroller.h"

Wallet Bank::Balance;

void Bank::initBank() {
  //Bills initBalance = {30, 30, 30, 30, 30, 30, 30};
  //Balance.setBalance(initBalance);
  Balance.setBalance(20580);
}

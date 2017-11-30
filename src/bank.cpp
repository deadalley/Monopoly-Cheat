#include "bank.h"

Wallet Bank::Balance;

void Bank::initBank() {
  Bills initBalance;
  initBalance.ones = 30;
  initBalance.fives = 30;
  initBalance.tens = 30;
  initBalance.twenties = 30;
  initBalance.fifties = 30;
  initBalance.one_hundreds = 30;
  initBalance.five_hundreds = 30;
  Balance.setBalance(initBalance);
}

void Bank::_currentBalance() {
  cout << "Bank's current balance:" << endl;
  Balance.printBalance();
}

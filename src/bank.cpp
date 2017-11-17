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
/*
void Bank::deposit(Bills bills) {
  balance += bills;
}

bool Bank::deduct(int value) {
  return deduct(convert(value));
}

bool Bank::deduct(Bills bills) {
  // Check if there are enough bills to deduct
  if(bills > balance) {
    cerr << "Cannot deduct from bank: not enough bills" << endl;
    return false;
  }

  balance -= bills;
  return true;
}

Bills Bank::convert(int value) {
  if(value < 0) {
    cerr << "Cannot convert negative value" << endl;
    return {0, 0, 0, 0, 0, 0, 0};
  }
  Bills newBills;

  newBills.five_hundreds = value / 500;
  value -= newBills.five_hundreds * 500;

  newBills.one_hundreds = value / 100;
  value -= newBills.one_hundreds * 100;

  newBills.fifties = value / 50;
  value -= newBills.five_hundreds * 50;

  newBills.twenties = value / 20;
  value -= newBills.twenties * 20;

  newBills.tens = value / 10;
  value -= newBills.tens * 10;

  newBills.fives = value / 5;
  value -= newBills.fives * 5;

  newBills.ones = value;

  return newBills;
}
*/
void Bank::_currentBalance() {
  cout << "Bank's current balance:" << endl;
  Balance.printBalance();
}

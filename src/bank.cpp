#include "bank.h"

Bills Bank::balance;

void Bank::initBank() {
  balance.ones = 30;
  balance.fives = 30;
  balance.tens = 30;
  balance.twenties = 30;
  balance.fifties = 30;
  balance.one_hundreds = 30;
  balance.five_hundreds = 30;
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

void Bank::_currentBalance() {
  cout << "Bank's current balance:" << endl;
  cout << "Ones: " << balance.ones << endl;
  cout << "Fives: " << balance.fives << endl;
  cout << "Tens: " << balance.tens << endl;
  cout << "Twenties: " << balance.twenties << endl;
  cout << "Fifties: " << balance.fifties << endl;
  cout << "One hundreds: " << balance.one_hundreds << endl;
  cout << "Five hundreds: " << balance.five_hundreds << endl;
}

#include "wallet.h"

Wallet::Wallet() {
  
}

Wallet::Wallet(Bills bills) {
  this->balance = bills;
}

Wallet::Wallet(int value) {
  this->balance = convert(value);
}

void Wallet::setBalance(Bills bills) {
  this->balance = bills;
}

Bills Wallet::getBalance() {
  return this->balance;
}

Bills Wallet::convert(int value) {
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

void Wallet::deposit(Bills bills) {
  this->balance += bills;
}

void Wallet::deposit(int value) {
  this->balance += convert(value);
}

bool Wallet::deduct(Bills bills) {
  // Check if there are enough bills to deduct
  if(bills > this->balance) {
    cerr << "Cannot deduct from wallet: not enough bills" << endl;
    return false;
  }

  this->balance -= bills;
  return true;
}

bool Wallet::deduct(int value) {
  deduct(convert(value));
}

void Wallet::payTo(Wallet *entity, int value) {
  if(deduct(value))
    entity->deposit(value);
}

void Wallet::receiveFrom(Wallet *entity, int value) {
  if(entity->deduct(value))
    deposit(value);
}

void Wallet::printBalance() {
  cout << balance;
}

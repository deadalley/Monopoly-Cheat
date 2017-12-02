#include "wallet.h"
#include "bank.h"
//#include "gamecontroller.h"

Wallet::Wallet() {
  balance = 0;
}

void Wallet::setBalance(int value) {
  this->balance = value;
}

int Wallet::getBalance() {
  return this->balance;
}

void Wallet::deposit(int value) {
  this->balance += value;
}

bool Wallet::deduct(int value) {
  // Check if there are enough bills to deduct
  if(value > balance) {
    cout << "Cannot deduct. Not enoug credit." << endl;
    return false;
  }

  this->balance -= value;
  return true;
}

bool Wallet::payTo(Wallet *entity, int value) {
  cout << "\tCurrent balance: " << balance << endl;
  if(value <= 0)
    throw PAY_VALUE_ERROR;

  // Check if has credit to pay
  if(deduct(value)) {
    entity->deposit(value);
    cout << "Paid " << value << endl;
    return true;
  }

  return false;
}

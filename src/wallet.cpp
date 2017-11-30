#include "wallet.h"
#include "bank.h"

Wallet::Wallet() {
  balance.ones = 0;
  balance.fives = 0;
  balance.tens = 0;
  balance.twenties = 0;
  balance.fifties = 0;
  balance.one_hundreds = 0;
  balance.five_hundreds = 0;
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

int Wallet::getBalanceValue() {
  return convert(this->balance);
}

Bills Wallet::convert(int value) {
  if(value < 0) {
    cerr << "Cannot convert negative value" << endl;
    return {-1, -1, -1, -1, -1, -1, -1};
  }

  Bills newBills;

  int i, values[7] = {1, 5, 10, 20, 50, 100, 500};

  for(i = 6; i > 0; i--) {
    newBills[i] = value / values[i];
    value -= newBills[i] * values[i];
  }

  newBills[0] = value;
  return newBills;
}

int Wallet::convert(Bills bills) {
  int i, values[7] = {1, 5, 10, 20, 50, 100, 500}, value = 0;
  for(i = 0; i < 7; i++) {
    value += bills[i] * values[i];
  }

  return value;
}

void Wallet::deposit(Bills bills) {
  this->balance += bills;
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

bool Wallet::payTo(Wallet *entity, int value) {
  // Check if has credit to pay
  if(convert(balance) < value) {
    cerr << "Not enough money!" << endl;
    return false;
  }
  /*
  cout << "----> PAYING " << value << " <----" << endl;
  cout << balance << endl;
  cout << entity->getBalance() << endl;
  */
  int i, values[7] = {1, 5, 10, 20, 50, 100, 500}, v = value;
  Bills newBills = {0, 0, 0, 0, 0, 0, 0};

  // Deduct if possible
  for(i = 6; i >= 0; i--) {
    int q = v / values[i];
    int m = min(q, balance[i]);
    v -= m * values[i];
    balance[i] -= m;
    newBills[i] = m;
  }

  //cout << v << endl;

  // If couldn't deduct entire value, try to exchange bills
  if(v > 0) {
    for(i = 0; i < 7; i++) {
      // Find first bill greater than value to be exchange
      if(balance[i] * values[i] > v) {
        // Try to exchange with bank
        Bills exBills = Bank::Balance.exchange(values[i], v);
        if(exBills[0] == -1) {
          // Try to exchange with player
          exBills = entity->exchange(values[i], v);
          if(exBills[0] == -1) {
            cerr << "Could not convert. Aborted." << endl;
            return false;
          }
        }
        // Exchange bills
        balance[i]--;
        balance += exBills;

        // Pay remaining value
        exBills = convert(v);
        balance -= exBills;
        entity->deposit(exBills);
        break;
      }
    }
  }

  entity->deposit(newBills);
  /*
  cout << "Balance:" << endl;
  cout << balance << endl;
  cout << entity->getBalance() << endl;
  */
  return true;
}

void Wallet::receiveFrom(Wallet *entity, Bills bills) {
  if(entity->deduct(bills))
    deposit(bills);
}

void Wallet::receiveFrom(Wallet *entity, int value) {
  //cout << "----> RECEIVE " << value << " <----" << endl;
  entity->payTo(this, value);
}

void Wallet::printBalance() {
  cout << balance;
}

Bills Wallet::exchange(int value, int min_exchange) {
  // Example: exchange 1 $20 bill (value = 20, min_exchange = 10) for 2 $10 bills
  //cout << "----> EXCHANGE " << value << " <----" << endl;
  int i, values[7] = {1, 5, 10, 20, 50, 100, 500};
  Bills newBills = {0, 0, 0, 0, 0, 0, 0};

  // Convert into necessary bills
  newBills = convert(min_exchange);
  newBills += convert(value - min_exchange);

  if(deduct(newBills)) {
    deposit(convert(value));
    //cout << "Converted " << value << " with min " << min_exchange << " into: " << endl;
    //cout << newBills << endl;
    return newBills;
  }

  else return {-1, -1, -1, -1, -1, -1, -1};
}

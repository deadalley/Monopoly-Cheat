#include "wallet.h"
#include "bank.h"
//#include "gamecontroller.h"

Wallet::Wallet() {
  balance = {0, 0, 0, 0, 0, 0, 0};
}

void Wallet::setBalance(Bills bills) {
  this->balance = bills;
}

Bills Wallet::getBalance() {
  return this->balance;
}

int Wallet::getBalanceValue() {
  //return this->totalAmount;
  return convert(this->balance);
}

Bills Wallet::convert(int value) {
  if(value < 0) {
    cerr << "Cannot convert negative value (" << value << ")" << endl;
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
  int i;
  for(i = 0; i < 7; i++) {
    if(bills[i] != 0 && bills[i] > balance[i]) {
      cerr << "Cannot deduct from wallet: not enough bills" << endl;
      return false;
    }
  }

  this->balance -= bills;
  return true;
}

bool Wallet::payTo(Wallet *entity, int value) {
  int currentBalance = this->getBalanceValue();
  int otherCurrentBalance = entity->getBalanceValue();
  cout << "----> PAYING " << value << " <----" << endl;
  cout << ">> Payer balance: " << currentBalance << endl;
  cout << ">> Receiver balance: " << otherCurrentBalance << endl;

  if(value <= 0)
    throw PAY_VALUE_ERROR;

  // Check if has credit to pay
  if(this->getBalanceValue() < value) {
    cerr << "Not enough money!" << endl;
    return false;
  }
/*
  if(totalAmount >= value) {
    totalAmount -= value;
    entity->totalAmount += value;
    return true;
  }

  else {
    cerr << "Not enough money!" << endl;
    return false;
  }
  */
/*
  cout << ">> Payer" << endl;
  cout << balance << endl;
  cout << ">> Receiver" << endl;
  cout << entity->getBalance() << endl;
*/
  int i, values[7] = {1, 5, 10, 20, 50, 100, 500}, v = value;
  Bills newBills = {0, 0, 0, 0, 0, 0, 0};
  Bills billsToDeduct = {0, 0, 0, 0, 0, 0, 0};

  // Deduct if possible
  for(i = 6; i >= 0; i--) {
    int q = v / values[i];
    int m = min(q, balance[i]);
    v -= m * values[i];
    billsToDeduct[i] = m;
    newBills[i] = m;
  }
  //cout << "Rest: " << v << endl;

  // If couldn't deduct entire value, try to get change
  if(v > 0) {
    for(i = 0; i < 7; i++) {
      // Pay with bill greater than value
      if(balance[i] > 0 &&  values[i] > value) {
        int change = values[i] - value;
        Bills bills = convert(change);
        cout << "Change: " << change << endl;

        // Try to deduct change from other player
        if(entity->deduct(bills)) {
          // Deduct bill with greater value
          balance[i]--;
          // Deposit bill
          entity->deposit(convert(values[i]));
          // Deposit change
          this->deposit(bills);

          cout << ">> Payer" << endl;
          cout << balance << endl;
          cout << ">> Receiver" << endl;
          cout << entity->getBalance() << endl;

          if(this->getBalanceValue() + value != currentBalance || entity->getBalanceValue() - value != otherCurrentBalance) {
            cerr << "ERROR: Wrong amount deducted" << endl;
            throw PAY_VALUE_ERROR;
          }
          return true;
        }
        break;
      }
    }
  }

  // If couldn't deduct entire value, try to exchange bills
  if(v > 0) {
    for(i = 0; i < 7; i++) {
      Bills exBills;
      if(balance[i] > 0 && values[i] > value) {
        exBills = Bank::tryToExchangeBills(values[i], value);
        if(exBills[0] != -1) {
          balance[i]--;
          this->deposit(exBills);
          return this->payTo(entity, value);
        }
      }
      // Find first bill greater than value to be exchange
      if((balance[i] - billsToDeduct[i]) * values[i] > v) {
        // Try to exchange with bank
        /*cout << "==== BANK BALANCE ====" << endl;
        cout << Bank::Balance.getBalance() << endl;
        Bills exBills = Bank::Balance.exchange(values[i], v);
        cout << "==== BANK BALANCE ====" << endl;
        cout << Bank::Balance.getBalance() << endl;

        if(exBills[0] == -1) {
          // Try to exchange with player
          cout << "==== PLAYER BALANCE ====" << endl;
          cout << entity->getBalance() << endl;
          exBills = entity->exchange(values[i], v);
          cout << "==== PLAYER BALANCE ====" << endl;
          cout << entity->getBalance() << endl;
          if(exBills[0] == -1) {
            // Try to exchange with other players
            exBills = GameController::exchangeWithPlayers(values[i], v);
            if(exBills[0] == -1) {
              cerr << "Could not convert. Aborted." << endl;
              return false;
            }
          }
        }*/
        exBills = Bank::tryToExchangeBills(values[i], v);
        if(exBills[0] == -1) {
          cout << "Cannot pay. Not enough bills." << endl;
          return false;
        }
        // Exchange bills
        balance[i]--;
        this->deposit(exBills);
        //balance += exBills;

        // Pay remaining value
        exBills = convert(v);
        this->deduct(exBills);
        entity->deposit(exBills);
        break;
      }
    }
  }

  this->deduct(billsToDeduct);
  entity->deposit(newBills);
/*
  cout << ">> Payer" << endl;
  cout << balance << endl;
  cout << ">> Receiver" << endl;
  cout << entity->getBalance() << endl;
*/
  if(this->getBalanceValue() + value != currentBalance || entity->getBalanceValue() - value != otherCurrentBalance) {
    cerr << "ERROR: Wrong amount deducted" << endl;
    throw PAY_VALUE_ERROR;
  }
/*
  cout << "Deducted " << value << endl;
  cout << "Payer balance: " << this->getBalanceValue() << endl;
  cout << "Receiver balance: " << entity->getBalanceValue() << endl;
*/
  return true;
}

void Wallet::receiveFrom(Wallet *entity, Bills bills) {
  //totalAmount = convert(bills);
  if(entity->deduct(bills))
    deposit(bills);
}

void Wallet::printBalance() {
  cout << balance;
}

Bills Wallet::exchange(int value, int min_exchange) {
  // Example: exchange 1 $20 bill (value = 20, min_exchange = 10) for 2 $10 bills
  cout << "----> EXCHANGE " << value << " <----" << endl;
  int i, values[7] = {1, 5, 10, 20, 50, 100, 500};
  Bills newBills = {0, 0, 0, 0, 0, 0, 0};

  // Convert into necessary bills
  newBills = convert(min_exchange);
  newBills += convert(value - min_exchange);

  if(deduct(newBills)) {
    deposit(convert(value));
    cout << "Converted " << value << " with min " << min_exchange << " into: " << endl;
    //cout << newBills << endl;
    return newBills;
  }

  else return {-1, -1, -1, -1, -1, -1, -1};
}

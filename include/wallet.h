#ifndef H_WALLET
#define H_WALLET

//#include "bank"
#include "utils.h"
#include <algorithm>

class Wallet {
  private:
    int balance;
    void deposit(int);
    bool deduct(int);


  public:
    Wallet();

    void setBalance(int);
    int getBalance();

    bool payTo(Wallet*, int);
};

#endif

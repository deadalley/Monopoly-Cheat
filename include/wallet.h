#ifndef H_WALLET
#define H_WALLET

//#include "bank"
#include "utils.h"
#include <algorithm>

class Wallet {
  private:
    Bills balance;

    void deposit(Bills);

    bool deduct(Bills);

    Bills convert(int);
    int convert(Bills);

  public:
    //int totalAmount;
    Wallet();

    void setBalance(Bills);
    Bills getBalance();
    int getBalanceValue();

    bool payTo(Wallet*, int);
    void receiveFrom(Wallet*, Bills);
    void printBalance();
    Bills exchange(int, int);
};

#endif

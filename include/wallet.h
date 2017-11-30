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

  public:
    Wallet();
    Wallet(Bills);
    Wallet(int);

    static Bills convert(int);
    static int convert(Bills);

    void setBalance(Bills);
    Bills getBalance();
    int getBalanceValue();

    bool payTo(Wallet*, int);
    void receiveFrom(Wallet*, Bills);
    void receiveFrom(Wallet*, int);
    void printBalance();
    Bills exchange(int, int);
};

#endif

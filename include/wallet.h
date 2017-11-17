#ifndef H_WALLET
#define H_WALLET

//#include "bank"
#include "utils.h"

class Wallet {
  private:
    Bills balance;

    void deposit(Bills);
    void deposit(int);

    bool deduct(Bills);
    bool deduct(int);

  public:
    Wallet();
    Wallet(Bills);
    Wallet(int);

    static Bills convert(int);

    void setBalance(Bills);
    Bills getBalance();

    void payTo(Wallet*, int);
    void receiveFrom(Wallet*, Bills);
    void receiveFrom(Wallet*, int);
    void printBalance();
};

#endif

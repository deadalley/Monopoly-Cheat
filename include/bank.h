#ifndef H_BANK
#define H_BANK

#include "utils.h"
#include "wallet.h"

using namespace std;

class Bank {
  private:
    //static Bills balance;

  public:
    static Wallet Balance;

    static void initBank();
    static void _currentBalance();
};

#endif

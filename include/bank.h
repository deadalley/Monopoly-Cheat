#ifndef H_BANK
#define H_BANK

#include "utils.h"
#include "wallet.h"

using namespace std;

class Bank {
  public:
    static Wallet Balance;

    static void initBank();
    static Bills tryToExchangeBills(int, int);
};

#endif

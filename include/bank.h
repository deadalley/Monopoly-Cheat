#ifndef H_BANK
#define H_BANK

#include "utils.h"
#include "wallet.h"

using namespace std;

class Bank {
  public:
    Wallet Balance;

    void initBank();
};

#endif

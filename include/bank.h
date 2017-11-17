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
    //static Bills convert(int);
    //static bool deduct(int);
    //static bool deduct(Bills);
    //static void deposit(Bills);
    static void _currentBalance();
};

#endif

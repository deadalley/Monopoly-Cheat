#ifndef H_BANK
#define H_BANK

#include <iostream>
#include "utils.h"

using namespace std;

class Bank {
  private:
    static Bills balance;

  public:
    static void initBank();
    static Bills convert(int);
    static bool deduct(int);
    static bool deduct(Bills);
    static void _currentBalance();
};

#endif

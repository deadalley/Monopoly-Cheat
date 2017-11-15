#ifndef H_BANK
#define H_BANK

class Bank {
  public:
    Bills balance;

    Bank();
    static Bills convert(int);
};

#endif

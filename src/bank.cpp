#include "bank.h"

Bank::Bank() {
  bills.ones = 30;
  bills.fives = 30;
  bills.tens = 30;
  bills.twenties = 30;
  bills.fifties = 30;
  bills.one_hundreds = 30;
  bills.five_hundreds = 30;
}

Bills Bank::convert(int value) {
  Bills newBills;

  newBills.five_hundreds = value / 500;
  value -= newBills.five_hundreds * 500;

  newBills.one_hundreds = value / 100;
  value -= newBills.one_hundreds * 100;

  newBills.fifties = value / 50;
  value -= newBills.five_hundreds * 50;

  newBills.twenties = value / 20;
  value -= newBills.twenties * 20;

  newBills.tens = value / 10;
  value -= newBills.tens * 10;

  newBills.fives = value / 5;
  value -= newBills.fives * 5;

  newBills.ones = value;
}

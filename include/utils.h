#ifndef H_UTILS
#define H_UTILS

#define GO 0
#define MEDITERRANEAN_AV 1
#define CHEST_1 2
#define BALTIC_AV 3
#define INCOME_TAX 4
#define READING_RR 5
#define ORIENTAL_AV 6
#define CHANCE_1 7
#define VERMONT_AV 8
#define CONNECTICUT_AV 9
#define JAIL 10
#define ST_CHARLES_PLACE 11
#define ELECTRIC_CO 12
#define STATES_AV 13
#define VIRGINIA_AV 14
#define PENNSYLVANIA_RR 15
#define ST_JAMES_PLACE 16
#define CHEST_2 17
#define TENNESSEE_AV 18
#define NEW_YORK_AV 19
#define FREE_PARKING 20
#define KENTUCKY_AV 21
#define CHANCE_2 22
#define INDIANA_AV 23
#define ILLINOIS_AV 24
#define BO_RR 25
#define ATLANTIC_AV 26
#define VENTNOR_AV 27
#define WATER_WORKS 28
#define MARVIN_GARDENS 29
#define GO_TO_JAIL 30
#define PACIFIC_AV 31
#define NORTH_CAROLINA_AV 32
#define CHEST_3 33
#define PENNSYLVANIA_AV 34
#define SHORT_LINE 35
#define CHANCE_3 36
#define PARK_PLACE 37
#define LUXURY_TAX 38
#define BOARDWALK 39

#include <iostream>

using namespace std;

typedef struct Bills {
  int ones;
  int fives;
  int tens;
  int twenties;
  int fifties;
  int one_hundreds;
  int five_hundreds;

  void operator= (const int &v) {
    ones = v;
    fives = v;
    tens = v;
    twenties = v;
    fifties = v;
    one_hundreds = v;
    five_hundreds = v;
  }

  void operator += (const Bills &b) {
    ones += b.ones;
    fives += b.fives;
    tens += b.tens;
    twenties += b.twenties;
    fifties += b.fifties;
    one_hundreds += b.one_hundreds;
    five_hundreds += b.five_hundreds;
  }

  void operator -= (const Bills &b) {
    ones -= b.ones;
    fives -= b.fives;
    tens -= b.tens;
    twenties -= b.twenties;
    fifties -= b.fifties;
    one_hundreds -= b.one_hundreds;
    five_hundreds -= b.five_hundreds;
  }

  bool operator > (const Bills &b) {
    return ones > b.ones && \
           fives > b.fives && \
           tens > b.tens && \
           twenties > b.twenties && \
           fifties > b.fifties && \
           one_hundreds > b.one_hundreds && \
           five_hundreds > b.five_hundreds;
  }

  bool operator < (const Bills &b) {
    return ones < b.ones && \
           fives < b.fives && \
           tens < b.tens && \
           twenties < b.twenties && \
           fifties < b.fifties && \
           one_hundreds < b.one_hundreds && \
           five_hundreds < b.five_hundreds;
  }

  int& operator [] (int i) {
    switch(i) {
      case 0: return ones;
      case 1: return fives;
      case 2: return tens;
      case 3: return twenties;
      case 4: return fifties;
      case 5: return one_hundreds;
      case 6: return five_hundreds;
    }
  }

  friend ostream& operator<< (ostream &os, const Bills &b) {
    os << "Ones: " << b.ones << endl;
    os << "Fives: " << b.fives << endl;
    os << "Tens: " << b.tens << endl;
    os << "Twenties: " << b.twenties << endl;
    os << "Fifties: " << b.fifties << endl;
    os << "One hundreds: " << b.one_hundreds << endl;
    os << "Five hundreds: " << b.five_hundreds << endl;
  }
} Bills;

#endif

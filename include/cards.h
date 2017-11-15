#ifndef H_CARDS
#define H_CARDS

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "board.h"

#include "titledeed.h"
#include "railroad.h"
#include "utility.h"
#include "eventcard.h"

using namespace std;

class Cards {
  public:
    static Utility *utilities;
    static Railroad *railroads;
    static TitleDeed *deeds;
    static EventCard *chest;
    static EventCard *chance;

    static void inputTitleDeeds(string file_name);
    static void initRailroads();
    static void initUtilities();
    static void inputChanceCards(string file_name);
    static void inputChestCards(string file_name);
};

#endif

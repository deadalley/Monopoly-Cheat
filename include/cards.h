#ifndef H_CARDS
#define H_CARDS

#include <stdlib.h>
#include <fstream>
#include <string>

#include "utils.h"
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

    static void inputTitleDeeds(string);
    static void inputChanceCards(string);
    static void inputChestCards(string);
    static void initRailroads();
    static void initUtilities();
};

#endif

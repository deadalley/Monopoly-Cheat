#ifndef H_CARDS
#define H_CARDS

#include <string>

#include "eventcard.h"
#include "titledeed.h"
#include "railroad.h"
#include "utility.h"

class Cards {
  private:
    static void inputTitleDeeds(string);
    static void inputChanceCards(string);
    static void inputChestCards(string);
    static void initRailroads();
    static void initUtilities();

  public:
    static Utility *utilities;
    static Railroad *railroads;
    static TitleDeed *deeds;
    static EventCard *chest;
    static EventCard *chance;

    static void initCards();
};

#endif

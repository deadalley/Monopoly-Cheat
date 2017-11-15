#ifndef H_CARDS
#define H_CARDS

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "titledeed.h"
#include "railroad.h"
#include "utility.h"

using namespace std;

class Cards {
  public:
    static Utility *utilities;
    static Railroad *railroads;
    static TitleDeed *deeds;

    void inputTitleDeeds(string file_name);
    void initRailroads();
    void initUtilities();
};

#endif

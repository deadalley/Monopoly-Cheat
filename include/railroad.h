#ifndef H_RAILROAD
#define H_RAILROAD

#include <string>

using namespace std;

class Railroad {
  public:
    string name;
    int rent[4];
    int mortgage;

    Railroad(string name);
};

#endif
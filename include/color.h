#ifndef H_COLOR
#define H_COLOR

#include <string>

using namespace std;

enum Color {
  Purple,
  Cyan,
  Pink,
  Orange,
  Red,
  Yellow,
  Green,
  Blue
};

Color parseColor(string);
string colorToString(Color);
#endif

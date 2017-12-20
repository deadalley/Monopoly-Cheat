#include "color.h"

#include <algorithm>

Color parseColor(string name) {
  transform(name.begin(), name.end(), name.begin(), ::tolower);
  if(name.compare("purple") == 0)
    return Purple;
  if(name.compare("cyan") == 0)
    return Cyan;
  if(name.compare("pink") == 0)
    return Pink;
  if(name.compare("orange") == 0)
    return Orange;
  if(name.compare("red") == 0)
    return Red;
  if(name.compare("yellow") == 0)
    return Yellow;
  if(name.compare("green") == 0)
    return Green;
  if(name.compare("blue") == 0)
    return Blue;
}

string colorToString(Color color) {
  switch(color) {
    case Purple:
      return "Purple";
      break;
    case Cyan:
      return "Cyan";
      break;
    case Pink:
      return "Pink";
      break;
    case Orange:
      return "Orange";
      break;
    case Red:
      return "Red";
      break;
    case Yellow:
      return "Yellow";
      break;
    case Green:
      return "Green";
      break;
    case Blue:
      return "Blue";
      break;
  }
}

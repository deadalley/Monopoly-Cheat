#include "cards.h"

void Cards::inputTitleDeeds(string file_name) {
  // Open file
  ifstream file;

  file.open(file_name);
  if(!file) {
    cerr << "Unable to open file " << file_name;
  }

  // Parse line
  string line;
  TitleDeed newDeed;
  int i = 0;
  while(getline(file, line)){
    size_t k = 0;
    size_t pos = 0;
    string value;

    // Parse value
    while((pos = line.find(", ")) != string::npos) {
      value = line.substr(0, pos);

      switch(k) {
        case 0:
          newDeed.name = value;
          break;
        case 1:
          //TO DO: Fix
          newDeed.color = value;
          break;
        case 2:
          newDeed.price = stoi(value);
          break;
        case 3:
          while (k < 10) {
            pos = line.find(", ");
            newDeed.rent[k-3] = stoi(line.substr(0, pos));
            line.erase(0, pos + 2);
            k++;
          }
          k--;
          break;
        case 10:
          newDeed.mortgage = stoi(value);
          break;
        case 11:
          newDeed.house_cost = stoi(value);
          break;
        case 12:
          newDeed.hotel_cost = stoi(value);
          break;
      }

      line.erase(0, pos + 2);
      k++;
    }
    deeds[i] = newDeed;
    i++;
  }

  file.close();
}

void Cards::initRailroads() {
  Railroad r1("B & O Railroad");
  railroads[0] = r1;

  Railroad r2("Pennsylvania Railroad");
  railroads[1] = r2;

  Railroad r3("Reading Railroad");
  railroads[2] = r3;

  Railroad r4("Short Line Railroad");
  railroads[3] = r4;
}

void Cards::initUtilities() {
  Utility u1("Electric Company");
  utilities[0] = u1;

  Utility u2("Water Works");
  utilities[1] = u2;
}

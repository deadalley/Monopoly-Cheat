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

void Cards::inputChanceCards(string file_name) {
  // Open file
  ifstream file;

  file.open(file_name);
  if(!file) {
    cerr << "Unable to open file " << file_name;
  }

  // Parse line
  string line;
  int i = 0;
  while(getline(file, line)) {
    EventCard newCard(line, 0);

    if(i < 5) {
      newCard.effectType = GoToTile;
      switch(i) {
        case 0:
          newCard.tile = GO;
          break;
        case 1:
          newCard.tile = ILLINOIS_AV;
          break;
        case 2:
          newCard.tile = ST_CHARLES_PLACE;
          break;
        case 3:
          newCard.tile = READING_RR;
          break;
        case 4:
          newCard.tile = BOARDWALK;
          break;
      }
    }

    if(i == 5) {
      newCard.effectType = GoToUtility;
    }

    if(5 < i < 8) {
      newCard.effectType = GoToRailroad;
    }

    if(i == 8) {
      newCard.effectType = GoBack3;
    }

    if(i == 9) {
      newCard.effectType = GoToJail;
      newCard.tile = JAIL;
    }

    if(9 < i < 13) {
      newCard.effectType = Collect;
      switch(i) {
        case 10:
          newCard.value = 150;
          break;
        case 11:
          newCard.value = 100;
          break;
        case 12:
          newCard.value = 50;
          break;
      }
    }

    if(i == 13) {
      newCard.effectType = Pay;
      newCard.value = 15;
    }

    if(i == 14) {
      newCard.effectType = PayForEach;
    }

    if(i == 15) {
      newCard.effectType = PayToAll;
      newCard.value = 50;
    }

    if(i == 16) {
      newCard.effectType = GetOutJail;
    }

    chance[i] = newCard;
    i++;
  }

  file.close();

}

void Cards::inputChestCards(string file_name) {
  // Open file
  ifstream file;

  file.open(file_name);
  if(!file) {
    cerr << "Unable to open file " << file_name;
  }

  // Parse line
  string line;
  int i = 0;
  while(getline(file, line)) {
    EventCard newCard(line, 1);

    if(i == 0) {
      newCard.effectType = GoToTile;
      newCard.tile = GO;
    }

    if(i == 1) {
      newCard.effectType = GoToJail;
      newCard.tile = JAIL;
    }

    if(1 < i < 11) {
      newCard.effectType = Collect;
      switch(i) {
        case 2:
          newCard.value = 200;
          break;
        case 3:
          newCard.value = 50;
          break;
        case 4:
          newCard.value = 100;
          break;
        case 5:
          newCard.value = 20;
          break;
        case 6:
          newCard.value = 100;
          break;
        case 7:
          newCard.value = 100;
          break;
        case 8:
          newCard.value = 25;
          break;
        case 9:
          newCard.value = 10;
          break;
        case 10:
          newCard.value = 100;
          break;
      }
    }

    if(i == 11) {
      newCard.effectType = ReceiveFromAll;
      newCard.value = 50;
    }

    if(11 < i < 15) {
      newCard.effectType = Pay;
      switch(i) {
        case 12:
          newCard.value = 50;
          break;
        case 13:
          newCard.value = 100;
          break;
        case 14:
          newCard.value = 150;
          break;
      }
    }

    if(i == 15) {
      newCard.effectType = PayForEach;
    }

    if(i == 16) {
      newCard.effectType = GetOutJail;
    }

    chest[i] = newCard;
    i++;
  }

  file.close();

}

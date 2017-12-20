#include "board.h"
#include "bank.h"
#include "cards.h"
#include "utils.h"

#include <algorithm>
#include <random>

void Board::initBoard() {
  // Initialize chance and chest cards
  int i;
  vector<EventCard*> chance, chest;     // Aux vectors for shuffling
  for(i = 0; i < 17; i++) {
    chance.push_back(&Cards::chance[i]);
    chest.push_back(&Cards::chest[i]);
  }

  auto rng = default_random_engine(rand());

  shuffle(chance.begin(), chance.end(), rng);
  shuffle(chest.begin(), chest.end(), rng);

  for(i = 0; i < 17; i++) {
    chanceCards.push(chance[i]);
    chestCards.push(chest[i]);
  }

  // Initialize tiles
  int i_deed = 0, i_railroad = 0, i_utility = 0;
  for(i = GO; i < 40; i++) {
    Board::Tile *tile;
    Card *card = NULL;

    TileType type;
    if(i == GO)
      type = GoTile;

    else if(i == CHEST_1 || i == CHEST_2 || i == CHEST_3)
      type = ChestTile;

    else if(i == CHANCE_1 || i == CHANCE_2 || i == CHANCE_3)
      type = ChanceTile;

    else if(i == JAIL)
      type = JailTile;

    else if(i == GO_TO_JAIL)
      type = GoToJailTile;

    else if(i == FREE_PARKING)
      type = FreeParkingTile;

    else if(i == INCOME_TAX)
      type = IncomeTaxTile;

    else if(i == LUXURY_TAX)
      type = LuxuryTaxTile;

    else {
      type = PropertyTile;

      // Associate card to tile
      if(i == BO_RR || i == READING_RR || i == PENNSYLVANIA_RR || i == SHORT_LINE) {
        card = &Cards::railroads[i_railroad];
        i_railroad++;
      }

      else if(i == ELECTRIC_CO || i == WATER_WORKS) {
        card = &Cards::utilities[i_utility];
        i_utility++;
      }

      else {
        card = &Cards::deeds[i_deed];
        i_deed++;
      }

      card->position = i;
    }

    tile = new Board::Tile(type, i, card);
    map.push_back(*tile);
  }
}

Board::Tile* Board::getTile(int index) {
  return &map[index];
}

void Board::rollDice() {
  int d = 1;
  dice[0] = rand() % (d*6) + 1;
  dice[1] = rand() % (d*6) + 1;
}

int Board::getDie(int i) {
  return dice[i];
}

EventCard* Board::getEventCard(TileType type) {
  EventCard *card = NULL;
  if(type == ChanceTile) {
    card = chanceCards.top();
    chanceCards.pop();
  }

  if(type == ChestTile) {
    card = chestCards.top();
    chestCards.pop();
  }

  // If all cards have been popped from stack, reshuffle cards
  bool s;
  if(chestCards.size() == 0)
    s = true;
  else if(chanceCards.size() == 0)
    s = false;
  else return card;

  int i;
  vector<EventCard*> aux_v;     // Aux vectors for shuffling
  for(i = 0; i < 17; i++) {

    if(s) {
      aux_v.push_back(&Cards::chest[i]);
    }

    else if(!s) {
      aux_v.push_back(&Cards::chance[i]);
    }
  }

  auto rng = default_random_engine(rand());

  shuffle(aux_v.begin(), aux_v.end(), rng);

  for(i = 0; i < 17; i++) {
    if(s)
      chestCards.push(aux_v[i]);
    else if(!s)
      chanceCards.push(aux_v[i]);
  }

  return card;
}

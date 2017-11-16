#include "board.h"
#include <chrono>
void Board::initBoard() {
  int i;
  vector<EventCard*> chance, chest;
  for(i = 0; i < 17; i++) {
    chance.push_back(&Cards::chance[i]);
    chest.push_back(&Cards::chest[i]);
    //chanceCards.push(&Cards::chance[i]);
    //cout << "Pushed " << chanceCards.top()->description << endl;
    //chestCards.push(&Cards::chest[i]);
  }

  auto rng = default_random_engine {};

  shuffle(chance.begin(), chance.end(), rng);
  shuffle(chest.begin(), chest.end(), rng);

  for(i = 0; i < 17; i++) {
    //cout << i << chance[i]->description << endl;
    chanceCards.push(chance[i]);
    //cout << "Pushed " << chanceCards.top()->description << endl;
    chestCards.push(chest[i]);
  }
}

Board::Tile* Board::getTile(int index) {
  return &Board::map[index];
}

int Board::rollDice(int d) {
  return rand() % (d*6) + 1;
}

#include "board.h"

Board::Tile* Board::getTile(int index) {
  return &Board::map[index];
}

int Board::rollDice(int d) {
  return rand() % (d*6) + 1;
}

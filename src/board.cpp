#include "board.h"

Board::Tile* Board::getTile(int index) {
  return &Board::map[index];
}

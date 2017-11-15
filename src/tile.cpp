#include "board.h"

TileType Board::Tile::getType() {
  return this->type;
}

Card* Board::Tile::getCard() {
  return this->card;
}

EventCard* Board::Tile::getEventCard () {
  if (this->type == ChanceTile) {
    return chanceCards.top();
  }

  if (this->type == ChestTile) {
    return chestCards.top();
  }

  return NULL;
}

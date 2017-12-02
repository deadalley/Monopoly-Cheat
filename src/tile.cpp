#include "board.h"

Board::Tile::Tile(TileType type, int position, Card *card) {
  this->type = type;
  this->position = position;
  this->card = card;
  //this->card = NULL;
}

TileType Board::Tile::getType() {
  return this->type;
}

Card* Board::Tile::getCard() {
  return this->card;
}

void Board::Tile::setCard(Card *card) {
  this->card = card;
}

int Board::Tile::getPos() {
  return this->position;
}

#include "board.h"

Board::Tile::Tile(TileType type, int position) {
  this->type = type;
  this->position = position;
  this->card = NULL;
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

EventCard* Board::Tile::getEventCard() {
  if(this->type == ChanceTile) {
    EventCard* chance = Board::chanceCards.top();
    Board::chanceCards.pop();
    return chance;
  }

  if(this->type == ChestTile) {
    EventCard* chest = Board::chestCards.top();
    Board::chestCards.pop();
    return chest;
  }

  return NULL;
}

int Board::Tile::getPos() {
  return this->position;
}

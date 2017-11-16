#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>

#include "player.h"
#include "cards.h"
#include "eventcard.h"
#include "board.h"

using namespace std;

TitleDeed* Cards::deeds = (TitleDeed*) malloc(sizeof(TitleDeed)*22);
Railroad* Cards::railroads = (Railroad*) malloc(sizeof(Railroad)*4);
Utility* Cards::utilities = (Utility*) malloc(sizeof(Utility)*2);
EventCard* Cards::chance = (EventCard*) malloc(sizeof(EventCard)*17);
EventCard* Cards::chest = (EventCard*) malloc(sizeof(EventCard)*17);

vector<Board::Tile> Board::map;
stack<EventCard*> Board::chanceCards;
stack<EventCard*> Board::chestCards;

void init() {
  srand(time(NULL));
  Cards::inputTitleDeeds("titledeeds.cards");
  Cards::inputChanceCards("chance.cards");
  Cards::inputChestCards("chest.cards");
  Cards::initRailroads();
  Cards::initUtilities();
  Board::initBoard();
  Bank::initBank();
}

int main() {
  init();

  // Debug
  /*Bank::_currentBalance();
  Player p1("Player 1");
  Bank::_currentBalance();

  Bills b = Bank::convert(999);
  cout << "Ones: " << b.ones << endl;
  cout << "Fives: " << b.fives << endl;
  cout << "Tens: " << b.tens << endl;
  cout << "Twenties: " << b.twenties << endl;
  cout << "Fifties: " << b.fifties << endl;
  cout << "One hundreds: " << b.one_hundreds << endl;
  cout << "Five hundreds: " << b.five_hundreds << endl;*/


  return 0;
}

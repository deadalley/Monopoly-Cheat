#include "bank.h"
#include "gamecontroller.h"

Wallet Bank::Balance;

void Bank::initBank() {
  Bills initBalance = {30, 30, 30, 30, 30, 30, 30};
  Balance.setBalance(initBalance);
}

Bills Bank::tryToExchangeBills(int value, int min_exchange) {
  // Try to exchange with bank
  cout << "== Bank" << endl;
  cout << Balance.getBalance() << endl;
  Bills newBills = Balance.exchange(value, min_exchange);
  if(newBills[0] != -1)
    return newBills;

  int i;
  for(i = 0; i < GameController::getPlayerSize(); i++) {
    Player *p = GameController::getPlayer(i);
    cout << "== " << p->getName() << endl;
    cout << p->wallet.getBalance() << endl;
    newBills = p->wallet.exchange(value, min_exchange);
    if(newBills[0] != -1) {
      return newBills;
    }
  }
  return newBills;
}

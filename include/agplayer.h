#ifndef H_AGPLAYER
#define H_AGPLAYER

class AGPlayer {
  friend class AGController;
  private:
    int buyingChance[3];       // Chance of buying property, 0 < b < 100
    int buildingChance[3];     // Chance of building house/hotel
    int payingJailChance[3];   // Chance to pay to leave jail
    int mortgageChance[3];     // Chance to mortgage something
    int minimumBalance[3];     // Minimum balance the player withholds
    int tradingChance[3];      // Chance of trading cards with other players
    int minimumCards[3];       // Minimum title deeds player holds in hand

  protected:
    int id;
    int stage;

  public:
    AGPlayer(int);
    AGPlayer(const AGPlayer&);

    void setId(int);
    void setStage(int);
    void setBuyingChance(int);
    void setBuildingChance(int);
    void setPayingJailChance(int);
    void setMortgageChance(int);
    void setMinimumBalance(int);
    void setTradingChance(int);
    void setMinimumCards(int);

    int getId();
    int getBuyingChance();
    int getBuildingChance();
    int getPayingJailChance();
    int getMortgageChance();
    int getMinimumBalance();
    int getTradingChance();
    int getMinimumCards();
};

#endif

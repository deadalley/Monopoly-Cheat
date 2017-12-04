#ifndef H_AGPLAYER
#define H_AGPLAYER

class AGPlayer {
  friend class AGController;
  protected:
    int id;
    int buyingChance;       // Chance of buying property, 0 < b < 100
    int buildingChance;     // Chance of building house/hotel
    int payingJailChance;   // Chance to pay to leave jail
    int mortgageChance;     // Chance to mortgage something
    int minimumBalance;     // Minimum balance the player withholds
    int tradingChance;      // Chance of trading cards with other players
    int minimumCards;       // Minimum title deeds player holds in hand

  public:
    AGPlayer(int);
    AGPlayer(const AGPlayer&);

    void setId(int);
    void setBuyingChance(int);
    void setBuildingChance(int);
    void setPayingJailChance(int);
    void setMortgageChance(int);
    void setMinimumBalance(int);
    void setTradingChance(int);
    void setMinimumCards(int);

    int getId();
    int getTradingChance();
};

#endif

#ifndef _PLAYER_
#define _PLAYER_

#include <string>
#include <memory>
#include <vector>

#include "board.h"

class Square;

class Building;
class Academic;


class Player
{
    // fields
    //to represent whether in jail or not
    //to represent how many turns the player has been in the jail
    bool rolled;
    bool doubleRoll;

    std::string name;
    char token;
    unsigned int balance;
    unsigned int diceNum; // stores the number of the dice roll of both the dice
    std::shared_ptr<Square> landed;  // this is the square on which the player is present
    std::vector<std::string> buildingsOwned;

    unsigned int resNum;
    unsigned int gymNum;

    bool sentToTims;
    unsigned int numTims; // number of turns stuck in line
    unsigned int timCup; // number timCups they own
    
    bool bankrupt;
    int debt;
    Player* debtee;


public:
    Player(char, Board*);
    void setNumSentToTims(int);
    unsigned int getDiceNum();
    void settleLanded(std::shared_ptr<Square>);
    // Accessor, Mutator Methods
    unsigned int getRolled();
    void setRolled(bool);
    std::string getName();
    char getToken();

    unsigned int getBalance();
    void setBalance(int);

    void setTheCups(int);
    std::shared_ptr<Square> getLanded();
    void setLanded(int, Board*);

    unsigned int getResNum();
    void addResNum(int);

    unsigned int getGymNum();
    void addGymNum(int);

    unsigned int getNumSentToTims();
    void addNumSentToTims(int);
    bool getSentToTims();
    void setSentToTims(bool);
    unsigned int getTimsCup();
    void addTimsCup(int);

    //Command Methods

    int totalWorth(Board*);

    Square* rollDice(Board *, std::vector<Player*> & player, bool);
    bool getDoubleRoll();
    void setDoubleRoll(bool);

    bool checkTransaction(int, int);

    void bankTransfer(int); // transfer the amt out of player's balance to bank
    void transferFunds(int, Player&);// transfer the amt from the current player to the otherplayer
    
    // overlading the PlayerTrade fn to have flexibility for the 2nd and 3rd
    // arguments check for imporvements
    // here is how the player trade is going to take place it needs to make the
    // we will check whether the player has the property in main
    // you will only call this function once the player otherPlayer accepts it
    // need to make a funtion to make a make funtion that checks that the monopoly doesnt have any improvements
    void playerTrade(Player&, int, Building&, Board*);
    void playerTrade(Player&, Building&, Building&, Board*);
    void playerTrade(Player&, Building&, int, Board*);

    void playerBankrupt(); //not sure if we need it
    //void playerAuction(int);
    void mortgage(Building&);   // look at the specifications on the doc
    void unMortgage(Building&); // must pay 60% of the cost

    void improvements(Academic&, char, unsigned int);
    void displayAssets(Board*);

    void addBuildingOwned(std::string);
    std::vector<std::string> getBuildingOwned();

    bool getBankrupt();
    void setBankrupt(bool);

    int getDebt();
    Player* getDebtee();

    void setDebt(int);
    void setDebtee(Player*);
};

#endif




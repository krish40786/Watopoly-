#ifndef _BUILDING_
#define _BUILDING_
#include <iostream>
#include <vector>
#include <string>

#include "square.h"

//#include "player.h"
class Player;

class Building : public Square
{
    Player* owner;
    bool mortgaged;
    unsigned int purchaseCost;
    unsigned int improvementsNum;
    bool paid10;

public:
    Building(Player*, unsigned int, std::string, unsigned int, unsigned int, unsigned int);
    Player* getOwner();
    void setOwner(Player*);
    bool getMortgaged();
    void setMortgaged(bool);
    virtual unsigned int getImprovement(); 
    virtual void setImprovement(unsigned int);
    unsigned int getPurchaseCost();
    unsigned int buildingAuction(std::vector<Player*> &);
    bool improvementOnFaculty(Board*);
};

#endif

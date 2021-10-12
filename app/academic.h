#ifndef _ACADEMIC_
#define _ACADEMIC_
#include <string>
#include "building.h"
//class Building;


class Academic : public Building
{
    unsigned int tuition; // tuition
    std::string Faculty; // Monopoly Block
    unsigned int improvementCost; // how much improvement costs
    int improvements[6]; // array of improvement and tuition increases
    unsigned int purchasedCost; // cost to purchase
    unsigned int improvementsNum;

public:
    Academic(std::string, unsigned int, unsigned int, int[], unsigned int, std::string, unsigned int, unsigned int, unsigned int);
    unsigned int getImprovementCost();
    unsigned int getImprovement() override; 
    void setImprovement(unsigned int) override;
    unsigned int getTuition();
    std::string getFaculty();
};

#endif



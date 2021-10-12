#include "academic.h"
#include "building.h"

Academic::Academic(std::string Faculty, unsigned int purchasedCost, unsigned int improvementCost, int imp[6], unsigned int tuition, std::string block, unsigned int x, unsigned int y, unsigned int squareNum)
    : Building(nullptr, purchasedCost, block, x, y, squareNum), tuition{tuition}, Faculty{Faculty}, improvementCost{improvementCost}{
        for(int i = 0; i < 6; ++i){
            improvements[i] = imp[i];
        }
    }

unsigned int Academic::getImprovementCost(){
    return improvementCost;
}


unsigned int Academic::getImprovement(){
    return improvementsNum;
}

void Academic::setImprovement(unsigned int imp){
    improvementsNum = imp;
    tuition = improvements[improvementsNum];
}

unsigned int Academic::getTuition(){
    return tuition;
}

std::string Academic::getFaculty(){
    return Faculty;
}



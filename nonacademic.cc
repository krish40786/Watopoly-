#include "nonacademic.h"
#include <string>

NonAcademic::NonAcademic(int purchasedCost, std::string block, int x, int y, int squareNum) : Building(nullptr, purchasedCost, block, x, y, squareNum), payment{0}{}

int NonAcademic::calcPayment(int numProperty, int diceNum){
   if (this->getType() == 'G'){
       if (numProperty == 1){
           return diceNum * 4;
       }
       else{
           return diceNum * 10;
       }
   }
   else {
       return numProperty * 25;
   } 
}


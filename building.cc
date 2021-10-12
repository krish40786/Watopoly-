#include "building.h"
#include "player.h"
#include "academic.h"

#include <string>
#include <memory>

Building::Building(Player *owner, unsigned int purchaseCost, std::string block, unsigned int x, unsigned int y, unsigned int squareNum) : Square(x, y, block, squareNum), owner{owner}, mortgaged{false}, purchaseCost{purchaseCost}, improvementsNum{0}, paid10{false}{}

Player* Building::getOwner(){
    return this->owner;
}

void Building::setOwner(Player* player){
    this->owner = player;
}

bool Building::getMortgaged(){
    return mortgaged;
}

void Building::setMortgaged(bool val){
    mortgaged = val;
}

unsigned int Building::getPurchaseCost(){
    return purchaseCost;
}

unsigned int Building::getImprovement(){
    return improvementsNum;
}

void Building::setImprovement(unsigned int imp){
    improvementsNum = imp;
}

unsigned int Building::buildingAuction(std::vector<Player*> & player){
  std::cout << "The current player went bankrupt or choose not to buy the property. All active players are now included in the auction." << std::endl;
  char ans;
  unsigned int start_bid = this->getPurchaseCost()/2;
  unsigned int  best_bid, flag{1}, i{0}, num_withdraws{static_cast<unsigned int>(player.size())};
  unsigned int current_bid{start_bid}; int bid;

  while(num_withdraws){
    if(current_bid <= player.at(i)->getBalance()){
      std::cout << "Do you want to take part in the auction " + player.at(i)->getName() + "? (Y/N)" << std::endl;
      std::cin >> ans;
      if(ans == 'Y' || ans == 'y'){
          if(flag){
            std::cout << "The starting bid of the property is " << start_bid << std::endl;
            flag = 0;
            current_bid = current_bid + (this->getPurchaseCost()/10);
          } else {
              std::cout << "The current bid of the property is " << current_bid << std::endl;
          }
          std::cout << "Your minimum bid must be an positive integer and must be greater than " << current_bid << std::endl;
          while(true){
            std::cin >> bid;
            if(bid < 0 || bid <= current_bid || std::cin.fail()){
                std::cin.clear();
                std::cin.ignore();
                std::cerr << "You entered an invalid bid amount please make a bid that is greater than " << current_bid << std::endl;
            } else if(bid > player.at(i)->getBalance()){
                std::cerr << "You cannot raise the bid to " << bid << " as you do not own that much money. Please enter another bid amount to raise your bid to." << std::endl;
            } else {
                break;
            }
          }
          current_bid = bid;
          best_bid = i;
          num_withdraws = player.size() - 1; //this is set to zero because then the counter to end the loop is reset
        std::cout << "Thank you for your participation in the auction" << std::endl;
      } else if (ans == 'N' || ans == 'n'){
          std::cout << "You have decided not to be part of the auction, Thanks you for your time." << std::endl;
          num_withdraws--;
      }
      if(i == (player.size() - 1)){
        i = 0;
      } else {
          i++;
      }
    } else {
        std::cout << "Player " + player.at(i)->getName() + " will not be included in the action as they do not have sufficient funds to make a bid." << std::endl;
        num_withdraws--;
    }// end of if to check if the player has enough money
  }// end of while loop 
  if(flag == 1){
    std::cout << "Since no player participated in the bid the property remains unowned." << std::endl;
    return 0;
  } else {
      if(current_bid <= player.at(best_bid)->getBalance()){
        std::cout << "The winner of the auction is " + player.at(best_bid)->getName() << std::endl;
        player.at(best_bid)->setBalance(player.at(best_bid)->getBalance() - current_bid);
        this->setOwner(player.at(best_bid));
        this->getOwner()->addBuildingOwned(this->getBlock());
        std::cout << this->getOwner()->getName();
      } else {
          std::cout << "Since you do not have enough funds we give you the chance to increase your funds to pay you bid amount" << std::endl;
          player.at(best_bid)->playerBankrupt();
          int balance_remaining = current_bid - player.at(best_bid)->getBalance();
          player.at(best_bid)->setBalance(0);
          return balance_remaining;
          //the helping to improve the balance of the player we do that in the main
      }
  }

  return 0; //update to return remaining balance
}


bool Building::improvementOnFaculty(Board* board){
  bool noImps{false};
  if(this->getImprovement()){
    return true;
  }
  for(int i = 0; i < 40; ++i){
    if(board->getSquarePtr(i)->getType() == 'A'){
      auto buildingPtr = std::static_pointer_cast<Building>(board->getSquarePtr(i));
      auto academicPtr = std::static_pointer_cast<Academic>(buildingPtr);
      //auto buildingPtr = std::static_pointer_cast<Academic>(this);
      auto propertyPtr = std::static_pointer_cast<Academic>(std::shared_ptr<Square>(this));
      //if(academicPtr->getFaculty() == propertyPtr->getFaculty()){
        //if(academicPtr->getImprovement() != 0) {noImps = true; break;}
     // }
    }
  }
  return noImps;
}




#include "square.h"
#include "player.h"
#include "building.h"
#include "academic.h"
#include "nonacademic.h"
#include "nonproperty.h"

#include <string>
#include <iostream>
#include <memory>

Square::Square(int x, int y, std::string block, int squareNum) : block{block}, x{x}, y{y}, squareNum{squareNum} {
    std::vector<char> tk;
    std::vector<char> typeBoard = {
        'N','A','N','A', 'N','R','A','N','A','A','N', // 1-11
        'A','G','A','A','R','A','N','A','A','N', //12-21
        'A','N','A','A','R','A','A','G','A','N', // 22-31
        'A','A','N','A','R','N','A','N','A' //32-40 
    };
  type = typeBoard[squareNum-1];
}

int Square::getX()
{
    return x;
}

int Square::getY()
{
    return y;
}

std::string Square::getBlock(){
    return block;
}

int Square::getSquareNum(){
    return squareNum;
}

char Square::getType(){
    return type;
}

Square* Square::runAction(Player* currPlayer, Board * gameBoard, std::vector<Player*> & players){
// Do the square action
    int balance = currPlayer->getBalance();
    
    Square* auctionSquare = nullptr; 
    char yesNo;

    if (type != 'N'){ // if it's a Building
        auto buildingPtr = static_cast<Building*>(this);

        if (!buildingPtr){
            throw std::invalid_argument("Static pointer cast from Square to Building unsuccessful.");
        }
    
        int purchaseCost = buildingPtr->getPurchaseCost();

        if (!buildingPtr->getOwner()){ //if no owner
            std::cout << "This property is currently unowned. Your balance is: " << balance << std::endl
            << "The cost of the property is: " << purchaseCost << std::endl;
            if (currPlayer->checkTransaction(purchaseCost, balance)){
            std::cout << "You can afford property " << block << "! Do you want to purchase it? (Y/N)" << std::endl;
            
            while(true){
                std::cin >> yesNo;
                if (yesNo == 'Y'){
                    if (type == 'R'){
                        currPlayer->addResNum(1);
                    }
                    else if (type== 'G'){
                        currPlayer->addGymNum(1);
                    }
                    currPlayer->bankTransfer(purchaseCost); //pay for it
                    buildingPtr->setOwner(currPlayer); //make them the owner
                    currPlayer->addBuildingOwned(block);
                    std::cout << "Success! You just bought " << block << " for " << purchaseCost << ". Type the 'all' command to verify the transaction." << std::endl;
                    break;
                }
                else if(yesNo == 'N'){
                    buildingPtr->buildingAuction(players);
                    break;
                }
                else{
                    std::cerr << "Please input 'Y' for yes or 'N' for no." << std::endl;
                }
            }//while loop
            }// can afford
            else{
                std::cout << "You can't afford this property. So to protect you from being stupid and going bankrupt, we will not allow this transaction." << std::endl
                << "Instead, try to trade with other players or win this upcoming auction for this property." << std::endl;
                auctionSquare = this;
                buildingPtr->buildingAuction(players);
            } // can't afford
        }// no owner

        else{ // if owner
            if (buildingPtr->getMortgaged()){
            std::cout << "Lucky you, this property is owned but mortgaged. No payment due to the owner. You may proceed with your turn and enter next when ready." << std::endl;
            } //mortgaged

            else {
                std::cout << "Unfortunately, property " << block << " is already owned by " << buildingPtr->getOwner()->getName() << "." << std::endl;
                std::cout << "You must pay the owed amount of: ";
                int owedAmount;
                if (currPlayer->getLanded()->getType() == 'A'){
                    auto academicPtr = static_cast<Academic*>(buildingPtr);
                    owedAmount = academicPtr->getTuition();
                }//academic
                
                else{
                    auto nonAcademicPtr = static_cast<NonAcademic*>(buildingPtr);
                    if (currPlayer->getLanded()->getType() == 'R'){
                    int resNum = buildingPtr->getOwner()->getResNum();
                    owedAmount = nonAcademicPtr->calcPayment(resNum, 0);
                    }
                    else {
                    int numGym = buildingPtr->getOwner()->getGymNum();
                    owedAmount = nonAcademicPtr->calcPayment(numGym, currPlayer->getDiceNum());
                    }
                }//non academic
                std::cout << owedAmount << " to " << buildingPtr->getOwner()->getName() << "."<< std::endl;
                std::cout << "Processing your transaction..." << std::endl;

                if (currPlayer->checkTransaction(owedAmount, currPlayer->getBalance())){
                    currPlayer->transferFunds(owedAmount, *buildingPtr->getOwner());
                    std::cout << "Success! Your payment to " <<  buildingPtr->getOwner()->getName() << " was transferred. Type the 'all' command to verify the transaction." << std::endl;
                }
                else {
                    currPlayer->setDebtee(buildingPtr->getOwner());
                    currPlayer->setDebt(owedAmount - currPlayer->getBalance());
                    currPlayer->transferFunds(balance, *buildingPtr->getOwner());
                    currPlayer->setBankrupt(true);
                    std::cout << "Uh oh! You have insufficient funds to pay. " <<  buildingPtr->getOwner()->getName() << std::endl
                    << "We have paid all of your available balance and you are now in debt. You owe " << buildingPtr->getOwner()->getName() << "$" << std::endl;
                    std::cout << "You cannot continue in this game (you cannot execute the 'next' command) until you pay the debt you owe. You can try and accumulate the owed amount by trading with other players, mortgaging properties, or selling your improvements. Good luck." << std::endl;                
                }
            }//not mortgaged
        }//if owner
    }//if not non-property
    else{
        auto nonPropertyPtr = static_cast<NonProperty*>(this);
        //run the non-property function that does the action;
        nonPropertyPtr->action(currPlayer, gameBoard, players);
    } 
    return auctionSquare;   
}





#include "player.h"

//#include "board.h"

#include "square.h"
#include "building.h"
#include "academic.h"
#include "nonacademic.h"

#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <random>

Player::Player(char token, Board* gameBoard): rolled{false}, doubleRoll{false}, token{token}, balance{1000}, landed{nullptr}, timCup{0}, bankrupt{false}, sentToTims{false}{
  std::map<char, std::string> tkMap;
  tkMap['G'] = "Goose";
  tkMap['B'] = "GRT Bus";
  tkMap['D'] = "Tim Hortons Doughnut";
  tkMap['P'] = "Professor";
  tkMap['S'] = "Student";
  tkMap['$'] = "Money";
  tkMap['L'] = "Laptop";
  tkMap['T'] = "Pink tie";

  name = tkMap[token];
  diceNum = 0;
  //landed = nullptr;
  landed = gameBoard->squares.at(0); //set player to land on first square
  debt = 0;
  debtee = nullptr;
}

unsigned int Player::getRolled(){
  return rolled;
}

void Player::setRolled(bool val){
  rolled = val;
}

std::string Player::getName(){
  return name;
}

char Player::getToken(){
  return token;
}

unsigned int Player::getBalance(){
  return balance;
}

void Player::setBalance(int amt){
  balance = amt;
}

unsigned int Player::getDiceNum(){
  return diceNum;
}

bool Player::getDoubleRoll(){
  return doubleRoll;
}

void Player::setDoubleRoll(bool val){
  doubleRoll = val;
}

std::shared_ptr<Square> Player::getLanded(){
  return landed;
}

void Player::setLanded(int num, Board* gameBoard){
  if(num >= 40){
    num = num - 40;
  }

  std::string t{this->token};
  landed->tk.erase(std::find(landed->tk.begin(), landed->tk.end(), t));
  landed = gameBoard->squares[num - 1];

  std::cout << "You landed on " << landed->getBlock() << std::endl;
  
  landed->tk.emplace_back(t);
}

void Player::settleLanded(std::shared_ptr<Square> s){
  landed = s;
}

unsigned int Player::getResNum(){
  return resNum;
}

void Player::addResNum(int delta){
  resNum += delta;
}

unsigned int Player::getGymNum(){
  return gymNum;
}

void Player::setTheCups(int cups){
  this->timCup = cups;
}

void Player::addGymNum(int delta){
  gymNum += delta;
}

void Player::setNumSentToTims(int val){
  numTims = val;
}

unsigned int Player::getNumSentToTims(){
  return numTims;
}

void Player::addNumSentToTims(int val){
  numTims += val;
}

bool Player::getSentToTims(){
  return sentToTims;
}

void Player::setSentToTims(bool val){
  sentToTims = val;
}

unsigned int Player::getTimsCup(){
  return timCup;
}

void Player::addTimsCup(int val){
  timCup += val;
}

int Player::totalWorth(Board * board){
  unsigned int total{this->getBalance()};
  for(int i = 0; i < 40; ++i){
      std::vector<std::string>::iterator it = std::find(buildingsOwned.begin(), buildingsOwned.end(), board->getSquarePtr(i)->getBlock());
      if(it != buildingsOwned.end()){
        auto buildingPtr = std::static_pointer_cast<Building>(board->getSquarePtr(i));
        if(buildingPtr->getMortgaged()){
          total +=(buildingPtr->getPurchaseCost()/2);
        } else {
          total += buildingPtr->getPurchaseCost();
        }
        if(buildingPtr->getImprovement() != 0){
          auto academicPtr = std::static_pointer_cast<Academic>(buildingPtr);
          total += academicPtr->getImprovementCost() * buildingPtr->getImprovement();
        }
      }
  }
  return total;
}

Square* Player::rollDice(Board* gameBoard, std::vector<Player*> & player, bool test = false){
  //roll the dice
  Square* auctionSquare;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(1,6);

  int diceNum1 = distribution(gen);
  int diceNum2 = distribution(gen);

  if(test){
    std::cin >> diceNum1;
    std::cin >> diceNum2;
  }
  if (diceNum1 == diceNum2){
    doubleRoll = true;
  }
  diceNum = diceNum1 + diceNum2;
  
  //display roll
  std::cout << "You rolled: " << diceNum << std::endl;

  rolled = true;

  if (sentToTims){
    std::cout << "You are currently stuck in the DC Tims Line. To get out, let's hope you roll doubles!" << std::endl;
    if (doubleRoll){
      std::cout << "Yay, you rolled doubles! Congrats, you are free to move as originally planned" << std::endl;
      sentToTims = false;
    }
    else{
      char option;

      std::cout << "Unfortunately, you didn't roll doubles so you continue to be stuck in the DC Tims Line. You have 3 options: " << std::endl
      << "1) Pay $50 to get out immediately \t 2) Use a Roll Up the Rim Cup \t 3) Wait until your next turn to move and try and roll doubles again." << std::endl
      << "Please enter the number corresponding to the appropriate action to confirm your choice." << std::endl;

      while (true)
      {
        std::cin >> option;
        if (option == '1'){
          bankTransfer(50);
          sentToTims = false;
          numTims = 0;
          break;
        }
        else if (option == '2'){
          if (timCup >= 1) {
            timCup -= 1;
            sentToTims = false;
            numTims = 0;
            gameBoard->setTimsCups(gameBoard->getTimsCups() - 1);
            break;
          }
          else {
            std::cerr << "You don't have a Tims Cup :( Enter another option." << std::endl;
          }
        }
        else if (option == '3'){
          if (numTims == 3){
            std::cerr << "Unfortunately, according to our records, you have been stuck in the DC Tims Line for 3 consecutive turns now and Tims is closing." << std::endl
            << "You must choose either option 1 or option 2 at this point in time." << std::endl;
          }
          else {
            numTims += 1;
            return nullptr;
          }
        }
        else {
          std::cerr << "Please input 'Y' for yes or 'N' for no." << std::endl;
        }
        std::cin.ignore();
        std::cin.clear();
      }
    }
  }

  if (!sentToTims){
    //move the Player
    unsigned int currSquare = landed->getSquareNum();
    unsigned int squareNum = currSquare + diceNum;

    //check if exceeds 40;
    if(squareNum >= 41){
      squareNum = squareNum - 40;
      if (squareNum >= 42){
        balance += 200; // we've passed GO in this case.
        std::cout << "You passed the 'Collect OSAP' square! +$200 in your balance! Use command 'assets' to verify you've received your OSAP payment." << std::endl;
      }
    }
    std::string t{this->token};
    landed->tk.erase(std::find(landed->tk.begin(), landed->tk.end(), t));
    landed = gameBoard->squares[squareNum - 1];

    std::cout << "You landed on " << landed->getBlock() << std::endl;
    
    landed->tk.emplace_back(t);
  }
  auctionSquare = getLanded()->runAction(this, gameBoard, player);
  gameBoard->updateBoard();
  gameBoard->displayBoard();
  return auctionSquare;
}

bool Player::checkTransaction(int amt, int balance){
  if(amt < balance){
    return true;
  } else {
    return false;
  }
}

void Player::bankTransfer(int amt){
  if(checkTransaction(amt, balance)){
    balance -= amt;
    std::cout << "Success! You have successfully paid " << amt << " to the school :) Have a great turm (get it, pun on turn and term?... Nvm.)" << std::endl;
  } else {
    bankrupt = true;
    debt = amt - balance;
    balance = 0;
    std::cout << "Uh oh. You can't afford to pay " << amt <<  " to the school. You are now in debt and your balance is $0. You owe the school " << debt << "." << std::endl
    << "To contine in Monopoly you must pay the remaining balance to the school (can't use command 'next' until you do)." << std::endl;
  }
}

void Player::transferFunds(int amt, Player & otherPlayer){ // transfer from currPlayer to otherPlayer (you can also do vice versa with negative amt)
  if(amt < 0 && checkTransaction(-amt, otherPlayer.balance)){
    otherPlayer.balance += amt;
    this->balance += -amt;
  } else if ( checkTransaction(amt, this->balance)){
    otherPlayer.balance += amt;
    this->balance -= amt;
  }
  else {
    std::cerr << "Insufficient funds to transfer." << otherPlayer.getName() << std::endl;
  }
}

// check if they transfer gym or res and update resNum and gymNum
void Player::playerTrade(Player& player, int amt, Building& property, Board* board){
  std::vector<std::string>::iterator it = std::find(player.buildingsOwned.begin(), player.buildingsOwned.end(), property.getBlock());
  if(it != player.buildingsOwned.end()){
    if(this->balance < amt){
      std::cerr << "Cannot buy the property for the amount requested" << std::endl;
    } else {
      if(!property.improvementOnFaculty(board)){
       property.setOwner(this);
       player.buildingsOwned.erase(it);
       this->buildingsOwned.emplace_back(property.getBlock());
       //taking money from the current player and giving it to player 
       this->balance -= amt;
       player.balance += amt;
       if (property.getType() == 'R'){
          player.addResNum(-1);
          this->addResNum(1);
       }
       else if (property.getType() == 'G'){
          player.addGymNum(-1);
          this->addGymNum(1);
       }
       if (property.getMortgaged()){
          std::cout << name << ", you received property that is mortgaged. Thus, you are required to pay 10% of the original property's price. When unmortgaging in future, you will only need to pay the remaining 50% instead of the 60%." << std::endl;
          if (this->checkTransaction(0.1*property.getPurchaseCost(), balance)){
            this->bankTransfer(0.1*property.getPurchaseCost());
          }
          else{
            this->setDebt(balance - 0.1 * property.getPurchaseCost());
            balance = 0;
            bankrupt = true;
            std::cout << "Uh oh, you can't afford to pay the 10% of the purchase cost ($" << 0.1 * property.getPurchaseCost() << "). You are now in debt and need to sell improvements, trade or mortgage other properties before you can continue with the game." << std::endl;
          }
        }
      } else {
        std::cerr << "You cannot request this property as it has improvements" << std::endl;
      }
    }
  } else {
    std::cerr<< "This property doesn't belong to you " << player.getName();
  }
}

// check if they transfer gym or res and update resNum and gymNum
//this is the overloaded playertrade that take care of the second option
void Player::playerTrade(Player& player, Building& giveProperty, Building& getProperty, Board* board){
  std::vector<std::string>::iterator it = std::find(player.buildingsOwned.begin(), player.buildingsOwned.end(), getProperty.getBlock());
  if(it != player.buildingsOwned.end()){
      std::vector<std::string>::iterator it1 = std::find(buildingsOwned.begin(), buildingsOwned.end(), giveProperty.getBlock());
      if(it1 != this->buildingsOwned.end()){
        if(!giveProperty.improvementOnFaculty(board) && !getProperty.improvementOnFaculty(board)){
        //giving the player the property
          if (giveProperty.getMortgaged()){
            std::cout << player.getName() << ", you received property that is mortgaged. Thus, you are required to pay 10% of the original property's price. When unmortgaging in future, you will only need to pay the remaining 50% instead of the 60%." << std::endl;
            if (player.checkTransaction(0.1*giveProperty.getPurchaseCost(), player.getBalance())){
              player.bankTransfer(0.1 * giveProperty.getPurchaseCost());
            }
            else{
              player.setDebt(player.balance - 0.1 * giveProperty.getPurchaseCost());
              player.balance = 0;
              player.bankrupt = true;
              std::cout << "Uh oh, you can't afford to pay 10% of the purchase cost ($" << 0.1 * giveProperty.getPurchaseCost() << "). You are now in debt and need to sell improvements, trade or mortgage other properties on your next turn before you can continue with the game." << std::endl;
            }
          }
          giveProperty.setOwner(getProperty.getOwner()) ;
          player.buildingsOwned.emplace_back(giveProperty.getBlock());
          player.buildingsOwned.erase(it);
          if (giveProperty.getType() == 'R'){
            this->addResNum(-1);
            player.addResNum(1);
          }
          else if (giveProperty.getType() == 'G'){
            this->addGymNum(-1);
            player.addGymNum(1);
          }

          if (getProperty.getMortgaged()){
            std::cout << name << ", you received property that is mortgaged. Thus, you are required to pay 10% of the original property's price. When unmortgaging in future, you will only need to pay the remaining 50% instead of the 60%." << std::endl;
            if (this->checkTransaction(0.1*getProperty.getPurchaseCost(), balance)){
              this->bankTransfer(0.1 * getProperty.getPurchaseCost());
            }
            else{
              debt = balance - 0.1 * getProperty.getPurchaseCost();
              balance = 0;
              bankrupt = true;
              std::cout << "Uh oh, you can't afford to pay the 10% of the purchase cost ($" << 0.1 * getProperty.getPurchaseCost() << "). You are now in debt and need to sell improvements, trade or mortgage other properties before you can continue with the game." << std::endl;
            }
          }

          //give the property to player who initiated the trade
          getProperty.setOwner(this);
          this->buildingsOwned.emplace_back(getProperty.getBlock());
          this->buildingsOwned.erase(it1);
          if (getProperty.getType() == 'R'){
            this->addResNum(1);
            player.addResNum(-1);
          }
          else if (getProperty.getType() == 'G'){
            this->addGymNum(1);
            player.addGymNum(-1);
          }
        }

        else{
          std::cerr << "either or both of the properties associated with the monopoly have improvements." << std::endl;
        }
      }
      else {
        std::cerr << "Invalid trade request as you do not own the property you are giving up" << std::endl;
      }
  } 
  else {
    std::cerr << "Invalid trade request as" + player.getName() + "doesn't own the property that you requested" << std::endl;
  }
}

// check if they transfer gym or res and update resNum and gymNum
void Player::playerTrade(Player& player, Building& property, int amt, Board* board){
  std::vector<std::string>::iterator it = std::find(this->buildingsOwned.begin(), this->buildingsOwned.end(), property.getBlock());
  if(it != buildingsOwned.end()){
    if(player.balance < amt){
      std::cerr << "Player " + player.name + " doesn't have the sufficient funds to buy the property from you" << std::endl;
    } else {
      if(!property.improvementOnFaculty(board)){
      player.balance -= amt;
      if (player.balance <= 0){
        player.balance == 0;
        player.bankrupt = true;
        std::cerr << "Unfortunately " << player.name << ", you have accepted a trade which you can't afford to pay. As such, you are now in debt and will be forced to either pay off your debt or declare bankruptcy on your next turn." << std::endl;
      }
      if (property.getMortgaged()){
        std::cout << player.getName() << ", you received property that is mortgaged. Thus, you are required to pay 10% of the original property's price. When unmortgaging in future, you will only need to pay the remaining 50% instead of the 60%." << std::endl;
        if (player.checkTransaction(0.1*property.getPurchaseCost(), player.getBalance())){
          player.bankTransfer(0.1 * property.getPurchaseCost());
        }
        else{
          player.setDebt(player.balance - 0.1 * property.getPurchaseCost());
          player.balance = 0;
          player.bankrupt = true;
          std::cout << "Uh oh, you can't afford to pay 10% of the purchase cost ($" << 0.1 * property.getPurchaseCost() << "). You are now in debt and need to sell improvements, trade or mortgage other properties on your next turn before you can continue with the game." << std::endl;
        }
      }
      player.buildingsOwned.emplace_back(property.getBlock());
      property.setOwner(&player);
      this->buildingsOwned.erase(it);
      if (property.getType() == 'R'){
          this->addResNum(-1);
       }
       else if (property.getType() == 'G'){
          this->addGymNum(-1);
       }
      } else {
        std::cerr << "The monopoly of the property contains improvements." << std::endl;
      }
    }
  } else {
    std::cerr << "Invalid trade request as you do not own the property you are about to give up";
  }
}

void Player::playerBankrupt(){
  // call auction
  delete this;
}


void Player::mortgage(Building& property){

  //check if player owns the property
  std::vector<std::string>::iterator it = std::find(this->buildingsOwned.begin(), this->buildingsOwned.end(), property.getBlock());
  if(it != this->buildingsOwned.end()){
    if (property.getImprovement() >= 1){
      std::cout << "It looks like this property has "<< property.getImprovement() << " improvements. In order to mortgage the property, you must first sell all your improvements. Do you want to proceed? (Y/N)" << std::endl;
      std::string yesNo;
      while (true){
        std::cin >> yesNo;
        if (yesNo == "Y"){
          break;
        }
        else if (yesNo == "N"){
          return;
        }
        else{
          std::cerr << "Please input 'Y' for yes or 'N' for no." << std::endl;
        }
        std::cin.ignore();
        std::cin.clear();
      }
      Academic academic = static_cast<Academic&>(property);
      improvements(academic, 'S', property.getImprovement());
    }
    if (property.getImprovement() == 0){
      if (bankrupt){
        std::string owee;
        if (!debtee) {
          owee = "the school";
        }
        else{
          owee = debtee->getName();
        }
        std::cout << "According to our records, you owe $" << debt << " to " << owee << "." << std::endl;
        std::cout << "Your proceeds will go to " << owee << " until your debt is repaid. Any remaining amount from this sale will go into your bank account." << std::endl;
        if (debt >= property.getPurchaseCost() / 2){
          if (debtee){
            debtee->balance += property.getPurchaseCost() / 2;
          }
          debt -= property.getPurchaseCost() / 2;
        }
        else{
          balance += property.getPurchaseCost() / 2;
          balance -= debt;
          debt = 0;
        }
        if (debt == 0){
          std::cout << "Congratulations! You are now out of debt and may continue playing (commands 'roll' and 'next' have been unlocked)." << std::endl <<
          "Your balance is $" << balance << "." << std::endl;
          bankrupt = false;
        }
      }
      else {
        property.setMortgaged(true);
        balance += property.getPurchaseCost() / 2;
      }
    std::cout << "Success! You have successfully mortgaged " << property.getBlock() << std::endl;
    } //no improvements
  } // own building
  else {
    std::cerr << "You cannot mortgage this property as you do not own it" << std::endl;
  } // don't own
}

void Player::unMortgage(Building& property){
  std::vector<std::string>::iterator it = std::find(this->buildingsOwned.begin(), this->buildingsOwned.end(), property.getBlock());
  if(it != this->buildingsOwned.end()){
    if(checkTransaction(((property.getPurchaseCost()*6)/10), this->getBalance())){
      this->setBalance(this->getBalance() - ((property.getPurchaseCost()*6)/10));
      property.setMortgaged(false);
    } else {
      std::cerr << "You do not have sufficient funds to unmortgage the property requested" << std::endl;
    }
  } else {
    std::cerr << "You do not own this property hence you cannot mortgage this property" << std::endl;
  }
}

void Player::improvements(Academic& block, char buySell, unsigned int numSell){
  // add ability to sell improvements; add buySell char argument to this
  //we make sure that the academic building is academic in the main
  std::vector<std::string>::iterator it = std::find(buildingsOwned.begin(), buildingsOwned.end(), block.getBlock());
  if(it == buildingsOwned.end()){
    std::cerr << "You cannot make improvements as you do not own the building" << std::endl;
    return;
  }

  if (buySell == 'B'){
    if (balance < block.getImprovementCost()){
      std::cerr << "You cannot make an improvement on this property as you have insufficient funds." << std::endl;
      return;
    }
    else if(block.getImprovement() == 5){
      std::cerr << "Cannot make any new improvements to this property." << std::endl;
      return;
    } 
    else {
      this->balance -= block.getImprovementCost();
      block.setImprovement(block.getImprovement() + 1);// adding one to the improvements
      std::cout << "Congratulations! You have just bought a new improvement for " << block.getBlock() << ". It now has " << block.getImprovement() << " improvements."<< std::endl;
    }
  } 

  else{
    for (unsigned int i = 0; i < numSell; ++i){
      if(block.getImprovement() == 0){
        std::cerr << "Cannot sell any improvements as this property has none." << std::endl;
        return;
      } 
      if (bankrupt){
        std::string owee;
        if (!debtee) {
          owee = "the school";
        }
        else{
          owee = debtee->getName();
        }
        std::cout << "According to our records, you owe $" << debt << " to " << owee << "." << std::endl;
        std::cout << "All your improvements will go to " << owee << " until your debt is repaid. Any remaining amount from this sale will go into your bank account." << std::endl;
        if (debt >= block.getImprovementCost()){
          if (debtee){
            debtee->balance += block.getImprovementCost() / 2;
          }

          debt -= block.getImprovementCost() / 2;
          block.setImprovement(block.getImprovement() - 1);// remove one to the improvements
          
          if (debt != 0){
            std::cout << "You still owe: $" << debt << std::endl;
          }
        }
        else {
            balance += block.getImprovementCost() / 2;
            balance -= debt;
            debt = 0;
            if (debtee){
              debtee->balance += debt;
            }
            std::cout << "Congratulations! You are now out of debt and may continue playing (commands 'roll' and 'next' have been unlocked)." << std::endl <<
            "Your balance is $" << balance << "." << std::endl;
            bankrupt = false;
        }
      }
      if (!bankrupt){
        balance += block.getImprovementCost() / 2;
        block.setImprovement(block.getImprovement() - 1);// remove one to the improvements
      }
    }
    std::cout << "Congratulations! You have just sold " << numSell << " improvements!" << std::endl;
  }
}

std::vector<std::string> Player::getBuildingOwned(){
  return buildingsOwned;
}

void Player::addBuildingOwned(std::string block){
  buildingsOwned.emplace_back(block);
}

bool Player::getBankrupt(){
  return bankrupt;
}

void Player::setBankrupt(bool val){
  bankrupt = val;
}

int Player::getDebt(){
  return debt;
}

Player* Player::getDebtee(){
  return debtee;
}

void Player::setDebt(int val){
  debt = val;
}

void Player::setDebtee(Player* val){
  debtee = val;
}

void Player::displayAssets(Board* board){
  std::cout << "These are all the assets of the player " << this->getName() << std::endl;
  std::cout << "This is the list of buildings and their respective improvements with their monatary values:" << std::endl;
  for(int i = 0, y = 0; i < 40; ++i){
      std::vector<std::string>::iterator it = std::find(buildingsOwned.begin(), buildingsOwned.end(), board->getSquarePtr(i)->getBlock());
      if(it != buildingsOwned.end()){
        auto buildingPtr = std::static_pointer_cast<Building>(board->getSquarePtr(i));
        if(buildingPtr->getMortgaged()){
          if(buildingPtr->getType() == 'G' || buildingPtr->getType() == 'R'){
            std::cout << "The property " + buildingsOwned.at(y) + " is mortgaged, and has value of " << (buildingPtr->getPurchaseCost()/2) << std::endl;
          } else {
            std::cout << "The property " + buildingsOwned.at(y) + " is mortgaged, and has value of " << (buildingPtr->getPurchaseCost()/2) << " and has 0 improvements." << std::endl;
          }
        } else {
          if(buildingPtr->getType() == 'G' || buildingPtr->getType() == 'R'){
            std::cout << "The property " + buildingsOwned.at(y) + " is owned by " + this->getName() + " and has a monetary value of " << buildingPtr->getPurchaseCost() << std::endl;
          } else {
            std::cout << "The property " + buildingsOwned.at(y) + " is owned by " + this->getName() + " and has a monetary value of " << buildingPtr->getPurchaseCost() << " and has " << buildingPtr->getImprovement() << " improvements." << std::endl;
          }
        }
        //if(buildingPtr->getImprovement() != 0){
          //auto academicPtr = std::static_pointer_cast<Academic>(buildingPtr);
          //total += academicPtr->getImprovementCost() * buildingPtr->getImprovement();
        //}
        ++y;
      }
  }
  std::cout << "Your balance is: " << this->getBalance() << std::endl;
  std::cout << "You own " << this->getTimsCup() << " tim cups." << std::endl;
}



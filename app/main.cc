#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <exception>
#include <algorithm>
#include <sstream>

#include "board.h"
#include "player.h"
#include "building.h"
#include "academic.h"
#include "nonacademic.h"
#include "input.h"

const int MAX_NUM_PLAYERS = 8;

int main(int argc, char *argv[] /*TO DO: arg -load, -test*/)
{
  std::string commandName;
  char command;

  std::map<std::string, char> cmdMap; // create a map string to chars that we can use
  cmdMap["roll"] = 'A';
  cmdMap["next"] = 'B';
  cmdMap["trade"] = 'C';
  cmdMap["improve"] = 'D';
  cmdMap["mortgage"] = 'E';
  cmdMap["unmortgage"] = 'F';
  cmdMap["bankrupt"] = 'G';
  cmdMap["assets"] = 'H';
  cmdMap["all"] = 'I';
  cmdMap["save"] = 'J';
  cmdMap["q"] = 'K';
  cmdMap["help"]  = 'L';

  std::string name, give, receive, property, buySell, filename, yesNo, input;
  std::vector<std::string> token_name = {"Goose", "GRT Bus", "Tim Hortons Doughnut", "Professor", "Student", "Money", "Laptop", "Pink tie"};
  char token;
  int playNum = 0;
  unsigned int it = 0;
  bool skip = false;
  bool newGame = false;
  bool test = false;

  std::vector<Player*>players;

  Board* activeBoard= new Board;
  Square* auctionSquare = nullptr;
  
  //std::cout << activeBoard->gameBoard.size();

  std::string arg1 = (argc >= 2)? argv[1] : "";
  std::string arg2 = (argc >=3)? argv[2]: "";
  
  if (arg1 == "-load"){
    /*if (arg2 == ""){
      std::cerr << "No load file provided" << std::endl;
      exit;
    } else {
      std::ifstream infile{arg2};
      if(!infile.good()){
        std::cerr << "Give a valid file as the file given is either non-existant or cannot be read from";
        exit ;
      } else {

      }
    }*/

    std::string ip;
    std::ifstream infile(arg2);
    if(infile.fail()){
      std::cerr << "Give a vaild file as the file given is either non-existant or cannot be read from." << std::endl;
      exit(1);
    } else {
      int size;
      infile >> ip;

          if(checkIfNum(ip)){
            size = stoi(ip);
          }
        getline(infile, ip);
      for(int y = 0; y < size; y++){// this is to enter the player details
        getline(infile, ip);
        std::istringstream ss{ip};
        //ss >> ip; //this is to get the name of the player
        //std::vector<std::string>::iterator it = std::find(token_name.begin(), token_name.end(), ip);
        //if(it != token_name.end()){
          //std::cout  << ip << std::endl;
          ss >> ip;
          if(ip == "GRT"){
            ss >> ip;
          } else if(ip == "Tim"){
            ss >> ip;
            ss >> ip;
          } else if(ip == "Pink"){
            ss >> ip;
          }
          ss >> ip;
          players.emplace_back(new Player(ip[0], activeBoard));
          ss >> ip;
           players.at(players.size() - 1)->setTheCups(stoi(ip, nullptr, 10));
          ss >> ip;
          if(checkIfNum(ip)) players.at(players.size() - 1)->setBalance(stoi(ip));
          ss >> ip;
          if(checkIfNum(ip)) players.at(players.size() - 1)->settleLanded(activeBoard->getSquarePtr(stoi(ip) - 1));
          std::string tkt{players.at(players.size() - 1)->getToken()};
          activeBoard->getSquarePtr(stoi(ip) - 1)->tk.emplace_back(tkt);
          if(ss >> ip){
            if(checkIfNum(ip)) players.at(players.size() - 1)->setSentToTims(stoi(ip));
          }
          if(ss >> ip){
            if(checkIfNum(ip)) players.at(players.size() - 1)->setNumSentToTims(stoi(ip));

          }
        //for(int i = 0; (ss >> ip) && (ip != "") ; i++){
          /*while(ss >> ip){
            
          std::cout << ip << players.size() << i  << std::endl;
          if( i == 0){
            std::cout << " it reached this if" << std::endl;
            players.emplace_back(new Player(ip[0], activeBoard));
          } else if(checkIfNum(ip) && (i == 1)){
            if(ip != "0"){
            players.at(players.size() - 1)->setTheCups(stoi(ip));
            }
          } else if(i == 2){
            if(checkIfNum(ip)) players.at(players.size() - 1)->setBalance(stoi(ip));
          } else if(i == 3){
            if(checkIfNum(ip)) players.at(players.size() - 1)->settleLanded(activeBoard->getSquarePtr(stoi(ip)));
          } else if(i == 4){
            if(checkIfNum(ip)) players.at(players.size() - 1)->setSentToTims(stoi(ip));
          } else if(i == 5){
            if(checkIfNum(ip)) players.at(players.size() - 1)->setNumSentToTims(stoi(ip));
          }
          i++;
          std::cout << i << std::endl;
        } *///}
      //} else {
        //std::cerr << "the load file contained an illegal player name" << std::endl;
        //exit(1);
    }

    for(int i = 0; i < 40 ; ++i){// this is to input the property information
      
      //for(int y = 0; ss >> ip; ++y){
        //activeBoard->
        if(activeBoard->getSquarePtr(i)->getType() != 'N'){
          getline(infile, ip);
          std::istringstream ss{ip};
          ss >> ip;
          ss >> ip;
          if(ip != "BANK"){
            if(ip == "GRT"){
            ss >> ip;
            ip = "GRT Bus";
          } else if(ip == "Tim"){
            ss >> ip;
            ss >> ip;
            ip = "Tim Hortons Doughnut";
          } else if(ip == "Pink"){
            ss >> ip;
            ip = "Pink Tie";
          }
            for(auto z : players ){
              if(z->getName() == ip){
                auto buildingPtr = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(i));
                buildingPtr->setOwner(z);
                z->addBuildingOwned(activeBoard->getSquarePtr(i)->getBlock());
                
                if(activeBoard->getSquarePtr(i)->getType() == 'R'){
                  z->addResNum(1);
                } 
                if(activeBoard->getSquarePtr(i)->getType() == 'G'){
                  z->addGymNum(1);
                }
                break;
              }
            }
          }
            ss >> ip;
            auto buildingPtr = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(i));
            if(buildingPtr->getOwner()){
              buildingPtr->setImprovement(stoi(ip));
            } else {
              buildingPtr->setImprovement(0);
            }
            //std::cout << buildingPtr->getImprovement() << std::endl;
            //}
            //std::cout << buildingPtr->getImprovement() << std::endl;
          if(ss >> ip){
          if(ip == "-1"){
            auto buildingPtr = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(i));
            buildingPtr->setMortgaged(true);
          }
          }
        }
      //}
    }
  } 
  }

  else if (arg1 == "-testing"){
    test = true;
    newGame = true;
  }
  
  else{
  newGame = true;
  }

  while(true){
    while(newGame)
    {
      // If no args; FRESH GAME!
      std::cout << "Welcome to Watopoly! Skip intro? (Y/N)" << std::endl;

      while (true)
      {
        std::cin >> yesNo;
        if (yesNo == "Y" || yesNo == "N")
        {
          skip = (yesNo == "Y");
          break;
        }
        else
        {
          std::cerr << "Please input 'Y' for yes or 'N' for no." << std::endl;
        }
        std::cin.ignore();
        std::cin.clear();
      }

    if (!skip){
       std::cout
          << "A digital implementation of the classic board game Monopoly, only set in the exciting, goose-poop littered campus grounds of UW."
          << std::endl
          << "Before beginning, please make sure you are familiar with Monopoly's rules, found here : https://www.fgbradleys.com/rules/Monopoly%20Millennium%20Edition.pdf"
          << std::endl
          << "Otherwise, we should be ready to begin!" << std::endl; //make a help command to display the commands
    }

    std::cout << "Okay, let's begin! You can quit the game at any time by entering 'q' into the command line." 
      << std::endl
      << "How many players are we playing with today?" << std::endl;

    while (true)
      {
        std::cin >> playNum;
        
        if (std::cin.fail() || playNum < 1 || playNum > 8){
          std::cin.clear();
          std::cin.ignore(32767, '\n');
          std::cerr << "Watopoly only supports between 2 to 8 players. Please enter a valid number of players and try again." << std::endl;
        }
        else if (playNum >= 2 && playNum <= 8){
          break;
        }
      }

      for (int i = 0; i < playNum; ++i)
      {
        std::cout << "Hi Player " << i + 1 << " , choose your name and corresponding token from the options below (type in the respective char):"
        << std::endl;

        while (true)
        {std::cout
              << "Goose = G, GRT Bus = B, Tim Hortons Doughnut = D, Professor = P"
              << std::endl
              << "Student = S, Money = $, Laptop = L, Pink tie = T" <<std::endl;
          std::cin >> token;
          // change to try, catch, throw
          if (token == 'G' || token == 'B' || token == 'D' || token == 'P' ||
              token == 'S' || token == '$' || token == 'L' ||
              token == 'T')
          {
            int flag = 1;
            std::string t{token};
            for(auto i : players){
              if(i->getToken() == token){
                flag = 0;
              }
            }
            if (flag){
              players.emplace_back(new Player(token, activeBoard));
              
              activeBoard->getSquarePtr(0)->tk.emplace_back(t);
              //std::cout << players.size();
              break;
            }
            else {
              std::cerr << "Someone has already chosen this playing piece token. Please select a different token from the options below." << std::endl;
            }
          }
          else
          {
            std::cerr << "Please choose a valid token option." <<std::endl;
          }
        std::cin.ignore();
        std::cin.clear();
        }//end of while
      }//end of for loop
      std::cout << "Yay! Now all players have been set-up. Let's start the actual game - good luck! Player 1 will go first" << std::endl;
      newGame = false;
      
    } //while loop for NewGame

    //set currPlayer to Player 1.
    //if(players.size() != 0){
      Player* currPlayer = players[0];
    //}
    // While loop to input
    while (true)
    {
      //check if only one player remains. Then run the following.
      if (players.size() == 1)
      {
        std::cout << "Congratulations " << players.at(0)->getName() << "! You have one" << std::endl;
        break;
      }

      if (currPlayer->getBankrupt()){
        std::cout << "NOTICE!" << std::endl << "According to our records, you currently owe $" << currPlayer->getDebt() << " to " << currPlayer->getDebtee() << "." << std::endl <<
        "You can only begin your turn and roll after you pay back the remaining debt you owe. You do this by calling the 'repayment' command in the terminal and enter either the name of a player or the school to repay the debt you owe." << std::endl;

        if (currPlayer->totalWorth(activeBoard) < currPlayer->getDebt()){
          std::cout << "By our records, the net worth of all your assets is only " << currPlayer->totalWorth(activeBoard) << " and is not enough to cover the $" << currPlayer->getDebt() << " you owe to " << currPlayer->getDebtee()->getName() << "." << std::endl;
          std::cout << "As such, while you may still try to raise the money by selling/trading/mortgaging your assets, it is unlikely you will be able to raise the money required (unless your fellow players want to help bail you out in a disadvantageous trade)." << std::endl;
          std::cout << "Thus, unfortunately, at this point in the game, we would highly recommend you declare bankruptcy by calling the 'bankrupt' command and drop out of the game so your peers may resume playing to avenge you." << std::endl;
        }

        else{
          std::cout<< "You can try and raise the money you owe by trading with other players, selling improvements or mortgaging your property." << std::endl <<
          "If you are unable to do so, you will be forced to be dropped out by your peers since the game can't continue until you either pay the owed amount or drop out." << std::endl;
          std::cout << "Good luck!" << std::endl;
        }
      }

      // display whose turn it is
      std::cout << "It's your turn " << currPlayer->getName() << ". Input your actions: " << std::endl;

      std::cin >> commandName;

      //convert commandName (a string) to the corresponding char using map.
      
      //test this implementation
      command = cmdMap[commandName];

      if (std::cin.fail())
      {
        std::cerr << "Sorry, that command doesn't exist in Monopoly. Please review the cheat-sheet of commands found here: , and try again." << std::endl;
      }
      
      // Switch statement
      switch (command){
        case 'A':{ //roll
          if (currPlayer->getBankrupt()){
            std::cerr << "According to our records, you currently owe $" << currPlayer->getDebt() << " to " << currPlayer->getDebtee() << "." << std::endl <<
            "You can only begin your turn and roll after you pay back the remaining debt you owe. You do this by calling the 'repayment' command in the terminal and enter either the name of a player or the school to repay the debt you owe." << std::endl;
            if (currPlayer->totalWorth(activeBoard) < currPlayer->getDebt()){
              std::cout << "By our records, the net worth of all your assets is only " << currPlayer->totalWorth(activeBoard) << " and is not enough to cover the $" << currPlayer->getDebt() << " you owe to " << currPlayer->getDebtee()->getName() << "." << std::endl;
              std::cout << "As such, while you may still try to raise the money by selling/trading/mortgaging your assets, it is unlikely you will be able to raise the money required (unless your fellow players want to help bail you out in a disadvantageous trade)." << std::endl;
              std::cout << "Thus, unfortunately, at this point in the game, we would highly recommend you declare bankruptcy by calling the 'bankrupt' command and drop out of the game so your peers may resume playing to avenge you." << std::endl;
            }
            else{
              std::cout<< "You can try and raise the money you owe by trading with other players, selling improvements or mortgaging your property." << std::endl <<
              "If you are unable to do so, you will be forced to be dropped out by your peers since the game can't continue until you either pay the owed amount or drop out." << std::endl;
              std::cout << "Good luck!" << std::endl;
            }
          }
          else if (currPlayer->getRolled()){
            std::cerr << "You cannot roll twice in a turn. Please enter 'next' to pass your turn off to the next player if you have finished." << std::endl;
          }
          else{
            // Roll the dice
              auctionSquare = test? currPlayer->rollDice(activeBoard, players, true) : currPlayer->rollDice(activeBoard, players, false);
          }
          break;
        }
        case 'B':{ //next
          if (currPlayer->getBankrupt()){
            std::cerr << "According to our records, you currently owe $" << currPlayer->getDebt() << " to " << currPlayer->getDebtee()->getName() << "." << std::endl <<
            "You can only end your turn after you pay back the remaining debt you owe. You do this by calling the 'repayment' command in the terminal and enter either the name of a player or the school to repay the debt you owe." << std::endl;
            if (currPlayer->totalWorth(activeBoard) < currPlayer->getDebt()){
              std::cout << "By our records, the net worth of all your assets is only " << currPlayer->totalWorth(activeBoard) << " and is not enough to cover the $" << currPlayer->getDebt() << " you owe to " << currPlayer->getDebtee() << "." << std::endl;
              std::cout << "As such, while you may still try to raise the money by selling/trading/mortgaging your assets, it is unlikely you will be able to raise the money required (unless your fellow players want to help bail you out in a disadvantageous trade)." << std::endl;
              std::cout << "Thus, unfortunately, at this point in the game, we would highly recommend you declare bankruptcy by calling the 'bankrupt' command and drop out of the game so your peers may resume playing to avenge you." << std::endl;
            }
            else{
              std::cout<< "You can try and raise the money you owe by trading with other players, selling improvements or mortgaging your property." << std::endl <<
              "If you are unable to do so, you will be forced to be dropped out by your peers since the game can't continue until you either pay the owed amount or drop out." << std::endl;
              std::cout << "Good luck!" << std::endl;
            }
          }
          else if(!currPlayer->getRolled()){
            std::cerr << "You haven't rolled yet! You need to move around the board every turn in Watopoly. Take a risk and roll the dice :p" << std::endl;
          }
          else {
            // move the currPlayer to the first player if last player
            // check if in debt, if in debt, they can't move. ask them to get out of debt, or otherwise, to declare bankruptcy
            currPlayer->setRolled(false);
            if (currPlayer == players[playNum-1]){
              currPlayer = players[0];
              it = 0;
            }
            // move the currPlayer over to the next
            else{
              it++;
              currPlayer = players[it];
            }
          }
          break;
        }

        case 'C':{ //trade <name> <give> <receive>
          bool active = false;
          Player * otherPlayer;

          std::cin >> name;
          std::cin >> give;
          std::cin >> receive;

          std::cout << "Name: " << name << " Give: " << give << " Receive: " << receive;

          for (unsigned int i = 0; i < players.size(); ++i){
            if (players[i]->getName() == name){
              active = true;
              otherPlayer = players[i];
              break;
            }
          }

          if (!active){
            std::cerr << "The player you are trying to trade with is not active in this game. Please choose one of the following players: " << std::endl;
            for (unsigned int i = 0; i < players.size(); ++i) {
              if (i != it){
                std::cout << players[i]->getName() << std::endl;
              }
            }
            break;
          }

          if (name == currPlayer->getName()){
            std::cerr << "You can't do a trade with yourself silly :p Please input one of the following player's names: " << std::endl;
            for (unsigned int i = 0; i < players.size(); ++i) {
              if (i != it){
                std::cout << players[i]->getName() << " = " << std::endl;
              }
            }
            break;
          }

          bool giveProperty = false;
          int amount = 0;
          bool giveIt = false;

          std::cout << currPlayer->getName() << std::endl;
          for (unsigned int i = 0; i < currPlayer->getBuildingOwned().size(); ++i){
            std::cout << currPlayer->getBuildingOwned().at(i) << std::endl;
            if (currPlayer->getBuildingOwned().at(i) == give){
              giveIt = true;
            }
          }

          std::cout << currPlayer->getBuildingOwned().size() << std::endl;
          //std::cout << *giveIt << std::endl;
        
          //std::vector<std::string>::iterator giveIt  = std::find(currPlayer->getBuildingOwned().begin(), currPlayer->getBuildingOwned().end(), give);

          if(giveIt){
            giveProperty = true;
          }
          else{
            try{
              amount = std::stoi(give);
              std::cout << amount << std::endl;
              if (amount < 0 || amount > currPlayer->getBalance()) throw 1;
            }
            catch(...){
              std::cerr << "Please enter a valid amount of money you have (non-negative integers within your balance), or a valid property name that you own." << std::endl;
              std::cout << "For reference: " << std::endl;
              currPlayer->displayAssets(activeBoard);              
              break;
            }
          } 
          bool getProperty = false;
          std::vector<std::string>::iterator getIt  = std::find(otherPlayer->getBuildingOwned().begin(), otherPlayer->getBuildingOwned().end(), receive);
          
          if (getIt != currPlayer->getBuildingOwned().end()){
            getProperty = true;
          }

          else{
            try{
              std::stoi(receive);
              throw std::invalid_argument("Please enter a valid amount of money (non-negative integers only) or property the other player owns to receive in your proposed trade.");
              std::cout << "For reference: " << std::endl;
              otherPlayer->displayAssets(activeBoard); 
              break;
            }
            catch(std::invalid_argument & e){
              std::cerr << e.what();
              std::cout << "For reference: " << std::endl;
              currPlayer->displayAssets(activeBoard);
              break;
            }
            if (std::stoi(give) < 0 || std::stoi(give) > otherPlayer->getBalance()){
              std::cerr << "Please enter a valid amount of money you have (non-negative integers only), or a valid property name that you own." << std::endl;
              std::cout << "For reference: " << std::endl;
              otherPlayer->displayAssets(activeBoard);              
              break;
            }
          }

          if (!giveProperty && !getProperty){
            std::cerr << "Invalid trade. Remember, you can only trade money for property or a property you own for money. Try again." << std::endl;
            break;
          }

          std::shared_ptr<Building> giveBuilding;
          std::shared_ptr<Building> getBuilding;

            if (giveProperty){
              giveBuilding = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(give));
              if (giveBuilding->improvementOnFaculty(activeBoard)){
                std::cerr << "You can't trade " << give << " as it, or one of the buildings in its monopoly has improvements. You can only trade properties that don't have improvements themselves and don't belong to any monopolies with improvements either. You can attempt to sell those improvements, and try again." << std::endl;
                break;
              }
            }
            
            if (getProperty){
              getBuilding = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(receive));
              if (getBuilding->improvementOnFaculty(activeBoard)){
                std::cerr << "You can't trade " << receive << " as it, or one of the buildings in its monopoly has improvements. You can only trade properties that don't have improvements themselves and don't belong to any monopolies with improvements either. You can attempt to sell those improvements, and try again." << std::endl;
                break;
              }
            }

          //No errors:
          std::cout << "Attention " << name << " you are getting a trade request from " << currPlayer->getName() << " for " << give << " in exchange for " << receive << ". Do you want to accept? (accept/reject)" << std::endl;

          bool accept;

          while (true){
            std::cin >> yesNo;
            if (yesNo == "accept" || yesNo == "reject"){
              accept = (yesNo == "accept");
              break;
            }
            else{
              std::cerr << "Please input 'accept' for yes or 'reject'for no." << std::endl;
            }
            std::cin.ignore();
            std::cin.clear();
          }

          if (!accept){
            std::cout << "Sorry, your trade was rejected." << std::endl;
            break;
          }
          else{
            //FINALLY! Call the methods.
            if (!giveProperty && getProperty){
              currPlayer->playerTrade(*otherPlayer, stoi(give), *getBuilding, activeBoard);
            }
            else if(giveProperty && !getProperty){
              currPlayer->playerTrade(*otherPlayer, *giveBuilding, stoi(receive), activeBoard);
            }
            else{
              currPlayer->playerTrade(*otherPlayer, *giveBuilding, *getBuilding, activeBoard);
            }
            std::cout << "Trade between " << currPlayer->getName() << " and " << name << " is complete." << std::endl;
            break;
          }
        }

        case 'D':{ //improve property buy/sell
          int flag{1};
          std::cin >> property;
          std::cin >> buySell;

          char buySellArg;

          if (buySell == "buy"){
            buySellArg = 'B';
          }

          else if(buySell == "sell"){
            buySellArg = 'S';
          }
          else{
            std::cerr << "Please enter either buy or sell as your third argument: improve <property> buy/sell." << std::endl;
          }
          for(int i = 0; i < 40; ++i){
            if(activeBoard->getSquarePtr(i)->getBlock() == property){
              if(activeBoard->getSquarePtr(i)->getType() != 'A'){
                std::cerr << "You cannot make an improvemnt on this type of property as its is not an academic building." << std::endl;
                flag = 0;
                break;
              }
            }
          }
          if(flag){
          std::shared_ptr<Square> propArg = activeBoard->getSquarePtr(property);
          auto academic = std::static_pointer_cast<Academic>(propArg);

          currPlayer->improvements(*academic,buySellArg,1);
          }
          activeBoard->updateBoard();
          
          activeBoard->displayBoard();
          break;
        }

        case 'E':{
          std::cin >> property;
          std::shared_ptr<Square> propArg = activeBoard->getSquarePtr(property);
          auto building = std::static_pointer_cast<Building>(propArg);
          currPlayer->mortgage(*building);
          break;
        }

        case 'F':{
          std::cin >> property;
          std::shared_ptr<Square> propArg = activeBoard->getSquarePtr(property);
          auto building = std::static_pointer_cast<Building>(propArg);
          currPlayer->unMortgage(*building);
          break;
        }

        case 'G':{
          //check if player can declare bankruptcy; if they can't then break.
          bool over;
          if (currPlayer->getBankrupt()){
            std::cout << "Are you sure you want to declare bankruptcy? You can try to sell of your assets in hopes of being able to pay what you owe." << std::endl;
            while (true){
              std::cin >> yesNo;
              if (yesNo == "Y" ||yesNo == "N"){
                over = (yesNo == "Y");
              }
              else{
                std::cerr << "Please input 'accept' for yes or 'reject'for no." << std::endl;
              }
              std::cin.ignore();
              std::cin.clear();
            }
          }
          else{
            std::cerr << "You can't declare bankruptcy as you are not in debt. To leave the game, you can enter command 'q'." << std::endl;
          }

          if (over){
            std::cout << currPlayer->getName() << " has declared bankruptcy. They are now out of the game :(" << std::endl;
            Player* bankruptPlayer = players[it];
            players[it] = nullptr;
            players.erase(players.begin() + it);

            if (bankruptPlayer->getDebtee()){
              for (unsigned int i = 0; i < bankruptPlayer->getBuildingOwned().size(); ++i){
                auto building = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(bankruptPlayer->getBuildingOwned().at(i)));
                building->setOwner(bankruptPlayer->getDebtee());
              }
              bankruptPlayer->getDebtee()->addTimsCup(bankruptPlayer->getTimsCup());
              bankruptPlayer->getDebtee()->setBalance(bankruptPlayer->getBalance() + bankruptPlayer->getDebtee()->getBalance());
              std::cout << bankruptPlayer->getDebtee()->getName() << ", since " << bankruptPlayer->getName() << " owes you money, you will receive all of their assets." << std::endl;
            }
            else{
              std::cout << "Since " << bankruptPlayer->getName() << " owed money to the bank, all properties are now being auctionned off for grabs to remaining active players. Good luck!" << std::endl;
              for (unsigned int i = 0; i < bankruptPlayer->getBuildingOwned().size(); ++i){
                auto building = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(bankruptPlayer->getBuildingOwned().at(i)));
                building->setMortgaged(false);
                building->buildingAuction(players);
              }
              activeBoard->setTimsCups(activeBoard->getTimsCups() - bankruptPlayer->getTimsCup());
            }
            delete bankruptPlayer;
            it += 1;
            currPlayer = players[it];
            std::cout << currPlayer->getName() << "has been officially removed from the Watopoly game. We are now continuing with " << currPlayer->getName() << std::endl;
          }
          break;
        }

        case 'H':{
          currPlayer->displayAssets(activeBoard);
          break;
        }

        case 'I':{
          for (unsigned int i = 0; i < players.size(); ++i){
            players[i]->displayAssets(activeBoard);
            std::cout << std::endl;
          }
          //If no errors, display all player's assets by running the displayAssets methods for all Players in players.
          break;
        }

        case 'J':{ //save the state of the game in a file
          std::string filename;
          std::cin >> filename;
          std::ofstream outfile (filename);
          outfile << players.size() << std::endl;
          for(auto i : players){// displays all the players with all the their deets
            if(i->getLanded()->getSquareNum() != 10){
            outfile << i->getName() << " " << i->getToken() << " " << i->getTimsCup() << " " << i->getBalance() << " " << i->getLanded()->getSquareNum() << std::endl;
            } else {
              if(!i->getSentToTims()){
              outfile << i->getName() << " " << i->getToken() << " " << i->getTimsCup() << " " << i->getBalance() << " " << i->getLanded()->getSquareNum() << " " << i->getSentToTims() <<std::endl;
              } else {
              outfile << i->getName() << " " << i->getToken() << " " << i->getTimsCup() << " " << i->getBalance() << " " << i->getLanded()->getSquareNum() << " " << i->getSentToTims() << " " << i->getNumSentToTims() <<std::endl;
              }
            }
          }
          
          // Now to display all the 
          for(int i = 0; i < 40; ++i){
            //board->getSquarePtr(i);
          if(activeBoard->getSquarePtr(i)->getType() != 'N'){
            auto buildingPtr = std::static_pointer_cast<Building>(activeBoard->getSquarePtr(i));
            if(activeBoard->getSquarePtr(i)->getType() == 'A'){ // this takes care of the academic builings
              if(buildingPtr->getMortgaged()){
                outfile << activeBoard->getSquarePtr(i)->getBlock() << " " << (buildingPtr->getOwner()? buildingPtr->getOwner()->getName() : "BANK") << " " << -1 << std::endl;
              } else {
                outfile << activeBoard->getSquarePtr(i)->getBlock() << " " << (buildingPtr->getOwner()? buildingPtr->getOwner()->getName() : "BANK") << " " << (buildingPtr->getOwner()? buildingPtr->getImprovement() : 0) << std::endl;
              }
            } else if(activeBoard->getSquarePtr(i)->getType() == 'R' || activeBoard->getSquarePtr(i)->getType() == 'G'){ // for all non academic buildings
              if(buildingPtr->getMortgaged()){
                outfile << activeBoard->getSquarePtr(i)->getBlock() << " " << (buildingPtr->getOwner()? buildingPtr->getOwner()->getName() : "BANK") << " " << -1 << std::endl; 
              } else {
                outfile << activeBoard->getSquarePtr(i)->getBlock() << " " << (buildingPtr->getOwner()? buildingPtr->getOwner()->getName() : "BANK") << " " << (buildingPtr->getOwner()? buildingPtr->getImprovement() : 0) << std::endl;
              }
            }
            }
          }
          break;
        }

        case 'K':{
          //Maybe add extra layer asking if they are sure they want to quit.
          std::cout << "Are you sure you want to quit? (Y/N)" << std::endl;

          while (true)
          {
            std::cin >> yesNo;
            if (yesNo == "Y"){
              std::cout << "Do you want to save before quitting? (Y/N)" << std::endl;
              while (true){
                std::cin >> yesNo;
                if (yesNo == "Y"){
                  std::cout << "Input the name of the file you want to save the game in. (Y/N)" << std::endl;
                  std::cin >> filename;
                  //run save
                  return 0;
                }
                else if (yesNo == "N"){
                  exit(0);
                  //break;
                }
                else{
                  std::cerr << "Please input 'Y' for yes or 'N' for no. (Y/N)";
                }
              }
            }
            else if (yesNo == "N"){
              break;
            }
            else{
              std::cerr << "Please input 'Y' for yes or 'N' for no. (Y/N)" << std::endl;
            }
          }
          break;
        }

        case 'L':{
          std::cout << 
          "                                                         List of Valid Watopoly Commands                                     " << std::endl << 
          std::endl <<
          "roll                           Roll the dice, move and execute action based on square landed on. Can only roll once per turn." << std::endl <<
          "next                           Give control to the next player. Can only be used after you have rolled." << std::endl <<
          "trade <name> <give> <receive>  Offer a trade offering <give> in exchange of <receive> to player with <name>. NOTE: <give> and <receive> cannot be of monetary value." << std::endl <<
          "improve <property> buy/sell    Buy or sell an improvement on an academic building you own on campus." << std::endl << 
          "mortgage <property>            Mortgage the property you own for half the cost of the property. Building must not have any improvements prior to being mortgaged." << std::endl <<
          "unmortgage <property>          Unmortgage the property you own by paying half of the cost of the property plus 10% more of the cost of the property (total 60% of property)." << std::endl <<
          "bankrupt                       Declare bankruptcy and drop out of the game. Can only be done if you owe money to another player unpayable with your current balance." << std::endl <<
          "assets                         Display your assets. Use only to verify the correctness fo transactions. Won't work when trying to decide how to pay tutition." << std::endl <<
          "all                            Display the assets of all players. Use only to verify the correctness fo transactions. Won't work when trying to decide how to pay tutition." << std::endl <<
          "save <filename>                Save the current state of the game to <filename>" << std::endl;
          break;
        }

        default:{
          std::cerr << "Command not found. Please use the 'help' command to see a list of all possible commands for Watopoly and a quick explanation for each. " << std::endl;
        }
      }// switch
    }//while

    // Done the game!

    //call the player destructor for the one remaining player in the vector
    std::cout << "Thanks for playing Watopoly! New Game? (Y/N) To load or test, please exit the program and rerun with the correct command line options." << std::endl;
    //ask if you want to save your finished game.
    //delete gameBoard
    // destruct all Players in the vector (but don't delete the vector itself)

    while (true)
    {
      std::cin >> yesNo;
      if (yesNo == "Y")
      {
        newGame = true;
        //create a new gameboard
      }
      else if (yesNo == "N")
      {
        break;
      }
      else
      {
        std::cerr << "Please input 'Y' for yes or 'N' for no.";
      }
    }
  }//end of while(true) before newGame
  return 0;
}//end of main()





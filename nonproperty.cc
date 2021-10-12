#include "nonproperty.h"

#include <iostream>
#include <string>
#include <random>
#include <vector>

NonProperty::NonProperty(int collect, std::string block, int x, int y, int squareNum) : Square(x, y, block, squareNum), collect{collect}{}

void NonProperty::action(Player * player, Board * gameBoard, std::vector<Player*> & players){
    if (this->getBlock() == "Collect OSAP"){
        std::cout << "Collecting OSAP! +$200 in your balance! Use command 'assets' to verify you've received your OSAP payment." << std::endl;
        player->setBalance(player->getBalance() + collect);
    }
    else if (this->getBlock() == "Go to Tims"){
        std::cout << "Uh oh, you were sent on a coffee run to the DC Tims Line by your peers on a study session during rush hour! You will be stuck there until you either " << std::endl
        << "1) Roll doubles your next turn, 2) Pay $50 your next turn, or 3) Use a Roll Up the Rim Cup youe next turn." << std::endl;
        player->setLanded(11, gameBoard);
        player->setSentToTims(true);
    }
    else if (this->getBlock()== "DC Tims Line"){
        if (player->getSentToTims()){
            std::cout << "Uh oh, you were sent on a coffee run to the DC Tims Line by your peers on a study session during rush hour! You will be stuck there until you either " << std::endl
            << "1) Roll doubles your next turn, 2) Pay $50 your next turn, or 3) Use a Roll Up the Rim Cup youe next turn." << std::endl;
            player->addNumSentToTims(1);
            return;
        }
        else {
            std::cout << "Just visiting the DC Tims Line huh? Lucky you aren't stuck in line :p" << std::endl;
        }
    }

    else if (this->getBlock() == "Goose Nesting"){
        std::cout << "You are spontaneously attacked by a flock of nesting geese. Luckily, you survive... this time..." << std::endl;
    }

    else if (this->getBlock() == "Tuition"){
        int payment = player->totalWorth(gameBoard) * 0.1;

        std::string option = "";
        std::cout << "Time to pay tuition! Luckily though, you have a choice as to HOW you pay." << std::endl;
        while (true){
            std::cout << "You can either: " << std::endl <<
            "1) Pay $300 in Tuition \t 2) Pay 10% of your total worth (savings, purchase costs of all building you own, and the costs of each improvement)." << std::endl <<
            "Please enter either 1 or 2 to confirm your decision:" << std::endl;
            std::cin >> option;
            if (option == "1"){
                player->bankTransfer(300);
                break;
            }
            else if (option == "2"){
                player->bankTransfer(payment);
                break;
            }
            else if (option == "assets" || option == "all"){
                std::cerr << "At this point, you might feel the need to call the 'assets' or 'all' commands to make your financial decision." << std::endl << 
                "Unfortunately, these are not available to you right now, so hopefully you passed 'Keeping track of your own finances 101'." << std::endl;
            }
            else {
                std::cerr << "Please input a valid option." << std::endl;
            }
            std::cin.ignore();
            std::cin.clear();
        }
        std::cout << "Your balance is now " << player->getBalance() << ". Just so you know, your best option would've been:" << std::endl;
            
        if (payment < 300){
            std::cout << "Option 2: 10% your net worth" << std::endl;
            if (option == "1"){
                std::cout << "You chose Option 1 however and paid $" << 300 - payment << " in excess. Better luck next time. The school does appreciate your contribution though :)" << std::endl;
            }
        }
        else if (payment > 300){
            std::cout << "Option 1: $300" << std::endl;
            if (option == "2"){
                std::cout << "You chose Option 2 howeve and paid $" << payment - 300 << " in excess. Better luck next time. The school does appreciate your contribution though :)" << std::endl;
            }
        }
        else {
            std::cout << "Option 1 or Option. You would've paid $300 either way." << std::endl;
            if (option == "2"){
                std::cout << "You chose Option 2 howeve and paid $" << payment - 300 << " in excess. Better luck next time. The school does appreciate your contribution though :)" << std::endl;
            }
        }
    }
    else if (this->getBlock() == "Coop Fee"){
        std::cout << "Coop Fee time! You owe $150 for this term." << std::endl << "Processing your transaction..." << std::endl;
        player->bankTransfer(150);
    }
    else {
        //roll for the Tim's cup
        if (gameBoard->getTimsCups() < 4){
             std::cout << "We are now drawing to if you'll get a Roll Up the Rim Cup (1/100 chance)! Fingers crossed..." << std::endl;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::discrete_distribution<>d({99,1});
            
            int genNum = d(gen);
            if (genNum == 1){
                player->addTimsCup(genNum);
                std::cout << "You got a Roll Up the Rim Cup! Congrats! This can be used to get out of the DC Tims Line without rolling doubles or paying $50 in case you're in a rush ;)" << std::endl;
            }
            else{
                std::cout << ":( No Roll Up Rim Cup..." << std::endl;
            }
        }
        if (this->getBlock() == "SLC"){
            std::cout << "We are now drawing to see where SLC's campus map directs you to go on campus (aka. where you will move to on the board)." << std::endl;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::vector<int> SLCVal = {-3, -2, -1, 1, 2, 3, 11, 0};
            std::discrete_distribution<>d({3,4,4,3,4,4,1,1});
            
            int movement = SLCVal[d(gen)];
            int newPos = player->getLanded()->getSquareNum() + movement;
            int diff;

            if (movement < 0){
                std::cout << "You got sent Back " << std::abs(movement) << " squares." << std::endl;
                
                if (newPos <= 0){
                    newPos += 40;
                }
                int origNum = player->getLanded()->getSquareNum();
                player->setLanded(newPos,gameBoard);
                std::string t{player->getToken()};

                if (origNum == 3 && movement == -3){
                    std::cout << "You passed the 'Collect OSAP' square! +$200 in your balance! Use command 'assets' to verify you've received your OSAP payment." << std::endl;
                    player->setBalance(player->getBalance() + 200);
                }
            }
            else if (movement >= 1 && movement <= 3){
                std::cout << "You got sent Forward " << movement << " squares." << std::endl;

                if (newPos > 40){
                    newPos = newPos - 40;
                }
                player->setLanded(newPos,gameBoard);
                std::string t{player->getToken()};
            }
            else if (movement == 0){
                diff = 41 - player->getLanded()->getSquareNum();
                std::cout << "You got sent Forward " << diff << " squares." << std::endl;
                player->setLanded(1, gameBoard);
            }
            else if (movement == 11){
                if (player->getLanded()->getSquareNum() >= 11 && player->getLanded()->getSquareNum() <= 40){
                    diff = 51 - player->getLanded()->getSquareNum();
                }
                else{
                    diff = 11 - player->getLanded()->getSquareNum();
                }
                std::cout << "You got sent Forward " << diff << " squares." << std::endl;
                player->setSentToTims(true);
                player->setLanded(11, gameBoard);
            }
            else{
                std::cerr << "Something's wrong with this random number distribution generator for SLC" << std::endl;
            }
            player->getLanded()->runAction(player,gameBoard,players);
        }//distribution roll for SLC
        else{
            std::cout << "We are now drawing to see if the Needles Hall vending machine will reimburse you for the years of toonies it has stolen from you or steal more money from you... (aka. how much money you will have to pay or give)." << std::endl;
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::vector<int> NHVal = {-200, -100, -50, 25, 50, 100, 200};
            std::discrete_distribution<>d({1,2,3,6,3,2,1});
            
            int payment = NHVal[d(gen)];

            if ((payment != -200) && (payment != -100) && (payment != -50) && (payment != 25) && (payment != 50) && (payment != 100) && (payment != 200)){
                std::cerr << "Something's wrong with this random number distribution generator for NH" << std::endl;
            }
            if (payment >= 0){
                std::cout << "Congrats! The vending machine's coin return outputted $" << payment << ". Lucky you!" << std::endl;
                player->setBalance(player->getBalance() + payment);
            }
            else {
                std::cout << "Sighs... unfortunately, the vending machine has once again stolen $" << -payment << " from you without dispensing your chips... Better luck next time :(" << std::endl;
                player->bankTransfer(-payment);
            }
        }//distribution roll for Needles Hall
    }
}


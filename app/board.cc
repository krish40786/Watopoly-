#include "board.h"
#include "square.h"
#include "nonproperty.h"
#include "building.h"
#include "academic.h"
#include "nonproperty.h"
#include "nonacademic.h"

#include <memory>
#include <iostream>
#include <string>
#include <vector>

Board::Board()
{
    //initializing improvements array for tuition increases
    int AL[6] = {2, 10, 30, 90, 160, 250};
    int ML[6] = {4, 20, 60, 180, 320, 450};
    int ECH_PAS[6] = {6, 30, 90, 270, 400, 550};
    int HH[6] = {8, 40, 100, 300, 450, 600};
    int RCH_DWE[6] = {10, 50, 150, 450, 625, 750};
    int CPH[6] = {12, 60, 180, 500, 700, 900};
    int LHI_BMH[6] = {14, 70, 200, 550, 750, 950};
    int OPT[6] = {16, 80, 220, 600, 800, 1000};
    int EV1[6] = {18, 90, 250, 700, 875, 1050};
    int EV2[6] = {18, 90, 250, 700, 875, 1050};
    int EV3[6] = {20, 100, 300, 750, 925, 1100};
    int PHYS[6] = {22, 110, 330, 800, 975, 1150};
    int B1[6] = {22, 110, 330, 800, 975, 1150};
    int B2[6] = {24, 120, 360, 850, 1025, 1200};
    int EIT[6] = {26, 130, 390, 900, 1100, 1275};
    int ESC[6] = {26, 130, 390, 900, 1100, 1275};
    int C2[6] = {28, 150, 450, 1000, 1200, 1400};
    int MC[6] = {35, 175, 500, 1100, 1300, 1500};
    int DC[6] = {50, 200, 600, 1400, 1700, 2000};

    std::vector<std::shared_ptr<Square>> squares1= {
        // do on the heap
        std::make_shared<NonProperty>(200, "COLLECT OSAP", 91, 51, 1),
        std::make_shared<Academic>("Arts1", 40, 50, AL, 2, "AL", 82, 51, 2),
        std::make_shared<NonProperty>(0, "SLC", 73, 51, 3),
        std::make_shared<Academic>("Arts1", 60, 50, ML, 4, "ML", 64, 51, 4),
        std::make_shared<NonProperty>(300, "TUITION", 55, 51, 5),
        std::make_shared<NonAcademic>(200, "MKV", 46, 51, 6),
        std::make_shared<Academic>("Arts2", 100, 50, ECH_PAS, 6, "ECH", 37, 51, 7),
        std::make_shared<NonProperty>(0, "NEEDLES HALL", 28, 51, 8),
        std::make_shared<Academic>("Arts2", 100, 50, ECH_PAS, 6, "PAS", 19, 51, 9),
        std::make_shared<Academic>("Arts2", 120, 50, HH, 8, "HH", 10, 51, 10),
        std::make_shared<NonProperty>(50, "DC Tims Line", 1, 51, 11),
        std::make_shared<Academic>("Eng", 140, 100, RCH_DWE, 10,"RCH", 1, 46, 12),
        std::make_shared<NonAcademic>(150, "PAC", 1, 41, 13),
        std::make_shared<Academic>("Eng", 140, 100, RCH_DWE, 10,"DWE", 1, 36, 14),
        std::make_shared<Academic>("Eng", 160, 100, CPH, 12,"CPH", 1, 31, 15),
        std::make_shared<NonAcademic>(200, "UWP", 1, 26, 16),
        std::make_shared<Academic>("Health", 180, 100, LHI_BMH, 14,"LHI", 1, 21, 17),
        std::make_shared<NonProperty>(0, "SLC", 1, 16, 18),
        std::make_shared<Academic>("Health", 180, 100, LHI_BMH, 14, "BMH", 1, 11, 19),
        std::make_shared<Academic>("Health", 200, 100, OPT, 16, "OPT", 1, 6, 20),
        std::make_shared<NonProperty>(0, "Goose Nesting", 1, 1, 21),
        std::make_shared<Academic>("Env", 220, 150, EV1, 18, "EV1", 10, 1, 22),
        std::make_shared<NonProperty>(0, "NEEDLES HALL", 19, 1, 23),
        std::make_shared<Academic>("Env", 220, 150, EV2, 18, "EV2", 28, 1, 24),
        std::make_shared<Academic>("Env", 220, 150, EV3, 20, "EV3", 37, 1, 25),
        std::make_shared<NonAcademic>(200, "V1", 46, 1, 26),
        std::make_shared<Academic>("Sci1", 260, 150, PHYS, 22,"PHYS", 55, 1, 27),
        std::make_shared<Academic>("Sci1", 260, 150, B1, 22, "B1", 64, 1, 28),
        std::make_shared<NonAcademic>(150, "CIF", 73, 1, 29),
        std::make_shared<Academic>("Sci1", 280, 150, B2, 24, "B2", 82, 1, 30),
        std::make_shared<NonProperty>(0, "GO TO TIMS", 91, 1, 31),
        std::make_shared<Academic>("Sci2", 300, 200, EIT, 26, "EIT", 91, 6, 32),
        std::make_shared<Academic>("Sci2", 300, 200, ESC, 26, "ESC", 91, 11, 33),
        std::make_shared<NonProperty>(0, "SLC", 91, 16, 34),
        std::make_shared<Academic>("Sci2", 320, 200, C2, 28, "C2", 91, 21, 35),
        std::make_shared<NonAcademic>(200, "REV", 91, 26, 36),
        std::make_shared<NonProperty>(0, "NEEDLES HALL", 91, 31, 37),
        std::make_shared<Academic>("Math", 350, 200, MC, 35, "MC", 91, 36, 38),
        std::make_shared<NonProperty>(150, "COOP FEE", 91, 41, 39),
        std::make_shared<Academic>("Math", 400, 200, DC, 50, "DC", 91, 46, 40)
};
    squares = squares1;

    std::vector<std::string> gameBoard1 = {
            "____________________________________________________________________________________________________", 
            "|Goose   |        |NEEDLES |        |        |V1      |        |        |CIF     |        |GO TO   |", 
            "|Nesting |--------|HALL    |--------|--------|        |--------|--------|        |--------|TIMS    |", 
            "|        |EV1     |        |EV2     |EV3     |        |PHYS    |B1      |        |B2      |        |", 
            "|        |        |        |        |        |        |        |        |        |        |        |", 
            "|________|________|________|________|________|________|________|________|________|________|________|", 
            "|        |                                                                                |        |", 
            "|--------|                                                                                |--------|", 
            "|OPT     |                                                                                |EIT     |", 
            "|        |                                                                                |        |", 
            "|________|                                                                                |________|", 
            "|        |                                                                                |        |", 
            "|--------|                                                                                |--------|", 
            "|BMH     |                                                                                |ESC     |", 
            "|        |                                                                                |        |", 
            "|________|                                                                                |________|", 
            "|SLC     |                                                                                |SLC     |", 
            "|        |                                                                                |        |", 
            "|        |                                                                                |        |", 
            "|        |                                                                                |        |", 
            "|________|                                                                                |________|", 
            "|        |                                                                                |        |", 
            "|--------|                                                                                |--------|", 
            "|LHI     |                                                                                |C2      |",
            "|        |            --------------------------------------------------------            |        |", //WATOPOLY
            "|________|            |                                                      |            |________|", 
            "|UWP     |            |  #  #  #   ###  #####  ###   ###    ###   #  #     # |            |REV     |", 
            "|        |            |  #  #  #  #   #   #   #   #  #  #  #   #  #   #   #  |            |        |", 
            "|        |            |  #  #  #  #####   #   #   #  ###   #   #  #     #    |            |        |", 
            "|        |            |  #  #  #  #   #   #   #   #  #     #   #  #     #    |            |        |", 
            "|________|            |   #####   #   #   #    ###   #      ###   ####  #    |            |________|", 
            "|        |            |                                                      |            |NEEDLES |",
            "|--------|            --------------------------------------------------------            |HALL    |", //WATOPOLY END
            "|CPH     |                                                                                |        |", 
            "|        |                                                                                |        |", 
            "|________|                                                                                |________|", 
            "|        |                                                                                |        |", 
            "|--------|                                                                                |--------|", 
            "|DWE     |                                                                                |MC      |",
            "|        |                                                                                |        |", 
            "|________|                                                                                |________|", 
            "|PAC     |                                                                                |COOP    |", 
            "|        |                                                                                |FEE     |", 
            "|        |                                                                                |        |", 
            "|        |                                                                                |        |", 
            "|________|                                                                                |________|", 
            "|        |                                                                                |        |", 
            "|--------|                                                                                |--------|", 
            "|RCH     |                                                                                |DC      |", 
            "|        |                                                                                |        |", 
            "|________|________________________________________________________________________________|________|", 
            "|DC Tims |        |        |NEEDLES |        |MKV     |TUITION |        |SLC     |        |COLLECT |", 
            "|Line    |--------|--------|HALL    |--------|        |        |--------|        |--------|OSAP    |", 
            "|        |HH      |PAS     |        |ECH     |        |        |ML      |        |AL      |        |", 
            "|        |        |        |        |        |        |        |        |        |        |        |", 
            "|________|________|________|________|________|________|________|________|________|________|________|"};
            
    gameBoard = gameBoard1;
    timsCups = 0;
}

void Board::displayBoard()
{
    //std::cout << this->gameBoard << std::endl;
    for (unsigned int i = 0; i < gameBoard.size(); ++i)
    {
        std::cout << gameBoard.at(i) << std::endl;
    }
}

int Board::getSize(){
    return squares.size();
}

void Board::updateBoardHelper(Square &square)
{
    //adding the imporvements
    int imp;
    if (square.getType() != 'N'){
        Building& building = static_cast<Building&>(square);
        imp = building.getImprovement();
    }
    else {
        imp = 0;
    }

    //int players = block.getPlayers();
    
    int x = square.getX();
    
    std::string str = gameBoard.at(square.getY());
    if(imp){
    for (unsigned int i = 0, x = square.getX(); i < 5; ++i, ++x)
    {   if(imp != 0){
            str.replace(x, 1, "I");
            --imp;
        } else {
            str.replace(x, 1, " ");
        }
    }
    gameBoard.at(square.getY()) = str;
    }
    //for displaying the players
    str = gameBoard.at(square.getY() + 3);
    int playerLen = square.tk.size();
    for (unsigned int y = 0; y < 8; ++y, ++x)
    {   
        if(playerLen != 0){
            str.replace(x, 1, square.tk.at(y));
            playerLen--;
        } else {
            str.replace(x, 1, " ");
        }
    }
    gameBoard.at(square.getY() + 3) = str;
}

void Board::updateBoard(){
    for (unsigned int i = 0; i < squares.size(); ++i){
        updateBoardHelper(*getSquarePtr(i));
    }
}

std::shared_ptr<Square> Board::getSquarePtr(int i){
    return squares[i];
}

unsigned int Board::getTimsCups(){
    return timsCups;
}

void Board::setTimsCups(int val){
    timsCups = val;
}

std::shared_ptr<Square> Board::getSquarePtr (std::string name){
    for (unsigned int i = 0; i < squares.size(); ++i){
        if (squares[i]->getBlock() == name){
            return squares[i];
        }
    }
    return nullptr;
}



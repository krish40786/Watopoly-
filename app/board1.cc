#include "board1.h"
#include <string>

Board::Board()
{   std::vector<std::string>
        gameBoard1 = {
            "____________________________________________________________________________________________________", 
            "|Goose   |        |NEEDLES |        |        |V1      |        |        |CIF     |        |GO TO   |", 
            "|Nesting |--------|HALL    |--------|--------|        |--------|--------|        |--------|TIMS    |", 
            "|        |EV1     |        |EV2     |EV3     |        |PHYS    |B1      |        |        |        |", 
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
}

void Board::displayBoard()
{
    //std::cout << this->gameBoard << std::endl;
    for (int i = 0; i < gameBoard.size(); ++i)
    {
        std::cout << gameBoard.at(i) << std::endl;
    }
}

void Board::updateBoard(Square &block)
{
    //adding the imporvements
    int imp = block.getImprovements();

    //int players = block.getPlayers();
    int x = block.getX();
    std::string str = gameBoard.at(block.getY());
    for (int i = 0, x = block.getX(); i < 5; ++i, ++x)
    {   if(imp != 0){
            str.replace(x, 1, "I");
            --imp;
        } else {
            str.replace(x, 1, " ");
        }
    }
    gameBoard.at(block.getY()) = str;
    //for displaying the players
    str = gameBoard.at(block.getY() + 3);
    int playerLen = block.tk.size();
    for (int y = 0; y < 8; ++y, ++x)
    {   
        if(playerLen != 0){
            str.replace(x, 1, block.tk.at(y));
            playerLen--;
        } else {
            str.replace(x, 1, " ");
        }
    }
    gameBoard.at(block.getY() + 3) = str;
}

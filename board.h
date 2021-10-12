#ifndef _BOARD_
#define _BOARD_
#include <iostream>
#include <string>

#include "square.h"
#include "player.h"

#include <memory>
#include <vector>

class Square;

class Board
{
    int timsCups;
    std::vector<std::string> gameBoard;
    std::vector<std::shared_ptr<Square>> squares;
public:
    std::shared_ptr<Square> getSquarePtr(int i);
    std::shared_ptr<Square> getSquarePtr (std::string name);
    int getSize();
    friend class Player;
    void updateBoardHelper(Square &square);
    Board();
    void displayBoard();
    void updateBoard();
    unsigned int getTimsCups();
    void setTimsCups(int);
    //void setCurrPlayer(Player *player);
};

#endif

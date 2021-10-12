#ifndef _BOARD_
#define _BOARD_
#include <iostream>
#include <string>
#include <vector>
#include "square1.h"

class Board
{
    //Player &currPlayer;
    std::vector<std::string> gameBoard;
    //Square squares[40];

public:
    Board();
    void displayBoard();
    void updateBoard(Square &block);
};

#endif

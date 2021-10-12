#ifndef _SQUARE_
#define _SQUARE_
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Board;
class Player;

class Square
{
    std::string block; //this basically stores the name e.g. slc, uwp etc..
    int x;             //this is the x position on the board
    int y;              //this is the y position on the board
    int squareNum;
    char type;
public:
    std::vector<std::string> tk;

    Square(int, int, std::string, int);
    int getX();
    int getY();
    std::string getBlock();
    int getSquareNum();
    char getType();

    Square* runAction(Player *, Board *, std::vector<Player*> &);
};

#endif



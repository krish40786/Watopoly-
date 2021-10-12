#ifndef _SQUARE_
#define _SQUARE_
#include <iostream>
#include <vector>

class Square
{
    //std::string block; //this basically stores the name e.g. slc, uwp etc..
    int x;             //this is the x position on the board
    int y;              //this is the y position on the board
    int improvements; 
    
public:
    std::vector<std::string> tk;
    Square(int, int, int);
    int getX();
    int getY();
    int getImprovements();
    void setImprovements(int);
    //std::string getBlock();
    
};

#endif

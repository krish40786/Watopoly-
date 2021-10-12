#ifndef _NONPROPERTY_
#define _NONPROPERTY_

#include <string>
#include <vector>

#include "square.h"
#include "board.h"

class Player;

class NonProperty : public Square
{
    int collect;

public:
    NonProperty(int, std::string, int, int, int);
    void action(Player*, Board*, std::vector<Player*> &);
};

#endif

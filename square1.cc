#include "square1.h"

Square::Square(int x, int y, int improvements) : x{x}, y{y}, improvements{improvements}{
    std::vector<char> tk;
}

int Square::getX()
{
    return x;
}

int Square::getY()
{
    return y;
}

int Square::getImprovements(){
    return improvements;
}

void Square::setImprovements(int imp){
    improvements = imp;
}


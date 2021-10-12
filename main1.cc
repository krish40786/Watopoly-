#include "square1.h"
#include "board1.h"
#include <iostream>

int main()
{
    //std::string gameBoard;
    Board b;
    //b.displayBoard();
    Square LHI{1, 21, 2};
    LHI.tk.emplace_back("P");
    LHI.tk.emplace_back("K");
    LHI.tk.emplace_back("L");
    b.updateBoard(LHI);
    //b.displayBoard();
    LHI.tk.pop_back();
    b.updateBoard(LHI);
    //b.displayBoard();
    LHI.setImprovements(1);
    std::cout << LHI.getImprovements();
    //b.displayBoard();
    //LHI.setImprovements(4);
    LHI.tk.emplace_back("$");
    b.updateBoard(LHI);
    b.displayBoard();
}

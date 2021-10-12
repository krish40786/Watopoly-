#include "input.h"


bool checkIfNum(std::string & str){
    try{
        int i = stoi(str);
        return true;

    } catch(const std::invalid_argument & ia){
        return false;
    }
}




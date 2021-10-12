#ifndef _NONACADEMIC_
#define _NONACADEMIC_

#include <string>
#include "building.h"
//class Building;

class NonAcademic : public Building
{
    int payment;

public:
    NonAcademic(int, std::string, int, int, int);
    int calcPayment(int, int);
};

#endif

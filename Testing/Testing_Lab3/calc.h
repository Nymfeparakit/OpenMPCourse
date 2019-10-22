#ifndef CALC_H
#define CALC_H
#include <iostream>
#include <stdlib.h>

class Calc
{
public:
    Calc();
    double sum(double, double);
    double subtract(double, double);
    double multiply(double, double);
    double divide(double, double) throw(std::invalid_argument);
};
#endif // CALC_H

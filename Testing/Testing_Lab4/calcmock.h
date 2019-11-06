#ifndef CALCMOCK_H
#define CALCMOCK_H
#include "calculator.h"

class CalcMock : public Calculator
{
public:
    CalcMock();
    double sum(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
};

#endif // CALCMOCK_H

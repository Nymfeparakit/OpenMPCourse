#include "calc.h"

Calc::Calc()
{

}

double Calc::sum(double a, double b)
{
    return a+b;
}

double Calc::subtract(double a, double b)
{
    return a-b;
}

double Calc::multiply(double a, double b)
{
    return a*b;
}
double Calc::divide(double a, double b) throw(std::invalid_argument)
{
    if (abs(b) < 10e-8)
        throw std::invalid_argument("Деление на 0");
    return a/b;
}


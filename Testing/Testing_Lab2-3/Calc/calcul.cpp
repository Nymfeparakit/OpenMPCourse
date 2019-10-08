#include "calcul.h"
#include <iostream>
#include <stdlib.h>

Calcul::Calcul()
{

}

double Calcul::sum(double a, double b)
{
    return a+b;
}

double subtract(double a, double b)
{
    return a-b;
}

double multiply(double a, double b)
{
    return a*b;
}
double divide(double a, double b) throw(std::invalid_argument)
{
    if (abs(b) < 10e-8)
        throw std::invalid_argument("Недопустимое значение второго аргумента");
    return a/b;
}
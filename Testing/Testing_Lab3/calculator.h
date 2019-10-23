#ifndef CALCULATOR_H
#define CALCULATOR_H


class Calculator
{
public:
    virtual double sum(double a, double b) = 0;
    virtual double subtract(double a, double b) = 0;
    virtual double multiply(double a, double b) = 0;
    virtual double divide(double a, double b) = 0;
    virtual ~Calculator() = 0;
};

#endif // CALCULATOR_H

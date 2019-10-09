#ifndef CALCVIEWMOCK_H
#define CALCVIEWMOCK_H
#include "calculatorview.h"

class CalcViewMock : public CalculatorView
{
public:
    CalcViewMock();
    void printResult(double result);
    void displayError(QString message);
    QString getFirstArgumentAsString();
    QString getSecondArgumentAsString();

    double result;
    QString errorMsg;
    QString firstArg;
    QString secondArg;

};

#endif // CALCVIEWMOCK_H

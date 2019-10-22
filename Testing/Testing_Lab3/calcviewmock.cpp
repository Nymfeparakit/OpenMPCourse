#include "calcviewmock.h"

CalcViewMock::CalcViewMock()
{
    pushBtnPlus = new QPushButton;
    pushBtnMinus = new QPushButton;
    pushBtnMultiply = new QPushButton;
    pushBtnDivide = new QPushButton;
}

void CalcViewMock::printResult(double result)
{
    this->result = result;
}

void CalcViewMock::displayError(QString message)
{
    errorMsg = message;
}

QString CalcViewMock::getFirstArgumentAsString()
{
    return firstArg;
}

QString CalcViewMock::getSecondArgumentAsString()
{
    return secondArg;
}

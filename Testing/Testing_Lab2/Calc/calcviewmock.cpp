#include "calcviewmock.h"

CalcViewMock::CalcViewMock()
{

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

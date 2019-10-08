#include "tc.h"

TC::TC()
{

}

void TC::takeArguments()
{
    CalcView* calcView = new CalcView();
    Calc* calc = new Calc();
    CalcPresenter calcPres(calcView, calc);
    double a, b;

    QCOMPARE(calcPres.takeArguments(a, b), true);
}

void TC::divide_SecondArgIsZero_ThrowsInvalidArgException()
{
    Calc* calc = new Calc();
    double a = 1;
    double b = 0;

    QVERIFY_EXCEPTION_THROWN(calc->divide(a, b), std::invalid_argument);

}



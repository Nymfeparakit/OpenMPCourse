#include "test_calcpresenter.h"
void Test_CalcPresenter::takeArguments()
{
    CalcView* calcView = new CalcView();
    Calc* calc = new Calc();
    CalcPresenter calcPres(calcView, calc);
    double a, b;

    QCOMPARE(calcPres.takeArguments(a, b), true);
}

//QTEST_MAIN(Test_CalcPresenter)
//#include "tests.moc"


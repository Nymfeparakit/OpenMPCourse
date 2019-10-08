#include "tc.h"
#include "calcviewmock.h"
#include "calcpresenter.h"

TC::TC()
{

}

/*
void TC::takeArguments()
{
    CalcView* calcView = new CalcView();
    Calc* calc = new Calc();
    CalcPresenter calcPres(calcView, calc);
    double a, b;

    QCOMPARE(calcPres.takeArguments(a, b), true);
}
*/

void TC::divide_SecondArgIsZero_ThrowsInvalidArgException()
{
    Calc calc;
    double a = 1;
    double b = 0;

    QVERIFY_EXCEPTION_THROWN(calc.divide(a, b), std::invalid_argument);

}

void TC::takeArguments_FirstArgIsNotNumber_setErrorMsg()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "not a number";
    calcViewMock.secondArg = "2";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "В качестве аргумента должно быть число");
}

void TC::takeArguments_FirstArgIsOutOfRange_setErrorMsg()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "2e+308";
    calcViewMock.secondArg = "2";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "Аргументы не должны выходить "
                                    "за пределы допустимых значений");
}

void TC::takeArguments_FirstArgIsEmpty_setErrorMsg()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "";
    calcViewMock.secondArg = "2";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "В качестве аргумента должно быть число");
}

void TC::onPlusClicked_NumberArgs_SetCorrectOpResult_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");
    QTest::addColumn<QString>("result");

    QTest::newRow("1+5") << "1" << "5" << "6";
    QTest::newRow("-1+5") << "-1" << "5" << "4";
    QTest::newRow("3.2+4.6") << "3.2" << "4.6" << "7.8";
    QTest::newRow("64.2e+12 + 34e+12") << "64.2e+12" << "34e+12" << "98e+12";
}

void TC::onPlusClicked_NumberArgs_SetCorrectOpResult()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    QFETCH(QString, result);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a = firstArg.toDouble();
    double b = secondArg.toDouble();

    //Act
    calcPresenter.onPlusClicked();

    //Assert
    QCOMPARE(calcViewMock.result, a + b);
}

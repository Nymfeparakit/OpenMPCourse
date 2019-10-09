#include "tc.h"
#include "calcviewmock.h"
#include "calcpresenter.h"

Test_CalcPresenter::Test_CalcPresenter()
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

void Test_CalcPresenter::divide_SecondArgIsZero_ThrowsInvalidArgException()
{
    Calc calc;
    double a = 1;
    double b = 0;

    QVERIFY_EXCEPTION_THROWN(calc.divide(a, b), std::invalid_argument);

}

void Test_CalcPresenter::takeArguments_FirstArgIsNotNumber_setErrorMsg()
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

void Test_CalcPresenter::takeArguments_SecondArgIsNotNumber_setErrorMsg()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "2";
    calcViewMock.secondArg = "not a number";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "В качестве аргумента должно быть число");
}

void Test_CalcPresenter::takeArguments_FirstArgIsOutOfRange_setErrorMsg_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");

    QTest::newRow("first arg = 2e+308(above range)") << "2e+308" << "5";
    QTest::newRow("first arg = -5e+400(below range)") << "-5e+400" << "5";
}

void Test_CalcPresenter::takeArguments_FirstArgIsOutOfRange_setErrorMsg()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "Аргументы не должны выходить "
                                    "за пределы допустимых значений");
}

void Test_CalcPresenter::takeArguments_SecondArgIsOutOfRange_setErrorMsg_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");

    QTest::newRow("second arg = 2e+308(above range)") << "3" << "2e+308";
    QTest::newRow("second arg = -5e+400(below range)") << "4" << "-5e+400";
}

void Test_CalcPresenter::takeArguments_SecondArgIsOutOfRange_setErrorMsg()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "Аргументы не должны выходить "
                                    "за пределы допустимых значений");
}

void Test_CalcPresenter::takeArguments_FirstArgIsEmpty_setErrorMsg()
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

void Test_CalcPresenter::takeArguments_SecondArgIsEmpty_setErrorMsg()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "2";
    calcViewMock.secondArg = "";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(calcViewMock.errorMsg, "В качестве аргумента должно быть число");
}

void Test_CalcPresenter::takeArguments_FirstArgUsesSciNotation_ParseArgCorrectly()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "64.2e+12";
    calcViewMock.secondArg = "2";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(a, 64.2e+12);
}

void Test_CalcPresenter::takeArguments_SecondArgUsesSciNotation_ParseArgCorrectly()
{
    //Arrange
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = "3";
    calcViewMock.secondArg = "64.2e+12";
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);
    double a,b;

    //Act
    calcPresenter.takeArguments(a,b);

    //Assert
    QCOMPARE(b, 64.2e+12);
}

/*
void TC::setTestData()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");
    QTest::addColumn<QString>("result");

    QTest::newRow("1+5") << "1" << "5" << "6";
    QTest::newRow("-1+5") << "-1" << "5" << "4";
    QTest::newRow("3.2+4.6") << "3.2" << "4.6" << "7.8";
    QTest::newRow("64.2e+12 + 34e+12") << "64.2e+12" << "34e+12" << "98e+12";
}
*/

void Test_CalcPresenter::onPlusClicked_NumberArgs_SetCorrectOpResult_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");
    QTest::addColumn<double>("result");

    QTest::newRow("1+5") << "1" << "5" << 6.0;
    QTest::newRow("-1+5") << "-1" << "5" << 4.0;
    QTest::newRow("3.2+4.6") << "3.2" << "4.6" << 7.8;
    QTest::newRow("64.2e+12 + 34e+11") << "64.2e+12" << "34e+11" << 67.6e+12;
}

void Test_CalcPresenter::onPlusClicked_NumberArgs_SetCorrectOpResult()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    QFETCH(double, result);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);

    //Act
    calcPresenter.onPlusClicked();

    //Assert
    QCOMPARE(calcViewMock.result, result);
    //QCOMPARE(calcViewMock.result, a + b);
}

void Test_CalcPresenter::onMinusClicked_NumberArgs_SetCorrectOpResult_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");
    QTest::addColumn<double>("result");

    QTest::newRow("1-5") << "1" << "5" << -4.0;
    QTest::newRow("-1-5") << "-1" << "5" << -6.0;
    QTest::newRow("3.2-4.6") << "3.2" << "4.6" << -1.4;
    QTest::newRow("64.2e+12 - 34e+11") << "64.2e+12" << "34e+11" << 60.8e+12;
}

void Test_CalcPresenter::onMinusClicked_NumberArgs_SetCorrectOpResult()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    QFETCH(double, result);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);

    //Act
    calcPresenter.onMinusClicked();

    //Assert
    QCOMPARE(calcViewMock.result, result);
    //QCOMPARE(calcViewMock.result, a - b);
}

void Test_CalcPresenter::onMultiplyClicked_NumberArgs_SetCorrectOpResult_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");
    QTest::addColumn<double>("result");

    QTest::newRow("1*5") << "1" << "5" << 5.0;
    QTest::newRow("-1*(-5)") << "-1" << "-5" << 5.0;
    QTest::newRow("3.2*4.6") << "3.2" << "4.6" << 14.72;
    QTest::newRow("64.2e+12 * 34e+11") << "64.2e+12" << "34e+11" << 2182.8e+23;
}

void Test_CalcPresenter::onMultiplyClicked_NumberArgs_SetCorrectOpResult()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    QFETCH(double, result);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);

    //Act
    calcPresenter.onMultiplyClicked();

    //Assert
    QCOMPARE(calcViewMock.result, result);
}

void Test_CalcPresenter::onDivideClicked_NumberArgs_SetCorrectOpResult_data()
{
    QTest::addColumn<QString>("firstArg");
    QTest::addColumn<QString>("secondArg");
    QTest::addColumn<double>("result");

    QTest::newRow("6/2") << "6" << "2" << 3.0;
    double res = 7.0/3;
    QTest::newRow("7/3") << "7" << "3" << res;
    res = 3.2/4.6;
    QTest::newRow("3.2/4.6") << "3.2" << "4.6" << res;
    res = 64.2e+12/34e+11;
    QTest::newRow("64.2e+12 / 34e+11") << "64.2e+12" << "34e+11" << res;
}

void Test_CalcPresenter::onDivideClicked_NumberArgs_SetCorrectOpResult()
{
    //Arrange
    QFETCH(QString, firstArg);
    QFETCH(QString, secondArg);
    QFETCH(double, result);
    CalcViewMock calcViewMock;
    calcViewMock.firstArg = firstArg;
    calcViewMock.secondArg = secondArg;
    Calc calc;
    CalcPresenter calcPresenter(&calcViewMock, &calc);

    //Act
    calcPresenter.onDivideClicked();

    //Assert
    QCOMPARE(calcViewMock.result, result);
}

#include "test_calcui.h"
#include "calcpresenter.h"

Test_CalcUI::Test_CalcUI()
{

}

void Test_CalcUI::plusClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);

    //Act
    QTest::keyClicks(calcView.LEditFirstArg, "12");
    QTest::keyClicks(calcView.lEditSecondArg, "2");
    QTest::mouseClick(calcView.pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView.lEditRes->text(), "14");
}

void Test_CalcUI::minusClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);

    //Act
    QTest::keyClicks(calcView.LEditFirstArg, "12");
    QTest::keyClicks(calcView.lEditSecondArg, "2");
    QTest::mouseClick(calcView.pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView.lEditRes->text(), "10");
}

void Test_CalcUI::multiplyClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);

    //Act
    QTest::keyClicks(calcView.LEditFirstArg, "12");
    QTest::keyClicks(calcView.lEditSecondArg, "2");
    QTest::mouseClick(calcView.pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView.lEditRes->text(), "24");
}

void Test_CalcUI::divideClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);

    //Act
    QTest::keyClicks(calcView.LEditFirstArg, "12");
    QTest::keyClicks(calcView.lEditSecondArg, "2");
    QTest::mouseClick(calcView.pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView.lEditRes->text(), "6");
}
void Test_CalcUI::divideClickedSecondArgIsZero_msgBoxWithErrorShows()
{
    //Arrange
    CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);

    //Act
    QTest::keyClicks(calcView.LEditFirstArg, "12");
    QTest::keyClicks(calcView.lEditSecondArg, "0");
    QTest::mouseClick(calcView.pushBtnDivide, Qt::LeftButton);

    //Assert
    QVERIFY2(calcView.msgBxError, "Message box not created");
    QVERIFY2(calcView.msgBxError->isVisible(), "Message box is not visible");
    QCOMPARE(calcView.msgBxError->text(), "Деление на 0");
}

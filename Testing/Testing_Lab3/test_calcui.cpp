#include "test_calcui.h"
#include <QTimer>

Test_CalcUI::Test_CalcUI()
{
}

void Test_CalcUI::initTestCase()
{
    calcView = new CalcView();
    calcView->show();
    calc = new Calc;
    calcPresenter = new CalcPresenter(calcView, calc);
}

void Test_CalcUI::cleanup()
{
    calcView->LEditFirstArg->clear();
    calcView->lEditSecondArg->clear();
    calcView->lEditRes->clear();
}

Test_CalcUI::~Test_CalcUI()
{
    delete calcView;
    delete calc;
    delete calcPresenter;
}

void Test_CalcUI::plusClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    /*CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);*/

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "14");
}

void Test_CalcUI::minusClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    /*CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);*/

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "10");
}

void Test_CalcUI::multiplyClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    /*CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);*/

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "24");
}

void Test_CalcUI::divideClicked_numberInResultFieldIsCorrect()
{
    //Arrange
    /*CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);*/

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "6");
}
void Test_CalcUI::divideClickedSecondArgIsZero_msgBoxWithErrorShows()
{
    //Arrange
    /*CalcView calcView;
    calcView.show();
    Calc calc;
    CalcPresenter calcPres(&calcView, &calc);*/
    //calcView.setSingleShotMsgError(true);

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "0");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Деление на 0");

}

void Test_CalcUI::inputFirstArgIsNotANumber()
{
    QTest::keyClicks(calcView->LEditFirstArg, "not a number");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTimer::singleShot(200, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    //Act
    inputFirstArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}


void Test_CalcUI::minusClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    inputFirstArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    inputFirstArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    inputFirstArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputSecondArgIsNotANumber()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3");
    QTest::keyClicks(calcView->lEditSecondArg, "not a number");
    QTimer::singleShot(200, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    //Act
    inputSecondArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}


void Test_CalcUI::minusClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    inputSecondArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    inputSecondArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    inputSecondArgIsNotANumber();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //QTimer::singleShot(200, this, SLOT(updateCaption()));

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputFirstArgIsOutOfRange()
{
    QTest::keyClicks(calcView->LEditFirstArg, "2e+308");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputFirstArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::minusClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputFirstArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::multiplyClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputFirstArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::divideClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputFirstArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::inputSecondArgIsOutOfRange()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3");
    QTest::keyClicks(calcView->lEditSecondArg, "2e+308");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputSecondArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::minusClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputSecondArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::multiplyClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputSecondArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::divideClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Act
    inputSecondArgIsOutOfRange();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void  Test_CalcUI::inputFirstArgIsEmpty()
{
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgIsEmpty_setErrorMsg()
{
    //Act
    inputFirstArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedFirstArgIsEmpty_setErrorMsg()
{
    //Act
    inputFirstArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedFirstArgIsEmpty_setErrorMsg()
{
    //Act
    inputFirstArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedFirstArgIsEmpty_setErrorMsg()
{
    //Act
    inputFirstArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void  Test_CalcUI::inputSecondArgIsEmpty()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgIsEmpty_setErrorMsg()
{
    //Act
    inputSecondArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedSecondArgIsEmpty_setErrorMsg()
{
    //Act
    inputSecondArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedSecondArgIsEmpty_setErrorMsg()
{
    //Act
    inputSecondArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedSecondArgIsEmpty_setErrorMsg()
{
    //Act
    inputSecondArgIsEmpty();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputFirstArgWithCommaAsSeparator()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3,2");
    QTest::keyClicks(calcView->lEditSecondArg, "44");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputSecondArgWithCommaAsSeparator()
{
    QTest::keyClicks(calcView->LEditFirstArg, "42");
    QTest::keyClicks(calcView->lEditSecondArg, "4,2");
    QTimer::singleShot(0, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputSecondArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputSecondArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputSecondArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Act
    inputSecondArgWithCommaAsSeparator();
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}


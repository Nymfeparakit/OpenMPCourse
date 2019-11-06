#include "test_calcui.h"
#include "calcpresentermock.h"
#include <QTimer>
#include <QSignalSpy>
#include <QThread>

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
    QTest::qWait(1000);
}

/*void Test_CalcUI::plusClicked_onPlusClickedCalled()
{
    //Arrange
    CalcPresenterMock calcPresMock(calcView);
    QSignalSpy spy(calcView->pushBtnPlus, SIGNAL(clicked()));

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(spy.count(), 1);
    QVERIFY(QObject::connect(calcView->pushBtnPlus,
                                       SIGNAL(clicked()),
                                       &calcPresMock,
                                       SLOT(onPlusClicked()), Qt::UniqueConnection));

}

void Test_CalcUI::minusClicked_onMinusClickedCalled()
{
    //Arrange
    CalcPresenterMock calcPresMock(calcView);
    QSignalSpy spy(calcView->pushBtnMinus, SIGNAL(clicked()));

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(spy.count(), 1);
    QVERIFY(QObject::connect(calcView->pushBtnMinus,
                                       SIGNAL(clicked()),
                                       &calcPresMock,
                                       SLOT(onMinusClicked()), Qt::UniqueConnection));

}

void Test_CalcUI::multiplyClicked_onMultiplyClickedCalled()
{
    //Arrange
    CalcPresenterMock calcPresMock(calcView);
    QSignalSpy spy(calcView->pushBtnMultiply, SIGNAL(clicked()));

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(spy.count(), 1);
    QVERIFY(QObject::connect(calcView->pushBtnMultiply,
                                       SIGNAL(clicked()),
                                       &calcPresMock,
                                       SLOT(onMultiplyClicked()), Qt::UniqueConnection));

}

void Test_CalcUI::divideClicked_onDivideClickedCalled()
{
    //Arrange
    CalcPresenterMock calcPresMock(calcView);
    QSignalSpy spy(calcView->pushBtnDivide, SIGNAL(clicked()));

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(spy.count(), 1);
    QVERIFY(QObject::connect(calcView->pushBtnDivide,
                                       SIGNAL(clicked()),
                                       &calcPresMock,
                                       SLOT(onDivideClicked()), Qt::UniqueConnection));

}

void Test_CalcUI::displayErrorCalled_ErrorMsgWasShown()
{
    //Arrange
    CalcPresenterMock calcPresMock(calcView);

    //Act
    QTimer::singleShot(200, calcView->msgBxError, SLOT(accept()));
    calcPresMock.calcView->displayError("Error");

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Error");

}

void Test_CalcUI::argsWereSet_argumentsReadCorrectrly()
{
    //Arrange
    double a, b;

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(a, 12);
    QCOMPARE(b, 2);
}*/

Test_CalcUI::~Test_CalcUI()
{
    delete calcView;
    //delete calc;
    //delete calcPresenter;
}


void Test_CalcUI::divideClickedSecondArgIsZero_msgBoxWithErrorShows()
{
    //Arrange
    //calcView.setSingleShotMsgError(true);
    double a, b;

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "0");
    QTest::qWait(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Деление на 0");

}

/*void Test_CalcUI::plusClicked_numberInResultFieldIsCorrect()
{
    //Arrange

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::qWait(1000);
    QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "14");
    QTest::qWait(1000);
}

void Test_CalcUI::minusClicked_numberInResultFieldIsCorrect()
{
    //Arrange


    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::qWait(1000);
    QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "10");
    QTest::qWait(1000);
}

void Test_CalcUI::multiplyClicked_numberInResultFieldIsCorrect()
{
    //Arrange


    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::qWait(1000);
   QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "24");
    QTest::qWait(1000);
}

void Test_CalcUI::divideClicked_numberInResultFieldIsCorrect()
{
    //Arrange

    //Act
    QTest::keyClicks(calcView->LEditFirstArg, "12");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::qWait(1000);
  QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);

    //Assert
    QCOMPARE(calcView->lEditRes->text(), "6");
    QTest::qWait(1000);
}

void Test_CalcUI::inputFirstArgIsNotANumber()
{
    QTest::keyClicks(calcView->LEditFirstArg, "not a number");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTest::qWait(1000);
    //QThread::msleep(500);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;
    calcView->pushBtnPlus->setMouseTracking(true);

    //Act
    inputFirstArgIsNotANumber();
    //QTest::mousePress(calcView->pushBtnPlus, Qt::MouseButton::LeftButton);
    //QTest::mouseRelease(calcView->pushBtnPlus, Qt::MouseButton::LeftButton);
  QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}


void Test_CalcUI::minusClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    inputFirstArgIsNotANumber();
  QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    inputFirstArgIsNotANumber();
  QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedFirstArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    inputFirstArgIsNotANumber();
 //  QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputSecondArgIsNotANumber()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3");
    QTest::qWait(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "not a number");
    QTest::qWait(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsNotANumber();
//   QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
   // calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}


void Test_CalcUI::minusClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    inputSecondArgIsNotANumber();
  QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    inputSecondArgIsNotANumber();
  QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedSecondArgIsNotNumber_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    inputSecondArgIsNotANumber();
 //  QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputFirstArgIsOutOfRange()
{
    QTest::keyClicks(calcView->LEditFirstArg, "2e+308");
    QTest::qWait(1000);
    //QThread::msleep(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsOutOfRange();
 //  QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::minusClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::multiplyClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::divideClickedFirstArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::inputSecondArgIsOutOfRange()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3");
    QThread::msleep(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "2e+308");
    QTest::qWait(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::minusClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::multiplyClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void Test_CalcUI::divideClickedSecondArgIsOutOfRange_msgBoxWithErrorShows()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsOutOfRange();
   QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);
    //Assert
    QCOMPARE(calcView->msgBxError->text(), "Аргументы не должны выходить "
                                           "за пределы допустимых значений");
}

void  Test_CalcUI::inputFirstArgIsEmpty()
{
    QTest::keyClicks(calcView->lEditSecondArg, "2");
    QThread::sleep(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedFirstArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedFirstArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedFirstArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void  Test_CalcUI::inputSecondArgIsEmpty()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3");
    QThread::sleep(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedSecondArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedSecondArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedSecondArgIsEmpty_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgIsEmpty();
   QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputFirstArgWithCommaAsSeparator()
{
    QTest::keyClicks(calcView->LEditFirstArg, "3,2");
    QThread::sleep(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "44");
    QTest::qWait(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedFirstArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputFirstArgWithCommaAsSeparator();
    QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::inputSecondArgWithCommaAsSeparator()
{
    QTest::keyClicks(calcView->LEditFirstArg, "42");
    QThread::sleep(1000);
    QTest::keyClicks(calcView->lEditSecondArg, "4,2");
    QTest::qWait(1000);
    QTimer::singleShot(1000, calcView->msgBxError, SLOT(accept()));
}

void Test_CalcUI::plusClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgWithCommaAsSeparator();
    QTest::mouseMove(calcView->pushBtnPlus);
    QTest::mouseClick(calcView->pushBtnPlus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::minusClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgWithCommaAsSeparator();
   QTest::mouseMove(calcView->pushBtnMinus);
    QTest::mouseClick(calcView->pushBtnMinus, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::multiplyClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgWithCommaAsSeparator();
   QTest::mouseMove(calcView->pushBtnMultiply);
    QTest::mouseClick(calcView->pushBtnMultiply, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

void Test_CalcUI::divideClickedSecondArgUsesCommaAsSeparator_setErrorMsg()
{
    //Arrange
    double a, b;

    //Act
    inputSecondArgWithCommaAsSeparator();
   QTest::mouseMove(calcView->pushBtnDivide);
    QTest::mouseClick(calcView->pushBtnDivide, Qt::LeftButton);
    //calcPresenter->takeArguments(a, b);

    //Assert
    QCOMPARE(calcView->msgBxError->text(), "В качестве аргумента должно быть число");
}

*/



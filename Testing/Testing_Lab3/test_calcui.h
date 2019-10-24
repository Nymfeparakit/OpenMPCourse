#ifndef TEST_CALCUI_H
#define TEST_CALCUI_H
#include <QTest>
#include "calcpresenter.h"
#include "calcmock.h"

class Test_CalcUI : public QObject
{
    Q_OBJECT
public:
    Test_CalcUI();
    ~Test_CalcUI();
private slots:
    //void init();
    void initTestCase();
    void cleanup();
    //void cleanupTestCase();

    void plusClicked_onPlusClickedCalled();
    void minusClicked_onMinusClickedCalled();
    void multiplyClicked_onMultiplyClickedCalled();
    void divideClicked_onDivideClickedCalled();

    void argsWereSet_argumentsReadCorrectrly();

    void displayErrorCalled_ErrorMsgWasShown();

    //void plusClicked_numberInResultFieldIsCorrect();

/*void minusClicked_numberInResultFieldIsCorrect();
    void multiplyClicked_numberInResultFieldIsCorrect();
    void divideClicked_numberInResultFieldIsCorrect();*/

    //void divideClickedSecondArgIsZero_msgBoxWithErrorShows();

    void plusClickedFirstArgIsNotNumber_msgBoxWithErrorShows();
    void minusClickedFirstArgIsNotNumber_msgBoxWithErrorShows();
    void multiplyClickedFirstArgIsNotNumber_msgBoxWithErrorShows();
    void divideClickedFirstArgIsNotNumber_msgBoxWithErrorShows();

    void plusClickedSecondArgIsNotNumber_msgBoxWithErrorShows();
    void minusClickedSecondArgIsNotNumber_msgBoxWithErrorShows();
    void multiplyClickedSecondArgIsNotNumber_msgBoxWithErrorShows();
    void divideClickedSecondArgIsNotNumber_msgBoxWithErrorShows();

    void plusClickedFirstArgIsOutOfRange_msgBoxWithErrorShows();
    void minusClickedFirstArgIsOutOfRange_msgBoxWithErrorShows();
    void multiplyClickedFirstArgIsOutOfRange_msgBoxWithErrorShows();
    void divideClickedFirstArgIsOutOfRange_msgBoxWithErrorShows();

    void plusClickedSecondArgIsOutOfRange_msgBoxWithErrorShows();
    void minusClickedSecondArgIsOutOfRange_msgBoxWithErrorShows();
    void multiplyClickedSecondArgIsOutOfRange_msgBoxWithErrorShows();
    void divideClickedSecondArgIsOutOfRange_msgBoxWithErrorShows();

    void plusClickedFirstArgIsEmpty_setErrorMsg();
    void minusClickedFirstArgIsEmpty_setErrorMsg();
    void multiplyClickedFirstArgIsEmpty_setErrorMsg();
    void divideClickedFirstArgIsEmpty_setErrorMsg();

    void plusClickedSecondArgIsEmpty_setErrorMsg();
    void minusClickedSecondArgIsEmpty_setErrorMsg();
    void multiplyClickedSecondArgIsEmpty_setErrorMsg();
    void divideClickedSecondArgIsEmpty_setErrorMsg();

    void plusClickedFirstArgUsesCommaAsSeparator_setErrorMsg();
    void minusClickedFirstArgUsesCommaAsSeparator_setErrorMsg();
    void multiplyClickedFirstArgUsesCommaAsSeparator_setErrorMsg();
    void divideClickedFirstArgUsesCommaAsSeparator_setErrorMsg();

    void plusClickedSecondArgUsesCommaAsSeparator_setErrorMsg();
    void minusClickedSecondArgUsesCommaAsSeparator_setErrorMsg();
    void multiplyClickedSecondArgUsesCommaAsSeparator_setErrorMsg();
    void divideClickedSecondArgUsesCommaAsSeparator_setErrorMsg();
private:
    void inputFirstArgIsNotANumber();
    void inputSecondArgIsNotANumber();
    void inputFirstArgIsOutOfRange();
    void inputSecondArgIsOutOfRange();
    void inputFirstArgIsEmpty();
    void inputSecondArgIsEmpty();
    void inputFirstArgWithCommaAsSeparator();
    void inputSecondArgWithCommaAsSeparator();
    CalcView* calcView;
    CalcMock* calc;
    CalcPresenter* calcPresenter;
};

#endif // TEST_CALCUI_H

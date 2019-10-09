#ifndef TC_H
#define TC_H
#include <QTest>
#include <calcpresenter.h>

class Test_CalcPresenter : public QObject
{
    Q_OBJECT
public:
    Test_CalcPresenter();
    //void setTestData();
private slots:
    //void takeArguments();
    void divide_SecondArgIsZero_ThrowsInvalidArgException();

    void takeArguments_FirstArgIsNotNumber_setErrorMsg();
    void takeArguments_SecondArgIsNotNumber_setErrorMsg();

    void takeArguments_FirstArgIsOutOfRange_setErrorMsg();
    void takeArguments_FirstArgIsOutOfRange_setErrorMsg_data();
    void takeArguments_SecondArgIsOutOfRange_setErrorMsg();
    void takeArguments_SecondArgIsOutOfRange_setErrorMsg_data();

    void takeArguments_FirstArgIsEmpty_setErrorMsg();
    void takeArguments_SecondArgIsEmpty_setErrorMsg();

    void takeArguments_FirstArgUsesSciNotation_ParseArgCorrectly();
    void takeArguments_SecondArgUsesSciNotation_ParseArgCorrectly();

    void takeArguments_FirstArgUsesCommaAsSeparator_setErrorMsg();
    void takeArguments_SecondArgUsesCommaAsSeparator_setErrorMsg();

    void onPlusClicked_NumberArgs_SetCorrectOpResult();
    void onPlusClicked_NumberArgs_SetCorrectOpResult_data();

    void onMinusClicked_NumberArgs_SetCorrectOpResult();
    void onMinusClicked_NumberArgs_SetCorrectOpResult_data();

    void onMultiplyClicked_NumberArgs_SetCorrectOpResult();
    void onMultiplyClicked_NumberArgs_SetCorrectOpResult_data();

    void onDivideClicked_NumberArgs_SetCorrectOpResult();
    void onDivideClicked_NumberArgs_SetCorrectOpResult_data();
};

#endif // TC_H

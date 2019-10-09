#ifndef TC_H
#define TC_H
#include <QTest>
#include <calcpresenter.h>

class TC : public QObject
{
    Q_OBJECT
public:
    TC();
private slots:
    //void takeArguments();
    void divide_SecondArgIsZero_ThrowsInvalidArgException();

    void takeArguments_FirstArgIsNotNumber_setErrorMsg();
    void takeArguments_SecondArgIsNotNumber_setErrorMsg();

    void takeArguments_FirstArgIsOutOfRange_setErrorMsg();
    void takeArguments_SecondArgIsOutOfRange_setErrorMsg();

    void takeArguments_FirstArgIsEmpty_setErrorMsg();
    void takeArguments_SecondArgIsEmpty_setErrorMsg();

    void takeArguments_FirstArgUsesSciNotation_ParseArgCorrectly();
    void takeArguments_SecondArgUsesSciNotation_ParseArgCorrectly();

    void onPlusClicked_NumberArgs_SetCorrectOpResult();
    void onPlusClicked_NumberArgs_SetCorrectOpResult_data();
};

#endif // TC_H

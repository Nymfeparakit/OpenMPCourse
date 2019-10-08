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
    void takeArguments();
    void divide_SecondArgIsZero_ThrowsInvalidArgException();
    //void takeArguments_FirstArgIsNotNumber_
};

#endif // TC_H

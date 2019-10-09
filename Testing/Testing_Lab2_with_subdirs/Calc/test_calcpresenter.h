#ifndef TEST_CALCPRESENTER_H
#define TEST_CALCPRESENTER_H

#include <QtTest>
#include <calcpresenter.h>
#include <calc.h>
#include <calcview.h>

class Test_CalcPresenter : public QObject
{
    Q_OBJECT
public:
    Test_CalcPresenter();
private slots:
    void takeArguments();
};

#endif // TEST_CALCPRESENTER_H

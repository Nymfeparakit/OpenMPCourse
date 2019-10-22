#include "calcview.h"
#include <QApplication>
//#include <QtTest>
//#include "test_calcpresenter.h"
#include "tc.h"
#include "calcviewmock.h"

int main(int argc, char *argv[])
{
    int b = 0;
    QApplication a(argc, argv);
    CalcView v;
    v.show();
    Test_Calc* tc = new Test_Calc();
    QTest::qExec(tc, argc, argv);
    return a.exec();
}

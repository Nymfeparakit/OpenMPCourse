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
    Test_CalcPresenter* tc = new Test_CalcPresenter();
    QTest::qExec(tc, argc, argv);
    return a.exec();
}

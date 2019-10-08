#include "calcview.h"
#include <QApplication>
//#include <QtTest>
//#include "test_calcpresenter.h"
#include "tc.h"

int main(int argc, char *argv[])
{
    int b = 0;
    QApplication a(argc, argv);
    TC* tc = new TC();
    QTest::qExec(tc, argc, argv);
    CalcView w;
    w.show();

    return a.exec();
}

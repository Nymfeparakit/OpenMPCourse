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
    TC* tc = new TC();
    QTest::qExec(tc, argc, argv);
    /*
    CalcView w;
    w.show();
    CalcViewMock calcMock;
    calcMock.firstArg = "1";
    calcMock.secondArg = "2";
    Calc calc;
    CalcPresenter calcPres(&calcMock, &calc);
    calcPres.onPlusClicked();
    */
    return a.exec();
}

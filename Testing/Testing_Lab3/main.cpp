#include "calcview.h"
#include "test_calc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcView w;
    w.show();
    Calc calc;
    CalcPresenter calcPresenter(&w, &calc);
    //Test_Calc* tc = new Test_Calc();
    //QTest::qExec(tc, argc, argv);
    return a.exec();
}

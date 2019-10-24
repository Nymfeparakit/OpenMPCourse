#ifndef CALCPRESENTER_H
#define CALCPRESENTER_H
#include <calc.h>
#include <calcview.h>
#include "calculatorpresenter.h"

class CalcPresenter : public QObject, public CalculatorPresenter
{
    Q_OBJECT
public:
    CalcPresenter(CalculatorView*, Calculator*);
    bool takeArguments(double& a, double &b);
public slots:
    void onPlusClicked();
    void onMinusClicked();
    void onDivideClicked();
    void onMultiplyClicked();
private:
    CalculatorView* calcView;
    Calculator* calc;
};
#endif // CALCPRESENTER_H

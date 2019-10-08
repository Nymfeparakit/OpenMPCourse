#ifndef CALCPRESENTER_H
#define CALCPRESENTER_H
#include <calc.h>
#include <calcview.h>

class CalcPresenter
{
public:
    CalcPresenter(CalculatorView*, Calc*);
    void onPlusClicked();
    void onMinusClicked();
    void onDivideClicked();
    void onMultiplyClicked();
    bool takeArguments(double& a, double &b);
private:
    CalculatorView* calcView;
    Calc* calc;
};
#endif // CALCPRESENTER_H

#ifndef CALCPRESENTER_H
#define CALCPRESENTER_H
#include <calc.h>
#include <calcview.h>

class CalcPresenter
{
public:
    CalcPresenter(CalcView*, Calc*);
    void onPlusClicked();
    void onMinusClicked();
    void onDivideClicked();
    void onMultiplyClicked();
    bool takeArguments(double& a, double &b);
private:
    CalcView* calcView;
    Calc* calc;
};
#endif // CALCPRESENTER_H

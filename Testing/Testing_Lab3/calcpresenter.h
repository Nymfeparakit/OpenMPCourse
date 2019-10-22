#ifndef CALCPRESENTER_H
#define CALCPRESENTER_H
#include <calc.h>
#include <calcview.h>

class CalcPresenter : public QObject
{
    Q_OBJECT
public:
    CalcPresenter(CalculatorView*, Calc*);
    bool takeArguments(double& a, double &b);
public slots:
    void onPlusClicked();
    void onMinusClicked();
    void onDivideClicked();
    void onMultiplyClicked();
private:
    CalculatorView* calcView;
    Calc* calc;
};
#endif // CALCPRESENTER_H

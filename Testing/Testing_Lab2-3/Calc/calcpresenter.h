#ifndef CALCPRESENTER_H
#define CALCPRESENTER_H
#include <calcul.h>
#include <calcview.h>

class CalcPresenter
{
public:
    CalcPresenter(CalcView*);
    void onPlusClicked();
    void onMinusClicked();
    void onDivideClicked();
    void onMultiplyClicked();
private:
    CalcView* calcView;
    Calcul* calc;
};

#endif // CALCPRESENTER_H

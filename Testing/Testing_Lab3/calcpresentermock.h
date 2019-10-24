#ifndef CALCPRESENTERMOCK_H
#define CALCPRESENTERMOCK_H
#include "calculatorpresenter.h"
#include <QObject>
#include "calcview.h"

class CalcPresenterMock : public QObject, public CalculatorPresenter
{
    Q_OBJECT
    friend class Test_CalcUI;
public:
    CalcPresenterMock(CalculatorView*);
public slots:
    void onPlusClicked();
    void onMinusClicked();
    void onDivideClicked();
    void onMultiplyClicked();
private:
    CalculatorView* calcView;
};

#endif // CALCPRESENTERMOCK_H

#ifndef CALCULATORPRESENTER_H
#define CALCULATORPRESENTER_H


class CalculatorPresenter
{
public:
    virtual void onPlusClicked() = 0;
    virtual void onMinusClicked() = 0;
    virtual void onDivideClicked() = 0;
    virtual void onMultiplyClicked() = 0;
    virtual ~CalculatorPresenter() = 0;
};

#endif // CALCULATORPRESENTER_H

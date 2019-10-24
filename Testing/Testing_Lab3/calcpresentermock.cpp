#include "calcpresentermock.h"

CalcPresenterMock::CalcPresenterMock(CalculatorView* _calcView)
    :calcView(_calcView)
{
    connect(calcView->pushBtnPlus, &QPushButton::clicked, this, &CalcPresenterMock::onPlusClicked);
    connect(calcView->pushBtnMinus, &QPushButton::clicked, this, &CalcPresenterMock::onMinusClicked);
    connect(calcView->pushBtnMultiply, &QPushButton::clicked, this, &CalcPresenterMock::onMultiplyClicked);
    connect(calcView->pushBtnDivide, &QPushButton::clicked, this, &CalcPresenterMock::onDivideClicked);
}

void CalcPresenterMock::onPlusClicked()
{

}

void CalcPresenterMock::onMinusClicked()
{

}
void CalcPresenterMock::onDivideClicked()
{

}
void CalcPresenterMock::onMultiplyClicked()
{

}

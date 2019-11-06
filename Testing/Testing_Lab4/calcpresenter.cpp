#include "calcpresenter.h"
#include "cmath"
#include <QDebug>

CalcPresenter::CalcPresenter(CalculatorView* _calcView, Calculator* _calc)
    :calcView(_calcView)
    ,calc(_calc)
{
    QPushButton *btn = calcView->pushBtnPlus;
    //QLineEdit *lEdit = calcView->LEditFirstArg;
    //QString text = lEdit->text();
    QString btnName = calcView->pushBtnPlus->text();
    connect(calcView->pushBtnPlus, &QPushButton::clicked, this, &CalcPresenter::onPlusClicked);
    //connect(calcView->pushBtnPlus, SIGNAL(clicked()), this, SLOT(onPlusClicked()));
    connect(calcView->pushBtnMinus, &QPushButton::clicked, this, &CalcPresenter::onMinusClicked);
    connect(calcView->pushBtnMultiply, &QPushButton::clicked, this, &CalcPresenter::onMultiplyClicked);
    connect(calcView->pushBtnDivide, &QPushButton::clicked, this, &CalcPresenter::onDivideClicked);
}

bool CalcPresenter::takeArguments(double& a, double &b)
{
    //получаем аргументы
    QString aStr = calcView->getFirstArgumentAsString();
    QString bStr = calcView->getSecondArgumentAsString();
    bool ok;//Пытаемся преобразовать в double00
    try
    {
        a = aStr.toDouble(&ok);
        if (std::isinf(a))
            throw std::invalid_argument("Arguments must not exceed acceptable values");
        else if (!ok)
            throw std::invalid_argument("The argument must be a number");

        b = bStr.toDouble(&ok);
        if (std::isinf(b))
            throw std::invalid_argument("Arguments must not exceed acceptable values");
        else if (!ok)
            throw std::invalid_argument("The argument must be a number");
    }
    catch(const std::invalid_argument& e)
    {
       calcView->displayError(e.what());
       return false;
    }
    return true;
}

void CalcPresenter::onPlusClicked()
{
    //qDebug() << QString("onPlusClicked");
    double a,b;
    if (!takeArguments(a, b))
        return;
    double res = calc->sum(a, b);
    calcView->printResult(res);
}
void CalcPresenter::onMinusClicked()
{
    double a,b;
    if (!takeArguments(a, b))
        return;
    double res = calc->subtract(a, b);
    calcView->printResult(res);
}
void CalcPresenter::onDivideClicked()
{
    double a,b;
    if (!takeArguments(a, b))
        return;
    double res = 0;
    try
    {
        res = calc->divide(a, b);
    }
    catch(std::invalid_argument& e)
    {
        calcView->displayError(e.what());
        return;
    }
    calcView->printResult(res);
}
void CalcPresenter::onMultiplyClicked()
{
    double a,b;
    if (!takeArguments(a, b))
        return;
    double res = calc->multiply(a, b);
    calcView->printResult(res);
}

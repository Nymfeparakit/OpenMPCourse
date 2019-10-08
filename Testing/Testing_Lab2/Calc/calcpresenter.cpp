#include "calcpresenter.h"

CalcPresenter::CalcPresenter(CalcView* _calcView, Calc* _calc)
    :calcView(_calcView)
    ,calc(_calc)
{

}

bool CalcPresenter::takeArguments(double& a, double &b)
{
    //получаем аргументы
    //QString aStr = calcView->getFirstArgumentAsString();
    //QString bStr = calcView->getSecondArgumentAsString();
    QString aStr = "1";
    QString bStr = "2";
    bool ok;//Пытаемся преобразовать в double
    try
    {
        a = aStr.toDouble(&ok);
        if (!ok)
            throw std::invalid_argument("В качестве аргумента должно быть число");
        b = bStr.toDouble(&ok);
        if (!ok)
            throw std::invalid_argument("В качестве аргумента должно быть число");
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
    double a,b;
    if (!takeArguments(a, b))
        return;
    calc->sum(a, b);
}
void CalcPresenter::onMinusClicked()
{
    double a,b;
    if (!takeArguments(a, b))
        return;
    calc->subtract(a, b);
}
void CalcPresenter::onDivideClicked()
{
    double a,b;
    if (!takeArguments(a, b))
        return;
    calc->divide(a, b);
}
void CalcPresenter::onMultiplyClicked()
{
    double a,b;
    if (!takeArguments(a, b))
        return;
    calc->multiply(a, b);
}

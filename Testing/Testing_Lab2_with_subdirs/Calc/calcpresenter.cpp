#include "calcpresenter.h"
#include "cmath"

CalcPresenter::CalcPresenter(CalculatorView* _calcView, Calc* _calc)
    :calcView(_calcView)
    ,calc(_calc)
{

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
            throw std::invalid_argument("Аргументы не должны выходить "
                                        "за пределы допустимых значений");
        else if (!ok)
            throw std::invalid_argument("В качестве аргумента должно быть число");

        b = bStr.toDouble(&ok);
        if (std::isinf(b))
            throw std::invalid_argument("Аргументы не должны выходить "
                                        "за пределы допустимых значений");
        else if (!ok)
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
    double res = calc->divide(a, b);
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

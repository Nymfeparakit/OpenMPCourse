#ifndef CALCULATORVIEW_H
#define CALCULATORVIEW_H
#include <QString>
#include <QObject>

class CalculatorView
{
    //Q_OBJECT
public:
    virtual void printResult(double result) = 0;
    virtual void displayError(QString message) = 0;
    virtual QString getFirstArgumentAsString() = 0;
    virtual QString getSecondArgumentAsString() = 0;
    virtual ~CalculatorView() = 0;
};

#endif // CALCULATORVIEW_H

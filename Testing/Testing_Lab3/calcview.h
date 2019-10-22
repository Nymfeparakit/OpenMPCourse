#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include "CalculatorView.h"
//#include "calcpresenter.h"


//class Calc;

namespace Ui {
class CalcView;
}

class CalcView : public QMainWindow, public CalculatorView
{
    Q_OBJECT

public:
    explicit CalcView(QWidget *parent = nullptr);
    ~CalcView();
    void printResult(double result);
    void displayError(QString message);
    QString getFirstArgumentAsString();
    QString getSecondArgumentAsString();

private:
    QTextEdit* MsgField;
    Ui::CalcView *ui;
    //CalcPresenter *calcPresenter;
};

#endif // CALCVIEW_H

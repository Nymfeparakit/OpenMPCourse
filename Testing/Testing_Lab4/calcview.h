#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "CalculatorView.h"
//#include "calcpresenter.h"


//class Calc;

namespace Ui {
class CalcView;
}

class CalcView : public QMainWindow, public CalculatorView
{
    Q_OBJECT

    friend class Test_CalcUI;

public:
    explicit CalcView(QWidget *parent = nullptr);
    ~CalcView();
    void printResult(double result);
    void displayError(QString message);
    QString getFirstArgumentAsString();
    QString getSecondArgumentAsString();
    void setFirstArgument(QString arg);
    void setSecondArgument(QString arg);
    void setSingleShotMsgError(bool);
    QLineEdit* getResField();
    QPushButton* getPlusBtn();

private:
    QTextEdit* MsgField;
    Ui::CalcView *ui;
    QLineEdit *LEditFirstArg;
    QLineEdit *lEditSecondArg;
    QLineEdit *lEditRes;
    QMessageBox *msgBxError;
    bool singleShotMsgError = false;
    //CalcPresenter *calcPresenter;
};

#endif // CALCVIEW_H

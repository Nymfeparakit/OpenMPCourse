#include "calcview.h"
#include "ui_calcview.h"
#include <QMessageBox>
class CalcPresenter;

CalcView::CalcView(QWidget *pwgt)
    :ui(new Ui::CalcView)
{

    //Calc calc;
    //calcPresenter = new CalcPresenter(this, &calc);
    //CalcPresenter c(this, &calc);
    ui->setupUi(this);
    pushBtnPlus = ui->pushBtnPlus;
    pushBtnMinus = ui->pushBtnMinus;
    pushBtnMultiply = ui->pushBtnMultiply;
    pushBtnDivide = ui->pushBtnDivide;
    LEditFirstArg = ui->lineEFirstArg;
    lEditSecondArg = ui->lineESecondArg;
    lEditRes = ui->lineEResult;
    msgBxError = nullptr;
    //LEditFirstArg->setText("aaa");
    /*connect(ui->pushBtnPlus, &QPushButton::clicked, calcPresenter, &CalcPresenter::onPlusClicked);
    connect(ui->pushBtnMinus, &QPushButton::clicked, calcPresenter, &CalcPresenter::onMinusClicked);
    connect(ui->pushBtnMultiply, &QPushButton::clicked, calcPresenter, &CalcPresenter::onMultiplyClicked);
    connect(ui->pushBtnDivide, &QPushButton::clicked, calcPresenter, &CalcPresenter::onDivideClicked);
    */
}

CalcView::~CalcView()
{
    delete ui;
}

void CalcView::printResult(double result)
{
    ui->lineEResult->setText(QString::number(result));
}
void CalcView::displayError(QString message)
{
    //QMessageBox msgBox;
    msgBxError = new QMessageBox();
    msgBxError->setText(message);
    int ret = msgBxError->exec();
    delete msgBxError;
}
QString CalcView::getFirstArgumentAsString()
{
    return ui->lineEFirstArg->text();
}
QString CalcView::getSecondArgumentAsString()
{
    return ui->lineESecondArg->text();
}
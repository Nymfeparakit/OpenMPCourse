#include "calcview.h"
//#include "ui_calcview.h"

CalcView::CalcView(QWidget *pwgt)
    //ui(new Ui::CalcView)
{
    MsgField = new QTextEdit;
    MsgField->setReadOnly(true);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(MsgField);
    setLayout(vBoxLayout);
    int a = 0;
    //ui->setupUi(this);
}

CalcView::~CalcView()
{
    //delete ui;
}

void CalcView::printResult(double result)
{

}
void CalcView::displayError(QString message)
{

}
QString CalcView::getFirstArgumentAsString()
{

}
QString CalcView::getSecondArgumentAsString()
{

}

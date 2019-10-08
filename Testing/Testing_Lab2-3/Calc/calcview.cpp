#include "calcview.h"
#include "ui_calc.h"

CalcView::CalcView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calc)
{
    ui->setupUi(this);
}

CalcView::~CalcView()
{
    delete ui;
}

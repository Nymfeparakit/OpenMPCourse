#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

namespace Ui {
class Calc;
}

class CalcView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalcView(QWidget *parent = nullptr);
    ~CalcView();

private:
    Ui::Calc *ui;
};

#endif // CALC_H

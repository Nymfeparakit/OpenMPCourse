#ifndef TEST_CALCUI_H
#define TEST_CALCUI_H
#include <QTest>

class Test_CalcUI : public QObject
{
    Q_OBJECT
public:
    Test_CalcUI();
private slots:
    void plusClicked_numberInResultFieldIsCorrect();
    void minusClicked_numberInResultFieldIsCorrect();
    void multiplyClicked_numberInResultFieldIsCorrect();
    void divideClicked_numberInResultFieldIsCorrect();
    void divideClickedSecondArgIsZero_msgBoxWithErrorShows();
};

#endif // TEST_CALCUI_H

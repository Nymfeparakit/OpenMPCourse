#include <QTimer>
#include "catch_qt.h"
#include "calcpresenter.h"


SCENARIO( "Add two numbers", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = GENERATE(as<std::string>{}, "50.2", "-34");
    std::string secondArg = GENERATE(as<std::string>{}, "20.3", "200");

    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press add" ) {

                view.pushBtnPlus->clicked();

                double result = stod(firstArg) + stod(secondArg);
                THEN("the result should be " + std::to_string(result) + " on the screen") {

                    REQUIRE( view.getResField()->text() == QString::number(result) );

                }

            }

        }

    }

}

SCENARIO( "Substract two numbers", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = GENERATE(as<std::string>{}, "50.3", "-34.0");
    std::string secondArg = GENERATE(as<std::string>{}, "20", "200.2");

    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press minus" ) {

                view.pushBtnMinus->clicked();

                double result = stod(firstArg) - stod(secondArg);
                THEN("the result should be " + std::to_string(result) + " on the screen") {

                    REQUIRE( view.getResField()->text() == QString::number(result) );

                }

            }

        }

    }

}

SCENARIO( "Multiply two numbers", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = GENERATE(as<std::string>{}, "50.3", "-34");
    std::string secondArg = GENERATE(as<std::string>{}, "20.2", "200");

    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press multiply" ) {

                view.pushBtnMultiply->clicked();

                double result = stod(firstArg) * stod(secondArg);
                THEN("the result should be " + std::to_string(result) + " on the screen") {

                    REQUIRE( view.getResField()->text() == QString::number(result) );

                }

            }

        }

    }

}

SCENARIO( "Divide two numbers", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = GENERATE(as<std::string>{}, "50.3", "-34");
    std::string secondArg = GENERATE(as<std::string>{}, "20.2", "200");

    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press divide" ) {

                view.pushBtnDivide->clicked();

                double result = stod(firstArg) / stod(secondArg);
                THEN("the result should be " + std::to_string(result) + " on the screen") {

                    REQUIRE( view.getResField()->text() == QString::number(result) );

                }

            }

        }

    }

}

SCENARIO( "Divide by zero", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = "2";
    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        std::string secondArg = "0";
        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press divide" ) {

                QTimer::singleShot(500, view.msgBxError, SLOT(accept()));
                view.pushBtnDivide->clicked();

                QString errorMsg = "Divide by zero";
                THEN("The error shown should be: " + errorMsg) {

                    REQUIRE( view.msgBxError->text() == errorMsg );

                }

            }

        }

    }

}

SCENARIO( "First argument is not a number", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = "not a number";
    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        std::string secondArg = "2";
        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press plus" ) {

                QTimer::singleShot(500, view.msgBxError, SLOT(accept()));
                view.pushBtnPlus->clicked();

                QString errorMsg = "The argument must be a number";
                THEN("The error shown should be: " + errorMsg) {

                    REQUIRE( view.msgBxError->text() == errorMsg );

                }

            }

        }

    }

}

SCENARIO( "First argument is out of range", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = "2e+308";
    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        std::string secondArg = "2";
        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press plus" ) {

                QTimer::singleShot(500, view.msgBxError, SLOT(accept()));
                view.pushBtnPlus->clicked();

                QString errorMsg = "Arguments must not exceed acceptable values";
                THEN("The error shown should be: " + errorMsg) {

                    REQUIRE( view.msgBxError->text() == errorMsg );

                }

            }

        }

    }

}

SCENARIO( "Second argument is empty", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = "2";
    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));
            WHEN( "I press plus" ) {

                QTimer::singleShot(500, view.msgBxError, SLOT(accept()));
                view.pushBtnPlus->clicked();

                QString errorMsg = "The argument must be a number";
                THEN("The error shown should be: " + errorMsg) {

                    REQUIRE( view.msgBxError->text() == errorMsg );

                }

            }

    }

}

SCENARIO( "First argument uses comma as a separator", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    std::string firstArg = "2,2";
    GIVEN( "I have entered " + firstArg + " into the calculator" ) {
        view.setFirstArgument(QString::fromUtf8(firstArg.c_str()));

        std::string secondArg = "2";
        AND_GIVEN("I have entered " + secondArg + " into the calculator") {
            view.setSecondArgument(QString::fromUtf8(secondArg.c_str()));
            WHEN( "I press plus" ) {

                QTimer::singleShot(500, view.msgBxError, SLOT(accept()));
                view.pushBtnPlus->clicked();

                QString errorMsg = "The argument must be a number";
                THEN("The error shown should be: " + errorMsg) {

                    REQUIRE( view.msgBxError->text() == errorMsg );

                }

            }

        }

    }

}




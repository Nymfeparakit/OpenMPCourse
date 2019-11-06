#include "catch_qt.h"
#include "calcpresenter.h"

SCENARIO( "Add two numbers", "" ) {

    CalcView view;
    view.show();
    Calc calc;
    CalcPresenter calcPresenter(&view, &calc);

    GIVEN( "I have entered 50 into the calculator" ) {
        view.setFirstArgument("50");

        AND_GIVEN("I have entered 70 into the calculator") {
            view.setSecondArgument("70");
            WHEN( "I press add" ) {

                view.pushBtnPlus->clicked();

                THEN("the result should be 120 on the screen") {

                    REQUIRE( view.getResField()->text() == 120 );

                }

            }

        }

    }



}

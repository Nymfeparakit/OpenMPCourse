#define CATCH_CONFIG_RUNNER
#include <QApplication>
#include "calcpresenter.h"
#include "tests.cpp"

int main( int argc, char* argv[] ) {

    QApplication app(argc, argv);
    //CalcView w;
    //w.show();
    //Calc calc;
    //CalcPresenter calcPresenter(&w, &calc);

    int result = Catch::Session().run( argc, argv );

    return ( result < 0xff ? result : 0xff );

}

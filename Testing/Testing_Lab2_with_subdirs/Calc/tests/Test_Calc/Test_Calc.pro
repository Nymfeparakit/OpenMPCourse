TARGET = Test_Calc

CONFIG += c++11

QT      += testlib

HEADERS += \
    ../../calcpresenter.h \
    ../../calcview.h \
    ../../calc.h \
    ../../calcviewmock.h
    ../calculatorview.h

SOURCES += \
    ../../calcpresenter.cpp \
    ../../calcview.cpp \
    ../../calc.cpp \
    ../../calcviewmock.cpp
    ../calculatorview.cpp

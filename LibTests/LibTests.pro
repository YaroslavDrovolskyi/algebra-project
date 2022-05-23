QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_modarithmetictest.cpp

win32: LIBS += -L$$PWD/../ModularArithmeticLib/ -lModularArithmeticLib

INCLUDEPATH += $$PWD/../ModularArithmeticLib
DEPENDPATH += $$PWD/../ModularArithmeticLib

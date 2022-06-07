QT -= gui

TEMPLATE = lib
DEFINES += MODULARARITHMETICLIB_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BigInt.cpp \
    BigModInt.cpp \
    EulerPhiCarmichaelLambda.cpp \
    FiniteField.cpp \
    ModPolynomial.cpp \
    Polynomial.cpp \
    discrete_log.cpp \
    pollard_fact.cpp

HEADERS += \
    BigInt.h \
    BigModInt.h \
    EulerPhiCarmichaelLambda.h \
    FiniteField.h \
    IrreduciblePolynomial.h \
    ModPolynomial.h \
    ModularArithmeticLib_global.h \
    Polynomial.h \
    PrimeProbabilityChecker.h \
    discrete_log.h \
    pollard_fact.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

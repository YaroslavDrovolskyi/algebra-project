#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QVector>
#include <QString>
#include "BigModInt.h"
#include "Polynomial.h"
#include "ModPolynomial.h"

class NumberCalculator
{
public:
    NumberCalculator();
    const QVector<QString> operations_names;
    const QVector<QString> algorithms_names;

    QString calculate(std::size_t op_index, const BigModInt& a, const BigModInt& b);
    QString calculate(std::size_t algo_index, const BigModInt& a);
};


class PolynomialRingCalculator{
public:
    PolynomialRingCalculator();
    const QVector<QString> operations_names;

    QString calc(std::size_t op_index, const Polynomial& a, const Polynomial& b);
    QString calcDerivative(const Polynomial& a);
    QString calcValue(Polynomial a, BigModInt point);
    std::pair<QString, QString> calcFractionRemainer(Polynomial a, Polynomial b);
    QString calcCyclotomicPolynomial(BigInt modulus, BigInt order);
};



class PolynomialFieldCalculator{
public:
    PolynomialFieldCalculator();
    const QVector<QString> algorithms_names;

    QString calc(std::size_t op_index, Polynomial irreducible_pol, ModPolynomial a);
};

#endif // CALCULATOR_H

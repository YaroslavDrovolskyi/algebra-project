#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QVector>
#include <QString>
#include "BigModInt.h"

class Calculator
{
public:
    Calculator();
    const QVector<QString> operations_names;

    BigModInt calculate(std::size_t op_index, const BigModInt& a, const BigModInt& b);
};

#endif // CALCULATOR_H

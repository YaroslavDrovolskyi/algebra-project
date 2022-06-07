#ifndef CYCLOTOMICPOLYNOMIAL_H
#define CYCLOTOMICPOLYNOMIAL_H

#include <vector>

#include "ModularArithmeticLib_global.h"
#include "BigModInt.h"
#include "EulerPhiCarmichaelLambda.h"

class MODULARARITHMETICLIB_EXPORT CyclotomicPolynomial {
private:
    std::vector<BigModInt> polynomialDivision(std::vector<BigModInt> a, std::vector<BigModInt> b);
public:
    std::vector<BigModInt> cyclotomicPolynomial(BigInt n);
};


#endif //CYCLOTOMICPOLYNOMIAL_H
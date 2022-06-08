#ifndef CYCLOTOMICPOLYNOMIAL_H
#define CYCLOTOMICPOLYNOMIAL_H

#include <vector>

#include "ModularArithmeticLib_global.h"
#include "BigModInt.h"
#include "Polynomial.h"
#include "EulerPhiCarmichaelLambda.h"

class MODULARARITHMETICLIB_EXPORT CyclotomicPolynomial {
private:
    struct term {
        BigInt coefficient;
        BigInt exponent;
    };
    static Polynomial toPolynomial(std::vector<term> p, BigInt m);
    static std::vector<term> polynomialSupplement(std::vector<term> a, std::vector<term> b, term term);
    static std::vector<term> polynomialDivision(std::vector<term> a, std::vector<term> b);
    static std::vector<term> cyclotomicPolynomialRecursive(BigInt n, BigInt m);
public:
    static Polynomial cyclotomicPolynomial(BigInt n, BigInt m);
};


#endif //CYCLOTOMICPOLYNOMIAL_H

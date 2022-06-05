#ifndef EULERPHICARMICHAELLAMBDA_H
#define EULERPHICARMICHAELLAMBDA_H

#include <vector>

#include "ModularArithmeticLib_global.h"
#include "BigInt.h"

class MODULARARITHMETICLIB_EXPORT EulerPhiCarmichaelLambda {
private:
    struct primeFactors {
        BigInt base;
        BigInt exponent;
    };
    static std::vector<primeFactors> primeFactorization(BigInt n);
    static BigInt sqrt(BigInt n);
    static BigInt gcd(BigInt a, BigInt b);
    static BigInt lcm(BigInt a, BigInt b);
public:
    static BigInt eulerPhi(BigInt n);
    static BigInt carmichaelLambda(BigInt n);
};


#endif //EULERPHICARMICHAELLAMBDA_H

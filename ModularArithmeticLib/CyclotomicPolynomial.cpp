#include "CyclotomicPolynomial.h"

#define EPCL EulerPhiCarmichaelLambda

std::vector<BigModInt> CyclotomicPolynomial::polynomialDivision(std::vector<BigModInt> a, std::vector<BigModInt> b) {

}

std::vector<BigModInt> CyclotomicPolynomial::cyclotomicPolynomial(BigInt n) {
    if (n <= 0) throw std::invalid_argument("Only positive integers");
    if (n == 1) {
        // Polynomial: x - 1
        std::vector<BigModInt> p = {{1,  1},
                                    {-1, 0}};
        return p;
    }

    std::vector<EPCL::primeFactors> factors = EPCL::primeFactorization(n);
    if (factors.size() == 1 && factors[0].base != 2 && factors[0].exponent == 1) {
        // n prime
        std::vector<BigModInt> p;
        for (BigInt i = 0; i < n; i++) p.emplace_back(1, i);
        std::reverse(p.begin(), p.end());
        return p;
    }
    else if (factors.size() == 2 && factors[0].base == 2 && factors[0].exponent == 1 && factors[1].exponent == 1) {
        // n = 2p
        std::vector<BigModInt> p;
        BigInt coefficient = -1;
        for (BigInt i = 0; i < factors[1].exponent; i++) {
            coefficient = coefficient * -1;
            p.emplace_back(coefficient, i);
        }
        std::reverse(p.begin(), p.end());
        return p;
    }
    else if (factors.size() == 1 && factors[0].base == 2) {
        // n = 2^h
        std::vector<BigModInt> p;
        p.emplace_back(1, pow(2, factors[0].exponent - 1));
        p.emplace_back(1, 0);
        return p;
    }
    else if (factors.size() == 1 && factors[0].base != 2) {
        // n = p^k
        std::vector<BigModInt> p;
        for (BigInt i = 0; i < factors[0].base; i++)
            p.emplace_back(1, i * pow(factors[0].base, factors[0].exponent - 1));
        std::reverse(p.begin(), p.end());
        return p;
    }
    else if (factors.size() == 2 && factors[0].base == 2) {
        // n = 2^h * p^k
        std::vector<BigModInt> p;
        BigInt coefficient = -1;
        BigInt twoExp = pow(2, factors[0].exponent - 1);
        for (BigInt i = 0; i < factors[1].base; i++) {
            coefficient = coefficient * -1;
            p.emplace_back(coefficient, i * twoExp * pow(factors[1].base, factors[1].exponent - 1));
        }
        return p;
    }

    // General Case
    std::vector<BigModInt> p = {{1,  n},
                                {-1, 0}};
    for (int i = 0; i < factors.size(); i++) {
        for (BigInt y = 0; y < factors[i].exponent; y++) {
            auto temp = cyclotomicPolynomial(i);
            p = polynomialDivision(p, temp);
        }
    }
    return p;
}

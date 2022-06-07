#include "CyclotomicPolynomial.h"

#define EPCL EulerPhiCarmichaelLambda

std::vector<BigModInt> CyclotomicPolynomial::polynomialSupplement(std::vector<BigModInt> a, std::vector<BigModInt> b, BigModInt term) {
    for(int i=0; i<b.size(); i++) {
        b[i].setNumber(b[i].getNumber() * term.getNumber() * -1);
        b[i].setModulus(b[i].getModulus() + term.getModulus());
    }
    std::vector<BigModInt> result;
    int aCount = a.size();
    int bCount = b.size();
    while (aCount > 0 || bCount > 0) {
        if (aCount == 0) {
            result.emplace_back(b[bCount - 1]);
            bCount--;
        }
        else if (bCount == 0) {
            result.emplace_back(a[aCount - 1]);
            aCount--;
        } else {
            auto polyTerm = b[bCount - 1];
            auto thisTerm = a[aCount - 1];
            if (thisTerm.getModulus() == polyTerm.getModulus()) {
                BigModInt t = {polyTerm.getNumber()+thisTerm.getNumber(), thisTerm.getModulus()};
                if (t.getNumber() != 0) result.emplace_back(t);
                aCount--;
                bCount--;
            } else if (thisTerm.getModulus() < polyTerm.getModulus()) {
                result.emplace_back(thisTerm);
                aCount--;
            } else {
                result.emplace_back(polyTerm);
                bCount--;
            }
        }
    }
    return result;
}

std::vector<BigModInt> CyclotomicPolynomial::polynomialDivision(std::vector<BigModInt> a, std::vector<BigModInt> b) {
    std::vector<BigModInt> result;
    BigInt lcb = b[0].getNumber();
    BigInt db = b[0].getModulus();
    while (a[0].getModulus() >= db) {
        BigInt lca = b[0].getNumber();
        BigInt s = lca / lcb;
        BigModInt term = {s, a[0].getModulus() - db};
        result.emplace_back(term);
        a = polynomialSupplement(a, b, term);
    }
    return result;
}

std::vector<BigModInt> CyclotomicPolynomial::cyclotomicPolynomial(BigInt n, BigInt m) {
    if (n <= 0) throw std::invalid_argument("Only positive integers");
    if (m < n-1) throw std::invalid_argument("Module cannot be less than order");
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
        std::reverse(p.begin(), p.end());
        return p;
    }

    // General Case
    std::vector<BigModInt> p = {{1,  n},
                                {-1, 0}};
    p = polynomialDivision(p, cyclotomicPolynomial(1, m));
    for (int i = 0; i < factors.size(); i++) {
        for (BigInt y = 0; y < factors[i].exponent; y++) {
            auto temp = cyclotomicPolynomial(factors[i].base, m);
            p = polynomialDivision(p, temp);
        }
    }
    return p;
}

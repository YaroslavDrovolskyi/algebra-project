#include "CyclotomicPolynomial.h"

#define EPCL EulerPhiCarmichaelLambda
#define term CyclotomicPolynomial::term

Polynomial CyclotomicPolynomial::toPolynomial(std::vector<term> p, BigInt m) {
    std::string tempString;
    tempString.clear();
    for(int i=0; i<p.size(); i++) {
        if(p[i].exponent == 0) tempString += p[i].coefficient.GetString();
        else tempString += p[i].coefficient.GetString() + "x^" + p[i].exponent.GetString();
    }
    return Polynomial(tempString, m);
}

std::vector<term> CyclotomicPolynomial::polynomialSupplement(std::vector<term> a, std::vector<term> b, term termToAdd) {
    for(int i=0; i<b.size(); i++) {
        b[i].coefficient = b[i].coefficient * termToAdd.coefficient * -1;
        b[i].exponent = b[i].exponent + termToAdd.exponent;
    }
    std::vector<term> result;
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
            if (thisTerm.exponent == polyTerm.exponent) {
                term t = {polyTerm.coefficient+thisTerm.coefficient, thisTerm.exponent};
                if (t.coefficient != 0) result.emplace_back(t);
                aCount--;
                bCount--;
            } else if (thisTerm.exponent < polyTerm.exponent) {
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

std::vector<term> CyclotomicPolynomial::polynomialDivision(std::vector<term> a, std::vector<term> b) {
    std::vector<term> result;
    BigInt lcb = b[0].coefficient;
    BigInt db = b[0].exponent;
    while (a[0].exponent >= db) {
        BigInt lca = b[0].coefficient;
        BigInt s = lca / lcb;
        term termTemp = {s, a[0].exponent - db};
        result.emplace_back(termTemp);
        a = polynomialSupplement(a, b, termTemp);
    }
    return result;
}

std::vector<term> CyclotomicPolynomial::cyclotomicPolynomialRecursive(BigInt n, BigInt m) {
    if (n <= 0) throw std::invalid_argument("Only positive integers");
    //if (m < n-1) throw std::invalid_argument("Module cannot be less than order");
    if (n == 1) {
        // Polynomial: x - 1
        std::vector<term> p = {{1,  1},
                                    {-1, 0}};
        return p;
    }

    std::vector<EPCL::primeFactors> factors = EPCL::primeFactorization(n);
    if (factors.size() == 1 && factors[0].base != 2 && factors[0].exponent == 1) {
        // n prime
        std::vector<term> p;
        for (BigInt i = 0; i < n; i++) p.emplace_back(term{1, i});
        std::reverse(p.begin(), p.end());
        return p;
    }
    else if (factors.size() == 2 && factors[0].base == 2 && factors[0].exponent == 1 && factors[1].exponent == 1) {
        // n = 2p
        std::vector<term> p;
        BigInt coefficient = -1;
        for (BigInt i = 0; i < factors[1].exponent; i++) {
            coefficient = coefficient * -1;
            p.emplace_back(term{coefficient, i});
        }
        std::reverse(p.begin(), p.end());
        return p;
    }
    else if (factors.size() == 1 && factors[0].base == 2) {
        // n = 2^h
        std::vector<term> p;
        p.emplace_back(term{1, pow(2, factors[0].exponent - 1)});
        p.emplace_back(term{1, 0});
        return p;
    }
    else if (factors.size() == 1 && factors[0].base != 2) {
        // n = p^k
        std::vector<term> p;
        for (BigInt i = 0; i < factors[0].base; i++)
            p.emplace_back(term{1, i * pow(factors[0].base, factors[0].exponent - 1)});
        std::reverse(p.begin(), p.end());
        return p;
    }
    else if (factors.size() == 2 && factors[0].base == 2) {
        // n = 2^h * p^k
        std::vector<term> p;
        BigInt coefficient = -1;
        BigInt twoExp = pow(2, factors[0].exponent - 1);
        for (BigInt i = 0; i < factors[1].base; i++) {
            coefficient = coefficient * -1;
            p.emplace_back(term{coefficient, i * twoExp * pow(factors[1].base, factors[1].exponent - 1)});
        }
        std::reverse(p.begin(), p.end());
        return p;
    }

    // General Case
    std::vector<term> p = {{1,  n},
                                {-1, 0}};
    p = polynomialDivision(p, cyclotomicPolynomialRecursive(1, m));
    for (int i = 0; i < factors.size(); i++) {
        for (BigInt y = 0; y < factors[i].exponent; y++) {
            auto temp = cyclotomicPolynomialRecursive(factors[i].base, m);
            p = polynomialDivision(p, temp);
        }
    }
    return p;
}

Polynomial CyclotomicPolynomial::cyclotomicPolynomial(BigInt n, BigInt m) {
    return toPolynomial(cyclotomicPolynomialRecursive(n, m), m);
}

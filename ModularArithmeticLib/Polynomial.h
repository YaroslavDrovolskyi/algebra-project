#pragma once
#include <iostream>
#include <vector>
#include "FiniteField.h"
#include "BigModInt.h"
#include "ModularArithmeticLib_global.h"

using number = double;

class MODULARARITHMETICLIB_EXPORT Polynomial {
private:
    std::vector<BigModInt> polynomial;
    BigInt modulus;
    Polynomial removeZeros();

    std::string numberToSting(BigModInt);
    BigModInt pow(BigModInt value, int i);
    bool isCorrect(std::string input);
    Polynomial(std::vector<BigModInt> pol);
    Polynomial(std::vector<BigModInt> pol, BigInt modulus);
    void setPolynomial(std::vector<BigModInt> pol) {
        polynomial = pol;
        if(!pol.empty())
            this->modulus = pol[0].getModulus();
    }
public:
    //friend class ModPolynomial;
    Polynomial() {
        polynomial = std::vector<BigModInt>();
    }
    BigInt getFieldModulus() const {
        return modulus;
    }
    Polynomial(std::vector<BigInt> pol, BigInt modulus);

    Polynomial(std::string pol, BigInt modulus);


    std::vector<BigModInt> getPolynomial() const{
        return polynomial;
    }

    BigModInt valueAtPoint(BigModInt point);
    Polynomial differentiation();

    std::pair<Polynomial, Polynomial> divide(Polynomial& pol); // we get fraction and remainder as the return values
    Polynomial gcd(Polynomial& pol);

    Polynomial operator+(const Polynomial& second)const;
    Polynomial operator-(const Polynomial& second)const;
    Polynomial operator*(const Polynomial& second)const;
    Polynomial operator=(const Polynomial& second);

    std::string toString() const;

    friend std::ostream& operator<< (std::ostream& out, const Polynomial& a);
};

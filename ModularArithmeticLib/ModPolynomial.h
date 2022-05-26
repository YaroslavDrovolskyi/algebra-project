#pragma once
#include <iostream>
#include <vector>
#include "FiniteField.h"
#include "BigModInt.h"
#include "ModularArithmeticLib_global.h"

class MODULARARITHMETICLIB_EXPORT ModPolynomial{
private:
    std::vector<BigModInt> modPolynomial;
    ModPolynomial removeZeros();
    bool isCorrect(std::string);
public:
    ModPolynomial() {
        modPolynomial = std::vector<BigModInt>();
    }

    ModPolynomial(std::vector<BigModInt> pol) {
        modPolynomial = pol;
    }

    ModPolynomial(std::string pol);

    void setModPolynomial(std::vector<BigModInt> pol) {
        modPolynomial = pol;
    }

    std::vector<BigModInt> getModPolynomial() {
        return modPolynomial;
    }

    std::pair<ModPolynomial, ModPolynomial> divide(ModPolynomial& pol); // we get fraction and remainder as the return values

    ModPolynomial inversePolynomial(ModPolynomial& modulus);

    ModPolynomial operator*(const ModPolynomial& second);
    ModPolynomial operator-(const ModPolynomial& second)const;

    std::string toString();

    friend std::ostream& operator<< (std::ostream& out, ModPolynomial& a);
};

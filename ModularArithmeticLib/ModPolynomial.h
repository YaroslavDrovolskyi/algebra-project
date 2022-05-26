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

public:
    ModPolynomial() {
        modPolynomial = std::vector<BigModInt>();
    }

    ModPolynomial(std::vector<BigModInt> pol) {
        modPolynomial = pol;
    }

    void setModPolynomial(std::vector<BigModInt> pol) {
        modPolynomial = pol;
    }

    std::vector<BigModInt> getModPolynomial() {
        return modPolynomial;
    }

    std::pair<ModPolynomial, ModPolynomial> divide(ModPolynomial& pol); // we get fraction and remainder as the return values

    ModPolynomial inversePolynomial(ModPolynomial& modulus, FiniteField num);

    ModPolynomial operator*(const ModPolynomial& second);
    ModPolynomial operator-(const ModPolynomial& second)const;
};

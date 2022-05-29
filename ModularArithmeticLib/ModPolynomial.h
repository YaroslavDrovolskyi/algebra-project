#pragma once
#include <iostream>
#include <vector>
#include "Polynomial.h"
#include "ModularArithmeticLib_global.h"

class MODULARARITHMETICLIB_EXPORT ModPolynomial{
private:
    Polynomial value;
    Polynomial modulus;

public:
    ModPolynomial() {
    }

    ModPolynomial(Polynomial value, Polynomial modulus);


    Polynomial getValue() const{
        return value;
    }
    Polynomial getModulus() const {
        return modulus;
    }


    ModPolynomial inversePolynomial();
    /*
    ModPolynomial operator*(const ModPolynomial& second);
    ModPolynomial operator-(const ModPolynomial& second)const;
    std::string toString();
    */
    //friend std::ostream& operator<< (std::ostream& out, ModPolynomial& a);

};

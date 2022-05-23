#pragma once
#include <iostream>
#include <vector>
#include "ModularArithmeticLib_global.h"

using number = double;

class MODULARARITHMETICLIB_EXPORT Polynomial {
private:
	std::vector<number> polynomial;

	Polynomial removeZeros();
public:
	Polynomial() {
		polynomial = std::vector<number>();
	}

	Polynomial(std::vector<number> pol) {
		polynomial = pol;
	}

	void setPolynomial(std::vector<number> pol) {
		polynomial = pol;
	}

	std::vector<number> getPolynomial() {
		return polynomial;
	}

	number valueAtPoint(number point);
	Polynomial differentiation();

	std::pair<Polynomial, Polynomial> divide(Polynomial& pol); // we get fraction and remainder as the return values
	Polynomial gcd(Polynomial& pol);

	Polynomial operator+(const Polynomial& second)const;
	Polynomial operator-(const Polynomial& second)const;
	Polynomial operator*(const Polynomial& second)const;
};

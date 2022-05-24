#pragma once
#include <iostream>
#include <vector>
#include "FiniteField.h"
#include "BigModInt.h"

using number = BigModInt;

class ModPolynomial {
private:
	std::vector<number> modPolynomial;
	ModPolynomial removeZeros();

public:
	ModPolynomial() {
		modPolynomial = std::vector<number>();
	}

	ModPolynomial(std::vector<number> pol) {
		modPolynomial = pol;
	}

	void setModPolynomial(std::vector<number> pol) {
		modPolynomial = pol;
	}

	std::vector<number> getModPolynomial() {
		return modPolynomial;
	}

	std::pair<ModPolynomial, ModPolynomial> divide(ModPolynomial& pol); // we get fraction and remainder as the return values

	ModPolynomial inversePolynomial(ModPolynomial& modulus, FiniteField num);

	ModPolynomial operator*(const ModPolynomial& second)const;
	ModPolynomial operator-(const ModPolynomial& second)const;
};
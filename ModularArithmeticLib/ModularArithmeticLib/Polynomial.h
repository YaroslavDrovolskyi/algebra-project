#pragma once
#include <iostream>
#include <vector>

using number = double;

class Polynomial {
private:
	std::vector<number> polynomial;
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
	Polynomial removeZeros();

	std::pair<Polynomial, Polynomial> divide(Polynomial& pol); // we get fraction and remainder as the return values
	Polynomial gcd(Polynomial& pol);
};
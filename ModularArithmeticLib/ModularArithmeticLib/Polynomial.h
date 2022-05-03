#pragma once
#include <iostream>
#include <vector>

using uint = unsigned int;

class Polynomial {
private:
	std::vector<uint> polynomial;
public:

	Polynomial(std::vector<uint> pol) {
		polynomial = pol;
	}

	void setPolynomial(std::vector<uint> pol) {
		polynomial = pol;
	}

	std::vector<uint> getPolynomial() {
		return polynomial;
	}

	std::pair<Polynomial, Polynomial> fraction(Polynomial pol);
	Polynomial gcd();
};
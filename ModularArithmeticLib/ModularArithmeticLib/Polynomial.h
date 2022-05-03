#pragma once
#include <iostream>
#include <vector>

using number = long long;

class Polynomial {
private:
	std::vector<long long> polynomial;
public:
	Polynomial() {
		polynomial = std::vector<long long>();
	}

	Polynomial(std::vector<long long> pol) {
		polynomial = pol;
	}

	void setPolynomial(std::vector<long long> pol) {
		polynomial = pol;
	}

	std::vector<long long> getPolynomial() {
		return polynomial;
	}

	number valueAtPoint(number point);

	std::pair<Polynomial, Polynomial> divide(Polynomial& pol); // we get fraction and remainder as the return values
	//Polynomial gcd();
};
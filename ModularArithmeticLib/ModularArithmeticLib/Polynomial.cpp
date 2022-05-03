#include "pch.h"
#include "Polynomial.h"

number Polynomial::valueAtPoint(number point)
{
	number res = 0;
	for (int i = 0; i < polynomial.size(); ++i) {
		res += (pow(point, i)*polynomial[i]);
	}
	return res;
}

Polynomial Polynomial::differentiation()
{
	std::vector<number> res = std::vector<number>(polynomial.size() - 1);
	for (int i = 0; i < res.size(); ++i) {
		res[i] = polynomial[i+1]*(i+1);
	}
	return Polynomial(res);
}

std::pair<Polynomial, Polynomial> Polynomial::divide(Polynomial& pol) {
	if (pol.getPolynomial().size() > this->polynomial.size()) {
		return std::make_pair(Polynomial(), this->polynomial);
	}

	long fractionSize = this->polynomial.size() - 1 - (pol.getPolynomial().size() - 1) + 1;
	long polSize = pol.getPolynomial().size();

	number currentIndex;
	std::vector<number> fraction(fractionSize);
	std::vector<number> remainder = this->polynomial;

	for (int i = 0; i < fractionSize; ++i) {
		currentIndex = fractionSize - 1 - i;
		if (this->polynomial[this->polynomial.size() - 1 - i] == 0) {
			fraction[currentIndex] = 0;
		}
		else {
			fraction[currentIndex] = remainder[remainder.size() - 1 - i] / pol.getPolynomial()[polSize - 1 - i];
		}
		for (int j = 0; j < polSize; ++j) {
			remainder[this->polynomial.size() - 1 - j - i] -= pol.getPolynomial()[polSize - 1 - j] * fraction[currentIndex];
		}
	}

	return std::make_pair(Polynomial(fraction), Polynomial(remainder));
}
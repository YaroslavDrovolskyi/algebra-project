#include "pch.h"
#include "Polynomial.h"

std::pair<Polynomial, Polynomial> Polynomial::divide(Polynomial& pol) {
	/*if (pol.getPolynomial().size() > this->polynomial.size()) {
		return std::make_pair(Polynomial(), this->polynomial);
	}*/

	long long fractionSize = this->polynomial[this->polynomial.size() - 1] - (pol.getPolynomial().size() - 1) + 1;
	std::vector<number> tmp(fractionSize);
	Polynomial fraction(tmp);

	number currentIndex = fractionSize - 1;
	fraction.getPolynomial()[currentIndex] =  
}
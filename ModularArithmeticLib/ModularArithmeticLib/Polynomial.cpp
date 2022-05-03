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

std::pair<Polynomial, Polynomial> Polynomial::divide(Polynomial& pol) {
	/*if (pol.getPolynomial().size() > this->polynomial.size()) {
		return std::make_pair(Polynomial(), this->polynomial);
	}*/
	Polynomial fraction;

}
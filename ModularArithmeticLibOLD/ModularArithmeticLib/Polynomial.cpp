#include "pch.h"
#include "Polynomial.h"

number Polynomial::valueAtPoint(number point)
{
	this->removeZeros();
	number res = 0;
	for (int i = 0; i < polynomial.size(); ++i) {
		res += (pow(point, i) * polynomial[i]);
	}
	return res;
}

Polynomial Polynomial::differentiation()
{
	this->removeZeros();
	std::vector<number> res = std::vector<number>(polynomial.size() - 1);
	for (int i = 0; i < res.size(); ++i) {
		res[i] = polynomial[i + 1] * (i + 1);
	}
	return Polynomial(res);
}

Polynomial Polynomial::removeZeros() {
	while (this->polynomial[this->polynomial.size() - 1] == 0 && this->polynomial.size() > 1) {
		this->polynomial.pop_back();
	}
	return this->polynomial;
}

std::pair<Polynomial, Polynomial> Polynomial::divide(Polynomial& pol) {
	pol.removeZeros();
	this->removeZeros();
	if (pol.getPolynomial().size() > this->polynomial.size()) {
		return std::make_pair(Polynomial(), this->polynomial);
	}

	long long fractionSize = this->polynomial.size() - 1 - (pol.getPolynomial().size() - 1) + 1;
	long long polSize = pol.getPolynomial().size();

	number currentIndex;
	std::vector<number> fraction(fractionSize);
	std::vector<number> remainder = this->polynomial;

	for (int i = 0; i < fractionSize; ++i) {
		currentIndex = fractionSize - 1 - i;
		if (remainder[remainder.size() - 1 - i] == 0) {
			continue;
		}
		else {
			fraction[currentIndex] = remainder[remainder.size() - 1 - i] / pol.getPolynomial()[polSize - 1];
		}
		for (int j = 0; j < polSize; ++j) {
			remainder[this->polynomial.size() - 1 - j - i] -= pol.getPolynomial()[polSize - 1 - j] * fraction[currentIndex];
		}
	}

	return std::make_pair(Polynomial(fraction), Polynomial(remainder).removeZeros());
}

Polynomial Polynomial::gcd(Polynomial& pol) {
	Polynomial pol1;
	Polynomial pol2;
	if (pol.getPolynomial().size() > this->polynomial.size()) {
		pol1 = pol;
		pol2 = *this;
	}
	else if (pol.getPolynomial().size() < this->polynomial.size()) {
		pol1 = *this;
		pol2 = pol;
	}
	else {
		if (abs(pol.getPolynomial()[pol.getPolynomial().size() - 1]) >= abs(this->polynomial[this->polynomial.size() - 1])) {
			pol1 = pol;
			pol2 = *this;
		}
		else {
			pol1 = *this;
			pol2 = pol;
		}
	}
	if (pol2.getPolynomial().size() == 1) {
		std::vector<number> tmp;
		tmp.push_back(1);
		return Polynomial(tmp);
	}
	std::pair<Polynomial, Polynomial> tmp = pol1.divide(pol2);
	if (tmp.second.getPolynomial()[tmp.second.getPolynomial().size() - 1] == 0) {
		return pol2;
	}
	else {
		return pol2.gcd(tmp.second);
	}
}

Polynomial Polynomial::operator+(const Polynomial& second)const {
	Polynomial result;
	result.polynomial.resize(max(second.polynomial.size(), polynomial.size()));
	(polynomial.size() < second.polynomial.size()) ? result.setPolynomial(second.polynomial) : result.setPolynomial(polynomial);
	for (size_t i = 0; i != min(polynomial.size(), second.polynomial.size()); ++i) {
		result.polynomial[i] = polynomial[i] + second.polynomial[i];
	}
	result.removeZeros();
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& second)const {
	Polynomial result;
	result.polynomial.resize(max(second.polynomial.size(), polynomial.size()));
	(polynomial.size() < second.polynomial.size()) ? result.setPolynomial(second.polynomial) : result.setPolynomial(polynomial);
	for (size_t i = 0; i != min(polynomial.size(), second.polynomial.size()); ++i) {
		result.polynomial[i] = polynomial[i] - second.polynomial[i];
	}
	result.removeZeros();
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& second)const {
	Polynomial result;
	result.polynomial.resize(polynomial.size() + second.polynomial.size());
	for (size_t i = 0; i != polynomial.size(); ++i) {
		for (size_t j = 0; j != second.polynomial.size(); ++j) {
			result.polynomial[i + j] += polynomial[i] * second.polynomial[j];
		}
	}
	result.removeZeros();
	return result;
}
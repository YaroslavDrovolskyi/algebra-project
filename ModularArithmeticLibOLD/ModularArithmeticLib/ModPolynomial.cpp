#include "ModPolynomial.h"
#include "pch.h"


ModPolynomial ModPolynomial::removeZeros() {
	number zero(0, this->modPolynomial[0].getModulus());
	while (this->modPolynomial[this->modPolynomial.size() - 1] == zero && this->modPolynomial.size() > 1) {
		this->modPolynomial.pop_back();
	}
	return this->modPolynomial;
} 

std::pair<ModPolynomial, ModPolynomial> ModPolynomial::divide(ModPolynomial& pol) {
	pol.removeZeros();
	this->removeZeros();
	if (pol.getModPolynomial().size() > this->modPolynomial.size()) {
		return std::make_pair(ModPolynomial(), this->modPolynomial);
	}

	long long fractionSize = this->modPolynomial.size() - 1 - (pol.getModPolynomial().size() - 1) + 1;
	long long polSize = pol.getModPolynomial().size();

	int currentIndex;
	std::vector<number> fraction(fractionSize);
	std::vector<number> remainder = this->modPolynomial;

	for (int i = 0; i < fractionSize; ++i) {
		number zero(0, this->modPolynomial[0].getModulus());
		currentIndex = fractionSize - 1 - i;
		if (remainder[remainder.size() - 1 - i] == zero) {
			continue;
		}
		else {
			fraction[currentIndex] = remainder[remainder.size() - 1 - i] / pol.getModPolynomial()[polSize - 1];
		}
		for (int j = 0; j < polSize; ++j) {
			remainder[this->modPolynomial.size() - 1 - j - i] = remainder[this->modPolynomial.size() - 1 - j - i] 
				- pol.getModPolynomial()[polSize - 1 - j] * fraction[currentIndex];
		}
	}

	return std::make_pair(ModPolynomial(fraction), ModPolynomial(remainder).removeZeros());
}


ModPolynomial ModPolynomial::inversePolynomial(ModPolynomial& modulus, FiniteField num) {
	number one(1, this->modPolynomial[0].getModulus());
	number oneMinus(-1, this->modPolynomial[0].getModulus());
	ModPolynomial onePol({ one });
	ModPolynomial onePolMinus({ oneMinus });
	ModPolynomial a = modulus;
	ModPolynomial b = *this;
	ModPolynomial ka = onePol;
	ModPolynomial kb = onePol;
	ModPolynomial res = onePol;
	std::pair<ModPolynomial, ModPolynomial> pair;

	do {
		pair = modulus.divide(*this);
		res = a - pair.first * res;
		a = b;
		b = pair.second;
		kb = onePolMinus * pair.first * kb;
		ka = onePol - ka * a;
	} while (pair.second.getModPolynomial().size() == 1 && pair.second.getModPolynomial()[0] == one);
	return kb;
}

int main() {
	std::vector<number> v1;
	v1.push_back(BigModInt(1, 2));
	v1.push_back(BigModInt(0, 2));
	v1.push_back(BigModInt(0, 2));
	v1.push_back(BigModInt(1, 2));
	v1.push_back(BigModInt(0, 2));
	v1.push_back(BigModInt(1, 2));
	ModPolynomial pol1(v1);

	std::vector<number> v2;
	v2.push_back(BigModInt(1, 2));
	v2.push_back(BigModInt(0, 2));
	v2.push_back(BigModInt(0, 2));
	v2.push_back(BigModInt(1, 2));
	v2.push_back(BigModInt(1, 2));
	v2.push_back(BigModInt(1, 2));
	ModPolynomial pol2(v2);

	ModPolynomial ans = pol2.inversePolynomial(pol1, 2);
	for (int i = 0; i < ans.getModPolynomial().size(); ++i) {
		std::cout << ans.getModPolynomial()[i].getNumber() << " ";
	}
}


ModPolynomial ModPolynomial::operator*(const ModPolynomial& second)const {
	ModPolynomial result;
	result.modPolynomial.resize(modPolynomial.size() + second.modPolynomial.size());
	for (size_t i = 0; i != modPolynomial.size(); ++i) {
		for (size_t j = 0; j != second.modPolynomial.size(); ++j) {
			result.modPolynomial[i + j] = result.modPolynomial[i + j] + modPolynomial[i] * second.modPolynomial[j];
		}
	}
	result.removeZeros();
	return result;
}



ModPolynomial ModPolynomial::operator-(const ModPolynomial& second)const {
	ModPolynomial result;
	result.modPolynomial.resize(max(second.modPolynomial.size(), modPolynomial.size()));
	(modPolynomial.size() < second.modPolynomial.size()) ? result.setModPolynomial(second.modPolynomial) : result.setModPolynomial(modPolynomial);
	for (size_t i = 0; i != min(modPolynomial.size(), second.modPolynomial.size()); ++i) {
		result.modPolynomial[i] = modPolynomial[i] - second.modPolynomial[i];
	}
	result.removeZeros();
	return result;
}

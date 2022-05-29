#include "Polynomial.h"
#include <sstream>

Polynomial::Polynomial(std::string pol)
{
    if(!this->isCorrect(pol))
        throw std::invalid_argument("incorrect input");
    std::string polForExp = pol;
    std::vector<number> koefs;
    number koef, prevXor, curXor;
    bool isPositiveNumber = 0;
    bool isNegativeNumber = 0;
    bool isXor = 0;
    bool isFirstXor = 0;

    pol.erase(remove(pol.begin(), pol.end(), ' '), pol.end());
    if (pol[pol.size() - 1] >= '0' && pol[pol.size() - 1] <= '9') {
        pol += "x^0";
        if (!isCorrect(pol)) {
            pol.erase(pol.size() - 3, pol.size());
        }
    }
    for (int i = 0; i < pol.size(); ++i) {
        if (pol[i] == 'x' && pol[i + 1] != '^') {
            pol.insert(i + 1, "^1");
            break;
        }
        else if (pol[i] == 'x' && i == pol.size() - 1) {
            pol += "^1";
        }
    }

    if (pol[0] != '-')
        pol = '+' + pol;
    for (int i = 0; i < pol.size(); ++i) {
        if (pol[i] == ' ')
            continue;
        if (pol[i] == '+') {
            isPositiveNumber = 1;
            koef = 0;
            continue;
        }
        else if (pol[i] == '-') {
            isNegativeNumber = 1;
            koef = 0;
            continue;
        }
        else if (pol[i] == '^') {
            isXor = 1;
            koef = 0;
            continue;
        }

        if (isPositiveNumber || isNegativeNumber || isXor) {
            if (pol[i] >= '0' && pol[i] <= '9') {
                koef = koef * 10;
                koef = koef + pol[i] - 48;
            }
            if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isPositiveNumber) {
                isPositiveNumber = 0;
                if (koef == 0)
                    koef = 1;
                koefs.push_back(koef);
            }
            else if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isNegativeNumber) {
                isNegativeNumber = 0;
                if (koef == 0)
                    koef = 1;
                koefs.push_back(-1 * koef);
            }
            else if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isXor) {
                isXor = 0;
                if (!isFirstXor) {
                    isFirstXor = 1;
                    prevXor = koef;
                }
                else {
                    if (prevXor - koef > 1) {
                        for (int i = 0; i < prevXor - koef - 1; ++i) {
                            koefs.insert(koefs.end() - 1, 0);
                        }
                    }
                    prevXor = koef;
                }
            }
        }
    }
    if (prevXor != 0) {
        for (int i = 0; i <  prevXor; ++i) {
            koefs.push_back(0);
        }
    }
    std::reverse(koefs.begin(), koefs.end());

    polynomial = koefs;
}

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
    if (this->polynomial.empty())
        return this->polynomial;
    while (this->polynomial[this->polynomial.size() - 1] == 0 && this->polynomial.size() > 1) {
        this->polynomial.pop_back();
    }
    return this->polynomial;
}

std::string Polynomial::numberToSting(number dbl)
{
    std::ostringstream strs;
    strs << dbl;
    std::string str = strs.str();
    return str;
}

bool Polynomial::isCorrect(std::string input)
{
    std::string str = input;
    bool isKoef = false;
    bool isX = false;
    bool isSC = false;
    bool isInd = false;
    int index = INT_MAX;
    int tmp = 0;
    while (!str.empty()) {
        if (str[0] == ' ') {
            str.erase(0, 1);
            continue;
        }else if ((!isKoef && !isX && !isSC && !isInd)) {
            if (str[0] >= '0' && str[0] <= '9' || str[0] == '+' || str[0] == '-') isKoef = true;
            else if (str[0] == 'x')isX = true;
            else
                return false;

        }else if (isKoef == true) {
            isKoef = false;
            if (str[0] >= '0' && str[0] <= '9') isKoef = true;
            else if (str[0] == 'x')  isX = true;
            else if (str[0] == '*') {
                str.erase(0, 1);
                if (str.empty()) return false;
                if (str[0] == 'x') isX = true;
                else return false;
            }
            else
                return false;
        }
        else if (isX == true) {
            isX = false;
            if (str[0] == '^') {
                isSC = true;
            }
            else if (str[0] == '+' || str[0] == '-') {
                tmp = 1;
                if (tmp >= index) return false;
                index = tmp;
                tmp = 0;
                isKoef = true;
            }
            else return false;
        }
        else if (isSC) {
            isSC = false;
            if (str[0] >= '0' && str[0] <= '9') {
                isInd = true;
                tmp *= 10;
                tmp += str[0] - '0';
            }
            else
                return false;
        }
        else if (isInd) {
            isInd = false;
            if (str[0] >= '0' && str[0] <= '9') {
                isInd = true;
                tmp *= 10;
                tmp += str[0] - '0';
            }
            else {
                if (tmp >= index) return false;
                index = tmp;
                tmp = 0;
                if (str[0] == '+' || str[0] == '-') isKoef = true;
                else return false;
            }

        }
        str.erase(0, 1);
    }
    if (isX && index <=1) {
        return false;
    }
    return (isKoef || isX || isInd);
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
    result.polynomial.resize(std::max(second.polynomial.size(), polynomial.size()));
    (polynomial.size() < second.polynomial.size()) ? result.setPolynomial(second.polynomial) : result.setPolynomial(polynomial);
    for (size_t i = 0; i != std::min(polynomial.size(), second.polynomial.size()); ++i) {
        result.polynomial[i] = polynomial[i] + second.polynomial[i];
    }
    result.removeZeros();
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& second)const {
	Polynomial result;
    result.polynomial.resize(std::max(second.polynomial.size(), polynomial.size()));
    (polynomial.size() < second.polynomial.size()) ? result.setPolynomial(second.polynomial) : result.setPolynomial(polynomial);
    for (size_t i = 0; i != std::min(polynomial.size(), second.polynomial.size()); ++i) {
		result.polynomial[i] = polynomial[i] - second.polynomial[i];
	}
	if(second.polynomial.size()>polynomial.size()){
		for(size_t i = std::min(polynomial.size(), second.polynomial.size()); i < std::max(polynomial.size(), second.polynomial.size());++i){
			result.polynomial[i] = - second.polynomial[i];
		}
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

std::string Polynomial::toString()
{
    this->removeZeros();
    std::string resultString = "";
    number zero(0);
    number one(1);
    bool isOut = false;
    for (int i = this->polynomial.size() - 1; i >= 0; --i) {
        if (polynomial[i] != 0) {
            if (isOut)
                resultString += " + ";
            isOut = true;
            if (i == 0) {
                resultString += this->numberToSting(polynomial[i]);
                break;
            }
            if (polynomial[i] != 1) {
                resultString += this->numberToSting(polynomial[i]);
                resultString += '*';
            }
            resultString += 'x';
            if (i > 1) {
                char ii = i + '0';
                resultString += '^';
                resultString += ii;

            }
        }
    }
    return resultString;
}

std::ostream& operator<<(std::ostream& out, Polynomial& a)
{
    out << a.toString();
    out << std::endl;
    return out;
}

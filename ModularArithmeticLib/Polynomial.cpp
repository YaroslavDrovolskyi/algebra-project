#include "Polynomial.h"
#include <sstream>

Polynomial::Polynomial(std::vector<BigInt> pol, BigInt modulus)
{
    this->modulus = modulus;
    polynomial.resize(pol.size());
    for (int i = 0; i < polynomial.size(); ++i) {
        this->polynomial[i] = BigModInt(pol[i], modulus);
    }
}

Polynomial::Polynomial(std::vector<BigModInt> pol, BigInt modulus)
{
    this->modulus = modulus;
    polynomial.resize(pol.size());
    for (int i = 0; i < polynomial.size(); ++i) {
        this->polynomial[i] = BigModInt(pol[i].getNumber(), modulus);
    }
}


Polynomial::Polynomial(std::string pol, BigInt modulus)
{
    if(!this->isCorrect(pol))
        throw std::invalid_argument("incorrect input");
    this->modulus = modulus;
    std::string polForExp = pol;
    std::vector<BigInt> koefs;
    std::vector<BigModInt> modKoefs;
    BigInt koef, prevXor, curXor;
    bool isPositiveNumber = 0;
    bool isNegativeNumber = 0;
    bool isXor = 0;
    bool isFirstXor = 0;
    bool isKoefZero = 1;

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
                isKoefZero = 0;
            }
            if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isPositiveNumber) {
                isPositiveNumber = 0;
                if (koef == 0 && isKoefZero)
                    koef = 1;
                koefs.push_back(koef);
                isKoefZero = 1;
            }
            else if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isNegativeNumber) {
                isNegativeNumber = 0;
                if (koef == 0 && isKoefZero)
                    koef = 1;
                koefs.push_back(-1 * koef);
                isKoefZero = 1;
            }
            else if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isXor) {
                isXor = 0;
                isKoefZero = 1;
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
    for (int i = koefs.size() - 1; i >= 0; --i) {
        modKoefs.push_back(BigModInt(koefs[i], modulus));
    }
    polynomial = modKoefs;
}

BigModInt Polynomial::valueAtPoint(BigModInt point)
{
    this->removeZeros();
    BigModInt res(BigInt(0),point.getModulus());
    if (polynomial.empty())
        return res;
    if (point.getModulus() != getFieldModulus())
        throw std::invalid_argument("incorrect input");

    for (int i = 0; i < polynomial.size(); ++i) {
        res = res + (pow(point, i) * polynomial[i]);
    }
    return res;
}

Polynomial Polynomial::differentiation()
{
    this->removeZeros();
    std::vector<BigModInt> res = std::vector<BigModInt>(polynomial.size() - 1);
    for (int i = 0; i < res.size(); ++i) {
        res[i] = polynomial[i + 1] * BigModInt(BigInt(i + 1), getFieldModulus() );
    }
    return Polynomial(res);
}

Polynomial Polynomial::removeZeros() {
    if (this->polynomial.empty())
        return this->polynomial;
    BigModInt zero(0, this->getFieldModulus());
    while (this->polynomial[this->polynomial.size() - 1] == zero && this->polynomial.size() > 1) {
        this->polynomial.pop_back();
    }
    return this->polynomial;
}
std::string Polynomial::numberToSting(BigModInt num)
{
    return num.getNumber().GetString();
}

BigModInt Polynomial::pow(BigModInt value, int power)
{
    if(power<0)
        throw std::invalid_argument("power must be positive");
    BigModInt res(BigInt(1),value.getModulus());
    for (int i = 0; i < power; ++i) {
        res = res * value;
    }
    return res;
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

Polynomial::Polynomial(std::vector<BigModInt> pol)
{
    polynomial = pol;
    if (!pol.empty())
        this->modulus = pol[0].getModulus();
}

std::pair<Polynomial, Polynomial> Polynomial::divide(Polynomial& pol) {
    pol.removeZeros();
    this->removeZeros();
    if(this->polynomial.empty() || pol.polynomial.empty())
        throw std::invalid_argument("polynom can't be empty");
    if(this->getFieldModulus() != pol.getFieldModulus())
        throw std::invalid_argument("Finite field must be same");
    BigModInt zero(BigInt(0), this->getFieldModulus());

    if (pol.polynomial.size()==1 && pol.polynomial[0] == zero)
        throw std::invalid_argument("dividing on zero");
    if (pol.getPolynomial().size() > this->polynomial.size()) {
        return std::make_pair(Polynomial("0", this->getFieldModulus()), Polynomial(this->polynomial));
    }

    long long fractionSize = this->polynomial.size() - 1 - (pol.getPolynomial().size() - 1) + 1;
    long long polSize = pol.getPolynomial().size();

    int currentIndex;
    std::vector<BigModInt> fraction(fractionSize);
    std::vector<BigModInt> remainder = this->polynomial;


    for (int i = 0; i < fractionSize; ++i) {
        currentIndex = fractionSize - 1 - i;
        if (remainder[remainder.size() - 1 - i] == zero) {
            continue;
        }
        else {
            fraction[currentIndex] = remainder[remainder.size() - 1 - i] / pol.getPolynomial()[polSize - 1];
        }
        for (int j = 0; j < polSize; ++j) {
            remainder[this->polynomial.size() - 1 - j - i] = remainder[this->polynomial.size() - 1 - j - i] -
                pol.getPolynomial()[polSize - 1 - j] * fraction[currentIndex];
        }
    }

    return std::make_pair(Polynomial(fraction, this->getFieldModulus()), Polynomial(remainder, this->getFieldModulus()).removeZeros());
}

Polynomial Polynomial::gcd(Polynomial& pol) {
    pol.removeZeros();
    this->removeZeros();
    if (this->polynomial.empty() || pol.polynomial.empty())
        throw std::invalid_argument("polynom can't be empty");
    if (this->getFieldModulus() != pol.getFieldModulus())
        throw std::invalid_argument("Finite field must be same");
    Polynomial pol1;
    Polynomial pol2;

    BigModInt zero(BigInt(0), this->getFieldModulus());
    BigModInt one(BigInt(1), this->getFieldModulus());

    if (pol.getPolynomial().size() > this->polynomial.size()) {
        pol1 = pol;
        pol2 = *this;
    }
    else if (pol.getPolynomial().size() < this->polynomial.size()) {
        pol1 = *this;
        pol2 = pol;
    }
    else {
        if ((pol.getPolynomial()[pol.getPolynomial().size() - 1]).getNumber() >= (this->polynomial[this->polynomial.size() - 1]).getNumber()) {
            pol1 = pol;
            pol2 = *this;
        }
        else {
            pol1 = *this;
            pol2 = pol;
        }
    }
    if (pol2.getPolynomial().size() == 1) {
        std::vector<BigModInt> tmp;
        tmp.push_back(one);
        return Polynomial(tmp);
    }
    std::pair<Polynomial, Polynomial> tmp = pol1.divide(pol2);
    if (tmp.second.getPolynomial()[tmp.second.getPolynomial().size() - 1] == zero) {
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

//Polynomial Polynomial::operator-(const Polynomial& second)const {
//	Polynomial result;
//    result.polynomial.resize(std::max(second.polynomial.size(), polynomial.size()));
//    (polynomial.size() < second.polynomial.size()) ? result.setPolynomial(second.polynomial) : result.setPolynomial(polynomial);
//    for (size_t i = 0; i != std::min(polynomial.size(), second.polynomial.size()); ++i) {
//		result.polynomial[i] = polynomial[i] - second.polynomial[i];
//	}
//	if(second.polynomial.size()>polynomial.size()){
//		for(size_t i = std::min(polynomial.size(), second.polynomial.size()); i < std::max(polynomial.size(), second.polynomial.size());++i){
//            result.polynomial[i] = - second.polynomial[i];
//		}
//	}
//	result.removeZeros();
//	return result;
//}


Polynomial Polynomial::operator*(const Polynomial& second)const {
    BigInt simpleZero(0);
    BigInt mod = this->getFieldModulus();
    BigModInt zero(simpleZero, mod);
    std::vector<BigModInt> pol(polynomial.size() + second.polynomial.size(), zero);
    Polynomial result(pol);
    //polynomial result;
    //result.polynomial.resize(polynomial.size() + second.polynomial.size());
    for (size_t i = 0; i != polynomial.size(); ++i) {
        for (size_t j = 0; j != second.polynomial.size(); ++j) {
            result.polynomial[i + j] = result.polynomial[i + j] + polynomial[i] * second.polynomial[j];
        }
    }
    result.removeZeros();
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& second)const {
    BigInt simpleOne(1);
    BigModInt oneMinus(getFieldModulus() - simpleOne, getFieldModulus());
    Polynomial onePolMinus({ oneMinus.getNumber() }, oneMinus.getModulus());
    Polynomial result, tmp;
    result.polynomial.resize(std::max(second.polynomial.size(), polynomial.size()));
    if (polynomial.size() < second.polynomial.size()) {
        result.setPolynomial((onePolMinus * second.polynomial).getPolynomial());
        tmp = (*this) * onePolMinus;
    }
    else {
        result.setPolynomial(polynomial);
        tmp = second;
    }
    for (size_t i = 0; i < std::min(polynomial.size(), second.getPolynomial().size()); ++i) {
        result.polynomial[i] = result.polynomial[i] - tmp.getPolynomial()[i];
    }
    result.removeZeros();
    return result;
}



Polynomial Polynomial::operator=(const Polynomial& second)
{
    if (this == &second)
        return *this;
    this->polynomial = second.getPolynomial();
    this->modulus = second.getFieldModulus();

    return *this;
}
std::string Polynomial::toString()const
{
    std::string resultString = "";
    BigInt zero(0);
    BigInt one(1);
    bool isOut = false;
    //if(this->polynomial.size()==1 && this->polynomial[0]==zero)
    for (long long i = this->polynomial.size() - 1; i >= 0; --i) {
        if (i==0 || polynomial[i].getNumber() != zero) {
            if (isOut)
                resultString += " + ";
            isOut = true;
            if (i == 0) {
                resultString += polynomial[i].getNumber().GetString();
                break;
            }
            if (polynomial[i].getNumber() != one) {
                resultString += polynomial[i].getNumber().GetString();
                resultString += '*';
            }
            resultString += 'x';
            if (i > 1) {

                BigInt ii = i;
                resultString += '^';
                resultString += ii.GetString();

            }
        }
    }
    return resultString;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& a)
{
    out << a.toString();
    out << std::endl;
    return out;
}

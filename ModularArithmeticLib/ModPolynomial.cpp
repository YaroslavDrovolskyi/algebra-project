#include "ModPolynomial.h"
#include <sstream>
ModPolynomial ModPolynomial::removeZeros() {
    if (this->modPolynomial.empty()) return this->modPolynomial;
    BigModInt zero(0, this->modPolynomial[0].getModulus());
    while (this->modPolynomial[this->modPolynomial.size() - 1] == zero && this->modPolynomial.size() > 1) {
        this->modPolynomial.pop_back();
    }
    return this->modPolynomial;
}
bool ModPolynomial::isCorrect(std::string input)
{
    std::string str = input;
    bool isKoef = false;
    bool isX = false;
    bool isSC = false;
    bool isInd = false;
    int index = INT_MAX;
    int tmp = 0;
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    bool isNumber = false;
    for (int i = str.size() - 1; i >= 0; --i) {
        if (i == str.size() - 1)
            if (str[i] >= '0' && str[i] <= '9') continue;
            else return false;
        else if (str[i] >= '0' && str[i] <= '9') continue;
        else if (str[i] == 'd' && i >= 2 && str[i - 1] == 'o' && str[i - 2] == 'm') {
            str.erase(str.begin() + i - 2, str.end());
            break;
        }
        else return false;
    }
    while (!str.empty()) {
        if ((!isKoef && !isX && !isSC && !isInd)) {
            if (str[0] >= '0' && str[0] <= '9' || str[0] == '+' || str[0] == '-') isKoef = true;
            else if (str[0] == 'x')isX = true;
            else
                return false;

        }
        else if (isKoef == true) {
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
                else if (str[0] == 'x') isX = true;
                else return false;
            }

        }
        str.erase(0, 1);
    }
    if (isX && index <= 1) {
        return false;
    }
    return (isKoef || isX || isInd);
}


ModPolynomial::ModPolynomial(std::string pol)
{
    if (!this->isCorrect(pol))
        throw std::invalid_argument("incorrect input");
    std::string polForExp;
    std::vector<BigInt> koefs;
    std::vector<BigModInt> modKoefs;
    BigInt mod, koef;
    bool isPositiveNumber = 0;
    bool isNegativeNumber = 0;
    bool isMod = 0;
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
        if (pol[i] == 'd') {
            isMod = 1;
            koef = 0;
            continue;
        }

        if (isPositiveNumber || isNegativeNumber || isMod) {
            if (pol[i] >= '0' && pol[i] <= '9') {
                koef = koef * 10;
                koef = koef + pol[i] - 48;
            }
            else if (koef == 0)
                koef = 1;
            if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isPositiveNumber) {
                isPositiveNumber = 0;
                koefs.push_back(koef);
            }
            else if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isNegativeNumber) {
                isNegativeNumber = 0;
                koefs.push_back(-1 * koef);
            }
            else if ((i == pol.size() - 1 || pol[i + 1] < '0' || pol[i + 1] > '9') && isMod) {
                isMod = 0;
                mod = koef;
            }
        }
    }

    for (int i = koefs.size() - 1; i >= 0; --i) {
        modKoefs.push_back(BigModInt(koefs[i], mod));
    }
    modPolynomial = modKoefs;

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
    std::vector<BigModInt> fraction(fractionSize);
    std::vector<BigModInt> remainder = this->modPolynomial;

    for (int i = 0; i < fractionSize; ++i) {
        BigModInt zero(0, this->modPolynomial[0].getModulus());
        currentIndex = fractionSize - 1 - i;
        if (remainder[remainder.size() - 1 - i] == zero) {
            fraction[currentIndex] = zero;
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


ModPolynomial ModPolynomial::inversePolynomial(ModPolynomial& modulus) {
    BigInt simpleOne(1);
    BigModInt one(simpleOne, this->modPolynomial[0].getModulus());
    BigModInt oneMinus(this->modPolynomial[0].getModulus() - simpleOne, this->modPolynomial[0].getModulus());
    ModPolynomial onePol({ one });
    ModPolynomial onePolMinus({ oneMinus });
    ModPolynomial a = modulus;
    ModPolynomial b = *this;
    ModPolynomial kaprev;
    ModPolynomial ka;
    ModPolynomial kbprev;
    ModPolynomial kb;
    ModPolynomial buf;
    //ModPolynomial res = b;
    int i = 0;
    std::pair<ModPolynomial, ModPolynomial> pair;

    do {
        pair = a.divide(b);
        //res = a - pair.first * res;
        if (i == 0) {
            kaprev = onePol;
            kbprev = onePolMinus * pair.first;
        }
        else if (i == 1) {
            ka = onePolMinus * pair.first;
            kb = onePol - kbprev * pair.first;
        }
        else {
            buf = ka;
            ka = kaprev - ka * pair.first;
            kaprev = buf;
            buf = kb;
            kb = kbprev - kb * pair.first;
            kbprev = buf;
        }
        a = b;
        b = pair.second;
        ++i;
        if (pair.second.getModPolynomial().size() == 1 && pair.second.getModPolynomial()[0] == one)
            break;
    } while (true);

    if (i == 1)
        return kbprev;
    else
        return kb;
}



ModPolynomial ModPolynomial::operator*(const ModPolynomial& second){
    BigInt simpleZero(0);
    BigInt mod = this->modPolynomial[0].getModulus();
    BigModInt zero(simpleZero, mod);
    std::vector<BigModInt> pol(modPolynomial.size() + second.modPolynomial.size(), zero);
    ModPolynomial result(pol);
    //ModPolynomial result;
    //result.modPolynomial.resize(modPolynomial.size() + second.modPolynomial.size());
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
    result.modPolynomial.resize(std::max(second.modPolynomial.size(), modPolynomial.size()));
    (modPolynomial.size() < second.modPolynomial.size()) ? result.setModPolynomial(second.modPolynomial) : result.setModPolynomial(modPolynomial);
    for (size_t i = 0; i != std::min(modPolynomial.size(), second.modPolynomial.size()); ++i) {
        result.modPolynomial[i] = modPolynomial[i] - second.modPolynomial[i];
    }
    result.removeZeros();
    return result;
}

std::string ModPolynomial::toString()
{
    this->removeZeros();
    std::string resultString = "";
    BigInt zero(0);
    BigInt one(1);
    bool isOut = false;
    for (int i = this->modPolynomial.size() - 1; i >= 0; --i) {
        if (modPolynomial[i].getNumber() != zero) {
            if (isOut)
                resultString += " + ";
            isOut = true;
            if (i == 0) {
                resultString += modPolynomial[i].getNumber().GetString();
                break;
            }
            if (modPolynomial[i].getNumber() != one) {
                resultString += modPolynomial[i].getNumber().GetString();
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

std::ostream& operator<<(std::ostream& out, ModPolynomial& a)
{
    out << a.toString();
    out << std::endl;
    return out;
}

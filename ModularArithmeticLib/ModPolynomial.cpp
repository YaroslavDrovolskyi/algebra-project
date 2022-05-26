#include "ModPolynomial.h"

ModPolynomial ModPolynomial::removeZeros() {
    BigModInt zero(0, this->modPolynomial[0].getModulus());
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


ModPolynomial ModPolynomial::inversePolynomial(ModPolynomial& modulus, FiniteField num) {
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

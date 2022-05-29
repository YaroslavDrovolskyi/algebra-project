#include "ModPolynomial.h"
#include <sstream>



ModPolynomial ModPolynomial::inversePolynomial() {
    BigInt simpleOne(1);
    BigModInt one(simpleOne, value.getFieldModulus());
    BigModInt oneMinus(value.getFieldModulus() - simpleOne, value.getFieldModulus());
    Polynomial onePol({ one.getNumber()}, one.getModulus());
    Polynomial onePolMinus({ oneMinus.getNumber()}, oneMinus.getModulus());
    Polynomial a = modulus;
    Polynomial b = value;
    Polynomial kaprev;
    Polynomial ka;
    Polynomial kbprev;
    Polynomial kb;
    Polynomial buf;
    //ModPolynomial res = b;
    int i = 0;
    std::pair<Polynomial, Polynomial> pair;

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
        if (pair.second.getPolynomial().size() == 1 && pair.second.getPolynomial()[0] == one)
            break;
    } while (true);

    if (i == 1)
        return ModPolynomial(kbprev, modulus);
    else
        return ModPolynomial(kb, modulus);
}


/*
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
}*/


//std::ostream& operator<<(std::ostream& out, ModPolynomial& a)
//{
//	out << a.toString();
//	out << std::endl;
//	return out;
//}

ModPolynomial::ModPolynomial(Polynomial value, Polynomial modulus)
{
    this->value = value;
    this->modulus = modulus;
}

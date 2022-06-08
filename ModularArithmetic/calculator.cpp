#include "calculator.h"
#include "discrete_log.h"
#include "pollard_fact.h"
#include "PrimeProbabilityChecker.h"
#include "EulerPhiCarmichaelLambda.h"
#include "IrreduciblePolynomial.h"
#include "CyclotomicPolynomial.h"
#include "sqrt.h"


#include <limits>

NumberCalculator::NumberCalculator():
    operations_names{"+", "-", "*", "/", "^ (fast)"},
    primality_tests_names {"Miller–Rabin test", "Solovey-Shtrassen test", "Ferma test"},
    int_functions_names{"Factorize (naive)", "Factorize (Pollard)", "Euler's totient function", "Carmichael function"},
    int_modular_functions_names {"Inverse element", "Square root"}
{

}


QString NumberCalculator::calculate(std::size_t op_index, const BigModInt& a, const BigModInt& b){
    switch(op_index){
        case 0:{
            return QString((a+b).getNumber().GetString().c_str());
            break;
        }
        case 1:{
            return QString((a-b).getNumber().GetString().c_str());
            break;
        }
        case 2:{
            return QString((a*b).getNumber().GetString().c_str());
            break;
        }
        case 3:{
            return QString((a/b).getNumber().GetString().c_str());
            break;
        }
        case 4:{ // fast powering

            // check if input is not bigger than MAX of int (because algo doesn't support BigInt)
            if (a.getModulus() > BigInt(std::to_string(std::numeric_limits<int>::max())) ||
                    a.getNumber() > BigInt(std::to_string(std::numeric_limits<int>::max())) ||
                    b.getNumber() > BigInt(std::to_string(std::numeric_limits<int>::max())))
            {
                throw std::invalid_argument("BigInt does not supported by this algo");
            }


            int base_int = std::stoi(a.getNumber().GetString());
            int exponent_int = std::stoi(b.getNumber().GetString());
            int modulus_int = std::stoi(a.getModulus().GetString());

            int result_int = Sqrt::powerMod(base_int, exponent_int, modulus_int);

            QString result = QString{std::to_string(result_int).c_str()};

            return result;
            break;
        }
        default:{
            return "";
            break;
        }
    }
}

QString NumberCalculator::calcIntFunction(std::size_t algo_index, const BigInt& number){
    switch(algo_index){
        case 0:{ // factorize (naive)
            if (number > BigInt(std::to_string(std::numeric_limits<int>::max())))
            {
                throw std::invalid_argument("BigInt does not supported by this algo");
            }

            LL n = std::stoi(number.GetString());

            if (n == 0){
                return "0";
            }
            else if (n == 1){
                return "1";
            }

            std::vector<LL> factorization = make_factorize2(n);

            QString result;
            for (int factor : factorization){
                result += QString::number(factor) + " ";
            }

            return result;
            break;
        }
        case 1:{ // factorize (Pollard)
            if (number > BigInt(std::to_string(std::numeric_limits<LL>::max())))
            {
                throw std::invalid_argument("BigInt does not supported by this algo");
            }

            int n = std::stoi(number.GetString());
            std::vector<LL> factorization = make_factorize(n);



            QString result;
            for (int factor : factorization){
                result += QString::number(factor) + " ";
            }

            if (n == 1){
                result = "1";
            }

            return result;
            break;
        }
        case 2:{ // Euler's totient function
            BigInt result = EulerPhiCarmichaelLambda::eulerPhi(number);
            return QString(result.GetString().c_str());
            break;
        }
        case 3:{ // Carmichael function
            BigInt result = EulerPhiCarmichaelLambda::carmichaelLambda(number);
            return QString(result.GetString().c_str());
            break;
        }
        default:{
            return "";
            break;
        }

    }
}


QString NumberCalculator::calcModIntFunction(std::size_t algo_index, const BigModInt& number){
    switch(algo_index){
        case 0:{ // inverse number
            BigModInt result = inverse(number);
            return QString(result.getNumber().GetString().c_str());
            break;
        }
        case 1:{ // sqrt
            // check if input is not bigger than MAX of int (because algo doesn't support BigInt)
            if (number.getModulus() > BigInt(std::to_string(std::numeric_limits<int>::max())) ||
                    number.getNumber() > BigInt(std::to_string(std::numeric_limits<int>::max())))
            {
                throw std::invalid_argument("BigInt does not supported by this algo");
            }

            int number_int = std::stoi(number.getNumber().GetString());
            int modulus_int = std::stoi(number.getModulus().GetString());

            int result_int = Sqrt::calcSquareRoot(number_int, modulus_int);

            QString result = QString{std::to_string(result_int).c_str()};

            return result;
            break;
        }
        default:{
            return "";
            break;
        }

    }
}


QString NumberCalculator::calcLog(const BigModInt& number, const BigModInt& base){
    // check if input is not bigger than MAX of long long (because algo doesn't support BigInt)
    if (number.getModulus() > 1e9 ||
            number.getNumber() > BigInt(std::to_string(std::numeric_limits<LL>::max())) ||
            base.getNumber() > BigInt(std::to_string(std::numeric_limits<LL>::max())))
    {
        throw std::invalid_argument("BigInt does not supported by this algo");
    }


    LL number_int = std::stoi(number.getNumber().GetString());
    LL base_int = std::stoi(base.getNumber().GetString());
    LL modulus_int = std::stoi(number.getModulus().GetString());

    LL result_int = baby_step_giant_step_discrete_logarithm(base_int, number_int, modulus_int);

    QString result = "";
    if (result_int == -2){
        result = "Base and modulus must be coprime";
    }
    else if (result_int == -1){
        result = "No solutions";
    }
    else{
        result = QString{std::to_string(result_int).c_str()};
    }

    return result;
}


QString NumberCalculator::calcPrimalityTest(std::size_t algo_index, const BigInt& a){
    if (a < 0){
        throw std::invalid_argument("Number must be >= 0");
    }

    QString result;
    PrimeProbabilityChecker checker;

    switch(algo_index){
        case 0:{
            bool result_bool = checker.checkByMillerRabin(a);
            result = result_bool ? "Number is prime" : "Number is not prime";
            break;
        }
        case 1:{
            bool result_bool = checker.checkBySoloveyShtrassen(a);
            result = result_bool ? "Number is prime" : "Number is not prime";
            break;
        }
        case 2:{
            bool result_bool = checker.checkByFerma(a);
            result = result_bool ? "Number is prime" : "Number is not prime";
            break;
        }
        default:{
            result = "default case";
            break;
        }
    }

    return result;
}

PolynomialRingCalculator::PolynomialRingCalculator() :
    operations_names{"+", "-", "*", "gcd"}

{

}

QString PolynomialRingCalculator::calc(std::size_t op_index, const Polynomial &a, const Polynomial &b){
    switch(op_index){
        case 0:{
            return QString((a+b).toString().c_str());
            break;
        }
        case 1:{
            return QString((a-b).toString().c_str());
            break;
        }
        case 2:{
            return QString((a*b).toString().c_str());
            break;
        }
        case 3:{
            Polynomial a_copy(a);
            Polynomial b_copy(b);
            return QString(a_copy.gcd(b_copy).toString().c_str());
            break;
        }
        default:{
            return "";
            break;
        }
    }
}

QString PolynomialRingCalculator::calcDerivative(const Polynomial& a){
    Polynomial a_copy(a);
    Polynomial result = a_copy.differentiation();
    return QString(result.toString().c_str());
}

QString PolynomialRingCalculator::calcValue(Polynomial a, BigModInt point){

    BigModInt result = a.valueAtPoint(point);
    return QString(result.getNumber().GetString().c_str());

}

std::pair<QString, QString> PolynomialRingCalculator::calcFractionRemainer(Polynomial a, Polynomial b){
    std::pair<Polynomial, Polynomial> result = a.divide(b);

    QString fraction_str = result.first.toString().c_str();
    QString remainder_str = result.second.toString().c_str();

    return std::make_pair(fraction_str, remainder_str);
}

QString PolynomialRingCalculator::calcCyclotomicPolynomial(BigInt modulus, BigInt order){
    if (modulus <= 0){
        throw std::invalid_argument("Modulus must be > 0");
    }
    if (order <= 0){
        throw std::invalid_argument("Order must be > 0");
    }

    CyclotomicPolynomial generator;
    std::vector<BigModInt> polynomial_coefs_non_format = generator.cyclotomicPolynomial(order, modulus);

    std::vector<BigInt> polynomial_coefs;
    for (const BigModInt& i : polynomial_coefs_non_format){
        polynomial_coefs.push_back(i.getNumber());
    }

    Polynomial result_polynomial{polynomial_coefs, modulus};


    return QString(result_polynomial.toString().c_str());
}



PolynomialFieldCalculator::PolynomialFieldCalculator() :
    algorithms_names{"revert"}
{

}

QString PolynomialFieldCalculator::calc(std::size_t op_index, Polynomial irreducible_pol, ModPolynomial a){
    switch(op_index){
        case 0:{
            ModPolynomial result = a.inversePolynomial();
            return QString(result.getValue().toString().c_str());
            break;
        }
        default:{
           return QString("Default case");
           break;
        }
    }
}


QString PolynomialFieldCalculator::calcIrreducibilityTest(Polynomial polynomial){
    IrreduciblePolynomial checker;
    bool result_bool = checker.isIrreducible(polynomial);

    QString result = "Polynomial is ";
    result += result_bool ? "irreducible" : "reducible";

    return result;
}

#include "calculator.h"

NumberCalculator::NumberCalculator():
    operations_names{"+", "-", "*", "/", "^ (fast)"},
    algorithms_names{"Revert element", "factorize (naive)", "factorize (Pollard)", "Square root",
                     "Euler's totient function", "Carmichael function", "Miller–Rabin test"}
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
        case 4:{
            return QString((a+b).getNumber().GetString().c_str()); // ///////////////// need to add implementation of task 4 fast powering
            break;
        }
    default:
        return "";
        break;
    }
}

QString NumberCalculator::calculate(std::size_t algo_index, const BigModInt& a){
    switch(algo_index){
        case 0:{
            BigModInt result = inverse(a);
            return QString(result.getNumber().GetString().c_str());
            break;
        }
        case 1:{ // factorize (naive)
            BigModInt result = BigModInt(0, 5);
            return QString(result.getNumber().GetString().c_str()); // //////////////////////// need to add implementation of factorize (naive)
            break;
        }
        case 2:{ // factorize (Pollard)
            if (a.getNumber() > MAX || a.getModulus() > MAX){
                throw std::invalid_argument("modulus and number must be < 100000000 (BigInt doesn't not supported by this algo)");
            }

            int n = std::stoi(a.getNumber().GetString());
            std::vector<int> factorization = make_factorize(n);

            QString result;
            for (int factor : factorization){
                result += QString::number(factor) + " ";
            }

            return result; // //////////////////////// need to add implementation of factorize (Pollard)
            break;
        }
        case 3:{
            BigModInt result = BigModInt(0, 5);
            return QString(result.getNumber().GetString().c_str()); // //////////////////////// need to add implementation of Square root (task 6)
            break;
        }
        case 4:{
            BigModInt result = BigModInt(0, 5);
            return QString(result.getNumber().GetString().c_str()); // //////////////////////// need to add implementation of Euler's totient function
            break;
        }
        case 5:{
            BigModInt result = BigModInt(0, 5);
            return QString(result.getNumber().GetString().c_str()); // //////////////////////// need to add implementation of Carmichael function
            break;
        }
        case 6:{
            bool result = true;
            return result ? "true" : "false"; // //////////////////////// need to add implementation of Miller–Rabin test
            break;
        }
        default:{
            return "";
            break;
        }

    }
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
    // ////// add implementation of cyclotomic polynomial order

    return QString("This is a cyclotomic polynomial");
}



PolynomialFieldCalculator::PolynomialFieldCalculator() :
    algorithms_names{"Check for irreducibility", "revert"}
{

}

QString PolynomialFieldCalculator::calc(std::size_t op_index, Polynomial irreducible_pol, ModPolynomial a){
    switch(op_index){
        case 0:{
            return QString("It will be checking for resucibility"); // ////////////////////////// need to add implmentation of chicnking for reducibility
            break;
        }
        case 1:{
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

#include "EulerPhiCarmichaelLambda.h"

#define primeFactors EulerPhiCarmichaelLambda::primeFactors
#define sqrt EulerPhiCarmichaelLambda::sqrt
#define gcd EulerPhiCarmichaelLambda::gcd
#define lcm EulerPhiCarmichaelLambda::lcm

BigInt sqrt(BigInt n) {
    if(n == 0 || n == 1) return n;
    BigInt i = 1, result = 1;
    while(result <= n) {
        i++;
        result = pow(n, 2);
    }
    return n - 1;
};
BigInt gcd (BigInt a, BigInt b) {
    if (a == 0) return b;
    BigInt gcdTemp = gcd(b % a, a);
    return gcdTemp;
}
BigInt lcm(BigInt a, BigInt b) {
    return (a * b) / gcd(a, b);
};

std::vector<primeFactors> EulerPhiCarmichaelLambda::primeFactorization(BigInt n) {
    // find prime factors
    std::vector<BigInt> intermediateResult;
    while (n % 2 == 0) {
        n = n / 2;
        intermediateResult.emplace_back(2);
    }
    for (BigInt i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            intermediateResult.emplace_back(i);
            n = n / i;
        }
    }
    if(n > 2) intermediateResult.push_back(n);
    // compress prime factors
    std::vector<primeFactors> result;
    for (int i = 0; i < intermediateResult.size(); i++) {
        bool mark = false;
        for (int x = 0; x < result.size(); x++) {
            if (result[x].base == intermediateResult[i]) {
                result[x].exponent++;
                mark = true;
                break;
            }
        }
        if (mark) continue;
        result.push_back(primeFactors{intermediateResult[i], 1});
    }
    return result;
}

BigInt EulerPhiCarmichaelLambda::eulerPhi(BigInt n) {
    if(n <= 0) throw std::invalid_argument("Only positive integers");
    if (n == 1) return n;
    else {
        std::vector<primeFactors> primeFactorsTemp = primeFactorization(n);
        if(primeFactorsTemp.size() == 1 && primeFactorsTemp[0].exponent == 1) return n-1;
        BigInt result = 1;
        for (int i = 0; i < primeFactorsTemp.size(); i++) {
            result = result * (pow(primeFactorsTemp[i].base, primeFactorsTemp[i].exponent - 1) * (primeFactorsTemp[i].base - 1));
        }
        return result;
    }
}

BigInt EulerPhiCarmichaelLambda::carmichaelLambda(BigInt n) {
    if(n <= 0) throw std::invalid_argument("Only positive integers");
    if(n == 1) return n;
    std::vector<primeFactors> primeFactorsTemp = primeFactorization(n);
    if(primeFactorsTemp.size() == 1) {
        if(n == 4 || primeFactorsTemp[0].base == n || primeFactorsTemp[0].base != 2) return eulerPhi(n);
        else if(primeFactorsTemp[0].base == 2) return eulerPhi(n) / 2;
    }
    BigInt result = 1;
    for(int i=0; i<primeFactorsTemp.size(); i++) {
        BigInt tempCarmichael = carmichaelLambda(pow(primeFactorsTemp[i].base, primeFactorsTemp[i].exponent));
        result = lcm(result, tempCarmichael);
    }
    return result;
}

#include "PrimeProbabilityChecker.h"
using namespace std;

int main()
{
    PrimeProbabilityChecker checker;
    for (BigInt i = BigInt("123"), length = 100; length > 0; i++, length--) {
        cout << i << " ";
        if (checker.checkBySoloveyShtrassen(i) == checker.checkByFerma(i)) cout << "is correct \n";
        else cout << "WRONG ERROR WEEEUUUU\n";
    }
}

// числа Кармайкла - 561 1105 1729 2465 2821 6601 2911
// Andrii Cherniayev K-29 #6

#pragma once
#include <math.h>
#include "ModularArithmeticLib_global.h"

class MODULARARITHMETICLIB_EXPORT Sqrt
{
private:
	static int gcd(int a, int b);
	static int orderValues(int p, int b);
	static int findx2e(int x, int& e);

public:
	static int powerMod(int base, int exponent, int modulus);
	static int calcSquareRoot(int n, int p);
};

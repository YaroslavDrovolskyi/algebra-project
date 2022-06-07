// Andrii Cherniayev K-29 #6

#pragma once
#include <math.h>

class Sqrt
{
private:
	static int powerMod(int base, int exponent, int modulus);
	static int gcd(int a, int b);
	static int orderValues(int p, int b);
	static int findx2e(int x, int& e);

public:
	int calcSquareRoot(int n, int p);
};
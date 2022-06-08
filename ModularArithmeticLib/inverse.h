#pragma once
#include "big_integers/bigint.h"
#include<vector>
#include<string>
#include <cmath>
using namespace std;



bigint inverse(bigint a, bigint m) {
	if (a % m == bigint(0)|| m % a == bigint(0)) {
		cout << "There is no modular multiplicative inverse for this integer" << endl;
		return bigint(-1);
	}
	if (a == bigint(1)) {
		return a;
	}
	a = a % m;
	bigint x = bigint(1);
	while (x<m) {
		if((a * x) % m == bigint(1)) {
			return x;
		}
		x += bigint(1);
	}
}

bigint power(bigint x,  bigint y,  bigint m) {
	if (y == 0)
		return 1;
	bigint p = power(x, y / 2, m) % m;
	p = (p * p) % m;

	return (y % 2 == 0) ? p : (x * p) % m;
}

bigint gcd_bl(bigint a, bigint b) {
	if (a == 0)
		return b;
	return gcd_bl(b % a, a);
}


bigint modInverse(bigint a, bigint m) {
	bigint g = gcd_bl(a, m);
	if (g != 1) {
		cout << "Inverse doesn't exist";
		return bigint(-1);
	} else {
		return power(a, m - 2, m);
	}
}

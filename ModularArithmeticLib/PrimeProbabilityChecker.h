#pragma once
#include <bits/stdc++.h>
#include "BigModInt.h"
using namespace std;

#define bi(x) BigInt(x)
#define bmi(x, y) BigModInt(x, y)

const BigInt MOD = BigInt(1e9 + 7);

class PrimeProbabilityChecker
{
public:

	bool checkByFerma(BigInt p, int tests = 5) {
		if (p < 10) {
			if (p == 2 || p == 3 || p == 5 || p == 7)
				return true;
			return false;
		}
		for (int i = 2; i <= tests + 1; i++) {
			if (gcd(bi(i), p) != 1) return false;
			BigModInt a(bi(i), p);
			if (fpow(a, p - 1).getNumber() != 1) return false;
		}
		return true;
	}

	bool checkBySoloveyShtrassen(BigInt p, int tests = 5) {
		if (p < 10) {
			if (p == 2 || p == 3 || p == 5 || p == 7)
				return true;
			return false;
		}
		if (p % 2 == 0) return false;
		for (int i = 2; i <= tests + 1; i++) {
			if (gcd(bi(i), p) != 1) return false;
			BigModInt a(bi(i), p);
			BigInt jac = jacobi(bi(i), p);
			if (jac == -1) jac = p - 1;
			if (fpow(a, (p - 1) / 2).getNumber() != jac) return false;
		}
		return true;
	}

private:

	BigInt gcd(BigInt a, BigInt b) { 
		if (a == 0) return b; return gcd(b % a, a);
	}

	BigModInt fpow(BigModInt a, BigInt n) {
		if (n == 0) return bmi(bi(1), a.getModulus());
		if (n % 2 == 1)
			return fpow(a * a, n / 2) * a;
		return fpow(a * a, n / 2);
	}

	BigInt jacobi(BigInt a, BigInt n) {
		if (a < 0) return (((n - 1) / 2) % 2 == 0 ? 1 : -1) * jacobi(a * -1, n);
		a = a % n;
		BigInt t = bi(1);
		while (a != 0) {
			while (a % 2 == 0) {
				a = a / 2;
				BigInt r = n % 8;
				if (r == 3 || r == 5) t = t * -1;
			}
			swap(a, n);
			if (a % 4 == 3 && n % 4 == 3) t = t * -1;
			a = a % n;
		}
		if (n == 1) return t;
		else return 0;
	}
};


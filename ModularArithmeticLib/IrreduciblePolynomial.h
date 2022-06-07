#pragma once
//#include <bits/stdc++.h>
#include "BigModInt.h"
#include "Polynomial.h"
using namespace std;

class IrreduciblePolynomial
{
public:

	bool isIrreducible(Polynomial pol) {
//        cout << pol << endl;
		int n = pol.getPolynomial().size() - 1;
		BigInt p = pol.getFieldModulus();
		if (n == 1) return true;
		Polynomial d("x", p);
		for (int i = 1; i <= n; i++) {
			Polynomial temp = d;
			for (BigInt j(1); j < p; j++) {
				temp = temp * d;
				temp = temp.divide(pol).second;
			}
			d = temp;
			if (n % i == 0 && isPrime(n / i)) {
				Polynomial d_check = d - Polynomial("x", p);
				if (d_check.getPolynomial().size() == 1 && d_check.getPolynomial().front().getNumber() == 0) return false;
				if (d_check.gcd(pol).getPolynomial().size() > 1 || d_check.gcd(pol).getPolynomial()[0].getNumber() != 1) return false;
			}
		}
		d = d - Polynomial("x", p);

		Polynomial reminder = d.divide(pol).second;

		if (reminder.getPolynomial().size() > 1) return false;
		if (reminder.getPolynomial().front().getNumber() != 0) return false;
		return true;
	}

private:

	bool isPrime(int n) {
		if (n == 1) return false;
		for (int i = 2; i * i <= n; i++)
			if (n % i == 0) return false;
		return true;
	}
};


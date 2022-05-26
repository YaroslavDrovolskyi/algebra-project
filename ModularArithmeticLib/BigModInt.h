#pragma once

#ifndef BIGMODINT_H
#define BIGMODINT_H

#include "ModularArithmeticLib_global.h"
#include "BigInt.h"


extern "C++" {
    class MODULARARITHMETICLIB_EXPORT BigModInt{
	private:
		BigInt number;
		BigInt modulus;

	public:
		BigModInt(const BigInt& number, const BigInt& modulus);

        MODULARARITHMETICLIB_EXPORT friend BigModInt operator+(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt operator-(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt operator*(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt operator/(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt inverse(const BigModInt&a);
	};
}

extern "C++" BigModInt operator+(const BigModInt& a, const BigModInt& b);
extern "C++" BigModInt operator*(const BigModInt& a, const BigModInt& b);
extern "C++" BigModInt operator/(const BigModInt& a, const BigModInt& b);



#endif /* BIGMODINT_H */


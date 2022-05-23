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




		friend BigModInt operator+(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator-(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator*(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator/(const BigModInt& a, const BigModInt& b);
		friend BigModInt inverse(const BigModInt&a);
	};
}





#endif /* BIGMODINT_H */


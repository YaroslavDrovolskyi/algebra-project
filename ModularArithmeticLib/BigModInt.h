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
        BigModInt() { number = BigInt(0); modulus = BigInt(2); }
		BigModInt(const BigInt& number, const BigInt& modulus);

        BigInt getNumber() {
            return number;
        }

        void setNumber(const BigInt& number);

        BigInt getModulus() {
            return modulus;
        }

        void setModulus(const BigInt& modulus);

        MODULARARITHMETICLIB_EXPORT friend BigModInt operator+(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt operator-(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt operator*(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt operator/(const BigModInt& a, const BigModInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigModInt inverse(const BigModInt&a);
        MODULARARITHMETICLIB_EXPORT friend bool operator==(const BigModInt& a, const BigModInt& b);

	};
}




#endif /* BIGMODINT_H */


#pragma once

#ifndef BIGMODINT_H
#define BIGMODINT_H

#ifdef MODULARARITHMETICLIB_EXPORTS
#define MODULARARITHMETICLIB_API __declspec(dllexport)
#else
#define MODULARARITHMETICLIB_API __declspec(dllimport)
#endif

#include "BigInt.h"


extern "C++" {
	class BigModInt{
	private:
		BigInt number;
		BigInt modulus;

	public:
		BigModInt(const BigInt& number, const BigInt& modulus);




		friend BigModInt operator+(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator-(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator*(const BigModInt& a, const BigModInt& b);
	};
}





#endif /* BIGMODINT_H */

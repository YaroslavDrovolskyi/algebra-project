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
	class MODULARARITHMETICLIB_API BigModInt{
	private:
		BigInt number;
		BigInt modulus;

	public:
		BigModInt(const BigInt& number, const BigInt& modulus);


		BigInt getNumber() {
			return number;
		}

		void setNumber() {
			this->number = number;
		}

		BigInt getModulus() {
			return number;
		}

		void setModulus() {
			this->number = number;
		}

		friend BigModInt operator+(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator-(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator*(const BigModInt& a, const BigModInt& b);
		friend BigModInt operator/(const BigModInt& a, const BigModInt& b);
		friend BigModInt inverse(const BigModInt&a);

		friend bool operator==(const BigModInt& a, const BigModInt& b);
	};
}





#endif /* BIGMODINT_H */


#include "pch.h"
#include "BigModInt.h"


BigModInt::BigModInt(const BigInt& number, const BigInt& modulus) : number(number), modulus(modulus)
{
	assert(modulus > 1);
	assert(number >= 0);

	this->number = number % modulus;
}


BigModInt operator+(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.number);

	BigInt result_number = (a.number + b.number) % a.modulus;
	return BigModInt(result_number, a.modulus);
}

BigModInt operator*(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.number);

	BigInt result_number = (a.number * b.number) % a.modulus;
	return BigModInt(result_number, a.modulus);
}

BigModInt operator-(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.number);

	BigInt result_number = (a.number - b.number);
	if (result_number < 0) {
		result_number = a.modulus - abs(result_number);
	}
	return BigModInt(result_number, a.modulus);
}

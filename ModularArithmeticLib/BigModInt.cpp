#include "BigModInt.h"
#include <stdexcept>

BigModInt::BigModInt(const BigInt& number, const BigInt& modulus) : number(number), modulus(modulus)
{

    if (modulus <= 1){
        throw std::invalid_argument("Modulus must be > 1");
    }
    if (number < 0){
        throw std::invalid_argument("Number must be >= 0");
    }

	this->number = number % modulus;
}
void BigModInt::setModulus(const BigInt& modulus)
{
    assert(modulus > 1);
    this->modulus = modulus;
    this->number = number % modulus;
}
void BigModInt::setNumber(const BigInt &number)
{
            assert(number >= 0);
            this->number = number;
            this->number = number % modulus;
}
BigModInt operator+(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.modulus);

	BigInt result_number = (a.number + b.number) % a.modulus;
	return BigModInt(result_number, a.modulus);
}

BigModInt operator*(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.modulus);

	BigInt result_number = (a.number * b.number) % a.modulus;
	return BigModInt(result_number, a.modulus);
}

BigModInt operator-(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.modulus);

	BigInt result_number = (a.number - b.number);
	if (result_number < 0) {
		result_number = a.modulus - abs(result_number);
	}
	return BigModInt(result_number, a.modulus);
}

BigModInt operator/(const BigModInt& a, const BigModInt& b) {
	assert(a.modulus == b.modulus);
	BigModInt c = inverse(b);
	BigInt result_number = (a.number * c.number) % a.modulus;
	return BigModInt(result_number,a.modulus);

}

BigModInt inverse(const BigModInt&a) {
    BigInt x, y;
	assert(gcdExtended(a.number, a.modulus, &x, &y) == 1 && "Inverse doesn't exist");
	BigInt result_number;
	while(x<0){
		x = x + a.modulus;
	}
	result_number = (x % a.modulus + a.modulus) % a.modulus;
	return BigModInt(result_number,a.modulus);
}

bool operator==(const BigModInt& a, const BigModInt& b) {
    return (a.modulus == b.modulus && a.number == b.number);
}

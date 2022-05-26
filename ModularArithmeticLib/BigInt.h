#pragma once
#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "ModularArithmeticLib_global.h"

const std::size_t base = 1000000000; // 1 billion -- 10 symbols
std::size_t GetNumberOfDigits(int value);


extern "C++" {
    class MODULARARITHMETICLIB_EXPORT BigInt {
	private:
		bool is_negative_;
		std::vector<int> numbers_;


        void RemoveBeginZeros();
        bool IsCorrectNumber(std::string number);
		friend int CompareAbs(const BigInt& a, const BigInt& b);
		friend int Compare(const BigInt& a, const BigInt& b);
		friend std::pair<BigInt, BigInt> Divide(BigInt& a, BigInt& b);

        MODULARARITHMETICLIB_EXPORT friend BigInt abs(const BigInt& a);
        MODULARARITHMETICLIB_EXPORT friend BigInt gcdExtended(BigInt a, BigInt b, BigInt* x, BigInt* y);

        MODULARARITHMETICLIB_EXPORT friend std::ostream& operator<< (std::ostream& out, const BigInt& a); // print with space in each 3 symbols
        MODULARARITHMETICLIB_EXPORT friend BigInt operator+(const BigInt& a, const BigInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigInt operator-(const BigInt& a, const BigInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigInt operator*(const BigInt& a, const BigInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigInt operator/(const BigInt& a, const BigInt& b);
        MODULARARITHMETICLIB_EXPORT friend BigInt operator%(const BigInt& a, const BigInt& b);

        MODULARARITHMETICLIB_EXPORT friend BigInt operator/(const BigInt& a, int b); // we need it for calculating operator/(BigInt, BigInt)
        MODULARARITHMETICLIB_EXPORT friend BigInt operator%(const BigInt& a, int b);


	public:
        BigInt();
        BigInt(const BigInt& other);
        BigInt(const std::string& number);
		BigInt(int a);

		std::string GetString();
		void Print();

        BigInt& operator++();
        BigInt& operator--();
        BigInt operator++(int);
        BigInt operator--(int);
		BigInt& operator=(const BigInt& other);
		BigInt& operator=(int other);
	};


    MODULARARITHMETICLIB_EXPORT bool operator>(const BigInt& a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator==(const BigInt& a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator!=(const BigInt& a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator<(const BigInt& a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator>=(const BigInt& a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator<=(const BigInt& a, const BigInt& b);

    // other operators for convenience
    MODULARARITHMETICLIB_EXPORT bool operator>(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT bool operator>(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator==(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT bool operator==(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator!=(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT bool operator!=(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator<(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT bool operator<(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator>=(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT bool operator>=(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT bool operator<=(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT bool operator<=(int a, const BigInt& b);

    MODULARARITHMETICLIB_EXPORT BigInt operator+(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT BigInt operator+(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT BigInt operator-(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT BigInt operator-(int a, const BigInt& b);
    MODULARARITHMETICLIB_EXPORT BigInt operator*(const BigInt& a, int b);
    MODULARARITHMETICLIB_EXPORT BigInt operator*(int a, const BigInt& b);




    MODULARARITHMETICLIB_EXPORT BigInt pow(BigInt basis, BigInt exponent);

    struct MODULARARITHMETICLIB_EXPORT NumberWithPow {
		BigInt number;
		BigInt exponent;

		NumberWithPow(BigInt number, BigInt exponent) {
			this->number = number;
			this->exponent = exponent;
		}
	};
}




#endif /* BIGINT_H*/

#pragma once
#ifndef BIGINT_H
#define BIGINT_H

#ifdef MODULARARITHMETICLIB_EXPORTS
#define MODULARARITHMETICLIB_API __declspec(dllexport)
#else
#define MODULARARITHMETICLIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

const std::size_t base = 1000000000; // 1 billion -- 10 symbols
std::size_t GetNumberOfDigits(int value);


extern "C++" {
	class BigInt {
	private:
		bool is_negative_;
		std::vector<int> numbers_;


		void RemoveBeginZeros() {
			while (this->numbers_.size() > 1 && this->numbers_[this->numbers_.size() - 1] == 0) {
				this->numbers_.pop_back();
			}
		}

		bool IsCorrectNumber(std::string number);
		friend int CompareAbs(const BigInt& a, const BigInt& b);
		friend int Compare(const BigInt& a, const BigInt& b);
		friend std::pair<BigInt, BigInt> Divide(BigInt& a, BigInt& b);
		friend BigInt abs(const BigInt& a);



	public:
		BigInt() {
			this->is_negative_ = false;
		}

		BigInt(const BigInt& other) { // copy constructor
			this->is_negative_ = other.is_negative_;
			for (std::size_t i = 0; i < other.numbers_.size(); i++) {
				this->numbers_.push_back(other.numbers_[i]);
			}
		}

		BigInt(std::string number);
		BigInt(int a);

		std::string GetString();
		void Print();

//		std::pair<BigInt, int>AbsShortDivision(int b);

		BigInt& operator++() {
			*this = *this + 1;
			return *this;
		}

		BigInt& operator--() {
			*this = *this - 1;
			return *this;
		}

		BigInt operator++(int) {
			BigInt copy(*this);
			++(*this);
			return copy;
		}

		BigInt operator--(int) {
			BigInt copy(*this);
			--(*this);
			return copy;
		}

		BigInt& operator=(const BigInt& other);
		BigInt& operator=(int other);
		friend std::ostream& operator<< (std::ostream& out, const BigInt& a);
		friend BigInt operator+(const BigInt& a, const BigInt& b);
		friend BigInt operator-(const BigInt& a, const BigInt& b);
		friend BigInt operator*(const BigInt& a, const BigInt& b);
		friend BigInt operator/(const BigInt& a, int b);
		friend BigInt operator%(const BigInt& a, int b);
		friend BigInt operator/(const BigInt& a, const BigInt& b);
		friend BigInt operator%(const BigInt& a, const BigInt& b);

	};


	bool operator>(const BigInt& a, const BigInt& b);
	bool operator==(const BigInt& a, const BigInt& b);
	bool operator!=(const BigInt& a, const BigInt& b);
	bool operator<(const BigInt& a, const BigInt& b);
	bool operator>=(const BigInt& a, const BigInt& b);
	bool operator<=(const BigInt& a, const BigInt& b);
	bool operator>(const BigInt& a, int b);
	bool operator>(int a, const BigInt& b);
	bool operator==(const BigInt& a, int b);
	bool operator==(int a, const BigInt& b);
	bool operator!=(const BigInt& a, int b);
	bool operator!=(int a, const BigInt& b);
	bool operator<(const BigInt& a, int b);
	bool operator<(int a, const BigInt& b);
	bool operator>=(const BigInt& a, int b);
	bool operator>=(int a, const BigInt& b);
	bool operator<=(const BigInt& a, int b);
	bool operator<=(int a, const BigInt& b);



	BigInt operator+(const BigInt& a, int b);
	BigInt operator+(int a, const BigInt& b);
	BigInt operator-(const BigInt& a, int b);
	BigInt operator-(int a, const BigInt& b);
	BigInt operator*(const BigInt& a, int b);
	BigInt operator*(int a, const BigInt& b);


	BigInt pow(BigInt basis, BigInt exponent);

	struct  NumberWithPow {
		BigInt number;
		BigInt exponent;

		NumberWithPow(BigInt number, BigInt exponent) {
			this->number = number;
			this->exponent = exponent;
		}
	};




}




#endif /* BIGINT_H*/
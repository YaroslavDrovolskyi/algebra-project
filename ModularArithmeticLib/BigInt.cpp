#include "BigInt.h"
//#include <iostream>
#include <algorithm>


BigInt::BigInt(std::string number) {
	assert(IsCorrectNumber(number));

	if (number[0] == '-') {
		this->is_negative_ = true;
		number.erase(0, 1);
	}
	else {
		this->is_negative_ = false;
		if (number[0] == '+') {
			number.erase(0, 1);
		}
	}


	for (int i = number.length(); i > 0; i -= 9) {
		if (i < 9) {
			this->numbers_.push_back(stoi(number.substr(0, i)));
		}
		else {
			this->numbers_.push_back(stoi(number.substr(i - 9, 9)));
		}
	}

	RemoveBeginZeros();

	if (this->numbers_.size() == 1 && this->numbers_[0] == 0) {
		this->is_negative_ = false;
	}

}

BigInt::BigInt(int a) {
	if (a < 0) {
		this->is_negative_ = true;
		a = abs(a);
	}
	else {
		this->is_negative_ = false;
	}
	if (a == 0) {
		this->numbers_.push_back(0);
		return;
	}
	while (a > 0) {
		this->numbers_.push_back(a % base);
		a /= base;
	}
}

BigInt& BigInt::operator=(const BigInt& other) {
	this->is_negative_ = other.is_negative_;
	this->numbers_.clear();
	this->numbers_.shrink_to_fit();
	for (std::size_t i = 0; i < other.numbers_.size(); i++) {
		this->numbers_.push_back(other.numbers_[i]);
	}

	return *this;
}

BigInt& BigInt::operator=(int other) {
	(*this) = BigInt(other);
	return (*this);
}


void BigInt::Print() {
	if (this->is_negative_ == true) {
		std::cout << "-";
	}
	std::cout << this->numbers_[this->numbers_.size() - 1];
	for (int i = this->numbers_.size() - 2; i >= 0; i--) {
		printf("%09d", this->numbers_[i]);
	}
}


bool BigInt::IsCorrectNumber(std::string number) {
	if (number.length() < 1) { return false; }

	if (number[0] == '+' || number[0] == '-') {
		number.erase(0, 1);
	}
	if (number.length() == 0) { return false; }

	for (std::size_t i = 0; i < number.length(); i++) {
		if (number[i] < '0' || number[i] > '9') { return false; }
	}

	return true;
}




BigInt operator+(const BigInt& a, const BigInt& b) {
	BigInt result;
	if (a.is_negative_ && b.is_negative_) { // a < 0 && b < 0
		result = abs(a) + abs(b);
		result.is_negative_ = true;
	}
	else if (!a.is_negative_ && b.is_negative_) { // a >= 0 && b < 0
		result = a - abs(b);
	}
	else if (a.is_negative_ && !b.is_negative_) { // a < 0 && b >= 0
		result = b - abs(a);
	}
	else { // a >= 0, b >= 0, it is the basic case
        std::size_t size = std::max(a.numbers_.size(), b.numbers_.size());
		int carry = 0;
		for (std::size_t i = 0; i < size || carry > 0; i++) {
			int a_digit = (i < a.numbers_.size() ? a.numbers_[i] : 0);
			int b_digit = (i < b.numbers_.size() ? b.numbers_[i] : 0);

			int result_digit = a_digit + b_digit + carry;
			if (result_digit >= base) {
				result_digit -= base;
				carry = 1;
			}
			else {
				carry = 0;
			}

			result.numbers_.push_back(result_digit);
		}
	}


	return result;
}


int CompareAbs(const BigInt& a, const BigInt& b) {
	if (a.numbers_.size() > b.numbers_.size()) {
		return -1;
	}
	else if (a.numbers_.size() < b.numbers_.size()) {
		return 1;
	}
	else {
		for (int i = a.numbers_.size() - 1; i >= 0; i--) {
			if (a.numbers_[i] < b.numbers_[i]) { return 1; }
			if (a.numbers_[i] > b.numbers_[i]) { return -1; }
		}
	}

	return 0;
}

int Compare(const BigInt& a, const BigInt& b) {
	if (!a.is_negative_ && b.is_negative_) { return -1; } // a >= 0 && b < 0
	if (a.is_negative_ && !b.is_negative_) { return 1; } // a < 0 && b >= 0
	if (!a.is_negative_ && !b.is_negative_) { // if both are >= 0
		return CompareAbs(a, b);
	}
	else if (a.is_negative_ && b.is_negative_) { // if both are < 0
//		int compare_abs_result = CompareAbs(a, b);
//		if (compare_abs_result == -1) { return 1; }
//		else if (compare_abs_result == 1) { return -1; }
//		else { return 0; }
		return (-1) * CompareAbs(a, b);
	}

	return 0;
}


BigInt abs(const BigInt& a) {
	BigInt new_number(a);
	new_number.is_negative_ = false;

	return new_number;
}


BigInt operator-(const BigInt& a, const BigInt& b) {
	BigInt result;
	if (!a.is_negative_ && b.is_negative_) { // a >= 0 && b < 0
		result = a + abs(b);
	}
	else if (a.is_negative_ && !b.is_negative_) { // a < 0 && b >= 0
		result = abs(a) + b; // b = abs(b)
		result.is_negative_ = true;
	}
	else if (a.is_negative_ && b.is_negative_) { // a < 0 && b < 0
		result = a + abs(b);
	}
	else { // a >= 0 && b >= 0
		if (a < b) {
			result = b - a;
			result.is_negative_ = true;
		}
		else { // if all are OK (a >= b), it is the basic case
			int carry = 0;
			for (std::size_t i = 0; i < a.numbers_.size() || carry > 0; i++) {
				int a_digit = (i < a.numbers_.size() ? a.numbers_[i] : 0);
				int b_digit = (i < b.numbers_.size() ? b.numbers_[i] : 0);

				int result_digit = a_digit - b_digit - carry;
				if (result_digit < 0) {
					result_digit += base;
					carry = 1;
				}
				else {
					carry = 0;
				}

				result.numbers_.push_back(result_digit);
			}
		}
	}

	result.RemoveBeginZeros();
	return result;
}



BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt result;
	result.numbers_.resize(a.numbers_.size() + b.numbers_.size(), 0);

	for (std::size_t i = 0; i < a.numbers_.size(); i++) {
		int carry = 0;
		for (std::size_t j = 0; j < b.numbers_.size() || carry > 0; j++) {
			int b_digit = (j < b.numbers_.size() ? b.numbers_[j] : 0);
			long long current = result.numbers_[i + j] + a.numbers_[i] * 1ll * b_digit + carry;
			result.numbers_[i + j] = current % base;
			carry = current / base;
		}
	}

	result.RemoveBeginZeros();
	if (result.numbers_.size() != 1 || result.numbers_[0] != 0) { // if number isn't 0
		if (a.is_negative_ && !b.is_negative_ || !a.is_negative_ && b.is_negative_) {
			result.is_negative_ = true;
		}
	}

	return result;
}

BigInt operator/(const BigInt& a, int b) {
	assert(b != 0 && "Division by zero is impossible");
	BigInt fraction;
	bool b_negative = false;
	if (b < 0) {
		b_negative = true;
		b = abs(b); // to avoid sign conflict
	}
	int carry = 0;
	for (int i = a.numbers_.size() - 1; i >= 0; i--) {
		long long current = a.numbers_[i] + carry * 1ll * base;
		fraction.numbers_.push_back(current / b);
		carry = current % b;
	}
	std::reverse(fraction.numbers_.begin(), fraction.numbers_.end());
	fraction.RemoveBeginZeros();


	if (fraction.numbers_.size() != 1 || fraction.numbers_[0] != 0) { // if number isn't 0
		if (a.is_negative_ && !b_negative || !a.is_negative_ && b_negative) {
			fraction.is_negative_ = true;
		}
	}
	return fraction;
}

BigInt operator%(const BigInt& a, int b) {
	assert(b != 0 && "Division by zero is impossible");
	assert(!a.is_negative_ && b > 0 && "Impossible to get carry from ");
	BigInt b_big(std::to_string(b));
	return a - b_big * (a / b);
}

bool operator>(const BigInt& a, const BigInt& b) {
	return Compare(a, b) == -1;
}

bool operator==(const BigInt& a, const BigInt& b) {
	return Compare(a, b) == 0;
}

bool operator!=(const BigInt& a, const BigInt& b) {
	return Compare(a, b) != 0;
}

bool operator<(const BigInt& a, const BigInt& b) {
	return Compare(a, b) == 1;
}

bool operator>=(const BigInt& a, const BigInt& b) {
	return Compare(a, b) <= 0; // -1, 0 are possible
}

bool operator<=(const BigInt& a, const BigInt& b) {
	return Compare(a, b) >= 0; // 0, 1 are possible
}

BigInt operator+(const BigInt& a, int b) {
	return a + BigInt(b);
}
BigInt operator+(int a, const BigInt& b) {
	return BigInt(a) + b;
}
BigInt operator-(const BigInt& a, int b) {
	return a - BigInt(b);
}
BigInt operator-(int a, const BigInt& b) {
	return BigInt(a) - b;
}
BigInt operator*(const BigInt& a, int b) {
	return a * BigInt(b);
}
BigInt operator*(int a, const BigInt& b) {
	return BigInt(a) * b;
}



bool operator>(const BigInt& a, int b) {
	return Compare(a, BigInt(b)) == -1;
}

bool operator>(int a, const BigInt& b) {
	return Compare(BigInt(a), b) == -1;
}


bool operator==(const BigInt& a, int b) {
	return Compare(a, BigInt(b)) == 0;
}
bool operator==(int a, const BigInt& b) {
	return Compare(BigInt(a), b) == 0;
}

bool operator!=(const BigInt& a, int b) {
	return Compare(a, BigInt(b)) != 0;
}
bool operator!=(int a, const BigInt& b) {
	return Compare(BigInt(a), b) != 0;
}


bool operator<(const BigInt& a, int b) {
	return Compare(a, BigInt(b)) == 1;
}
bool operator<(int a, const BigInt& b) {
	return Compare(BigInt(a), b) == 1;
}


bool operator>=(const BigInt& a, int b) {
	return Compare(a, BigInt(b)) <= 0; // -1, 0 are possible
}
bool operator>=(int a, const BigInt& b) {
	return Compare(BigInt(a), b) <= 0; // -1, 0 are possible
}


bool operator<=(const BigInt& a, int b) {
	return Compare(a, BigInt(b)) >= 0; // 0, 1 are possible
}
bool operator<=(int a, const BigInt& b) {
	return Compare(BigInt(a), b) >= 0; // 0, 1 are possible
}


std::ostream& operator<< (std::ostream& out, const BigInt& a) {
	if (a.is_negative_ == true) {
		std::cout << "-";
	}
	std::string result;
	result += std::to_string(a.numbers_[a.numbers_.size() - 1]);
	for (int i = a.numbers_.size() - 2; i >= 0; i--) {
		result += std::string(9 - GetNumberOfDigits(a.numbers_[i]), '0');
		result += std::to_string(a.numbers_[i]);
	}

	int carry = result.length() % 3;
	for (std::size_t i = 0; i < result.length(); i++) {
		out << result[i];
		if ((i + 1) % 3 == carry && i != result.length() - 1) {
			out << " ";
		}
	}
	return out;
}

std::string BigInt::GetString() {
	std::string result;
	if (this->is_negative_ == true) {
		result += "-";
	}
	result += std::to_string(this->numbers_[this->numbers_.size() - 1]);
	for (int i = this->numbers_.size() - 2; i >= 0; i--) {
		result += std::string(9 - GetNumberOfDigits(this->numbers_[i]), '0');
		result += std::to_string(this->numbers_[i]);
	}

	return result;
}




BigInt operator/(const BigInt& a, const BigInt& b) {
	assert(b != 0 && "Division by zero is impossible");

		// case with don't clear signs
	if (a.is_negative_ || b.is_negative_) {
		BigInt result = abs(a) / abs(b);
		if (result != 0) {
			if (a.is_negative_ && !b.is_negative_ || !a.is_negative_ && b.is_negative_) {
				result.is_negative_ = true;
			}
		}
		return result;
	}

	BigInt fraction(0);
	BigInt left(0);
	BigInt right = a; // call copy constructor

	while (left <= right) {
		BigInt middle = (left + right) / 2;
		BigInt product = middle * b;
		if (product > a) {
			right = middle - 1;
		}
		else if (product < a) {
			fraction = middle;
			left = middle + 1;

		}
		else {
			fraction = middle;
			break;
		}
	}

	if (fraction.numbers_.size() != 1 || fraction.numbers_[0] != 0) { // if number isn't 0
		if (a.is_negative_ && !b.is_negative_ || !a.is_negative_ && b.is_negative_) {
			fraction.is_negative_ = true;
		}
	}


	return fraction;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
	assert(b != 0 && "Division by zero is impossible");
	assert(!a.is_negative_ && !b.is_negative_ && "Impossible to get carry from ");

	if (a < b) {
		return a;
	}

	return a - b * (a / b);
}


std::size_t GetNumberOfDigits(int value) {
	if (value == 0) { return 1; }
	std::size_t i = 0;
	while (value > 0) {
		i++;
		value /= 10;
	}
	return i;
}

// naive and non-optimal
BigInt pow(BigInt basis, BigInt exponent) {
	assert(exponent >= 0);
	assert(!(basis == 0 && exponent == 0));

	if (basis == 0 || basis == 1) {
		return basis;
	}

	BigInt result = 1;
	for (BigInt i = 1; i <= exponent; i++) {
		result = result * basis;
	}
	return result;
}

BigInt gcdExtended(BigInt a, BigInt b, BigInt* x, BigInt* y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    BigInt x1, y1;
    BigInt gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1; 
    return gcd;
}

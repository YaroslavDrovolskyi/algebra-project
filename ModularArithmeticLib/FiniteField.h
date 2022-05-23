#pragma once

#include "ModularArithmeticLib_global.h"

extern "C++" {
    class MODULARARITHMETICLIB_EXPORT FiniteField {
	public:
		unsigned int modulus;

		FiniteField(unsigned int modulus = 5);
	};
}


#pragma once


#ifdef MODULARARITHMETICLIB_EXPORTS
#define MODULARARITHMETICLIB_API __declspec(dllexport)
#else
#define MODULARARITHMETICLIB_API __declspec(dllimport)
#endif

extern "C++" {
	class FiniteField {
	public:
		unsigned int modulus;

		FiniteField(unsigned int modulus = 5);
	};
}


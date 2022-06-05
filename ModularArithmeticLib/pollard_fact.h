#ifndef ALGEBRA_TASK5_POLLARD_FACT_H
#define ALGEBRA_TASK5_POLLARD_FACT_H

#include <iostream>
#include <vector>
#include <cmath>
#include "ModularArithmeticLib_global.h"
typedef long long LL;

MODULARARITHMETICLIB_EXPORT bool isPrime(LL num); //функція для перевірки числа на простоту

//MODULARARITHMETICLIB_EXPORT LL abs(LL a); //функц для повернення додатнього значення

MODULARARITHMETICLIB_EXPORT LL gcd(LL a,LL b); //рекурсивна функція алгоритму Евкліда для пошуку нсд


MODULARARITHMETICLIB_EXPORT void naive_factorization(LL n);//наївний алгоритм


MODULARARITHMETICLIB_EXPORT int pollard_rho(LL n); // алгоритм полларда


MODULARARITHMETICLIB_EXPORT void factorize(LL n, std::vector<LL>& result); //функц для розкладу числа на множники

MODULARARITHMETICLIB_EXPORT std::vector<LL> make_factorize(LL n); //вектор, що зберігає наші множники (Поллард)

MODULARARITHMETICLIB_EXPORT std::vector<LL> make_factorize2(LL n);// вектор, що зберігає наші множники (Наївний алгоритм)


#endif //ALGEBRA_TASK5_POLLARD_FACT_H

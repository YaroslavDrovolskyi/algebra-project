#ifndef ALGEBRA_TASK5_POLLARD_RHO_FACTORIZATION_H
#define ALGEBRA_TASK5_POLLARD_RHO_FACTORIZATION_H

#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include "ModularArithmeticLib_global.h"

int MAX;
int LMT;
//bool isPrime[MAX];

MODULARARITHMETICLIB_EXPORT void sieve();    //решето Ератосфена


MODULARARITHMETICLIB_EXPORT int abs(int a);     //функц для повернення додатнього значення


MODULARARITHMETICLIB_EXPORT int gcd(int a,int b);    //рекурсивна функція алгоритму Евкліда для пошуку нсд


MODULARARITHMETICLIB_EXPORT int pollard_rho(int n);  //алгоритм полларда



MODULARARITHMETICLIB_EXPORT void factorize(int n, std::vector<int>& result);   //функц для розкладу числа на множники


MODULARARITHMETICLIB_EXPORT std::vector<int> make_factorize(int n); //вектор, що зберігає наші множники


#endif //ALGEBRA_TASK5_POLLARD_RHO_FACTORIZATION_H

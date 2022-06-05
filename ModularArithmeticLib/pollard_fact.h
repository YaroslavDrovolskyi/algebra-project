#ifndef ALGEBRA_TASK5_POLLARD_FACT_H
#define ALGEBRA_TASK5_POLLARD_FACT_H

#include <iostream>
#include <vector>
#include <cmath>
typedef long long LL;

bool isPrime(LL num); //функція для перевірки числа на простоту

LL abs(LL a); //функц для повернення додатнього значення

LL gcd(LL a,LL b); //рекурсивна функція алгоритму Евкліда для пошуку нсд


void naive_factorization(LL n);//наївний алгоритм


int pollard_rho(LL n); // алгоритм полларда


void factorize(LL n, std::vector<LL>& result); //функц для розкладу числа на множники

std::vector<LL> make_factorize(LL n); //вектор, що зберігає наші множники (Поллард)

std::vector<LL> make_factorize2(LL n);// вектор, що зберігає наші множники (Наївний алгоритм)


#endif //ALGEBRA_TASK5_POLLARD_FACT_H

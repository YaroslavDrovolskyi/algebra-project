#ifndef ALGEBRA_TASK7_DISCRETE_LOGARITHM_H
#define ALGEBRA_TASK7_DISCRETE_LOGARITHM_H

//#include<bits/stdc++.h>
#include <unordered_map>
#include "ModularArithmeticLib_global.h"


typedef long long LL;
typedef std::unordered_map < LL, LL > HASH_MAP;
#define remainder first
#define exponent second


MODULARARITHMETICLIB_EXPORT LL floor_sqrt(LL x);


MODULARARITHMETICLIB_EXPORT LL fast_power_modulo(LL a, LL k, LL n);


MODULARARITHMETICLIB_EXPORT LL gcd(LL a, LL b);


MODULARARITHMETICLIB_EXPORT LL inv(LL a, LL b);

//реалізація алгоритму baby-step giant-step
MODULARARITHMETICLIB_EXPORT LL baby_step_giant_step_discrete_logarithm(LL a, LL b, LL n);










#endif //ALGEBRA_TASK7_DISCRETE_LOGARITHM_H


#ifndef ALGEBRA_TASK7_DISCRETE_LOG_H
#define ALGEBRA_TASK7_DISCRETE_LOG_H

#include "ModularArithmeticLib_global.h"

#include "pollard_fact.h"


//#include <bits/stdc++.h>
typedef long long LL;

/*LL floor_sqrt(LL x);*/


//MODULARARITHMETICLIB_EXPORT bool isPrime(LL num);


MODULARARITHMETICLIB_EXPORT LL fast_power(LL base, LL power, LL mod);


//MODULARARITHMETICLIB_EXPORT LL gcd(LL a, LL b);


MODULARARITHMETICLIB_EXPORT LL baby_step_giant_step_discrete_logarithm(LL a, LL b, LL n);


#endif //ALGEBRA_TASK7_DISCRETE_LOG_H

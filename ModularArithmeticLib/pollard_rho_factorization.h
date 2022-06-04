#ifndef ALGEBRA_TASK5_POLLARD_RHO_FACTORIZATION_H
#define ALGEBRA_TASK5_POLLARD_RHO_FACTORIZATION_H

#include <iostream>
#include <vector>
#include <cmath>
typedef long long LL;

bool isPrime(LL num){ //функція для перевірки числа на простоту
    bool flag=true;
    if (num<2)
        return true;
    for(int i = 2; i <= num / 2; i++) {
        if(num % i == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}

LL abs(LL a)     //функц для повернення додатнього значення
{
    return a>0?a:-a;
}
LL gcd(LL a,LL b)    //рекурсивна функція алгоритму Евкліда для пошуку нсд
{
    if(b==0)
        return a;
    else
        return gcd(b,a%b);
}

void naive_factorization(LL n)
{
    n=abs(n);
    while (n%2 == 0)
    {
        std::cout<<2<<std::endl;
        n = n/2;
    }

    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        while (n%i == 0)
        {
            std::cout<<i<<std::endl;
            n = n/i;
        }
    }

    if (n > 2)
        std::cout<<n<<std::endl;
}

int pollard_rho(LL n)  //алгоритм полларда
{
    if(n%2==0)
        return 2;

    LL x = rand()%n+1;
    LL c = rand()%n+1;
    LL y = x;
    LL g = 1;

    //fn is f(x) = x*x + c
    while(g==1)
    {
        x = ((x*x)%n + c)%n;
        y = ((y*y)%n + c)%n;
        y = ((y*y)%n + c)%n;
        g = gcd(abs(x-y),n);
    }
    if(g==n)
    {
        pollard_rho(n);
    }
    return g;
}


void factorize(LL n, std::vector<LL>& result)   //функц для розкладу числа на множники
{
    if(n == 1)
        return;

    if(isPrime(n))
    {
        result.push_back(n);
        return;
    }
    LL divisor = pollard_rho(n);   //отримати дільник n
    factorize(divisor, result);
    factorize(n/divisor, result);
}
std::vector<LL> make_factorize(LL n) //вектор, що зберігає наші множники
{
    n=abs(n);
    std::vector<LL> result;
    factorize(n, result);
    return result;
}

#endif //ALGEBRA_TASK5_POLLARD_RHO_FACTORIZATION_H

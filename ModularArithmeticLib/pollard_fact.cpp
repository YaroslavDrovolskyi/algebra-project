#include "pollard_fact.h"

bool isPrime(LL num)

{
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

LL abs(LL a
)
{
    return a>0?a:-a;
}

LL gcd(LL a,LL b)
{
    if(b==0)
        return a;
    else
        return gcd(b,a%b);
}

void naive_factorization(LL n, std::vector<LL>& result2)
{
    while (n%2 == 0)
    {
        n = n/2;
        result2.push_back(2);
    }

    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        while (n%i == 0)
        {
            result2.push_back(i);
            n = n/i;

        }
    }

    if (n > 2)
    {
        result2.push_back(n);
    }
}

int pollard_rho(LL n)
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

void factorize(LL n, std::vector<LL>& result)
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

std::vector<LL> make_factorize2(LL n)
{
    n=abs(n);
    std::vector<LL> result2;
    naive_factorization(n, result2);
    return result2;
}






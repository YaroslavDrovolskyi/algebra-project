#include "discrete_log.h"
#include <vector>

/*LL floor_sqrt(LL x)
{
    LL res = 0;
    while(res*res <= x)
    {
        ++res;
    }

    return res -1;
}*/

/*
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
*/

LL fast_power(LL base, LL power, LL mod)
{
    LL result = 1;
    while(power>0)
    {
        if(power%2==1)
        {
            result = (result*base) % mod;
        }
        base = (base * base) % mod;
        power = power / 2;
    }
    return result;
}

/*
LL gcd(LL a, LL b)
{
    LL tmp;
    while(b!=0)
    {
        tmp=a%b;
        a=b;
        b=tmp;
    }
    return a;
}
*/

LL baby_step_giant_step_discrete_logarithm(LL a, LL b, LL n)
{
    if(gcd(a, n)!=1)
    {
        return -2;
    }
    if(!isPrime(n))
    {
        return -3;
    }
    if(a>=n || b>=n)
    {
        return -4;
    }

    LL k = int(sqrt(n))+1;
    LL m = int(sqrt(n))+1;

    std::vector<LL> vector1;
    std::vector<LL> vector2;

    LL cur;
    cur=b;
    vector1.push_back(b);
    for(int i=0; i<k; ++i)
    {
        cur=(cur*a)%n;
        vector1.push_back(cur);
    }


    LL cur2;
    for(int i=1; i<=k; ++i)
    {
        cur2=fast_power(a, i*m, n);
        vector2.push_back(cur2);

    }

    LL INF = n+100;
    LL res = INF;

    for (int i=0; i<k; ++i)
    {
        for(int j=0; j<k; ++j)
        {
            if(vector1[i]==vector2[j])
            {
                res=(j+1)*m-i;
                return res;
            }
        }
    }

    return ( res == INF ) ? -1 : res;

}

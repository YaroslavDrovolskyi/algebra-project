#include "pollard_rho_factorization.h"




void sieve()    //решето Ератосфена
{
    MAX = 100000000; //
    LMT = 10000; //
    bool isPrime[MAX]; //

    memset(isPrime, true, sizeof(isPrime));

    int i, k, j;
    isPrime[1] = false;
    for (i = 4; i <= MAX; i+=2)
    {
        isPrime[i] = false;
    }
    for (i = 3; i <= LMT; i+=2)
    {
        if(isPrime[i])
            for (j = i*i, k = i<<1; j <= MAX; j+=k)
            {
                isPrime[j] = false;
            }
    }
}

int abs(int a)     //функц для повернення додатнього значення
{
    return a>0?a:-a;
}
int gcd(int a,int b)    //рекурсивна функція алгоритму Евкліда для пошуку нсд
{
    if(b==0)
        return a;
    else
        return gcd(b,a%b);
}

int pollard_rho(int n)  //алгоритм полларда
{
    if(n%2==0)
        return 2;

    int x = rand()%n+1;
    int c = rand()%n+1;
    int y = x;
    int g = 1;

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


void factorize(int n, std::vector<int>& result)   //функц для розкладу числа на множники
{
    if(n == 1)
        return;

    if(isPrime[n])
    {
        result.push_back(n);
        return;
    }
    int divisor = pollard_rho(n);   //отримати дільник n
    factorize(divisor, result);
    factorize(n/divisor, result);
}
std::vector<int> make_factorize(int n) //вектор, що зберігає наші множники
{
    n=abs(n);
    std::vector<int> result;
    factorize(n, result);
    return result;
}


/*
int main() {

    sieve();

    int n;
    std::cin >> n;

    while (n!=-1)
    {
        std::vector<int> result=make_factorize(n);

        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            std::cout << std::endl;
        }
        std::cin>>n;

    }

    return 0;
}
*/
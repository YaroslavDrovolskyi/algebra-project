#include "discrete_log.h"
#include <cmath>

int main(){
    // Знаходження дсикретного логарифму за допомогою алгоритму baby-step giant-step
    // Дано цілі числа a, b, n (a,b>=0, n>0), ми хочемо знайти таке мінімальне додатнє ціле значення х,
    // що a^x = b (mod n)
    // Дана функція поверне найменший знайдений результат х>0 або х=-1(якщо дискретного логарифму не існує)
    // або х=-2, якщо a та n не взаэмнопрості

    LL a, b, n;
    std::cout<<( "We want to find (using baby-step giant-step algorithm) such a positive integer x that a^x = b (mod n).\nReminder: a,n must be comprise.\n\nData input\nEnter a = " );
    std::cin>>a;
    printf( "\nEnter b = " );
    std::cin>>b;
    printf( "\nEnter n = " );
    std::cin>>n;
    LL x = baby_step_giant_step_discrete_logarithm(a, b, n);

    if(x == -4)
    {
        std::cout<<" a and b must be less than n";
        return 0;
    }
    if(x == -3)
    {
        std::cout<<"n is not prime";
        return 0;
    }
    if( x == -2 ){ // помилка, a та n повинні бути взаємнопростими
        std::cout<<"a and n must be comprise";
        return 0;
    }
    if( x == -1 ){ // нема рішень
        std::cout<<( "\nNo solution\n" );
        return 0;
    }
    std::cout<< x;
   /* LL k = int(sqrt(n))+1;
    LL m = int(sqrt(n))+1;

    std::vector<LL> vector1;
    std::vector<LL> vector2;

    LL cur;
    cur=b;
    //vector1.push_back(b);
    std::cout<<"m = "<<m<<" k="<<k<<std::endl;
    for(int i=0; i<k; ++i)
    {
        cur=(cur*a)%n;
        vector1.push_back(cur);
    }
    std::cout<<"vector1"<<std::endl;

    for (int i=0; i<k; i++)
    {
        std::cout<<vector1[i]<<std::endl;
    }


    LL cur2;
    for(int i=1; i<=k; ++i)
    {
        cur2=fast_power(a, i*m, n);
        vector2.push_back(cur2);
        std::cout<<"cur2="<<cur2<<std::endl;
        std::cout<<"a= "<<a<<std::endl;
        std::cout<<"i*m ="<<i*m<<std::endl;
        std::cout<<"n ="<<n<<std::endl;
    }
    std::cout<<"vector2"<<std::endl;
    for (int i=0; i<k; i++)
    {
        std::cout<<vector2[i]<<std::endl;
    }*/

  /*  LL INF = n+100;
    LL res = INF;*/
   /* for (int i=0; i<k; ++i)
    {
        for(int j=0; j<k; j++)
        {
            if(vector1[i]==vector2[i])
            {
                res=(j+1)*m-i;
                std::cout<<"i="<<i<<"j="<<j<<std::endl;
                std::cout<<"m="<<m;
                std::cout<<res<<std::endl;
            }
        }
    }*/
    return 0;
}


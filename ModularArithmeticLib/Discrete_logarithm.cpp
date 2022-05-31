#include "discrete_logarithm.h"

int main(){

    // Знаходження дсикретного логарифму за допомогою алгоритму baby-step giant-step
    // Дано цілі числа a, b, n (a,b>=0, n>0), ми хочемо знайти таке мінімальне додатнє ціле значення х,
    // що a^x = b (mod n)
    // Дана функція поверне найменший знайдений результат х>0 або х=-1(якщо дискретного логарифму не існує)
    // або х=-2, якщо a та n не взаэмнопрості
    LL a, b, n;
    std::cout<<( "We want to find (using baby-step giant-step algorithm) such a positive integer x that a^x = b (mod n).\nReminder: a,n must be comprise.\n\nData input\nEnter (0 <= a <= 9*10^18):\na = " );
    std::cin>>a;

    printf( "\nEnter (0 <= b <= 9*10^18):\nb = " );
    std::cin>>b;

    printf( "\nEnter (1 <= n <= 10^9):\nn = " );
    std::cin>>n;


    LL x = baby_step_giant_step_discrete_logarithm(a, b, n);


    if( x == -2 ){ // помилка, a та n повинні бути взаємнопростими
        std::cout<<a<<"  "<<n ;
        return 0;
    }

    if( x == -1 ){ // нема рішень
        std::cout<<( "\nNo solution\n" );
        return 0;
    }

    std::cout<< x;

    return 0;
}
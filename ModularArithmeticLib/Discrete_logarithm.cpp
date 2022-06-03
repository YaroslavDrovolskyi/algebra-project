#include "Discrete_logarithm.h"

LL floor_sqrt(LL x){ //знаходження кореня

    LL res = 0;
    while( res*res <= x ){
        ++res;
    }

    return res - 1;
}


LL fast_power_modulo(LL a, LL k, LL n){// modular exponentiation calculator

    a %= n;

    LL res = 1 % n;

    while ( k > 0 ){
        if( k % 2 == 1 ){
            res = (res * a) % n;
        }

        a = (a * a) % n;

        k /= 2;
    }

    return res;
}


LL gcd(LL a, LL b){ //знаходження НСД

    LL tmp;
    while( b != 0 ){
        tmp = a%b;
        a = b;
        b = tmp;
    }

    return a;
}


LL inv(LL a, LL b){ // знаходження u = a^(-1) (mod b)(використовуємо алгоритм евкліда)

    LL u = 1,	v = 0,	w = a;
    LL x = 0,	y = 1,	z = b;


    if( w < z ){
        std::swap( u, x );
        std::swap( v, y );
        std::swap( w, z );
    }


    LL q;
    while( z != 0 ){

        q = w / z;

        u -= q*x;
        v -= q*y;
        w -= q*z;

        std::swap( u, x );
        std::swap( v, y );
        std::swap( w, z );
    }

    if( u < 0 ){
        u += b;// отримуємо додатній розв'язок
    }

    return u;
}

//реалізація алгоритму baby-step giant-step
LL baby_step_giant_step_discrete_logarithm(LL a, LL b, LL n){

    if( gcd(a, n) != 1 ){

        return -2;// помилка, a та n не взаємнопрості
    }

    a %= n;
    b %= n;

    LL k = floor_sqrt( n );

    HASH_MAP baby_remainders, giant_remainders;

    //формуємо першу таблицю, що буде скалдатися зі значень a^(k*i)(mod n)
    LL curr_remainder = a;
    for(int i=1;i<k;++i){
        if( baby_remainders.find( curr_remainder ) == baby_remainders.end() ){
            baby_remainders[ curr_remainder ] = i;
        }

        curr_remainder = (curr_remainder * a) % n;
    }





    // будуємо другу таблицю
    LL inv_a = inv(a, n); // знаходимо a^(-1)(mod b)
    LL a_to_minus_kth_power = fast_power_modulo( inv_a, k, n );// знаходимо a^(-k)(mod n)
    curr_remainder = (b * a_to_minus_kth_power) % n;//знаходимо [ b * a^(-k) ](mod n)

    LL r = 1;
    while( r*k <= n ){
        if( giant_remainders.find( curr_remainder ) == giant_remainders.end() ){
            giant_remainders[ curr_remainder ] = r*k;
        }

        curr_remainder = (curr_remainder * a_to_minus_kth_power) % n;
        ++r;
    }

    if( giant_remainders.find( curr_remainder ) == giant_remainders.end() ){
        giant_remainders[ curr_remainder ] = r*k;
    }

    LL INF = n + 100;
    LL res = INF;

    //шукаємо остачу "b" в таблиці "baby_remainders"
    auto baby_it = baby_remainders.find( b );
    if( baby_it != baby_remainders.end() ){
        res = std::min( res, baby_it -> exponent);
    }


    //шукаємо осатчу "b" в таблиці "giant_reminders"
    auto giant_it = giant_remainders.find( b );
    if( giant_it != giant_remainders.end() ){
        res = std::min( res, giant_it -> exponent );
    }

    //порівнємо дві таблиці та шукаємо спільне значення
    for(auto const& baby_It: baby_remainders ){


        auto giant_It = giant_remainders.find( baby_It.remainder );

        if( giant_It != giant_remainders.end() ){

            res = std::min( res, baby_It.exponent + giant_It -> exponent );

        }

    }



    return ( res == INF ) ? -1 : res;
}


/*
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

*/

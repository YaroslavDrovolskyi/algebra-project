// Andrii Cherniayev K-29 #6

#include <iostream>
#include "sqrt.h"


double Sqrt::PowerOfTen(int num) 
{
    double rst = 1.0;
    if (num >= 0) 
    {
        for (int i = 0; i < num; i++) 
        {
            rst *= 10.0;    
        }   
    }
    else 
    {
        for (int i = 0; i < (0 - num); i++) 
        {
            rst *= 0.1; 
        }   
    }
    
    return rst;
}

double Sqrt::SquareRoot(long long a)
{
    if (a >= 0)
    {
        double z = a;
        double rst = 0.0;
        int max = 8;
        int i;
        double j = 1.0;
        for (i = max; i > 0; i--) {
            if (z - ((2 * rst) + (j * PowerOfTen(i))) * (j * PowerOfTen(i)) >= 0)
            {
                while (z - ((2 * rst) + (j * PowerOfTen(i))) * (j * PowerOfTen(i)) >= 0)
                {
                    j++;
                    if (j >= 10) break;
                }
                j--;
                z -= ((2 * rst) + (j * PowerOfTen(i))) * (j * PowerOfTen(i));
                rst += j * PowerOfTen(i);
                j = 1.0;
            }
        }

        for (i = 0; i >= 0 - max; i--) {
            if (z - ((2 * rst) + (j * PowerOfTen(i))) * (j * PowerOfTen(i)) >= 0)
            {
                while (z - ((2 * rst) + (j * PowerOfTen(i))) * (j * PowerOfTen(i)) >= 0) j++;
                j--;
                z -= ((2 * rst) + (j * PowerOfTen(i))) * (j * PowerOfTen(i));
                rst += j * PowerOfTen(i);
                j = 1.0;
            }
        }
        return rst;
    }
    else
    {
        std::cout << "Isn`t valid value" << std::endl;
    }
}

void main()
{
    std::cout << Sqrt.SquareRoot(12) << std::endl;
}
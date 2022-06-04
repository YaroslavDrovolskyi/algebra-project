#include "pollard_rho_factorization.h"

int main() {
    LL n;
    std::cin >> n;
    if(n==0)
    {
        std::cout<<0;
    }
    if(n==1)
    {
        std::cout<<1;
    }


   /* while (n!=-1)
    {*/
   std::cout<<"pollard factorization"<<std::endl;
    std::vector<LL> result=make_factorize(n);

   for (int i = 0; i < result.size(); ++i)
   {
       std::cout << result[i];
       std::cout << std::endl;
   }
   std::cout<<"Naive factorization"<<std::endl;
   naive_factorization(n);
        //std::cin>>n;

   /* }*/


    return 0;
}

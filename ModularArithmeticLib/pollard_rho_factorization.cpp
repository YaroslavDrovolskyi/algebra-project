#include "pollard_rho_factorization.h"

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

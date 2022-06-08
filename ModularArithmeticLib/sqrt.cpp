// Andrii Cherniayev K-29 #6

#include <iostream>
#include "sqrt.h"

int Sqrt::powerMod(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}
int Sqrt::gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
int Sqrt::orderValues(int p, int b) {
    if (gcd(p, b) != 1) {
        return -1;
    }
    int k = 3;
    while (1) {
        if (powerMod(b, k, p) == 1)
            return k;
        k++;
    }
}
int Sqrt::findx2e(int x, int& e) {
    e = 0;
    while (x % 2 == 0) {
        x /= 2;
        e++;
    }
    return x;
}
int Sqrt::calcSquareRoot(int n, int p) {
    if (gcd(n, p) != 1) {
        return -1;
    }
    if (powerMod(n, (p - 1) / 2, p) == (p - 1)) {
        return -1;
    }
    int s, e;
    s = findx2e(p - 1, e);
    int q;
    for (q = 2; ; q++) {
        if (powerMod(q, (p - 1) / 2, p) == (p - 1))
            break;
    }
    int x = powerMod(n, (s + 1) / 2, p);
    int b = powerMod(n, s, p);
    int g = powerMod(q, s, p);
    int r = e;
    while (1) {
        int m;
        for (m = 0; m < r; m++) {
            if (orderValues(p, b) == -1)
                return -1;
            if (orderValues(p, b) == pow(2, m))
                break;
        }
        if (m == 0)
            return x;
        x = (x * powerMod(g, pow(2, r - m - 1), p)) % p;
        g = powerMod(g, pow(2, r - m), p);
        b = (b * g) % p;
        if (b == 1)
            return x;
        r = m;
    }
}

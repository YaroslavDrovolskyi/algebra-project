#include <iostream>
#include "polynomial_field.h"
#include "polynomial_ring.h"
#include "inverse.h"
#include "big_integers/bigint.h"

//first element, second element, modulus
bigint finFieldInverse(const string& first, const string& second, const string& modulus){
    bigint a(first);
    bigint b(second);
    bigint mod1(modulus);
    bigint i = modInverse(a, b);
    if (i==-1){
        return bigint(0);
    } else {
        return i%mod1;
    }
}
//first poly, second poly, modulus, irreducible poly
polynomial_ring polFieldAddition(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring p2(b, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    polynomial_field c(irreducible);
    return c.addition(p1,p2);
}
//first poly, second poly, modulus, irreducible poly
polynomial_ring polFieldSubtraction(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring p2(b, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    polynomial_field c(irreducible);
    return c.subtract(p1, p2);
}
//first poly, second poly, modulus, irreducible poly
polynomial_ring polFieldMultiply(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring p2(b, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    polynomial_field c(irreducible);
    return c.multiply(p1, p2);
}
//first polynomial, modulus
polynomial_ring polFieldNormality(const string& a, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    p1.normalize();
    return p1;
}
//first poly, second poly, modulus, irreducible poly
polynomial_ring polFieldFastPow(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    bigint degree(b);
    polynomial_ring irreducible(irred, polyMod);
    polynomial_field c(irreducible);
    return c.quickPow(p1, degree);
}
int main(){
	//task 3
	cout << finFieldInverse("5","4","11") << endl;
	//task 18
	cout << polFieldAddition("x^2+x^1+1","2x^2+x^1+2","5","x^5+x^2+1") << endl;
	cout << polFieldSubtraction("x^2+x^1+1","2x^2+x^1+2","5","x^5+x^2+1")<< endl;
	cout << polFieldMultiply("x^2+x^1+1","2x^2+x^1+2","5","x^5+x^2+1")<< endl;
	cout << polFieldNormality("x^2+x^1+1","5")<< endl;
	cout << polFieldFastPow("x^2+x^1+1","3","5","x^5+x^2+1")<< endl;
	
	return 0;
}

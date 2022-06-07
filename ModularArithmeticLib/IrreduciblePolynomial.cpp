#include "IrreduciblePolynomial.h"
using namespace std;

const int MOD = 2;

int main() {
	IrreduciblePolynomial ip;
	if (ip.isIrreducible(Polynomial("x^2 + x + 1", MOD))) cout << "Irreducible\n";
	else cout << "Reducible\n";
}
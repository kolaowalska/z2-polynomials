#include <iostream>
#include "z2_polynomials/Polynomial.h"

int main() {
    std::cout << "Z2 polynomial calculator\n"
              << "enter coefficients in ascending power order: {c0,c1,...,cn}\n"
              << "  e.g.  {1,0,1}  =  x^2 + 1\n\n";

    Polynomial p, q;
    std::cout << "p = ";
    std::cin >> p;
    std::cout << "q = ";
    std::cin >> q;

    std::cout << "\n  p        =  " << p.toString("x")
              << "\n  q        =  " << q.toString("x")
              << "\n  p + q    =  " << (p + q).toString("x")
              << "\n  p - q    =  " << (p - q).toString("x")
              << "\n  p * q    =  " << (p * q).toString("x")
              << "\n  p / q    =  " << (p / q).toString("x")
              << "\n  p mod q  =  " << (p % q).toString("x")
              << "\n";

    return 0;
}

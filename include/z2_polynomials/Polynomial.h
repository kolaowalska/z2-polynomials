#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Z2.h"
#include <iostream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdlib>

class Polynomial {
public:
    unsigned int order;
    Z2* coefficients;

    Polynomial(); 
    Polynomial(unsigned int degree, Z2* coefficients);
    Polynomial(const Polynomial& other); 

    ~Polynomial(); 

    Z2& operator[](unsigned int index) const;
    unsigned int degree() const;
    std::string toString(const std::string xVar) const;

    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

    friend Polynomial operator+(const Polynomial& a, const Polynomial& b);
    friend Polynomial operator-(const Polynomial& a, const Polynomial& b);
    friend Polynomial operator*(const Polynomial& a, const Polynomial& b);
    friend Polynomial operator/(const Polynomial& a, const Polynomial& b);

    friend void mod(const Polynomial u, const Polynomial v, Polynomial& q, Polynomial& r);
    friend Polynomial operator%(const Polynomial &u, const Polynomial &v);

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& polynomial);
    friend std::istream& operator>>(std::istream& in, Polynomial& polynomial);
    friend void optimizePolynomial(Polynomial& polynomial);
};

#endif

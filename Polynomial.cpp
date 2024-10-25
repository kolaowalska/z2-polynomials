#include "Polynomial.h"
#include "Z2.h"
#include <iostream>
#include <sstream>
#include <string>

Polynomial::Polynomial() : order(0), coefficients(new Z2[1]) {}

Polynomial::Polynomial(unsigned int degree, Z2 *coefficients) : order(degree), coefficients(new Z2[degree + 1]) {
    for (unsigned int i = 0; i <= degree; ++i) {
        this->coefficients[i] = coefficients[i];
    }
    optimizePolynomial(*this);
}

Polynomial::Polynomial(const Polynomial &other) : order(other.order), coefficients(new Z2[other.order + 1]) {
    std::memcpy(coefficients, other.coefficients, (order + 1) * sizeof(Z2));
}

Polynomial::~Polynomial() {
    delete[] coefficients;
}

Z2 &Polynomial::operator[](unsigned int index) const {
    if (index > degree()) {
        std::cout << "Niepoprawny indeks wielomianu\n";
        return coefficients[0];
    }
    return coefficients[index];
}

unsigned int Polynomial::degree() const {
    return order;
}

std::string Polynomial::toString(const std::string xVar) const {
    if (degree() == 0 && coefficients[0] == 0) {
        return "0";
    }
    std::stringstream ss;
    bool firstTermAdded = false;

    for (unsigned int i = 0; i <= degree(); ++i) {
        if (coefficients[i] == 0) continue;

        if (firstTermAdded) {
            ss << "+";
        } else {
            firstTermAdded = true;
        }

        if (i == 0) {
            ss << coefficients[i];
        }

        if (i >= 1) {
            ss << xVar;
            ss << "^" << i;
        }
    }
    return ss.str();
}

Polynomial &Polynomial::operator=(const Polynomial &other) {
    if (this != &other) {
        Z2 *new_coefficients = new Z2[other.degree() + 1];
        for (unsigned int i = 0; i <= other.degree(); ++i) {
            new_coefficients[i] = other.coefficients[i];
        }
        delete[] coefficients;
        coefficients = new_coefficients;
        order = other.degree();
    }
    return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &other) {
    unsigned int result_degree = std::max(degree(), other.degree());
    Z2 *result_coefficients = new Z2[result_degree + 1]{Z2()};

    for (unsigned int i = 0; i <= result_degree; ++i) {
        Z2 sum = Z2(0);

        if (i <= degree()) {
            sum += coefficients[i];
        }

        if (i <= other.degree()) {
            sum += other.coefficients[i];
        }

        result_coefficients[i] = sum;
    }

    delete[] coefficients;
    coefficients = result_coefficients;
    order = result_degree;
    optimizePolynomial(*this);

    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &other) {
    unsigned int result_degree = degree() + other.degree();
    Z2 *result_coefficients = new Z2[result_degree + 1]{Z2()};

    for (unsigned int i = 0; i <= degree(); ++i) {
        for (unsigned int j = 0; j <= other.degree(); ++j) {
            result_coefficients[i + j] += coefficients[i] * other.coefficients[j];
        }
    }

    delete[] coefficients;
    coefficients = result_coefficients;
    order = result_degree;
    optimizePolynomial(*this);

    return *this;
}

bool Polynomial::operator==(const Polynomial &other) const {
    if (order != other.order) {
        return false;
    }
    for (unsigned int i = 0; i <= order; ++i) {
        if (coefficients[i] != other.coefficients[i]) {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial &other) const {
    return !(*this == other);
}

Polynomial operator+(const Polynomial &a, const Polynomial &b) {
    unsigned int result_degree = std::max(a.degree(), b.degree());
    Z2 *result_coefficients = new Z2[result_degree + 1]{Z2()};

    for (unsigned int i = 0; i <= result_degree; i++) {
        result_coefficients[i] += i <= a.degree() ? a.coefficients[i] : Z2(0);
        result_coefficients[i] += i <= b.degree() ? b.coefficients[i] : Z2(0);
    }

    Polynomial result = Polynomial(result_degree, result_coefficients);
    optimizePolynomial(result);
    delete[] result_coefficients;

    return result;
}

Polynomial operator-(const Polynomial &a, const Polynomial &b) {
    unsigned int result_degree = std::max(a.degree(), b.degree());
    Z2 *result_coefficients = new Z2[result_degree + 1]{Z2()};

    for (unsigned int i = 0; i <= result_degree; i++) {
        result_coefficients[i] += i <= a.degree() ? a.coefficients[i] : Z2(0);
        result_coefficients[i] += i <= b.degree() ? b.coefficients[i] : Z2(0);
    }

    Polynomial result = Polynomial(result_degree, result_coefficients);
    optimizePolynomial(result);
    delete[] result_coefficients;

    return result;
}

Polynomial operator*(const Polynomial &a, const Polynomial &b) {
    unsigned int result_degree = a.degree() + b.degree();
    Z2 *result_coefficients = new Z2[result_degree + 1]();
    for (unsigned int i = 0; i <= a.degree(); i++) {
        for (unsigned int j = 0; j <= b.degree(); j++) {
            result_coefficients[i + j] += a.coefficients[i] * b.coefficients[j];
        }
    }
    Polynomial result(result_degree, result_coefficients);
    delete[] result_coefficients;
    return result;
}

Polynomial operator/(const Polynomial &u, const Polynomial &v) {
    if (v.degree() == 0 && v[0] == 0) {
        std::cout << "Dzielenie przez zero\n";
        return u;
    }

    if (u.degree() < v.degree() || u == Polynomial()) {
        return Polynomial();
    }

    Polynomial r = u;

    unsigned int degree_difference = r.degree() - v.degree();
    Z2 *aux_coefficients = new Z2[degree_difference + 1]();
    aux_coefficients[degree_difference] = Z2(1);

    Polynomial aux(degree_difference, aux_coefficients);
    delete[] aux_coefficients;

    r = r - (aux * v);
    return aux + (r / v);
}

void mod(const Polynomial u, const Polynomial v, Polynomial &q, Polynomial &r) {
    if (v == Polynomial()) {
        std::cout << "Dzielenie przez zero\n";
        return;
    }

    q = u / v;
    r = u - (q * v);
    optimizePolynomial(r);
    optimizePolynomial(q);
}

Polynomial operator%(const Polynomial &u, const Polynomial &v) {
    if (v == Polynomial()) {
        std::cout << "Dzielenie przez zero\n";
        return Polynomial();
    }
    Polynomial q;
//    mod(u, v, q, r);
    q = u / v;

    return u - (q * v);
}

std::ostream &operator<<(std::ostream &out, const Polynomial &polynomial) {
    out << "{";
    for (unsigned int i = 0; i <= polynomial.degree(); i++) {
        out << polynomial[i];
        if (i < polynomial.degree()) {
            out << ",";
        }
    }
    out << "}";

    return out;
}

std::istream &operator>>(std::istream &in, Polynomial &polynomial) {
    char read;
    Z2 *temp_coeffs = nullptr;
    size_t tempSize = 0;
    size_t tempCapacity;
    bool isValid = true;

    while (in >> read && read != '{');

    tempCapacity = 1;
    temp_coeffs = new Z2[1];

    while (isValid && in >> read && read != '}') {
        if (!isdigit(read)) continue;
        in.putback(read); // jesli znak nie jest przecinkiem/}, wykonaj putback

        Z2 coefficient;
        if (in >> coefficient) {
            if (tempSize < tempCapacity) {
                temp_coeffs[tempSize++] = coefficient;
            } else {
                // tempSize == tempCapacity
                Z2 *new_coeffs = new Z2[tempSize * 2];
                tempCapacity *= 2;

                for (size_t i = 0; i < tempSize; ++i) {
                    new_coeffs[i] = temp_coeffs[i];
                }
                delete[] temp_coeffs;
                temp_coeffs = new_coeffs;
                temp_coeffs[tempSize++] = coefficient;
            }
        }
    }

    if (!isValid || tempSize == 0) {
        delete[] temp_coeffs;
    } else {
        delete[] polynomial.coefficients;
        polynomial.coefficients = temp_coeffs;
        polynomial.order = tempSize - 1;
    }
    return in;
}

void optimizePolynomial(Polynomial &polynomial) {
    int diff = 0;
    for (int i = (int) polynomial.degree(); i >= 0; --i) {
        if (polynomial.coefficients[i] == 0) {
            diff++;
        } else break;
    }

    if (diff == 0) return;

    Polynomial *result;
    if (polynomial.degree() - diff == -1) {
        result = new Polynomial();
    } else {
        result = new Polynomial(polynomial.degree() - diff, polynomial.coefficients);
    }
    std::memcpy(&polynomial, result, sizeof(&result));
    return;
}

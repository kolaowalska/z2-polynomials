#include "Z2.h"

Z2::Z2() : value(0) {}

Z2::Z2(short int value) {
    if (value < 0) {
        value *= -1;
    }
    this->value = value % 2;
}

Z2::operator short int() const {
    return value;
}

Z2& Z2::operator=(const Z2& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

Z2& Z2::operator=(short int other) {
    this -> value = other % 2;
    return *this;
}

Z2& Z2::operator+=(const Z2& z2) {
    value = (value + z2.value) % 2;
    return *this;
}

Z2& Z2::operator*=(const Z2& z2) {
    value = (value * z2.value) % 2;
    return *this;
}

Z2& Z2::operator-=(const Z2& z2) {
    value = (value - z2.value) % 2;
    return *this;
}

Z2& Z2::operator/=(const Z2& z2) {
    if(z2.value == 0){
        std::cout << "Dzielenie przez zero\n";
    } else {
        value = (value * z2.value) % 2;
    }
    return *this;
}

Z2 operator+(const Z2& a, const Z2& b){
    Z2 aux = a;
    aux += b;
    return aux;
}

Z2 operator*(const Z2& a, const Z2& b) {
    Z2 aux = a;
    aux *= b;
    return aux;
}

Z2 operator-(const Z2& a, const Z2& b){
    Z2 aux = a;
    aux -= b;
    return aux;
}

Z2 operator/(const Z2& a, const Z2& b) {
    Z2 aux = a;
    aux /= b;
    return aux;
}

std::ostream& operator<<(std::ostream& out, const Z2& z2) {
    out << z2.value;
    return out;
}

std::istream &operator>>(std::istream &in, Z2 &z) {
    short int aux;
    if (in >> aux) {
        z = Z2(aux);
    }
    return in;
}

bool operator==(const Z2& z, int other) {
    return z.value == (other % 2);
}

bool operator!=(const Z2& z, int other) {
    return z.value != (other % 2);
}

bool operator==(int other, const Z2& z) {
    return (other % 2) == z.value;
}

bool operator!=(int other, const Z2& z) {
    return (other % 2) != z.value;
}

bool operator!=(const Z2& z1, const Z2& z2) {
    return z1.value != z2.value;
}

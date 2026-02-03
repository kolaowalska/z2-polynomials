#ifndef Z2_H
#define Z2_H

#include <iostream>

class Z2 {
public:
    short int value;

    Z2();
    Z2(short int value);
    operator short int() const;

    Z2& operator=(const Z2& other);
    Z2& operator=(short int other);
    Z2& operator+=(const Z2& z2);
    Z2& operator*=(const Z2& z2);
    Z2& operator-=(const Z2& z2);
    Z2& operator/=(const Z2& z2);

    friend Z2 operator+(const Z2& a, const Z2& b);
    friend Z2 operator*(const Z2& a, const Z2& b);
    friend Z2 operator-(const Z2& a, const Z2& b);
    friend Z2 operator/(const Z2& a, const Z2& b);

    friend std::ostream& operator<<(std::ostream& out, const Z2& z2);
    friend std::istream& operator>>(std::istream& in, Z2& z2);

    friend bool operator==(const Z2& z, int other);
    friend bool operator!=(const Z2& z, int other);
    friend bool operator==(int other, const Z2& z);
    friend bool operator!=(int other, const Z2& z);
    friend bool operator!=(const Z2& a, const Z2& b);
};

#endif

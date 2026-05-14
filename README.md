this program implements two classes to handle algebraic operations over the $\mathbb{Z}_2$ field and on polynomials with coefficients in $\mathbb{Z}_2$.

## quick start
### prerequisites

- CMake 4.1+ and a C++20-capable compiler

### usage
```bash
cmake -S . -B build
cmake --build build
```
the executable is at `build/z2_app`.

to run tests:
```bash
cmake --build build --target test
```

## functionalities

the `Z2` class represents elements in the field $\mathbb{Z}_2$ and supports:
1. **constructors**: default and from `short int`
2. **conversion operator**: converts a `Z2` element to `short int`
3. **operators**:
* `+=`, `*=`, `/=`
* `+`, `/`, `*` as global functions returning a new `Z2` object
* `<<` outputting the `Z2` element as an integer to `std::ostream`

the `Polynomial` class implements operations on polynomials with coefficients in $\mathbb{Z}_2$, allowing for any degree, and supports:
1. **constructors**: default and from an array of `Z2` coefficients
2. **operators**: 
* `+=`, `*=`
* `[]` returning the coefficient of the given power
3. `Degree`: returns the polynomial's non-degenerated degree
4. `toString`: outputs the polynomial in text format, ignoring zero terms

additional global functions include:
* `operator+` and `operator*` for polynomial addition and multiplication
* `mod` for computing the quotient and remainder for polynomial division
* `operator/` and `operator%` for division and modulus
* `operator<<` and `operator>>` for outputting and inputting polynomials in a custom format

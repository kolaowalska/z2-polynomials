this program implements two classes to handle algebraic operations over the $\mathbb{Z}_2$ field and on polynomials with coefficients in $\mathbb{Z}_2$.

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

## quick start
### prerequisites

- CMake 4.1+ and a C++20-capable compiler

### build
```bash
cmake -S . -B build
cmake --build build
```

### interactive calculator

`z2_app` reads two polynomials and prints the result of every operation:

```
$ ./build/z2_app
Z2 polynomial calculator
enter coefficients in ascending power order: {c0,c1,...,cn}
  e.g.  {1,0,1}  =  x^2 + 1

p = {1,1,0,1}
q = {1,1}

  p        =  1+x^1+x^3
  q        =  1+x^1
  p + q    =  x^3
  p - q    =  x^3
  p * q    =  1+x^2+x^3+x^4
  p / q    =  x^1+x^2
  p mod q  =  1
```

**note**: coefficient powers are listed in ascending order, so `{1,1,0,1}` means `1 + x + x³`.

### running tests

tests use [Catch2](https://github.com/catchorg/Catch2) (fetched automatically by CMake):

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

to run a specific tag only:

```bash
./build/z2_tests "[z2]"
./build/z2_tests "[polynomial]"
```



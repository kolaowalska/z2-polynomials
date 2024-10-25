This program implements two classes to handle algebraic operations over the $\mathbb{Z}_2\$ field and on polynomials with coefficients in $\mathbb{Z}_2\$.

The `Z2` class represents elements in the field $\mathbb{Z}_2\ = \\{0, 1\\}$ and supports:
1. Constructors: default and from `short int`
2. Conversion operator: converts a `Z2` element to `short int`
3. Operators:
* `+=`, `*=`, `/=`
* `+`, `/`, `*` as global functions returning a new `Z2` object
* `<<` outputting the `Z2` element as an integer to `std::ostream`

The `Polynomial` class implements operations on polynomials with coefficients in $\mathbb{Z}_2\$, allowing for any degree, and supports:
1. Constructors: default and from an array of `Z2` coefficients
2. Operators: 
* `+=`, `*=`
* `[]` returning the coefficient of the given power
3. `Degree`: returns the polynomial's non-degenerated degree
4. `toString`: outputs the polynomial in text format, ignoring zero terms

Additional global functions include:
* `operator+` and `operator*` for polynomial addition and multiplication
* `mod` for computing the quotient and remainder for polynomial division
* `operator/` and `operator%` for division and modulus
* `operator<<` and `operator>>` for outputting and inputting polynomials in a custom format

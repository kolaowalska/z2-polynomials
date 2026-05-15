#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include "z2_polynomials/Z2.h"
#include "z2_polynomials/Polynomial.h"

// Build a Polynomial from a list of int coefficients in ascending power order:
// {c0, c1, ..., cn} represents c0 + c1*x + ... + cn*x^n
static Polynomial makePoly(std::vector<int> coeffs) {
    std::vector<Z2> z2;
    z2.reserve(coeffs.size());
    for (int c : coeffs) z2.push_back(Z2(c));
    return Polynomial(static_cast<unsigned int>(z2.size() - 1), z2.data());
}

// ---------------------------------------------------------------------------
// Z2 tests
// ---------------------------------------------------------------------------

TEST_CASE("Z2 construction", "[z2]") {
    REQUIRE((short int)Z2()    == 0);
    REQUIRE((short int)Z2(0)   == 0);
    REQUIRE((short int)Z2(1)   == 1);
    REQUIRE((short int)Z2(2)   == 0); // 2 mod 2
    REQUIRE((short int)Z2(3)   == 1); // 3 mod 2
    REQUIRE((short int)Z2(-1)  == 1); // abs(-1) mod 2
    REQUIRE((short int)Z2(-4)  == 0); // abs(-4) mod 2
}

TEST_CASE("Z2 addition (characteristic 2)", "[z2]") {
    Z2 z(0), o(1);
    REQUIRE((short int)(z + z) == 0);
    REQUIRE((short int)(z + o) == 1);
    REQUIRE((short int)(o + z) == 1);
    REQUIRE((short int)(o + o) == 0); // 1+1=0 in Z2
}

TEST_CASE("Z2 subtraction equals addition in characteristic 2", "[z2]") {
    Z2 z(0), o(1);
    REQUIRE((short int)(o - o) == 0);
    REQUIRE((short int)(z - o) == 1); // -1 ≡ 1 (mod 2)
    REQUIRE((short int)(o - z) == 1);
    REQUIRE((short int)(z - z) == 0);
}

TEST_CASE("Z2 multiplication", "[z2]") {
    Z2 z(0), o(1);
    REQUIRE((short int)(z * z) == 0);
    REQUIRE((short int)(z * o) == 0);
    REQUIRE((short int)(o * z) == 0);
    REQUIRE((short int)(o * o) == 1);
}

TEST_CASE("Z2 division", "[z2]") {
    Z2 z(0), o(1);
    REQUIRE((short int)(z / o) == 0);
    REQUIRE((short int)(o / o) == 1);
}

TEST_CASE("Z2 compound assignment operators", "[z2]") {
    SECTION("+=") {
        Z2 a(1); a += Z2(1);
        REQUIRE((short int)a == 0);
    }
    SECTION("-=") {
        Z2 a(1); a -= Z2(1);
        REQUIRE((short int)a == 0);
    }
    SECTION("*=") {
        Z2 a(1); a *= Z2(1);
        REQUIRE((short int)a == 1);
    }
    SECTION("/=") {
        Z2 a(1); a /= Z2(1);
        REQUIRE((short int)a == 1);
    }
}

TEST_CASE("Z2 comparison with int", "[z2]") {
    Z2 z(0), o(1);
    REQUIRE(z == 0);  REQUIRE(z != 1);
    REQUIRE(o == 1);  REQUIRE(o != 0);
    REQUIRE(0 == z);  REQUIRE(1 != z);
    REQUIRE(1 == o);  REQUIRE(0 != o);
}

TEST_CASE("Z2 inequality between two Z2 values", "[z2]") {
    REQUIRE(Z2(0) != Z2(1));
    REQUIRE(!(Z2(1) != Z2(1)));
    REQUIRE(!(Z2(0) != Z2(0)));
}

TEST_CASE("Z2 stream output", "[z2]") {
    std::ostringstream oss;
    oss << Z2(0);
    REQUIRE(oss.str() == "0");
    oss.str("");
    oss << Z2(1);
    REQUIRE(oss.str() == "1");
}

TEST_CASE("Z2 stream input", "[z2]") {
    std::istringstream iss("1");
    Z2 z;
    iss >> z;
    REQUIRE((short int)z == 1);

    std::istringstream iss2("0");
    iss2 >> z;
    REQUIRE((short int)z == 0);
}

TEST_CASE("Z2 implicit conversion to short int", "[z2]") {
    short int v = Z2(1);
    REQUIRE(v == 1);
    short int w = Z2(3);
    REQUIRE(w == 1);
}

// ---------------------------------------------------------------------------
// Polynomial tests
// ---------------------------------------------------------------------------

TEST_CASE("Polynomial default construction is the zero polynomial", "[polynomial]") {
    Polynomial p;
    REQUIRE(p.degree() == 0);
    REQUIRE(p[0] == 0);
}

TEST_CASE("Polynomial construction from coefficient array", "[polynomial]") {
    // x^2 + 1: coefficients {1, 0, 1}
    auto p = makePoly({1, 0, 1});
    REQUIRE(p.degree() == 2);
    REQUIRE(p[0] == 1);
    REQUIRE(p[1] == 0);
    REQUIRE(p[2] == 1);
}

TEST_CASE("Polynomial leading zero coefficients are removed on construction", "[polynomial]") {
    // Providing a leading 0 should give degree 2, not 3
    auto p = makePoly({1, 0, 1, 0});
    REQUIRE(p.degree() == 2);
}

TEST_CASE("Polynomial degree", "[polynomial]") {
    REQUIRE(makePoly({1}).degree()       == 0); // constant
    REQUIRE(makePoly({0, 1}).degree()    == 1); // x
    REQUIRE(makePoly({1, 0, 1}).degree() == 2); // x^2 + 1
}

TEST_CASE("Polynomial copy construction", "[polynomial]") {
    auto p = makePoly({1, 1, 0, 1}); // x^3 + x + 1
    Polynomial q = p;
    REQUIRE(q.degree() == p.degree());
    for (unsigned int i = 0; i <= p.degree(); ++i) {
        REQUIRE(q[i] == p[i]);
    }
}

TEST_CASE("Polynomial assignment does not alias", "[polynomial]") {
    auto p = makePoly({1, 0, 1});
    Polynomial q;
    q = p;
    REQUIRE(q == p);
}

TEST_CASE("Polynomial equality and inequality", "[polynomial]") {
    auto p = makePoly({1, 0, 1});
    auto q = makePoly({1, 0, 1});
    auto r = makePoly({1, 1, 1});
    REQUIRE(p == q);
    REQUIRE(p != r);
    REQUIRE(!(p != q));
}

TEST_CASE("Polynomial stream output format is {c0,c1,...,cn}", "[polynomial]") {
    std::ostringstream oss;
    oss << makePoly({1, 0, 1});
    REQUIRE(oss.str() == "{1,0,1}");
}

TEST_CASE("Polynomial stream input skips non-digit prefix", "[polynomial]") {
    std::istringstream iss("someprefix{1,0,1}");
    Polynomial p;
    iss >> p;
    REQUIRE(p.degree() == 2);
    REQUIRE(p[0] == 1);
    REQUIRE(p[1] == 0);
    REQUIRE(p[2] == 1);
}

TEST_CASE("Polynomial stream round-trip", "[polynomial]") {
    auto original = makePoly({1, 1, 0, 1});
    std::ostringstream oss;
    oss << original;
    std::istringstream iss(oss.str());
    Polynomial restored;
    iss >> restored;
    REQUIRE(restored == original);
}

TEST_CASE("Polynomial toString", "[polynomial]") {
    SECTION("zero polynomial") {
        REQUIRE(Polynomial().toString("x") == "0");
    }
    SECTION("constant 1") {
        REQUIRE(makePoly({1}).toString("x") == "1");
    }
    SECTION("x (degree 1, no constant term)") {
        REQUIRE(makePoly({0, 1}).toString("x") == "x^1");
    }
    SECTION("x^2 + 1") {
        REQUIRE(makePoly({1, 0, 1}).toString("x") == "1+x^2");
    }
    SECTION("x^2 + x + 1") {
        REQUIRE(makePoly({1, 1, 1}).toString("x") == "1+x^1+x^2");
    }
    SECTION("custom variable name") {
        REQUIRE(makePoly({0, 1}).toString("t") == "t^1");
    }
}

TEST_CASE("Polynomial addition reduces degree when leading terms cancel", "[polynomial]") {
    // (x^2 + 1) + (x^2 + x) = x + 1 (x^2 cancels in Z2)
    auto p = makePoly({1, 0, 1}); // x^2 + 1
    auto q = makePoly({0, 1, 1}); // x^2 + x
    auto result = p + q;
    REQUIRE(result.degree() == 1);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 1);
}

TEST_CASE("Polynomial addition with different degrees", "[polynomial]") {
    // (x^2 + 1) + x = x^2 + x + 1
    auto result = makePoly({1, 0, 1}) + makePoly({0, 1});
    REQUIRE(result == makePoly({1, 1, 1}));
}

TEST_CASE("Polynomial is its own additive inverse (p + p = 0 in Z2)", "[polynomial]") {
    auto p = makePoly({1, 1, 0, 1}); // x^3 + x + 1
    auto result = p + p;
    REQUIRE(result == Polynomial());
}

TEST_CASE("Polynomial subtraction equals addition in Z2", "[polynomial]") {
    auto p = makePoly({1, 0, 1});
    auto q = makePoly({0, 1, 1});
    REQUIRE(p + q == p - q);
}

TEST_CASE("Polynomial multiplication: (x+1)^2 = x^2+1 in Z2", "[polynomial]") {
    // (x+1)(x+1) = x^2 + 2x + 1 = x^2 + 1  (since 2x ≡ 0)
    auto p = makePoly({1, 1});
    REQUIRE(p * p == makePoly({1, 0, 1}));
}

TEST_CASE("Polynomial multiplication commutativity", "[polynomial]") {
    auto p = makePoly({1, 1});
    auto q = makePoly({1, 0, 1});
    REQUIRE(p * q == q * p);
}

TEST_CASE("Polynomial multiplication by zero polynomial", "[polynomial]") {
    auto p = makePoly({1, 1, 0, 1});
    REQUIRE(p * Polynomial() == Polynomial());
}

TEST_CASE("Polynomial multiplication by constant 1", "[polynomial]") {
    auto p = makePoly({1, 1, 0, 1});
    REQUIRE(p * makePoly({1}) == p);
}

TEST_CASE("Polynomial += is consistent with +", "[polynomial]") {
    auto p = makePoly({1, 0, 1});
    auto q = makePoly({0, 1, 1});
    auto expected = p + q;
    p += q;
    REQUIRE(p == expected);
}

TEST_CASE("Polynomial *=  is consistent with *", "[polynomial]") {
    auto p = makePoly({1, 1});
    auto q = makePoly({1, 0, 1});
    auto expected = p * q;
    p *= q;
    REQUIRE(p == expected);
}

TEST_CASE("Polynomial division: (x^2+1) / (x+1) = (x+1)", "[polynomial]") {
    // (x+1)^2 = x^2+1 in Z2, so the quotient is exact
    auto dividend = makePoly({1, 0, 1}); // x^2 + 1
    auto divisor  = makePoly({1, 1});    // x + 1
    REQUIRE(dividend / divisor == makePoly({1, 1}));
}

TEST_CASE("Polynomial division when degree(u) < degree(v) gives zero", "[polynomial]") {
    auto u = makePoly({1, 1});    // x + 1  (degree 1)
    auto v = makePoly({1, 0, 1}); // x^2+1  (degree 2)
    REQUIRE(u / v == Polynomial());
}

TEST_CASE("Polynomial division by itself gives 1", "[polynomial]") {
    auto p = makePoly({1, 1, 0, 1}); // x^3 + x + 1
    REQUIRE(p / p == makePoly({1}));
}

TEST_CASE("Polynomial mod: Euclidean division identity u = q*v + r", "[polynomial]") {
    auto u = makePoly({1, 1, 0, 1}); // x^3 + x + 1
    auto v = makePoly({1, 1});        // x + 1
    Polynomial q, r;
    mod(u, v, q, r);
    REQUIRE(u == (q * v) + r);
}

TEST_CASE("Polynomial mod: remainder has degree less than divisor", "[polynomial]") {
    auto u = makePoly({1, 1, 0, 1}); // x^3 + x + 1
    auto v = makePoly({1, 1});        // x + 1
    Polynomial q, r;
    mod(u, v, q, r);
    REQUIRE(r.degree() < v.degree());
}

TEST_CASE("Polynomial operator% equals mod remainder", "[polynomial]") {
    auto u = makePoly({1, 1, 0, 1});
    auto v = makePoly({1, 1});
    Polynomial q, r;
    mod(u, v, q, r);
    REQUIRE((u % v) == r);
}

TEST_CASE("Polynomial mod: exact division gives zero remainder", "[polynomial]") {
    // (x^2+1) = (x+1)(x+1), so remainder should be 0
    auto u = makePoly({1, 0, 1}); // x^2 + 1
    auto v = makePoly({1, 1});    // x + 1
    Polynomial q, r;
    mod(u, v, q, r);
    REQUIRE(r == Polynomial());
}

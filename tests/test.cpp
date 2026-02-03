#include "../Z2.h"
#include "../include/z2_polynomials/Polynomial.h"
#include <iostream>
#include <sstream>
using namespace std;
#define LOGGER(x) std::cout << (#x) << "=" << x << std::endl;

int main(){
    Z2 x(1), y(2);

    LOGGER(x);
    LOGGER(y);
    LOGGER(x+y);
    LOGGER(x*y);

    std::istringstream in("sometext{0,1,1}");
    Polynomial w;
    in >> w;
    cout << w << endl;
    cout << w.toString("x") << endl;

    const int N1 = 18;
    const int N2 = 3;
    Z2 d1[N1+1] = {Z2(1),Z2(0),Z2(5),Z2(0),Z2(1),Z2(1),Z2(1),Z2(1),Z2(1)};
    Z2 d2[N2+1] = {Z2(0),Z2(0),Z2(1),Z2(1)};
    d1[N1] = 1;
    Polynomial u(N1,d1), v(N2,d2);
    LOGGER(u);
    LOGGER(v);
    LOGGER(u+v);
    LOGGER(u*v);
    LOGGER((u*v).toString("m"));
    LOGGER((u/v).toString("d"));

    Polynomial q, r;
    mod(u,v,q,r);
    LOGGER(q.toString("q"));
    LOGGER(r.toString("r"));

    return 0;
}

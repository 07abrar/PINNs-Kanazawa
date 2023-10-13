#include<iostream>
#include "dual.h"

int main(){
    Dual x(3);
    Dual y(2);

    /*
    Dual x1(2.0);
    Dual x2 (0.0);

    Dual w1(-3.0);
    Dual w2 (1.0);

    Dual b (6.8813735870195432);

    Dual x1w1 = x1*w1;
    Dual x2w2 = x2*w2;
    Dual x1w1x2w2 = x1w1+x2w2;
    Dual n = x1w1x2w2+b;
    Dual o = tanh(n);

    std::cout << o.getDerivative() << std::endl;
    */
    Dual f = x*y;

    //std::cout << f << std::endl;
    std::cout << f.getDerivative() << std::endl;
    return 0;
}
#include<iostream>
#include "dual.h"
#include "backprop.h"

int main() {
    Value x1(2.0);
    Value x2(0.0);
    Value w1(-3.0);
    Value w2(1.0);
    Value b(6.8813735870195432);

    Value x1w1 = x1 * w1;
    Value x2w2 = x2 * w2;
    Value x1w1x2w2 = x1w1 + x2w2;
    Value n = x1w1x2w2 + b;
    Value o = tanh(n);

    o.backprop();

    std::cout << "Gradient with respect to x1: " << x1.getGradient() << std::endl;
    std::cout << "Gradient with respect to w1: " << x2.getGradient() << std::endl;

    return 0;
}
/*
int main(){
    Dual x(4);
    Dual y(2);
    Dual temp = pow(x,2); 
    //Dual f = temp*y;

    //std::cout << f << std::endl;
    std::cout << temp.getDerivative() << std::endl;
    return 0;
}
*/
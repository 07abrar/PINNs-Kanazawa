#include<iostream>
#include "dual.h"

int main(){
    Dual x(5, 1);
    Dual y(6);

    //Dual f = pow(x,2)*y;
    Dual f = pow(x,2)*y+x*y;

    std::cout << f.getDerivative() << std::endl;
    return 0;
}
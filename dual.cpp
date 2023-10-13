#include "dual.h"

Dual::Dual(){ //default constructor, it initializes val and der to 0.
    this->val = 0; //this-> syntax refers to the current object's members.
    this->der = 0;
}

Dual::Dual(double val){ //initializes val with the given argument and sets der to 0.
    this->val = val;
    this->der = 0;
}

Dual::Dual(double val, double der){ //initializes both val and der with the given arguments.
    this->val = val;
    this->der = der;
}

void Dual::setDerivative(double derivative){ //This method sets the value of der to the passed derivative.
    this->der = derivative;
}

double Dual::getDerivative() const{ //This method returns the value of der. The const keyword ensures the method doesn't modify object members.
    return der;
}

Dual operator+(Dual& u, Dual& v){
    //Overloads the + operator. It returns a new Dual object whose val is the sum of the vals and whose der is the sum of the ders of the two operands.
    u.setDerivative(1);
    v.setDerivative(1);
    return Dual(u.val+v.val);
}

Dual operator*(Dual& u, Dual& v){
    //Overloads the * operator. The val is the product of the vals, and the der is calculated based on the product rule in calculus.
    u.setDerivative(v.val);
    v.setDerivative(u.val);
    return Dual(u.val*v.val);
}

std::ostream& operator<<(std::ostream& os, const Dual& a){
    //Overloads the << operator for std::ostream, allowing you to directly print Dual objects using std::cout.
    os << a.val;
    return os;
}

Dual sin(Dual d){
    return Dual(::sin(d.val), d.der*::cos(d.val));
}

Dual cos(Dual d){
    return Dual(::cos(d.val), -d.der*::sin(d.val));
}

Dual tanh(Dual d){
    return Dual(::tanh(d.val), d.der*(1-::tanh(d.val)*::tanh(d.val)));
}

Dual exp(Dual d){
    return Dual(::exp(d.val), d.der*::exp(d.val));
}

Dual log(Dual d){
    return Dual(::log(d.val), d.der/d.val);
}

Dual pow(Dual d, double p){
    return Dual(::pow(d.val, p), p*::pow(d.val, p-1));
}
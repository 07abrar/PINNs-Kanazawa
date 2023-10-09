#include <iostream>
#include <cmath>

#ifndef DUAL
#define DUAL

class Dual {
    private:
        double val;
        double der;
    
    public:
        Dual();
        Dual(double val);
        Dual(double val, double der);

        double getDerivative() const;
        void setDerivative(double derivative);

        friend Dual operator+(const Dual& u, const Dual& v);
        friend Dual operator-(const Dual& u, const Dual& v);
        friend Dual operator*(const Dual& u, const Dual& v);
        friend Dual operator/(const Dual& u, const Dual& v);

        friend std::ostream& operator<<(std::ostream& os, const Dual& a);

        friend Dual sin(Dual d);
        friend Dual cos(Dual d);
        friend Dual exp(Dual d);
        friend Dual log(Dual d);
        friend Dual abs(Dual d);
        friend Dual pow(Dual d, double p);
};
#endif

Dual::Dual(){
    this->val = 0;
    this->der = 0;
}

Dual::Dual(double val){
    this->val = val;
    this->der = 0;
}

Dual::Dual(double val, double der){
    this->val = val;
    this->der = der;
}

void Dual::setDerivative(double derivative){
    this->der = derivative;
}

double Dual::getDerivative() const{
    return der;
}

Dual operator+(const Dual& u, const Dual& v){
    return Dual(u.val+v.val, u.der+v.der);
}

Dual operator-(const Dual& u, const Dual& v){
    return Dual(u.val-v.val, u.der-v.der);
}

Dual operator*(const Dual& u, const Dual& v){
    return Dual(u.val*v.val, u.der*v.val+u.val*v.der);
}

Dual operator/(const Dual& u, const Dual& v){
    return Dual(u.val/v.val, (u.der*v.val-u.val*v.der)/(v.val*v.val));
}

std::ostream& operator<<(std::ostream& os, const Dual& a){
    os << a.val;
    return os;
}

Dual sin(Dual d){
    return Dual(::sin(d.val), d.der*::cos(d.val));
}

Dual cos(Dual d){
    return Dual(::cos(d.val), -d.der*::sin(d.val));
}

Dual exp(Dual d){
    return Dual(::exp(d.val), d.der*::exp(d.val));
}

Dual log(Dual d){
    return Dual(::log(d.val), d.der/d.val);
}

Dual pow(Dual d, double p){
    return Dual(::pow(d.val, p), p*d.der*::pow(d.val, p-1));
}

int main(){
    Dual x(5, 1);
    Dual y(6);

    Dual f = pow(x,2)*y;

    std::cout << f.getDerivative() << std::endl;
    return 0;
}
#include <iostream>
#include <cmath>

#ifndef DUAL //Preprocessor directive to check if DUAL is not defined. This is to avoid multiple declarations.
#define DUAL //Defines DUAL if it's not already defined. This goes along with the #ifndef to make sure that the following code is only included once.

class Dual {
    private:
        double val;
        double der;
    
    public:
        Dual(); //Declares a default constructor for the class Dual. This allows for creating objects without any arguments.
        Dual(double val); //Declares a constructor that takes a single double argument for the val member.
        Dual(double val, double der); //Declares another constructor that takes two double arguments, one for val and another for der.

        //A default constructor is a constructor that can be called with no arguments. 
        //In C++, if we don't provide any constructor, the compiler generates a default constructor for us.

        //A constructor without content (i.e., an empty body) still serves the purpose of initializing an object.
        //Sometimes the constructor doesn't need to do any additional setup beyond what's already done by the member initializer list or default member initializers.

        double getDerivative() const; //Declares a member function that returns the derivative (der). The const keyword means this function won't modify the object state.
        void setDerivative(double derivative); //Declares a function to set the value of der.

        //The friend syntax is used to give a function or another class access to private and protected members of the class.
        //The operator keyword is used for operator overloading.
        //For example, friend Dual operator+(...); allows us to define custom behavior for the + operator when used with objects of the Dual class.

        friend Dual operator+(Dual& u, Dual& v); 
        friend Dual operator*(Dual& u, Dual& v);

        //Declares friend functions for overloading the + and * operators for objects of type Dual.

        //std::ostream is a stream class to write on files. std::ostream& operator<<(std::ostream& os, const Dual& a); 
        //is overloading the << operator so we can directly use std::cout << dual_object; to print the Dual object.
        friend std::ostream& operator<<(std::ostream& os, const Dual& a); //Overloads the << operator to enable custom output for the Dual class.

        friend Dual sin(Dual d);
        friend Dual cos(Dual d);
        friend Dual tanh(Dual d);
        friend Dual exp(Dual d);
        friend Dual log(Dual d);
        friend Dual abs(Dual d);
        friend Dual pow(Dual d, double p);
};

#endif //Closes the #ifndef DUAL preprocessor directive started earlier. This ensures that the code between #ifndef and #endif is included only once.
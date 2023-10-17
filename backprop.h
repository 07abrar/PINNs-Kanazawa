#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include <functional>

class Value {
    private:
        double data;
        double grad;
        std::set<Value*> prev;
        std::function<void()> backward;
    
    public:
        Value(double data, std::initializer_list<Value*> children = {}, const std::function<void()> &backward = [](){});

        double getGradient() const;

        void backprop();

        friend Value operator+(Value& u, Value& v);
        friend Value operator*(Value& u, Value& v);
        friend Value tanh(Value& d);
};
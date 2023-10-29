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
        Value();
        Value(double data, std::initializer_list<Value*> children = {}, const std::function<void()> &backward = [](){});

        void setGradient(double gradient);
        void setData(double data);

        double getGradient() const;
        double getData() const;
        void getPrev() const;

        void backprop();

        friend std::ostream& operator<<(std::ostream& os, const Value& a);

        friend Value operator+(Value& u, Value& v);
        friend Value operator-(Value& u, Value& v);
        friend Value operator*(Value& u, Value& v);
        friend Value pow(Value& d, double p);
        friend Value tanh(Value& d);
};
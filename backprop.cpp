#include "backprop.h"

Value::Value(){
    this->data = 0.0;
    this->grad = 0.0;
    this->prev = {};
    this->backward = [](){};
}


Value::Value(double data, std::initializer_list<Value*> children, const std::function<void()> &backward){
    this->data = data;
    this->grad = 0.0;
    this->prev = children;
    this->backward = backward;
}

void Value::setGradient(double gradient){
    this->grad = gradient;
}

void Value::setData(double data){
    this->data = data;
}

double Value::getGradient() const{ //This method returns the value of der. The const keyword ensures the method doesn't modify object members.
    return grad;
}

double Value::getData() const{
    return data;
}

void Value::getPrev() const{
    for (auto prev : this->prev) {
        std::cout << prev << " - ";
    }
}

void Value::backprop(){
    std::vector<Value*> topo;
    std::set<Value*> visited;

    std::function<void(Value*)> build_topo = [&](Value* v) {
        if (visited.find(v) == visited.end()) {
            visited.insert(v);
            for (auto child : v->prev) {
                build_topo(child);
            }
            topo.push_back(v);
        }
    };

    build_topo(this);

    // Initialize the grad for the start node
    this->grad = 1.0;

    // Backpropagation
    for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
        (*it)->backward();
    }
}

std::ostream& operator<<(std::ostream& os, const Value& a){
    //Overloads the << operator for std::ostream, allowing you to directly print Dual objects using std::cout.
    os << a.data;
    return os;
}

Value operator+(Value& u, Value& v){
    Value out(u.data+v.data, {&u, &v});
    out.backward = [&]() {
        u.grad += 1.0 * out.grad;
        v.grad += 1.0 * out.grad;
    };
    return out;
}

Value operator-(Value& u, Value& v){
    Value out(u.data-v.data, {&u, &v});
    out.backward = [&]() {
        u.grad += 1.0 * out.grad;
        v.grad += -1.0 * out.grad;
    };
    return out;
}

Value operator*(Value& u, Value& v){
    Value out(u.data*v.data, {&u, &v});
    out.backward = [&]() {
        u.grad += v.data*out.grad;
        v.grad += u.data*out.grad;
    };
    return out;
}

Value pow(Value& d, double p) {
    Value out(::pow(d.data, p), {&d});
    out.backward = [&]() {
        d.grad += p * ::pow(d.data, p - 1)*out.grad;
    };
    return out;
}

Value tanh(Value& d) {
    Value out(::tanh(d.data), {&d});
    out.backward = [&]() {
        d.grad += (1-::tanh(d.data)*::tanh(d.data))*out.grad;
    };
    return out;
}
#include <iostream>
#include <set>
#include <vector>
#include <functional>
#include <cmath>

class Dual {
public:
    double data;
    double grad;
    std::set<Dual*> _prev;
    std::function<void()> _backward;

    Dual(double data, std::initializer_list<Dual*> children = {}, const std::function<void()> &backward = [](){})
        : data(data), grad(0.0), _prev(children), _backward(backward) {}

    void backward() {
        // Build topology in a simple way (not optimized)
        std::vector<Dual*> topo;
        std::set<Dual*> visited;

        std::function<void(Dual*)> build_topo = [&](Dual* v) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                for (auto child : v->_prev) {
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
            (*it)->_backward();
        }
    }
};

Dual operator+(Dual& a, Dual& b) {
    Dual out(a.data + b.data, {&a, &b});
    out._backward = [&]() {
        a.grad += 1.0 * out.grad;
        b.grad += 1.0 * out.grad;
    };
    return out;
}

Dual operator*(Dual& a, Dual& b) {
    Dual out(a.data * b.data, {&a, &b});
    out._backward = [&]() {
        a.grad += b.data*out.grad;
        b.grad += a.data*out.grad;
    };
    return out;
}

/*
Dual tanh(Dual* d) {
    Dual out(::tanh(d->data), {d});
    out._backward = [&]() {
        d->grad += (1-::tanh(d->data)*::tanh(d->data))*out.grad;
    };
    return out;
}
*/

Dual tanh(Dual& d) {
    Dual out(::tanh(d.data), {&d});
    out._backward = [&]() {
        d.grad += (1-::tanh(d.data)*::tanh(d.data))*out.grad;
    };
    return out;
}

int main() {
    Dual x1(2.0);
    Dual x2(0.0);
    Dual w1(-3.0);
    Dual w2(1.0);
    Dual b(6.8813735870195432);

    Dual x1w1 = x1 * w1;
    Dual x2w2 = x2 * w2;
    Dual x1w1x2w2 = x1w1 + x2w2;
    Dual n = x1w1x2w2 + b;
    Dual o = tanh(n);

    o.backward();

    std::cout << "Gradient with respect to x1: " << x1.grad << std::endl;
    std::cout << "Gradient with respect to w1: " << x2.grad << std::endl;

    return 0;
}

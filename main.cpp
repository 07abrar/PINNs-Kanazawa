#include<iostream>
#include "dual.h"
//#include "backprop.h"
#include "neuralnet.h"

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

    int nin = 2;
    Neuron neuron(nin);
    std::vector<Value> inputs = {Value(2.0), Value(3.0)};
    Value output = neuron(inputs);
    std::cout << "Output: " << output << std::endl;
    std::cout << "Neuron Parameters: " << neuron << std::endl;

    int nout = 2;
    Layer layer(nin, nout);
    std::vector<Value> layer_output = layer(inputs);
    std::cout << "Layer Output: ";
    for (const auto& out : layer_output) {
        std::cout << out << ' ';
    }
    std::cout << std::endl;
    std::cout << "Layer Parameters: ";
    for (const auto& param : layer.parameters()) {
        std::cout << param << ' ';
    }
    std::cout << std::endl;

    MLP mlp({2, 3, 1});
    std::vector<Value> mlp_output = mlp(inputs);
    std::cout << "MLP Output: ";
    for (const auto& out : mlp_output) {
        std::cout << out << ' ';
    }
    std::cout << std::endl;
    std::cout << "MLP Parameters: ";
    for (const auto& param : mlp.parameters()) {
        std::cout << param << ' ';
    }
    std::cout << std::endl;

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
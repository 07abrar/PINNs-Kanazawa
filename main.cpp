#include<iostream>
#include "dual.h"
#include "neuralnet.h"

int main() {
    Value x1(2.0);
    Value x2(3.0);
    Value w1(-0.2);
    Value w2(0.5);
    Value b(-0.3);

    Value x1w1 = x1 * w1;
    Value x2w2 = x2 * w2;
    Value x1w1x2w2 = x1w1 + x2w2;
    Value n = x1w1x2w2 + b;
    Value o = tanh(n);

    o.backprop();

    std::cout << "Gradient with respect to x1: " << x1w1x2w2 << std::endl;
    std::cout << "Gradient with respect to w1: " << x1w1x2w2.getGradient() << std::endl;

    std::vector<Value> x = {Value(2.0), Value(3.0)};
    std::vector<Value> w = {Value(-0.2), Value(0.5)};
    Value b2 = Value(-0.3);
    std::vector<Value> xw = {x[0] * w[0], x[1] * w[1]};
    std::vector<Value> xwxw = {xw[0] + xw[1]};
    Value xwb = xwxw[0] + b2;
    Value out2 = tanh(xwb);
    std::cout << "mem address: " << &xw[1] << std::endl;
    std::cout << "parent node: " << std::endl;
    xwxw[0].getPrev();
    std::cout << std::endl;
    out2.backprop();
    std::cout << "mem address: " << &xwxw[0] << std::endl;
    std::cout << "tes1: " << xwxw[0] << std::endl;
    std::cout << "tes2: " << xwxw[0].getGradient() << std::endl;

    std::vector<Value> xw2;
    std::vector<Value> xwxw2;
    for (size_t i = 0; i < x.size(); ++i) {
        Value dummy = x[i] * w[i];
        xw2.push_back(dummy);
    }
    for (size_t i = 0; i < x.size()-1; ++i) {
        if (i == 0) {
            Value dummy = xw2[i] + xw2[i+1];
            xwxw2.push_back(dummy);
        } else {
            Value dummy = xwxw2[i-1] + xw2[i+1];
            xwxw2.push_back(dummy);
        }
    }
    Value xwb2 = xwxw2[xwxw2.size()-1] + b2;
    Value out3 = tanh(xwb2);
    out3.backprop();
    std::cout << "testes1: " << xwxw2[0] << std::endl;
    std::cout << "testes2: " << xwxw2[0].getGradient() << std::endl;

    int nin = 2;
    Neuron neuron(nin);
    std::vector<Value> inputs = {Value(2.0), Value(3.0)};
    Value output = neuron(inputs);
    std::cout << "Output: " << output << std::endl;
    std::cout << "Neuron Parameters: " << neuron << std::endl;
    output.backprop();
    std::cout << "Gradient with respect to neuron: " << inputs[0].getGradient() << std::endl;
    std::cout << "Gradient with respect to neuron: " << inputs[1].getGradient() << std::endl;

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

    std::vector<Value> xs = {Value(2.0), Value(3.0)};
    Value ys = {Value(1.0)};

    // Create a neural network with architecture [2, 2, 1]
    MLP mlptes({2, 2, 1});

    // Train the neural network
    for (int k = 0; k < 10; k++) {
        // Forward pass
        std::vector<Value> ypred = mlptes(xs);

        Value temp = ypred[0] - ys;
        Value loss = pow(temp,2);

        // Backward pass
        mlptes.zeroGradient();
        loss.backprop();

        // Update weights and biases
        mlptes.updateParams(0.01);

        std::cout << k << " " << loss.getData() << std::endl;
    }

    std::vector<Value> yfinal = mlptes(xs);
    std::cout << yfinal[0].getData();
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
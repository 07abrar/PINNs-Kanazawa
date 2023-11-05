#include<iostream>
#include <memory>
#include "dual.h"
#include "neuralnet.h"

int main() {
    Value x1(2.0);
    Value x2(3.0);
    Value x3(4.0);
    Value w1(-0.2);
    Value w2(0.5);
    Value w3(0.3);
    Value b(-0.3);

    Value x1w1 = x1 * w1;
    Value x2w2 = x2 * w2;
    Value x3w3 = x3 * w3;
    Value x1w1x2w2 = x1w1 + x2w2;
    Value x2w2x3w3 = x1w1x2w2 + x3w3;
    Value n = x2w2x3w3 + b;
    Value o = tanh(n);

    o.backprop();

    std::cout << "Gradient with respect to x1: " << o << std::endl;
    std::cout << "Gradient with respect to w1: " << x2w2x3w3.getGradient() << std::endl;

    std::vector<Value> x = {Value(2.0), Value(3.0), Value(4.0)};
    std::vector<Value> w = {Value(-0.2), Value(0.5), Value(0.3)};
    Value b2 = Value(-0.3);
    /*
    std::vector<Value> xw = {x[0] * w[0], x[1] * w[1], x[2] * w[2]};
    std::vector<Value> xwxw = {xw[0] + xw[1]};
    Value dungdung = xwxw[0] + xw[2];
    xwxw.push_back(dungdung);
    Value xwb = xwxw[1] + b2;
    Value out2 = tanh(xwb);
    std::cout << "mem address: " << &xw[1] << std::endl;
    std::cout << "parent node: " << std::endl;
    xwxw[0].getPrev();
    std::cout << std::endl;
    std::cout << "mem address: " << &xw[0] << std::endl;
    std::cout << "tes1: " << xwxw[0] << std::endl;
    out2.backprop();
    std::cout << "tes2: " << xwxw[0].getGradient() << std::endl;
    */
    std::vector<Value> nodeList;
    nodeList.reserve(x.size()*2);
    for (size_t i = 0; i < x.size(); ++i) {
        nodeList.emplace_back(x[i] * w[i]);
    }
    for (size_t i = 0; i < x.size()-1; ++i) {
        if (i == 0) {
            nodeList.emplace_back(nodeList[i] + nodeList[i + 1]);
        } else {
            nodeList.emplace_back(nodeList[x.size() + i - 1] + nodeList[i + 1]);
        }
    }
    nodeList.emplace_back(nodeList.back() + b);
    nodeList.emplace_back(tanh(nodeList.back()));
    std::cout << "testes1: " << nodeList.back() << std::endl;
    //Value out3 = tanh(nodeList.back());
    //std::cout << "testes1: " << out3 << std::endl;
    nodeList[3].getPrev();
    std::cout << std::endl;
    nodeList.back().backprop();
    //out3.backprop();
    //std::cout << "testes2: " << out3.getGradient() << std::endl;
    std::cout << "testes3: " << nodeList[3].getGradient() << std::endl;

    int nin = 3;
    Neuron neuron(nin);
    std::vector<Value> inputs = {Value(2.0), Value(3.0), Value(4.0)};
    Value output = neuron(inputs);
    std::cout << "Output: " << output << std::endl;
    std::cout << "Neuron Parameters: " << neuron << std::endl;
    std::cout << "Get xw: " << std::endl;
    neuron.getXW();
    std::cout << std::endl;
    output.backprop();
    std::cout << "inputs[0]: " << inputs[0] << std::endl;
    std::cout << "inputs[0].gradient: " << inputs[0].getGradient() << std::endl;

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
    Value ys = {Value(3.0)};

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

        std::cout << k << " " << loss.getData() << " " << ypred[0] << std::endl;
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
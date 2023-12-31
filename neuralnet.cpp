#include <random>
#include <cmath>  // for std::tanh
#include <numeric> // for std::inner_product
#include "neuralnet.h"

double randomValue(double min, double max){
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

Neuron::Neuron(int nin) : w(nin) {
    for (int i = 0; i < nin; ++i) {
        w[i] = Value(randomValue(-1.0, 1.0));
    }
    b = Value(randomValue(-1.0, 1.0));
    std::vector<Value> nodeList;
}

Value Neuron::operator()(std::vector<Value>& x){
    
    for (size_t i = 0; i < x.size(); ++i) {
        Value dummy = x[i] * w[i];
        nodeList.push_back(dummy);
    }
    for (size_t i = 0; i < x.size()-1; ++i) {
        if (i == 0) {
            Value dummy = nodeList[i] + nodeList[i+1];
            nodeList.push_back(dummy);
        } else {
            Value dummy = nodeList[x.size()-1+i] + nodeList[i+1];
            nodeList.push_back(dummy);
        }
    }
    Value xwb = nodeList[nodeList.size()-1] + b;
    nodeList.push_back(xwb);
    Value out = tanh(xwb);
    return out;
}

std::vector<Value> Neuron::parameters(){
    std::vector<Value> params = w;
    params.push_back(b);
    return params;
}

std::ostream& operator<<(std::ostream& os, const Neuron& a){
    //Overloads the << operator for std::ostream, allowing you to directly print Dual objects using std::cout.
    os << "Weights: ";
    for (const auto& weight : a.w) {
        os << weight << ' ';  // Assuming Value has an overloaded << operator
    }
    os << "\nBias: " << a.b;  // Assuming Value has an overloaded << operator
    return os;
}

std::vector<Value> Neuron::getWeights() const{
    return w;
}

Value Neuron::getBias() const{
    return b;
}

void Neuron::getXW() const{
    for (auto x : this->nodeList) {
        x.getPrev();
        std::cout << std::endl;
    }
}

void Neuron::zeroGradient() {
    for (auto &param : w) {
        param.setGradient(0.0);
    }
    b.setGradient(0.0);
}

void Neuron::updateParams(double lr) {
    for (auto &param : w) {
        param.setData(param.getData() - lr * param.getGradient());
    }
    b.setData(b.getData() - lr * b.getGradient());
}

Layer::Layer(int nin, int nout) {
    for (int i = 0; i < nout; ++i) {
        neurons.emplace_back(Neuron(nin));
    }
}

std::vector<Value> Layer::operator()(std::vector<Value>& x) {
    std::vector<Value> outs;
    for (auto& neuron : neurons) {
        outs.push_back(neuron(x));
    }
    return outs;
}

std::vector<Value> Layer::parameters() {
    std::vector<Value> params;
    for (auto& neuron : neurons) {
        // Assuming Neuron has a method parameters() that returns std::vector<Value>
        auto neuron_params = neuron.parameters();
        params.insert(params.end(), neuron_params.begin(), neuron_params.end());
    }
    return params;
}

void Layer::zeroGradient() {
    for (auto &neuron : neurons) {
        neuron.zeroGradient();
    }
}

void Layer::updateParams(double lr) {
    for (auto &neuron : neurons) {
        neuron.updateParams(lr);
    }
}

MLP::MLP(std::vector<int> sizes) {
    for (size_t i = 0; i < sizes.size() - 1; ++i) {
        layers.emplace_back(Layer(sizes[i], sizes[i + 1]));
    }
}

std::vector<Value> MLP::operator()(std::vector<Value>& x) {
    std::vector<Value> out = x;
    for (auto& layer : layers) {
        out = layer(out);
    }
    return out;
}

std::vector<Value> MLP::parameters() {
    std::vector<Value> params;
    for (auto& layer : layers) {
        auto layer_params = layer.parameters();
        params.insert(params.end(), layer_params.begin(), layer_params.end());
    }
    return params;
}

void MLP::zeroGradient() {
    for (auto &layer : layers) {
        layer.zeroGradient();
    }
}

void MLP::updateParams(double lr) {
    for (auto &layer : layers) {
        layer.updateParams(lr);
    }
}
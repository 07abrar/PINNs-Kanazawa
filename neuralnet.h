#include <iostream>
#include <vector>
#include "backprop.h"

class Neuron{
    private:
        std::vector<Value> w;
        Value b;
    
    public:
        Neuron(int nin);
        Value operator()(const std::vector<Value>& x);
        
        friend std::ostream& operator<<(std::ostream& os, const Neuron& a);

        std::vector<Value> parameters();
        std::vector<Value> getWeights() const;
        Value getBias() const;
};

class Layer {
    private:
        std::vector<Neuron> neurons;
    public:
        Layer(int nin, int nout);
        std::vector<Value> operator()(const std::vector<Value>& x);
        std::vector<Value> parameters();
};

class MLP {
    private:
        std::vector<Layer> layers;
    public:
        MLP(std::vector<int> sizes);
        std::vector<Value> operator()(const std::vector<Value>& x);
        std::vector<Value> parameters();
};
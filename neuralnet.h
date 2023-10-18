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

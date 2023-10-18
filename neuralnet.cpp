#include <random>
#include <cmath>  // for std::tanh
#include <numeric> // for std::inner_product
#include "neuralnet.h"

double randomValue(double min, double max){
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

Value custom_inner_product(const std::vector<Value>& w, const std::vector<Value>& x, const Value& b) {
    Value sum = b;  // Initialize sum with b
    for (size_t i = 0; i < w.size(); i++) {
        Value temp_w = w[i];  // Create a temporary non-const Value
        Value temp_x = x[i];  // Create a temporary non-const Value
        Value product = temp_w * temp_x;  // Perform multiplication
        sum = sum + product;  // Perform addition
    }
    return sum;
}

Neuron::Neuron(int nin) : w(nin) {
    for (int i = 0; i < nin; ++i) {
        w[i] = Value(randomValue(-1.0, 1.0));
    }
    b = Value(randomValue(-1.0, 1.0));
}

Value Neuron::operator()(const std::vector<Value>& x){
    Value act = custom_inner_product(w, x, b);
    Value out = tanh(act);
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
#pragma once
#include <vector>
#include <iostream>

// CRTP.
template <typename Self>
class SomeNeurons {
public:
    template <typename T>
    void connect_to(T &other);
};

class Neuron : public SomeNeurons<Neuron> {
    friend std::ostream &operator<<(std::ostream &os, const Neuron &obj) {
        for(const Neuron * const n : obj.in) {
            os << n->id << "\t-->\t[" << obj.id << ']' << std::endl;
        }
        for(const Neuron * const n : obj.out) {
            os << '[' << obj.id << "]\t-->\t" << n->id << std::endl;
        }
        return os;
    }

    std::vector<Neuron*> in, out;
    unsigned id;
public:
    Neuron() {
        static unsigned id{1};
        this->id = id++;
    }

    Neuron *begin() {
        return this;
    }
    Neuron *end() {
        return this+1;
    }

    void add_connection_in(Neuron *neuron) {
        in.push_back(neuron);
    }
    void add_connection_out(Neuron *neuron) {
        out.push_back(neuron);
    }
};

class NeuronLayer : public SomeNeurons<NeuronLayer> { // Collection of neurons.
    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &obj) {
        for(const Neuron * const n: obj.neurons) {
            std::cout << *n;
        }
        return os;
    }

    std::vector<Neuron*> neurons;
public:
    NeuronLayer(int count) {
        while(count --> 0) { // count-- > 0, but --> can be seen as tends to.
            Neuron neuron;
            neurons.emplace_back(&neuron);
        }
    }

    auto begin() {
        return neurons.begin();
    }
    auto end() {
        return neurons.end();
    }
};

template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T &other) {
    for(Neuron &from : *static_cast<Self*>(this)) {
        for(Neuron &to : other) {
            from.add_connection_in(&other);
            to.add_connection_out(&from);
        }
    }
}
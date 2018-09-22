#pragma once
#include <vector>
#include <iostream>

// CRTP.
template <typename Self>
class SomeNeurons {
public:
    template <typename T>
    void connect_to(T &other) {
        for(Neuron &from : *static_cast<Self*>(this)) {
            for(Neuron &to : other) {
                from.out.push_back(&other);
                to.in.push_back(from);
            }
        }
    }
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

    void connect_to(Neuron &other) {
        out.push_back(&other);
        other.in.push_back(this);
    }
};

class NeuronLayer : public SomeNeurons<NeuronLayer> { // Collection of neurons.
    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &obj) {
        for(const Neuron * const n: obj.neurons) {
            std::cout << *n;
        }
    }

    std::vector<Neuron*> neurons;
public:
    NeuronLayer(int count) {
        while(count --> 0) { // count-- > 0, but --> can be seen as tends to.
            neurons.emplace_back(Neuron{});
        }
    }

    auto begin() {
        return neurons.begin();
    }
    auto end() {
        return neurons.end();
    }
};
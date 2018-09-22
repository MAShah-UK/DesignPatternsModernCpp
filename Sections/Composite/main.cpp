#include <iostream>
#include <vector>
#include "Graphic.h"
#include "Neuron.h"

void use_graphics() {
    GraphicsGroup root("root");

    Circle c1, c2;
    root.add_graphic(&c1);
    root.add_graphic(&c2);

    GraphicsGroup subgroup("subgroup");
    Circle c3;
    subgroup.add_graphic(&c3);
    root.add_graphic(&subgroup);

    Renderer renderer;
    renderer.draw_to_screen(&root); // Can pass one graphic, or a group of graphics.
}

void use_neurons() {
    Neuron n1, n2;
    n1.connect_to(n2);
    std::cout << n1 << n2 << std::endl;

    NeuronLayer layer1 {2}, layer2{3};
}

int main() {
    use_graphics();
    std::cout << std::endl;
    use_neurons();

    return 0;
}
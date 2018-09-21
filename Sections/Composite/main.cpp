#include <iostream>
#include <vector>

class Graphic {
public:
    virtual void draw() = 0;
};

class Renderer {
public:
    void draw_to_screen(Graphic *graphic) {
        graphic->draw();
    }
};

class Circle : public Graphic {
public:
    void draw() override {
        std::cout << "Circle" << std::endl;
    }
};

// Composite design pattern allows working with a group of graphics
// as if they were just one object, and vice versa.
// Any method that expects a Graphic may receive a single
// Circle object, or a group of graphics, and it'll treat them the same.
class Group : public Graphic {
    std::string name;
    std::vector<Graphic*> graphics;
public:
    Group(const std::string &name) : name{name} {}

    void draw() override {
        std::cout << "Group " << name << " contains: " << std::endl;
        for(const auto &graphic : graphics) {
            graphic->draw();
        }
    }

    void add_graphic(Graphic *graphic) {
        graphics.push_back(graphic);
    }
};

int main() {
    Group root("root");

    Circle c1, c2;
    root.add_graphic(&c1);
    root.add_graphic(&c2);

    Group subgroup("subgroup");
    Circle c3;
    subgroup.add_graphic(&c3);
    root.add_graphic(&subgroup);

    root.draw();

    return 0;
}
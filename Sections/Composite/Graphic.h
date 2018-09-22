#pragma once

#include <string>
#include <vector>
#include <iostream>

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
// Circle object, or a group of graphics, and it'll treat them the same
// because of the common interface.
class GraphicsGroup : public Graphic {
    std::string name;
    std::vector<Graphic*> graphics;
public:
    GraphicsGroup(const std::string &name) : name{name} {}

    void draw() override {
        std::cout << "GraphicsGroup " << name << " contains: " << std::endl;
        for(const auto &graphic : graphics) {
            graphic->draw();
        }
    }

    void add_graphic(Graphic *graphic) {
        graphics.push_back(graphic);
    }
};
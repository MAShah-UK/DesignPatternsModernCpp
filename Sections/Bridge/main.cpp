#include <iostream>
#include <string>

class Renderer {
public:
    virtual void render_circle(float x, float y, float radius) = 0;
};

class RasterRenderer : public Renderer {
public:
    virtual void render_circle(float x, float y, float radius) override {
        std::cout << "Rasterizing a circle of radius: " << radius << std::endl;
    }
};

class VectorRenderer : public Renderer {
public:
    void render_circle(float x, float y, float radius) override {
        std::cout << "Drawing a vector circle of radius: " << radius << std::endl;
    }
};

class Shape {
    Renderer &renderer;
public:
    Shape(Renderer &renderer) : renderer{renderer} {}

    Renderer &get_renderer() {
        return renderer;
    }

    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

class Circle : public Shape {
    float x;
    float y;
    float radius;
public:
    Circle(Renderer &renderer, float x, float y, float radius)
        : Shape{renderer}, x{x}, y{y}, radius{radius} {}

    void draw() override {
        get_renderer().render_circle(x, y, radius);
    }
    void resize(float factor) override {
        radius *= factor;
    }
};

int main() {
    RasterRenderer rasterRenderer;
    Circle raster_circle{rasterRenderer, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

    return 0;
}

/*
Challenge: Use bridge design pattern.
struct Renderer {
    virtual string what_to_render_as() const = 0;
};

struct VectorRenderer : Renderer {
    string what_to_render_as() const override {
        return "lines";
    }
};

struct RasterRenderer : Renderer {
    string what_to_render_as() const override {
        return "pixels";
    }
};

struct Shape {
    const Renderer &renderer;
    string name;

    Shape(const Renderer &renderer, string name)
        : renderer{renderer}, name{name} {}

    string str() const {
        return "Drawing " + name + " as " + renderer.what_to_render_as();
    }
};

struct Triangle : Shape {
    Triangle(const Renderer &renderer)
        : Shape{renderer, "Triangle"}  {}
};

struct Square : Shape {
    Square(const Renderer &renderer)
        : Shape{renderer, "Square"} {}
};
 */
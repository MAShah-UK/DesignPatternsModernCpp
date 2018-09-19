#include <iostream>

int main() {
    return 0;
}

/*
Challenge: Use adapter design pattern.
struct Square {
    int side{};

    explicit Square(int side)
        : side(side) {
    }
};

struct Rectangle {
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle {
    Square square;

    SquareToRectangleAdapter(const Square &square)
        : square{square} {}

    int width() const override {
        return square.side;
    }
    int height() const override {
        return square.side;
    }
};
 */
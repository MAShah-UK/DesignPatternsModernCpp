#pragma once

class Image {
public:
    virtual void draw() = 0;
};

class Bitmap : public Image {
public:
    Bitmap(const std::string& filename) {
        std::cout << "Loading bitmap from " << filename << std::endl;
    }
    void draw() override {
        std::cout << "Drawing bitmap" << std::endl;
    }
};

class LazyBitmap : public Image {
    std::string filename;
    std::unique_ptr<Bitmap> bitmap{};
public:
    LazyBitmap(const std::string& filename)
            : filename{filename} {}
    void draw() override {
        if(!bitmap) {
            bitmap = std::make_unique<Bitmap>(filename);
        }
        bitmap->draw();
    }
};
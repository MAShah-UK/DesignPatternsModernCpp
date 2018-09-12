#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// HELPERS.

template <typename T>
void print(const std::vector<T*> &data, std::ostream &stream = std::cout, bool list_horizontal = true) {
    for(const auto &item : data) {
        stream << *item;
        if(list_horizontal) {
            stream << ". ";
        } else {
            stream << std::endl;
        }
    }
}

// SINGLE RESPONSIBILITY PRINCIPLE.

class Journal {
    std::string title;
    std::vector<std::string> entries;
public:
    Journal(const std::string &title) : title{title} {}

    const std::vector<std::string> &get_entries() const {
        return entries;
    }

    // This is fine because adding entries is very specific to journals.
    void add_entry(const std::string &entry) {
        entries.push_back(entry);
    }
    // Violates the single responsibility principle.
    // This is BAD because saving is a general concept - persistence,
    // and it's not very specific to journals.
    // Other classes may also be saving data and duplicating code,
    // making changes such code will be very inefficient. It's better
    // to localise the persistence concept to one class.
    void save(const std::string &filename) const {
        std::ofstream target(filename);
        for(const std::string &entry : entries) {
            target << entry << std::endl;
        }
    }
};

class PersistenceManager {
public:
    // It's better to separate the persistence code because now the logic only
    // has to be changed in one place. This is an application of the single
    // responsibility principle.
    // Could easily switch from using file system to database.
    static void save(const Journal &journal, const std::string &filename) {
        std::ofstream target(filename);
        for(const std::string &entry : journal.get_entries()) {
            target << entry << std::endl;
        }
    }
};

// OPEN/CLOSED PRINCIPLE.

enum class Colour { red, green, blue };
enum class Size { small, medium, large };

struct Product {
    std::string name;
    Colour colour;
    Size size;
};

std::ostream &operator<<(std::ostream &lhs, const Product &rhs) {
    lhs << rhs.name;
    return lhs;
}

class BadProductFilter {
public:
    // It's alright to use raw pointers, just don't use them to allocate/deallocate.
    std::vector<Product*> by_color(const std::vector<Product*> &products, Colour colour) {
        std::vector<Product*> result;
        for(Product* product : products) {
            if(product->colour == colour) {
                result.push_back(product);
            }
        }
        return result;
    }
    // Violates the open/closed principle.
    // To write new filters are pre-existing class has to be modified every time.
    // This breaks binary compatibility.
    std::vector<Product*> by_size(const std::vector<Product*> &products, Size size) {
        std::vector<Product*> result;
        for(Product* product : products) {
            if(product->size == size) {
                result.push_back(product);
            }
        }
        return result;
    }
    // Violates the open/closed principle again.
    std::vector<Product*> by_size_and_colour(const std::vector<Product*> &products,
                                                    Size size, Colour colour) {
        std::vector<Product*> result;
        for(Product* product : products) {
            if(product->size == size && product->colour == colour) {
                result.push_back(product);
            }
        }
        return result;
    }
};

template <typename T> class Specification { // Specification design pattern.
public:
    virtual bool is_satisfied(const T &item) const = 0;
//    AndSpecification<T> operator&&(const Specification<T> &rhs) const {
//        return AndSpecification(*this, rhs);
//    }
};

template <typename T> class Filter {
public:
    virtual std::vector<T*> filter(const std::vector<T*> &items,
                                   const Specification<T> &spec) = 0;
};

class GoodProductFilter : public Filter<Product> {
public:
    std::vector<Product*> filter(const std::vector<Product*> &items,
                                 const Specification<Product> &spec) override {
        std::vector<Product*> result;
        for(Product *item : items) {
            if(spec.is_satisfied(*item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

class ColourSpecification : public Specification<Product> {
    Colour colour;
public:
    ColourSpecification(Colour colour) : colour {colour} {}
    bool is_satisfied(const Product &item) const override {
        return item.colour == colour;
    }
};

class SizeSpecification : public Specification<Product> {
    Size size;
public:
    SizeSpecification(Size size) : size {size} {}
    bool is_satisfied(const Product &item) const override {
        return item.size == size;
    }
};

template <typename T>
class AndSpecification : public Specification<T> {
    const Specification<T> &lhs, &rhs;
public:
    AndSpecification(const Specification<T> &lhs, const Specification<T> &rhs)
        : lhs {lhs}, rhs {rhs} {}
    bool is_satisfied(const T &item) const override {
        return lhs.is_satisfied(item) && rhs.is_satisfied(item);
    }
};

// LISKOV SUBSTITUTION PRINCIPLE.

class Rectangle {
    int width, height;
public:
    Rectangle(int width, int height) : width{width}, height{height} {}

    int getWidth() const {
        return width;
    }
    virtual void setWidth(int width) {
        Rectangle::width = width;
    }
    int getHeight() const {
        return height;
    }
    virtual void setHeight(int height) {
        Rectangle::height = height;
    }

    int area() {
        return width * height;
    }
};

// Makes mathematical sense since square is a special case of a rectangle,
// but in code you cannot treat it as such as it violates LSP.
class Square : public Rectangle {
public:
    Square(int size) : Rectangle{size, size} {}

    // Violates Liskov substitution principle.
    // Using the Square class in the same context as a Rectangle class can give
    // inconsistent outputs.

    void setWidth(int width) override {
        Rectangle::setWidth(width);
        Rectangle::setHeight(width);
    }

    void setHeight(int height) override {
        setWidth(height);
    }
};

void print_area(Rectangle &rectangle) {
    int width = rectangle.getWidth();
    rectangle.setHeight(10);
    std::cout << "Expected area: " << width * 10
              << ", Actual area: " << rectangle.area();
}

// INTERFACE SEGREGATION PRINCIPLE.

class Document {
    //...
};

class IMachine { // Seems reasonable, but can lead to ISP violation if a device can't do all three.
public:
    virtual void print(const Document &doc) = 0;
    virtual void scan(const Document &doc) = 0;
    virtual void fax(const Document &doc) = 0;
};

class OkayMultiFunctionPrinter : public IMachine {
public:
    void print(const Document &doc) override {
        // Makes sense for MFP.
    }

    void scan(const Document &doc) override {
        // Makes sense for MFP.
    }

    void fax(const Document &doc) override {
        // Makes sense for MFP.
    }
};

class BadScanner : public IMachine {
public:
    void print(const Document &doc) override {
        // Violates ISP: doesn't make sense for a scanner.
    }

    void scan(const Document &doc) override {
        // Makes sense for a scanner.
    }

    void fax(const Document &doc) override {
        // Violates ISP: doesn't make sense for a scanner.
    }
};

class IPrinter {
public:
    virtual void print(const Document &doc) = 0;
};

class IScanner {
public:
    virtual void scan(const Document &doc) = 0;
};

class IFax {
public:
    virtual void fax(const Document &doc) = 0;
};

class IMultiMachine : public IPrinter, public IScanner, public IFax {};

class GoodMultiFunctionPrinter : public IMultiMachine {
    void print(const Document &doc) override {
        // Makes sense for MFP.
    }

    void scan(const Document &doc) override {
        // Makes sense for MFP.
    }

    void fax(const Document &doc) override {
        // Makes sense for MFP.
    }
};

class GoodScanner : public IScanner {
public:
    void scan(const Document &doc) override {
        // Makes sense for a scanner.
    }
};

// MAIN.

int main() {
    // Single responsibility principle: each class focuses on one specific area of concern.
    Journal journal {"Dear Diary"};
    journal.add_entry("I ate a bug.");
    journal.add_entry("I cried today.");
    journal.save("Diary.txt");  // Bad: violates SRP.
    PersistenceManager::save(journal, "Diary.txt");

    // Open/closed principle: code entities are open for extension/inheritance, but closed for modification.
    Product apple {"Apple", Colour::green, Size::small};
    Product tree {"Tree", Colour ::green, Size::large};
    Product house {"House", Colour::blue, Size::large};
    std::vector<Product*> products {&apple, &tree, &house};
    BadProductFilter bpf;
    GoodProductFilter gpf;

    auto green_products = bpf.by_color(products, Colour::green); // Bad: violates OCP.
    auto blue_products = gpf.filter(products, ColourSpecification(Colour::blue));
    AndSpecification green_large_spec {ColourSpecification(Colour::green), SizeSpecification(Size::large)};
    auto green_large_products = gpf.filter(products, green_large_spec);

    std::cout << "Green products are: ";
    print(green_products);
    std::cout << std::endl
              << "Blue products are: ";
    print(blue_products);
    std::cout << std::endl
              << "Green/large products are: ";
    print(green_large_products);
    std::cout << std::endl << std::endl;

    // Liskov substitution principle: derived types should be able to substitute base types.
    std::cout << "Area for a 5 x 12 rectangle." << std::endl;
    Rectangle rectangle(5, 12);
    print_area(rectangle);
    std::cout << std::endl
              << "Area for a 5 x 5 square." << std::endl;
    Square square(5);
    print_area(square); // Bad: violates LSP.
    std::cout << std::endl << std::endl;

    // Interface segragation principle: keep interfaces concise.

    return 0;
}
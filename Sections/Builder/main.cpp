#include <iostream>
#include <sstream>
#include <vector>
#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

// BUILDER DESIGN PATTERN.

class HtmlElement { // Represents a tag.
    const size_t indent_size {2};
    std::string name, text;
    std::vector<HtmlElement> elements;
public:
    HtmlElement(const std::string &name = "", const std::string &text = "")
        : name{name}, text{text} {}

//    static HtmlBuilder build(std::string root_name) {
//        return {root_name};
//    }

    std::vector<HtmlElement> &get_elements() {
        return elements;
    }

    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indent_size*indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if(text.size() > 0) {
            oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;
        }
        for(const auto &elem : elements) {
            oss << elem.str(indent+1);
        }
        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

class HtmlBuilder { // Builder design pattern.
    HtmlElement root;
public:
    HtmlBuilder(const std::string &name) :
        root{name} {}

    HtmlBuilder &add_child(std::string child_name, std::string child_text) {
        HtmlElement e {child_name, child_text};
        root.get_elements().emplace_back(e);
        return *this; // Enables method chaining for fluent interface.
    }

    std::string str() const { // Explicit type conversion.
        return root.str();
    }

    operator HtmlElement() const { // Implicit type conversion.
        return root;
    }
};

// DOMAIN SPECIFIC LANGUAGE.

class Tag {
    friend std::ostream &operator<<(std::ostream &lhs, const Tag &tag) {
        lhs << "<" << tag.name;
        for(const auto &att : tag.attributes) {
            lhs << " " << att.first << "=\"" << att.second << "\"";
        }
        if(tag.children.size()==0 && tag.text.length()==0) {
            lhs << "/>" << std::endl;
        } else {
            lhs << ">" << std::endl;
            if(tag.text.length()) {
                lhs << tag.text << std::endl;
            }
            for(const auto &child : tag.children) {
                lhs << child;
            }
            lhs << "</" << tag.name << ">" << std::endl;
        }
        return lhs;
    }

    std::string name, text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;
public:
    Tag(const std::string &name, const std::string &text)
        : name{name}, text{text} {}
    Tag(const std::string &name, const std::vector<Tag> &children)
        : name{name}, children{children} { }

    Tag &add_attribute(const std::pair<std::string, std::string> &attribute) {
        attributes.emplace_back(attribute);
        return *this;
    }
};

class P : public Tag {
public:
    P(const std::string &text)
        : Tag{"p", text} {}
    P(const std::initializer_list<Tag> &children)
        : Tag{"p", children} {}
};

class IMG : public Tag {
public:
    explicit IMG(const std::string &url) // explicit means only a string can be used to construct IMG.
        : Tag{"img", ""} {
        add_attribute({"src", url});
    }
};

int main() {
    // This is bad code since it doesn't take advantage of OOP.
    // Although it works and produces the desired output, it won't scale.
    // It could be improved via the builder design pattern.
    const char text[6] {"hello"};
    std::string output {"<p>"}; // Paragraph tag.
    output += text;
    output += "</p>";
    std::cout << output << std::endl;

    std::string items[] {"hello", "world"};
    std::ostringstream oss;
    oss << "<ul>" << std::endl; // Unordered list tag.
    for(const auto &item : items) {
        oss << "    <li>" << item << "</li>" << std::endl; // List item tag.
    }
    oss << "</ul>";
    std::cout << oss.str() << std::endl << std::endl;

    // Builder design pattern: allows building an object step-by-step.
    // In this case HtmlBuilder builds HtmlElement.
    HtmlBuilder list_builder {"ul"};
    list_builder.add_child("li", "hello")
                .add_child("li", "world");
    std::cout << list_builder.str() << std::endl;

    std::cout << // Can build domain specific language (DSL) via initializer list.
    P {
        IMG {"http://pokemon.com/pikachu.png"}
    }
    << std::endl << std::endl;

    // Multiple builder design patterns.

    Person person = Person::create()
            .lives().at("123 London Road")
                    .with_postcode("SW1 1GB")
                    .in("London")
            .works().at("PragmaSoft")
                    .as_a("Consultant")
                    .earning(10e6);
    std::cout << "Person information: " << std::endl
              << person << std::endl << std::endl;

    return 0;
}

/*
Challenge: use builder design pattern.
class CodeBuilder {
    friend ostream& operator<<(ostream &os, const CodeBuilder &obj) {
        os << "class " << obj.class_name << endl
           << "{" << endl;
        for(pair<string, string> field : obj.fields) {
            os << string(obj.indent, ' ') << field.second << " " << field.first << ';' << endl;
        }
        os << "};";
        return os;
    }

    static constexpr int indent = 2;
    string class_name;
    vector<pair<string,string>> fields;
public:
    CodeBuilder(const string &class_name)
        : class_name{class_name} { }
    CodeBuilder &add_field(const string &name, const string &type) {
        fields.push_back(make_pair(name, type));
        return *this;
    }
};
 */
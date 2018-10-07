#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

class Token {
public:
    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << '\'' << token.text << '\'';
        return os;
    }

    enum Type {integer, plus, minus, lparen, rparen} type;
    std::string text;

    Token(Type type, const std::string& text)
            : type{type}, text{text} {}
};

class Element {
public:
    virtual int eval() const = 0;
};
class Integer : public Element {
    int value;
public:
    Integer(int value) : value(value) {}

    int eval() const override {
        return value;
    }
};
class BinaryOperation : public Element {
public:
    std::shared_ptr<Element> lhs, rhs;
    enum Type {addition, subtraction} type;

    int eval() const override {
        auto left = lhs->eval();
        auto right = rhs->eval();
        if(type == addition) {
            return left + right;
        } else {
            return left - right;
        }
    }
};

std::vector<Token> lex(std::string exp) { // Lexing/tokenisation converts a string into a token.
    std::vector<Token> result;
    for(size_t i{}; i < exp.size(); ++i) {
        switch(exp[i]) {
            case '+': {
                result.emplace_back(Token::plus, "+");
                break;
            }
            case '-': {
                result.emplace_back(Token::minus, "-");
                break;
            }
            case '(': {
                result.emplace_back(Token::lparen, "(");
                break;
            }
            case ')': {
                result.emplace_back(Token::rparen, ")");
                break;
            }
            default: {
                std::ostringstream buffer;
                buffer << exp[i];
                for(i += 1; i < exp.size(); ++i) {
                    if(std::isdigit(exp[i])) {
                        buffer << exp[i];
                    } else {
                        result.emplace_back(Token::integer, buffer.str());
                        i -= 1;
                        break;
                    }
                }
            }
        }
    }
    return result;
}
std::unique_ptr<BinaryOperation> parse(std::vector<Token> tokens) {
    auto result = std::make_unique<BinaryOperation>();
    bool have_lhs{false};
    for(size_t i{}; i < tokens.size(); ++i) {
        auto& token {tokens[i]};
        switch(token.type) {
            case Token::integer: {
                int to_int = std::stoi(token.text);
                auto to_integer = std::make_unique<Integer>(to_int);
                if(!have_lhs) {
                    result->lhs = std::move(to_integer);
                    have_lhs = true;
                } else {
                    result->rhs = std::move(to_integer);
                }
                break;
            }
            case Token::plus: {
                result->type = BinaryOperation::addition;
                break;
            }
            case Token::minus: {
                result->type = BinaryOperation::subtraction;
                break;
            }
            case Token::lparen: {
                size_t j = i;
                for(; j < tokens.size(); ++j) {
                    if(tokens[j].type == Token::rparen) {
                        break;
                    }
                }
                std::vector<Token> subexpression(&tokens[i+1], &tokens[j]);
                auto element = parse(subexpression);
                if(!have_lhs) {
                    result->lhs = std::move(element);
                    have_lhs = true;
                } else {
                    result->rhs = std::move(element);
                }
                i = j;
                break;
            }
        }
    }
    return result;
}

int main() {
    std::string expression = "(13-4)-(12+1)";
    auto tokens = lex(expression);
    for(const auto& token : tokens) {
        std::cout << '\'' << token.text << '\'' << ' ';
    }
    std::cout << std::endl;

    try {
        auto parsed = parse(tokens);
        std::cout << expression << " = " << parsed->eval() << std::endl;
    } catch(const std::exception& e) {

    }

    return 0;
}
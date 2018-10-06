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

class ExpressionInterpreter {
    std::string exp;
    std::vector<Token> tokens;

public:
    ExpressionInterpreter(const std::string& exp)
            : exp{exp} {
        lex();
    }

    std::string get_tokens() const {
        std::ostringstream result;
        for(const Token& token : tokens) {
            result << token << ' ';
        }
        return result.str();
    }

    void lex() { // Lexing/tokenisation converts a string into a token.
        std::vector<Token> result;
        for(size_t i{}; i < exp.size(); ++i) {
            switch(exp[i]) {
                case '+': {
                    result.emplace_back(Token::plus, "+");
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
        tokens = std::move(result);
    }
    void parse() {
        auto result = std::make_unique<BinaryOperation>();
        bool have_lhs{false};
        for(size_t i{}; i < tokens.size(); ++i) {
            auto& token {tokens[i]};
            switch(token) {
                case Token::integer: {
                    int to_int = std::stoi(token.text);
                    auto to_integer = std::make_shared<Integer>(to_int);
                    if(!have_lhs) {
                        result->lhs = to_integer;
                        have_lhs = true;
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
                        result->lhs = element;
                        have_lhs = true;
                    } else {
                        result->rhs = element;
                    }
                    i = j;
                    break;
                }
            }
        }
    }
};

int main() {
    ExpressionInterpreter exp{"(13-4)-(12+1)"};
    std::cout << exp.get_tokens() << std::endl;
    try {
        exp.parse();
        std::cout
    }
    return 0;
}
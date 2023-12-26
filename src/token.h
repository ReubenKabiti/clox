#pragma once
#include <memory>
#include <sstream>
#include <string>

enum class TokenType : char
{
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOF_
};

struct Literal 
{
    virtual std::string toString() { return ""; }
};

struct StringLiteral : public Literal
{
    std::string value;
    StringLiteral(std::string value) { this->value = value; }
    virtual std::string toString() { return value; }
};

struct NumberLiteral : public Literal
{
    double value;
    NumberLiteral(double value) { this->value = value; }
    virtual std::string toString() 
    {
        std::stringstream stream;
        stream << value;
        std::string str = stream.str();
        return str;
    }
};

struct Token
{
    TokenType type;
    std::string lexeme;
    size_t line;
    std::shared_ptr<Literal> literal = nullptr;
};

std::ostream& operator << (std::ostream& os, Token& token);
std::ostream& operator << (std::ostream& os, const Token& token);


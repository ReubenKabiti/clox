#include "token.h"

std::ostream& operator << (std::ostream& os, Token& token)
{
    std::string literal = "null";
    if (token.literal)
        literal = token.literal->toString();
    os << "[lexeme: " << token.lexeme << ", literal: "<< literal << ", line: " << token.line << "]\n";
    return os;
}

std::ostream& operator << (std::ostream& os, const Token& token)
{
    std::string literal = "null";
    if (token.literal)
        literal = token.literal->toString();
    os << "[lexeme: " << token.lexeme << ", literal: "<< literal << ", line: " << token.line << "]\n";
    return os;
}

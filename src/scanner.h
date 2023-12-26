#pragma once
#include <vector>
#include <map>
#include "Token.h"
#include "error_logger.h"

class Scanner
{
public:
    Scanner(std::string source, ErrorLogger& errorLogger);
    std::vector<Token> scanTokens();
private:
    void scanToken();
    void addToken(TokenType tokenType, std::shared_ptr<Literal> literal);
    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char c);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    void string();
    void number();
    void identifier();
private:
    std::string mSource;
    std::vector<Token> mTokens;
    size_t mStart = 0, mCurrent = 0, mLine = 1;
    ErrorLogger& mErrorLogger;
    std::map<std::string, TokenType> mKeywords;
};

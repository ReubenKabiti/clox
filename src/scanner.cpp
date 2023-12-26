#include "scanner.h"
#include <stdio.h>

Scanner::Scanner(std::string source, ErrorLogger& errorLogger)
    :
        mSource(source),
        mErrorLogger(errorLogger)
{
    mKeywords["and"] = TokenType::AND;
    mKeywords["class"] = TokenType::CLASS;
    mKeywords["else"] = TokenType::ELSE;
    mKeywords["false"] = TokenType::FALSE;
    mKeywords["fun"] = TokenType::FUN;
    mKeywords["for"] = TokenType::FOR;
    mKeywords["if"] = TokenType::IF;
    mKeywords["nil"] = TokenType::NIL;
    mKeywords["or"] = TokenType::OR;
    mKeywords["print"] = TokenType::PRINT;
    mKeywords["return"] = TokenType::RETURN;
    mKeywords["super"] = TokenType::SUPER;
    mKeywords["this"] = TokenType::THIS;
    mKeywords["true"] = TokenType::TRUE;
    mKeywords["var"] = TokenType::VAR;
    mKeywords["while"] = TokenType::WHILE;
}

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
    {
        mStart = mCurrent;
        scanToken();
    }

    Token eof = {
        TokenType::EOF_,
        "",
        mLine,
        nullptr
    };

    mTokens.push_back(eof);

    return mTokens;
}

void Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
        case '(': addToken(TokenType::LEFT_PAREN, nullptr); break;
        case ')': addToken(TokenType::RIGHT_PAREN, nullptr); break;
        case '{': addToken(TokenType::LEFT_BRACE, nullptr); break;
        case '}': addToken(TokenType::RIGHT_BRACE, nullptr); break;
        case ',': addToken(TokenType::COMMA, nullptr); break;
        case '.': addToken(TokenType::DOT, nullptr); break;
        case '-': addToken(TokenType::MINUS, nullptr); break;
        case '+': addToken(TokenType::PLUS, nullptr); break;
        case ';': addToken(TokenType::SEMICOLON, nullptr); break;
        case '*': addToken(TokenType::SLASH, nullptr); break;
        case ' ':
        case '\t':
        case '\r': break;
        case '\n': 
            mLine++;
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG, nullptr);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL, nullptr);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER, nullptr);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS, nullptr);
            break;
        case '/':
            if (peek() == '/') while (peek() != '\n' && !isAtEnd()) advance();
            else addToken(TokenType::SLASH, nullptr);
            break;
        case '"': string(); break;
        default:
            if (isDigit(c))
                number();
            if (isAlpha(c))
                identifier();
            else
                mErrorLogger.error(mLine, std::string("Unexpected character: ") + c);
            break;
    }
}

void Scanner::addToken(TokenType tokenType, std::shared_ptr<Literal> literal)
{
    std::string lexeme(mSource.begin() + mStart, mSource.begin() + mCurrent);
    // std::string lexeme = "";

    Token token = {
        tokenType,
        lexeme,
        mLine,
        literal
    };

    mTokens.push_back(token);
}

bool Scanner::isAtEnd() const
{
    return mCurrent >= mSource.size();
}
char Scanner::advance()
{
    return mSource[mCurrent++];
}

char Scanner::peek() const 
{
    if (isAtEnd())
        return '\0';
    return mSource[mCurrent];
}

char Scanner::peekNext() const 
{
    if (mCurrent + 1 >= mSource.size())
        return '\0';
    return mSource[mCurrent + 1];
}

bool Scanner::match(char c)
{
    if (mSource[mCurrent] == c)
    {
        mCurrent++;
        return true;
    }
    
    return false;
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            mLine++;
        advance();
    }
    if (isAtEnd())
    {
        mErrorLogger.error(mLine, "Unterminated string.");
        return;
    }

    // the last "
    advance();

    std::string literalValue(mSource.begin() + mStart + 1, mSource.begin() + mCurrent - 1);
    auto literal = std::make_shared<StringLiteral>(literalValue);
    addToken(TokenType::STRING, literal);
}

void Scanner::number()
{
    while (isDigit(peek()) && !isAtEnd()) advance();
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while (isDigit(peek()) && !isAtEnd()) advance();
    }

    std::string numberString(mSource.begin() + mStart, mSource.begin() + mCurrent);
    float number = atof(numberString.c_str());
    auto literal = std::make_shared<NumberLiteral>(number);
    addToken(TokenType::NUMBER, literal);
}


void Scanner::identifier()
{
    while(isAlphaNumeric(peek())) advance();
    std::string lexeme(mSource.begin() + mStart, mSource.begin() + mCurrent);

    TokenType tokenType;
    if (mKeywords.count(lexeme))
        tokenType = mKeywords[lexeme];
    else
        tokenType = TokenType::IDENTIFIER;

    addToken(tokenType, nullptr);
}

bool Scanner::isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool Scanner::isAlpha(char c) 
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

bool Scanner::isAlphaNumeric(char c) 
{
    return isDigit(c) || isAlpha(c);
}

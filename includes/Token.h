#ifndef TOKEN_H_
#define TOKEN_H_

#include "TokenVisitor.h"

class TokenVisitable
{
public:
        virtual void Accept(TokenVisitor & visitor) = 0;
        virtual ~TokenVisitable() { }
};

enum class TokenType
{
        SEMICOLON,
        COLON,
        COMMA,
        LPAREN, RPAREN,
        LCURLY, RCURLY,
        LSQUARE, RSQUARE,
        DOT,
        SCREEN,

        LITERAL,
        IDENTIFIER,
        OPERATOR,
        KEYWORD
};

class Token : public TokenVisitable
{
private:
        TokenType & tokType;
public:
        Token(TokenType tokType) :
        tokType(tokType) { }

        TokenType getToken() {
                return tokType;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

class Literal : public Token
{
private:
        int value;
public:
        Literal(int val) :
        Token(TokenType::LITERAL), value(val) { }

        int getValue() {
                return value;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

#endif /* !TOKEN_H_ */
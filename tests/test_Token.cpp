#include "../includes/Token.h"

#include "/usr/include/externals/catch.hpp"

#include <iostream>
#include <memory>

TEST_CASE("Token Class is Checked", "[Token]")
{
        TokenType type = TokenType::SEMICOLON;
        Token * t = new Token(type);
        REQUIRE(t->getToken() == TokenType::SEMICOLON);

        type = TokenType::COLON;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::COLON);

        type = TokenType::COMMA;
        Token tok(type);
        REQUIRE(tok.getToken() == TokenType::COMMA);

        type = TokenType::LPAREN;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::LPAREN);

        type = TokenType::RPAREN;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::RPAREN);

        type = TokenType::LCURLY;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::LCURLY);

        type = TokenType::RCURLY;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::RCURLY);

        type = TokenType::LSQUARE;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::LSQUARE);

        type = TokenType::RSQUARE;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::RSQUARE);

        type = TokenType::DOT;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::DOT);

        type = TokenType::SCREEN;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::SCREEN);

        type = TokenType::LITERAL;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::LITERAL);

        type = TokenType::IDENTIFIER;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::IDENTIFIER);

        type = TokenType::OPERATOR;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::OPERATOR);

        type = TokenType::KEYWORD;
        t = new Token(type);
        REQUIRE(t->getToken() == TokenType::KEYWORD);

        delete t;
}

/* Watching the Token Class Preety Printing as we want */
TEST_CASE("Watching the Token Class", "[Token]")
{
        TokenType type = TokenType::SEMICOLON;
        
        std::unique_ptr<Token> t(new Token(type));
        std::unique_ptr<TokenVisitor> printer(new TokenPrinter());

        t->Accept(*printer);

        std::unique_ptr<Token> t1(new Literal(3));
        t1->Accept(*printer);

        std::cout << std::endl;
}

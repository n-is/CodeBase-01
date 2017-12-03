#include "../includes/Token.h"

#include "catch.hpp"

#include <iostream>
#include <memory>

/* Watching the Token Class Preety Printing as we want */
TEST_CASE("Watching the Token Class", "[Token]")
{
        TokenType type = TokenType::COLON;
        
        std::unique_ptr<Token> t(new Token(type));
        std::unique_ptr<TokenVisitor> printer(new TokenPrinter());

        t->Accept(*printer);

        std::cout << std::endl;
}

TEST_CASE("Token Class is Checked", "[Token]")
{
        TokenType type;
        Token * t = new Token(TokenType::SEMICOLON);
        REQUIRE(t->getTokenType() == TokenType::SEMICOLON);

        type = TokenType::COLON;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::COLON);

        type = TokenType::COMMA;
        Token tok(type);
        REQUIRE(tok.getTokenType() == TokenType::COMMA);

        type = TokenType::LPAREN;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::LPAREN);

        type = TokenType::RPAREN;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::RPAREN);

        type = TokenType::LCURLY;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::LCURLY);

        type = TokenType::RCURLY;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::RCURLY);

        type = TokenType::LSQUARE;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::LSQUARE);

        type = TokenType::RSQUARE;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::RSQUARE);

        type = TokenType::DOT;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::DOT);

        type = TokenType::SCREEN;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::SCREEN);

        type = TokenType::QUESTION;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::QUESTION);

        type = TokenType::BANG;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::BANG);

        type = TokenType::CARET;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::CARET);

        type = TokenType::LEFT_ARROW;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::LEFT_ARROW);

        type = TokenType::RIGHT_ARROW;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::RIGHT_ARROW);

        type = TokenType::LITERAL;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::LITERAL);

        type = TokenType::IDENTIFIER;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::IDENTIFIER);

        type = TokenType::OPERATOR;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::OPERATOR);

        type = TokenType::EOS;
        t = new Token(type);
        REQUIRE(t->getTokenType() == TokenType::EOS);

        delete t;
}

#include "../includes/Lexer.h"
#include "../includes/TokenVisitor.h"

#include "catch.hpp"

#include <iostream>
#include <memory>

/* First Watch : Watching the Token Stream */
// TEST_CASE("Watching Tokens", "[Lexer][watch]")
// {
        // std::unique_ptr<Lexer> lex(new Lexer("test_Lexer.base"));
        // std::unique_ptr<TokenPrinter> plotter(new TokenPrinter());
        
        // int count = 0;
        // Token * tok;
        // do {
        //         ++count;
        //         tok = lex->getNextToken();
        //         tok->Accept(*plotter);
        //         std::cout << " ";
        // } while(tok->getTokenType() != TokenType::EOS);
        // std::cout << std::endl;
        // std::cout << "Number Of Tokens: " << count << std::endl;

        // delete tok;
// }

TEST_CASE("Checking Token Factory (Lexer) class", "[Lexer]")
{
        using std::unique_ptr;
        unique_ptr<Lexer> lex(new Lexer("test_Lexer.base"));
        unique_ptr<Token> tok(lex->getNextToken());

        REQUIRE(tok->getTokenType() == TokenType::DATA_TYPE);
        auto a0 = static_cast<DataType *>(tok.release());
        REQUIRE(a0->getType() == Type::INT);

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::IDENTIFIER);
        auto a1 = static_cast<Identifier *>(tok.release());
        REQUIRE(a1->getValue() == "fact");

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::LPAREN);

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::DATA_TYPE);
        auto a2 = static_cast<DataType *>(tok.release());
        REQUIRE(a2->getType() == Type::INT);

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::IDENTIFIER);
        auto a3 = static_cast<Identifier *>(tok.release());
        REQUIRE(a3->getValue() == "n");

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::RPAREN);

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::COLON);
        
        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::QUESTION);

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::IDENTIFIER);
        auto a4 = static_cast<Identifier *>(tok.release());
        REQUIRE(a4->getValue() == "n");
}

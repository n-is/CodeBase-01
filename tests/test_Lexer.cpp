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

        REQUIRE(tok->getTokenType() == TokenType::KEYWORD);
        auto a0 = static_cast<KeyWord *>(tok.release());
        REQUIRE(a0->getValue() == "int");

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::IDENTIFIER);
        auto a1 = static_cast<Identifier *>(tok.release());
        REQUIRE(a1->getValue() == "fact");

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::LPAREN);

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::KEYWORD);
        auto a2 = static_cast<KeyWord *>(tok.release());
        REQUIRE(a2->getValue() == "int");

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

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::OPERATOR);
        auto a5 = static_cast<Operator *>(tok.release());
        REQUIRE(a5->getOperatorType() == OperatorType::RELATION);
        auto a6 = static_cast<RelationOperator *>(a5);
        REQUIRE(a6->getType() == RelationType::LESSER);


        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::LITERAL);
        auto a7 = static_cast<Literal *>(tok.release());
        REQUIRE(a7->getLiteralType() == LiteralType::INTEGER);
        auto a8 = static_cast<IntegerLiteral *>(a7);
        REQUIRE(a8->getValue() == 0);
}

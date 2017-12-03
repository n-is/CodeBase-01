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
        auto k = static_cast<KeyWord *>(tok.release());
        REQUIRE(k->getValue() == "int");

        tok.reset(lex->getNextToken());
        REQUIRE(tok->getTokenType() == TokenType::IDENTIFIER);
        auto i = static_cast<Identifier *>(tok.release());
        REQUIRE(i->getValue() == "fact");
}

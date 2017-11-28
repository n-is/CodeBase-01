#include "../includes/Lexer.h"
#include "../includes/TokenVisitor.h"

#include "/usr/include/externals/catch.hpp"

#include <iostream>
#include <memory>

/* First Watch : Watching the Token Stream */
TEST_CASE("Watching Tokens", "[Lexer][watch]")
{
        std::unique_ptr<Lexer> lex(new Lexer("test_Lexer.base"));
        std::unique_ptr<TokenPrinter> plotter(new TokenPrinter());

        Token * tok;
        do {
                tok = lex->getNextToken();
                tok->Accept(*plotter);
                std::cout << " ";
        } while(tok->getTokenType() != TokenType::EOS);
        std::cout << std::endl;
        
        delete tok;
}

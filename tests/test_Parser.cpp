#include "../includes/Parser.h"
#include "../includes/AST_Visitor.h"

#include "catch.hpp"

#include <iostream>
#include <memory>

/* First test : Testing if the tree is being built */
TEST_CASE("Testing whether the tree is being constructed", "[Parser][AST]")
{
        std::unique_ptr<Lexer> lex(new Lexer("test_Parser.base"));
        std::unique_ptr<Parser> pas(new Parser(*lex));
        std::unique_ptr<AST_Visitor> plotter(new AST_Printer());
        std::unique_ptr<TokenVisitor> tok_plotter(new TokenPrinter());
        
        // std::unique_ptr<AST> three(new Float(3.1));
        // three->Accept(*plotter);
        // std::cout << std::endl;
        // Operator * plus = new Operator(OperatorType::PLUS);
        // std::unique_ptr<AST> plusThree(new Unary(*plus, std::move(three)));
        // plusThree->Accept(*plotter);
        // plus->Accept(*tok_plotter);

        auto result = pas->parse();
        result->Accept(*plotter);
}

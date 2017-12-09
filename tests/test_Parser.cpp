#include "../includes/Parser.h"
#include "../includes/AST_Visitor.h"

#include "catch.hpp"

#include <iostream>
#include <memory>

/* First test : Testing if the tree is being built */
// TEST_CASE("Testing whether the tree is being constructed", "[Parser][AST]")
// {
//         std::unique_ptr<Lexer> lex(new Lexer("test_Parser.base"));
//         std::unique_ptr<Parser> pas(new Parser(*lex));
//         std::unique_ptr<AST_Visitor> plotter(new AST_Printer());
//         std::unique_ptr<TokenVisitor> tok_plotter(new TokenPrinter());

//         auto result = pas->parse();
//         result->Accept(*plotter);
// }

TEST_CASE("Testing the C code generator", "[codegen]")
{
        std::unique_ptr<Lexer> lex(new Lexer("test_Parser.base"));
        std::unique_ptr<Parser> pas(new Parser(*lex));
        std::unique_ptr<AST_Visitor> codegen(new C_CodeGen("test_Parser.c"));

        auto result = pas->parse();
        result->Accept(*codegen);
}

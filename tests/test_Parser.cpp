#include "../includes/Parser.h"

#include "catch.hpp"

#include <iostream>
#include <memory>

/* First test : Testing if the tree is being built */
TEST_CASE("Testing whether the tree is being constructed", "[Parser][AST]")
{
        std::unique_ptr<Lexer> lex(new Lexer("test_Parser.base"));
        std::unique_ptr<Parser> pas(new Parser(*lex));

        pas->parse();
}

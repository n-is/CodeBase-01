#ifndef PARSER_H_
#define PARSER_H_

#include "AST.h"
#include "Lexer.h"

#include <iostream>
#include <memory>

class Parser
{
public:
        Parser(Lexer & lex);
        std::unique_ptr<AST> parse();

        ~Parser();

private:
        Lexer & lex_;
        Token * curr_tok_;

        void as_expected(TokenType t);

        std::unique_ptr<AST> identifier();
        std::unique_ptr<AST> literal();
        std::unique_ptr<AST> paren_expr();
        std::unique_ptr<AST> unary_expr();;

        std::unique_ptr<AST> primary_expr();

        std::unique_ptr<AST> mult_expr();
        std::unique_ptr<AST> add_expr();
        std::unique_ptr<AST> relation_expr();
        std::unique_ptr<AST> equality_expr();
        std::unique_ptr<AST> logicalOR_expr();
        std::unique_ptr<AST> logicalAND_expr();
        std::unique_ptr<AST> expr();

        std::unique_ptr<AST> assignment_stmt();
        std::unique_ptr<AST> selection_stmt();
        std::unique_ptr<AST> iteration_stmt();
        std::unique_ptr<AST> labeled_stmt();
        std::unique_ptr<AST> declaration_stmt();

        std::unique_ptr<AST> statement();
        std::unique_ptr<AST> body();

        std::unique_ptr<AST> parameter();
        std::unique_ptr<AST> prototype();
        std::unique_ptr<AST> function();
        std::unique_ptr<AST> program();
};

#endif // PARSER_H_
#include "../includes/Parser.h"
#include "../utils/Error.h"

#include <cassert>

Parser::Parser(Lexer & lex_) :
lex_(lex_)
{
        curr_tok_ = lex_.getNextToken();
}

Parser::~Parser()
{
        delete curr_tok_;
}

std::unique_ptr<AST> Parser::parse()
{
        return body();
}

void Parser::as_expected(TokenType t)
{
        if(curr_tok_->getTokenType() == t) {
                curr_tok_ = lex_.getNextToken();
        } else {
                raise(Error::TokenError, "Unrecognized Token", lex_.getCurrentLineNumber());
        }
}

std::unique_ptr<AST> Parser::identifier()
{
        assert(curr_tok_->getTokenType() == TokenType::IDENTIFIER);
        auto i = static_cast<Identifier *>(curr_tok_);
        std::string val = i->getValue();
        as_expected(TokenType::IDENTIFIER);
        if(curr_tok_->getTokenType() == TokenType::LPAREN) {
                // return function call here;
        }
        return std::make_unique<Id>(val);
}

std::unique_ptr<AST> Parser::literal()
{
        auto i0 = static_cast<Literal *>(curr_tok_);
        as_expected(TokenType::LITERAL);
        if(i0->getLiteralType() == LiteralType::INTEGER) {
                auto i1 = static_cast<IntegerLiteral *>(i0);
                return std::make_unique<Int>(i1->getValue());
        }
        else if(i0->getLiteralType() == LiteralType::FLOAT) {
                auto i2 = static_cast<FloatLiteral *>(i0);
                return std::make_unique<Float>(i2->getValue());
        }
        return nullptr;
}

std::unique_ptr<AST> Parser::paren_expr()
{
        as_expected(TokenType::LPAREN);
        auto expression = expr();
        as_expected(TokenType::RPAREN);
        return expression;
}

std::unique_ptr<AST> Parser::unary_expr()
{
        auto op_tok = static_cast<Operator *>(curr_tok_);
        if(op_tok->getOperatorType() == OperatorType::PLUS || 
           op_tok->getOperatorType() == OperatorType::MINUS) {
                   as_expected(TokenType::OPERATOR);
                   return std::make_unique<Unary>(*op_tok, std::move(primary_expr()));
        }
        return nullptr;
}

std::unique_ptr<AST> Parser::primary_expr()
{
        TokenType tokType = curr_tok_->getTokenType();
        if(tokType == TokenType::LITERAL) {
                return literal();
        }
        else if(tokType == TokenType::IDENTIFIER) {
                return identifier();
        }
        else if(tokType == TokenType::OPERATOR) {
                return unary_expr();
        }
        else if(tokType == TokenType::LPAREN) {
                return paren_expr();
        }
        return nullptr;
}

std::unique_ptr<AST> Parser::mult_expr()
{
        auto earlier_expr = primary_expr();
        while(curr_tok_->getTokenType() == TokenType::OPERATOR) {
                auto op_tok = static_cast<Operator *>(curr_tok_);
                if(op_tok->getOperatorType() == OperatorType::MULTIPLY ||
                   op_tok->getOperatorType() == OperatorType::DIVIDE ||
                   op_tok->getOperatorType() == OperatorType::MODULO) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(mult_expr()), *op_tok, std::move(earlier_expr));
                } else {
                        break;
                }
        }
        return earlier_expr;
}

std::unique_ptr<AST> Parser::add_expr()
{
        auto earlier_expr = mult_expr();
        while(curr_tok_->getTokenType() == TokenType::OPERATOR) {
                auto op_tok = static_cast<Operator *>(curr_tok_);
                if(op_tok->getOperatorType() == OperatorType::PLUS ||
                   op_tok->getOperatorType() == OperatorType::MINUS) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(add_expr()), *op_tok, std::move(earlier_expr));
                } else {
                        break;
                }
        }
        return earlier_expr;
}

std::unique_ptr<AST> Parser::relation_expr()
{
        auto earlier_expr = add_expr();
        while(curr_tok_->getTokenType() == TokenType::OPERATOR) {
                auto op_tok = static_cast<Operator *>(curr_tok_);
                if(op_tok->getOperatorType() == OperatorType::LESSER ||
                   op_tok->getOperatorType() == OperatorType::LESSER_EQUALS ||
                   op_tok->getOperatorType() == OperatorType::GREATER ||
                   op_tok->getOperatorType() == OperatorType::GREATER_EQUALS) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(relation_expr()), *op_tok, std::move(earlier_expr));
                } else {
                        break;
                }
        }
        return earlier_expr;
}

std::unique_ptr<AST> Parser::equality_expr()
{
        auto earlier_expr = relation_expr();
        while(curr_tok_->getTokenType() == TokenType::OPERATOR) {
                auto op_tok = static_cast<Operator *>(curr_tok_);
                if(op_tok->getOperatorType() == OperatorType::EQUALS ||
                   op_tok->getOperatorType() == OperatorType::NOT_EQUALS) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(equality_expr()), *op_tok, std::move(earlier_expr));
                } else {
                        break;
                }
        }
        return earlier_expr;
}

std::unique_ptr<AST> Parser::expr()
{
        return equality_expr();
}

std::unique_ptr<AST> Parser::assignment_stmt()
{
        assert(curr_tok_->getTokenType() == TokenType::IDENTIFIER);
        auto i = static_cast<Identifier *>(curr_tok_);
        std::string val = i->getValue();
        as_expected(TokenType::IDENTIFIER);

        assert(curr_tok_->getTokenType() == TokenType::OPERATOR);
        auto op_tok = static_cast<Operator *>(curr_tok_);
        assert(op_tok->getOperatorType() == OperatorType::ASSIGNMENT);
        auto assign_op = static_cast<AssignmentOperator *>(op_tok);
        as_expected(TokenType::OPERATOR);
        auto assignment = std::make_unique<AssignmentStatement>(val, *assign_op, std::move(expr()));
        as_expected(TokenType::SEMICOLON);
        return assignment;
}

std::unique_ptr<AST> Parser::selection_stmt()
{
        as_expected(TokenType::QUESTION);
        auto condition = expr();
        auto stmt = statement();
        return std::make_unique<IfStatement>(std::move(condition), std::move(stmt));
}

std::unique_ptr<AST> Parser::iteration_stmt()
{
        as_expected(TokenType::LSQUARE);
        auto condition = expr();
        as_expected(TokenType::RSQUARE);
        auto stmt = statement();
        return std::make_unique<WhileStatement>(std::move(condition), std::move(stmt));
}

std::unique_ptr<AST> Parser::labeled_stmt()
{
        as_expected(TokenType::CARET);
        auto ret = expr();
        as_expected(TokenType::SEMICOLON);
        return std::make_unique<ReturnStatement>(std::move(ret));
}

std::unique_ptr<AST> Parser::declaration_stmt()
{
        assert(curr_tok_->getTokenType() == TokenType::DATA_TYPE);
        auto typeTok = static_cast<DataType *>(curr_tok_);
        as_expected(TokenType::DATA_TYPE);
        std::vector<std::unique_ptr<AST>> vars;
        vars.push_back(std::move(identifier()));
        while(curr_tok_->getTokenType() == TokenType::COMMA) {
                as_expected(TokenType::COMMA);
                vars.push_back(std::move(identifier()));
        }
        as_expected(TokenType::SEMICOLON);
        return std::make_unique<Declaration>(*typeTok, std::move(vars));
}

std::unique_ptr<AST> Parser::statement()
{
        if(curr_tok_->getTokenType() == TokenType::IDENTIFIER) {
                return assignment_stmt();
        }
        else if(curr_tok_->getTokenType() == TokenType::QUESTION) {
                return selection_stmt();
        }
        else if(curr_tok_->getTokenType() == TokenType::LSQUARE) {
                return iteration_stmt();
        }
        else if(curr_tok_->getTokenType() == TokenType::CARET) {
                return labeled_stmt();
        }
        else if(curr_tok_->getTokenType() == TokenType::DATA_TYPE) {
                return declaration_stmt();
        }
        else if(curr_tok_->getTokenType() == TokenType::LCURLY) {
                return body();
        }
        return nullptr;
}

std::unique_ptr<AST> Parser::body()
{
        as_expected(TokenType::LCURLY);
        std::vector<std::unique_ptr<AST>> statement_list;
        while(curr_tok_->getTokenType() != TokenType::RCURLY) {
                if(auto stmt = statement()) {
                        statement_list.push_back(std::move(stmt));
                }
        }
        as_expected(TokenType::RCURLY);
        return std::make_unique<CompoundStatement>(std::move(statement_list));
}

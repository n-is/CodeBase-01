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
        if(curr_tok_) {
                delete curr_tok_;
        }
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
        auto i0 = expr();
        as_expected(TokenType::RPAREN);
        return i0;
}

std::unique_ptr<AST> Parser::unary_expr()
{
        auto op = static_cast<Operator *>(curr_tok_);
        if(op->getOperatorType() == OperatorType::PLUS || 
           op->getOperatorType() == OperatorType::MINUS) {
                   return std::make_unique<Unary>(*curr_tok_, std::move(primary_expr()));
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
                auto t0 = static_cast<Operator *>(curr_tok_);
                if(t0->getOperatorType() == OperatorType::MULTIPLY ||
                   t0->getOperatorType() == OperatorType::DIVIDE ||
                   t0->getOperatorType() == OperatorType::MODULO) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(mult_expr()), *curr_tok_, std::move(earlier_expr));
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
                auto t0 = static_cast<Operator *>(curr_tok_);
                if(t0->getOperatorType() == OperatorType::PLUS ||
                   t0->getOperatorType() == OperatorType::MINUS) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(add_expr()), *curr_tok_, std::move(earlier_expr));
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
                auto t0 = static_cast<Operator *>(curr_tok_);
                if(t0->getOperatorType() == OperatorType::RELATION) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(relation_expr()), *curr_tok_, std::move(earlier_expr));
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
                auto t0 = static_cast<Operator *>(curr_tok_);
                if(t0->getOperatorType() == OperatorType::EQUALS ||
                   t0->getOperatorType() == OperatorType::NOT_EQUALS) {
                        as_expected(TokenType::OPERATOR);
                        earlier_expr = std::make_unique<Binary>(std::move(equality_expr()), *curr_tok_, std::move(earlier_expr));
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
        auto lvalue = identifier();
        assert(curr_tok_->getTokenType() == TokenType::OPERATOR);
        auto t0 = static_cast<Operator *>(curr_tok_);
        assert(t0->getOperatorType() == OperatorType::ASSIGNMENT);
        as_expected(TokenType::OPERATOR);
        lvalue = std::make_unique<Binary>(std::move(lvalue), *curr_tok_, std::move(expr()));
        as_expected(TokenType::SEMICOLON);
        return lvalue;
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

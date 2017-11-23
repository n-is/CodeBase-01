#include "../includes/TokenVisitor.h"
#include "../includes/Token.h"

#include <iostream>

static std::string getTokenStr(TokenType t);

void TokenPrinter::visit(Token * tok)
{
        std::string tokValue = getTokenStr(tok->getToken());
        std::cout << "Token(" << tokValue << ")";
}

void TokenPrinter::visit(Literal * tok)
{
        int val = tok->getValue();
        std::cout << "Literal(" << val << ")";
}


static std::string getTokenStr(TokenType t)
{
        switch(t) {
                case TokenType::SEMICOLON : {
                        return ";";
                } break;

                case TokenType::COLON : {
                        return ":";
                } break;

                case TokenType::COMMA : {
                        return ",";
                } break;

                case TokenType::LPAREN : {
                        return "(";
                } break;

                case TokenType::RPAREN : {
                        return ")";
                } break;

                case TokenType::LCURLY : {
                        return "{";
                } break;

                case TokenType::RCURLY : {
                        return "}";
                } break;

                case TokenType::LSQUARE : {
                        return "[";
                } break;

                case TokenType::RSQUARE : {
                        return "]";
                } break;

                case TokenType::DOT : {
                        return ".";
                } break;

                case TokenType::SCREEN : {
                        return "[]";
                } break;

                default : {
                        return "None";
                }break;
        }
}

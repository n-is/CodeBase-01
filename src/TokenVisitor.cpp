#include "../includes/TokenVisitor.h"
#include "../includes/Token.h"

#include <iostream>

static std::string getTokenStr(TokenType t);
static std::string getOperatorStr(OperatorType op);
static std::string getAssignmentStr(AssignmentType assign);

void TokenPrinter::visit(Token * tok)
{
        std::string tokValue = getTokenStr(tok->getTokenType());
        std::cout << "(" << tokValue << ")";
}

void TokenPrinter::visit(IntegerLiteral * tok)
{
        int tokValue = tok->getValue();
        std::cout << "(" << tokValue << ")";
}

void TokenPrinter::visit(FloatLiteral * tok)
{
        float tokValue = tok->getValue();
        std::cout << "(" << tokValue << ")";
}

void TokenPrinter::visit(Operator * tok)
{
        std::string tokValue = getOperatorStr(tok->getOperatorType());
        std::cout << "(" << tokValue << ")";
}

void TokenPrinter::visit(AssignmentOperator * tok)
{
        AssignmentType tokValue = tok->getType();
        std::cout << "(" << getAssignmentStr(tokValue) << ")";
}

void TokenPrinter::visit(Identifier * tok)
{
        std::string tokValue = tok->getValue();
        std::cout << "(" << tokValue << ")";
}

void TokenPrinter::visit(KeyWord * tok)
{
        std::string tokValue = tok->getValue();
        std::cout << "(" << tokValue << ")";
}

void TokenPrinter::visit(DataType * tok)
{
        std::cout << "(";
        if(tok->getType() == Type::INT) {
                std::cout << "int";
        }
        else if(tok->getType() == Type::FLOAT) {
                std::cout << "float";
        }
        std::cout << ")";
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

                case TokenType::QUESTION : {
                        return "?";
                } break;

                case TokenType::BANG : {
                        return "!";
                } break;

                case TokenType::CARET : {
                        return "^";
                } break;

                case TokenType::LEFT_ARROW : {
                        return "<-";
                } break;

                case TokenType::RIGHT_ARROW : {
                        return "->";
                } break;

                case TokenType::EOS : {
                        return "\\0";
                } break;

                default : {
                        return "None Token";
                }break;
        }
}

static std::string getOperatorStr(OperatorType op)
{
        if(op == OperatorType::PLUS) {
                return "+";
        }
        else if(op == OperatorType::MINUS) {
                return "-";
        }
        else if(op == OperatorType::MULTIPLY) {
                return "*";
        }
        else if(op == OperatorType::DIVIDE) {
                return "/";
        }
        else if(op == OperatorType::MODULO) {
                return "%";
        }
        else if(op == OperatorType::EQUALS) {
                return "==";
        }
        else if(op == OperatorType::NOT_EQUALS) {
                return "!=";
        }
        else if (op == OperatorType::LESSER) {
                return "<";
        }
        else if (op == OperatorType::GREATER) {
                return ">";
        }
        else if (op == OperatorType::LESSER_EQUALS) {
                return "<=";
        }
        else if (op == OperatorType::GREATER_EQUALS) {
                return ">=";
        }
        return "None Operator";
}

static std::string getAssignmentStr(AssignmentType assign)
{
        switch(assign) {
                case AssignmentType::ASSIGN : {
                        return "=";
                } break;
                case AssignmentType::PLUS_EQ : {
                        return "+=";
                } break;
                case AssignmentType::MINUS_EQ : {
                        return "-=";
                } break;
                case AssignmentType::MULTIPLY_EQ : {
                        return "*=";
                } break;
                case AssignmentType::DIVIDE_EQ : {
                        return "/=";
                } break;
                case AssignmentType::MODULO_EQ : {
                        return "%=";
                } break;
                default :
                        return "None Operator";
        }
}

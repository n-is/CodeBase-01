#include "tokensToStrings.h"
#include "../includes/Token.h"

std::string getStr(TokenType t)
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

std::string getStr(OperatorType op)
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

std::string getStr(AssignmentType assign)
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

std::string getStr(Type datatype)
{
        if(datatype == Type::INT) {
                return "int";
        }
        else if(datatype == Type::FLOAT) {
                return "float";
        }

        return "None Data Type";
}

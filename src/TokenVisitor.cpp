#include "../includes/TokenVisitor.h"
#include "../includes/Token.h"

#include <iostream>

static std::string getTokenStr(TokenType t);
static std::string getOperatorStr(OperatorType op);
static std::string getAssignmentStr(AssignmentType assign);
static std::string getRelationStr(RelationType rltn);

void TokenPrinter::visit(Token * tok)
{
        std::string tokValue = getTokenStr(tok->getTokenType());
        std::cout << "Token(" << tokValue << ")";
}

void TokenPrinter::visit(IntegerLiteral * tok)
{
        int tokValue = tok->getValue();
        std::cout << "Int(" << tokValue << ")";
}

void TokenPrinter::visit(FloatLiteral * tok)
{
        float tokValue = tok->getValue();
        std::cout << "Float(" << tokValue << ")";
}

void TokenPrinter::visit(Operator * tok)
{
        std::string tokValue = getOperatorStr(tok->getOperatorType());
        std::cout << "Operator(" << tokValue << ")";
}

void TokenPrinter::visit(AssignmentOperator * tok)
{
        AssignmentType tokValue = tok->getType();
        std::cout << "Assignment(" << getAssignmentStr(tokValue) << ")";
}

void TokenPrinter::visit(RelationOperator * tok)
{
        RelationType tokValue = tok->getType();
        std::cout << "Relation(" << getRelationStr(tokValue) << ")";
}

void TokenPrinter::visit(Identifier * tok)
{
        std::string tokValue = tok->getValue();
        std::cout << "Identifier(" << tokValue << ")";
}

void TokenPrinter::visit(KeyWord * tok)
{
        std::string tokValue = tok->getValue();
        std::cout << "KeyWord(" << tokValue << ")";
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

static std::string getRelationStr(RelationType rltn)
{
        switch(rltn) {
                case RelationType::LESSER : {
                        return "<";
                } break;
                case RelationType::GREATER : {
                        return ">";
                } break;
                case RelationType::LESSER_EQUALS : {
                        return "<=";
                } break;
                case RelationType::GREATER_EQUALS : {
                        return ">=";
                } break;
                default :
                        return "None Relation Operator";
        }
}

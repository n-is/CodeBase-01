#include "../includes/TokenVisitor.h"
#include "../includes/Token.h"

#include <iostream>
#include "../helpers/tokensToStrings.h"

void TokenPrinter::visit(Token * tok)
{
        std::string tokValue = getStr(tok->getTokenType());
        std::cout << tokValue;
}

void TokenPrinter::visit(IntegerLiteral * tok)
{
        int tokValue = tok->getValue();
        std::cout << tokValue;
}

void TokenPrinter::visit(FloatLiteral * tok)
{
        float tokValue = tok->getValue();
        std::cout << tokValue;
}

void TokenPrinter::visit(Operator * tok)
{
        std::string tokValue = getStr(tok->getOperatorType());
        std::cout << tokValue;
}

void TokenPrinter::visit(AssignmentOperator * tok)
{
        AssignmentType tokValue = tok->getType();
        std::cout << getStr(tokValue);
}

void TokenPrinter::visit(Identifier * tok)
{
        std::string tokValue = tok->getValue();
        std::cout << tokValue;
}

void TokenPrinter::visit(KeyWord * tok)
{
        std::string tokValue = tok->getValue();
        std::cout << tokValue;
}

void TokenPrinter::visit(DataType * tok)
{
        std::cout << getStr(tok->getType());
}

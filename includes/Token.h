#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include "TokenVisitor.h"

class TokenVisitable
{
public:
        virtual void Accept(TokenVisitor & visitor) = 0;
        virtual ~TokenVisitable() { }
};

enum class TokenType
{
        SEMICOLON,
        COLON,
        COMMA,
        LPAREN, RPAREN,
        LCURLY, RCURLY,
        LSQUARE, RSQUARE,
        DOT,
        SCREEN,         // []

        QUESTION,       // ?
        BANG,           // !
        CARET,          // ^
        LEFT_ARROW,     // <-
        RIGHT_ARROW,    // ->

        LITERAL,
        IDENTIFIER,
        OPERATOR,
        KEYWORD,
        DATA_TYPE,

        EOS
};

class Token : public TokenVisitable
{
private:
        TokenType tokType;
public:
        Token(TokenType tokType) :
        tokType(tokType) { }

        TokenType getTokenType() {
                return tokType;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

enum class LiteralType
{
        INTEGER,
        FLOAT
};

class Literal : public Token
{
private:
        LiteralType literalType;
public:
        Literal(LiteralType literalType) :
        Token(TokenType::LITERAL), literalType(literalType) { }

        LiteralType getLiteralType() {
                return literalType;
        }
};

class IntegerLiteral : public Literal
{
private:
        int value;
public:
        IntegerLiteral(int val):
        Literal(LiteralType::INTEGER), value(val) { }

        int getValue() {
                return value;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

class FloatLiteral : public Literal
{
private:
        float value;
public:
        FloatLiteral(float val):
        Literal(LiteralType::FLOAT), value(val) { }

        float getValue() {
                return value;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

enum class OperatorType
{
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,

        EQUALS,
        NOT_EQUALS,

        ASSIGNMENT,
        RELATION
};

class Operator : public Token
{
private:
        OperatorType operatorType;
public:
        Operator(OperatorType operatorType):
        Token(TokenType::OPERATOR), operatorType(operatorType) { }

        OperatorType getOperatorType() {
                return operatorType;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

enum class AssignmentType
{
        ASSIGN,
        PLUS_EQ,
        MINUS_EQ,
        MULTIPLY_EQ,
        DIVIDE_EQ,
        MODULO_EQ
};

class AssignmentOperator : public Operator
{
private:
        AssignmentType assignmentType;
public:
        AssignmentOperator(AssignmentType assignmentType) :
        Operator(OperatorType::ASSIGNMENT), assignmentType(assignmentType) { }

        AssignmentType getType() {
                return assignmentType;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

enum class RelationType
{
        LESSER,
        GREATER,
        LESSER_EQUALS,
        GREATER_EQUALS
};

class RelationOperator : public Operator
{
private:
        RelationType relationType;
public:
        RelationOperator(RelationType type) :
        Operator(OperatorType::RELATION), relationType(type) { }

        RelationType getType() {
                return relationType;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
};

class Identifier : public Token
{
public:
        Identifier(std::string val) :
        Token(TokenType::IDENTIFIER), value(val) { }

        std::string getValue() {
                return value;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }

private:
        std::string value;
};

class KeyWord : public Token
{
public:
        KeyWord(std::string val) :
        Token(TokenType::KEYWORD), value(val) { }

        std::string getValue() {
                return value;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }

private:
        std::string value;
};

enum class Type
{
        INT,
        FLOAT
};

class DataType : public Token
{
public:
        DataType(Type t) :
        Token(TokenType::DATA_TYPE), type(t) { }

        Type getType() {
                return type;
        }

        void Accept(TokenVisitor & visitor) { visitor.visit(this); }
private:
        Type type;
};

#endif /* !TOKEN_H_ */
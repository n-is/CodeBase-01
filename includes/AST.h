#ifndef AST_H_
#define AST_H_

#include "Token.h"
#include <memory>
#include <vector>

class AST_Visitor;

class AST_Visitable
{
public:
        virtual ~AST_Visitable() { };
        // virtual void Accept(AST_Visitor & visitor) = 0;
};

class AST : public AST_Visitable
{
public:
        virtual ~AST() { }
};

class Int : public AST
{
public:
        Int(int value) :
        value(value) { };

        int getValue() {
                return value;
        }

        // void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        int value;
};

class Float : public AST
{
public:
        Float(float value) :
        value(value) { };

        float getValue() {
                return value;
        }

        // void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        float value;
};

class Id : public AST
{
public:
        Id(std::string value) :
        value(value) { };

        std::string getValue() {
                return value;
        }

private:
        std::string value;
};


class Unary : public AST
{
public:
        Unary(Token & tok, std::unique_ptr<AST> expr) :
        tok(tok), expr(std::move(expr)) { }

private:
        Token tok;
        std::unique_ptr<AST> expr;
};

class Binary : public AST
{
public:
        Binary(std::unique_ptr<AST> lvalue, Token & tok, std::unique_ptr<AST> rvalue) :
        lvalue(std::move(lvalue)), tok(tok), rvalue(std::move(rvalue)) { };

        // void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::unique_ptr<AST> lvalue;
        Token tok;
        std::unique_ptr<AST> rvalue;
};

class AssignmentStatement : public AST
{
public:
        AssignmentStatement(std::string & lvalue, Token & tok, std::unique_ptr<AST> rvalue) :
        lvalue(std::move(lvalue)), tok(tok), rvalue(std::move(rvalue)) { };

        // void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::string lvalue;
        Token tok;
        std::unique_ptr<AST> rvalue;
};

class IfStatement : public AST
{
public:
        IfStatement(std::unique_ptr<AST> condition, std::unique_ptr<AST> body) :
        condition(std::move(condition)), body(std::move(body)) { }

private:
        std::unique_ptr<AST> condition, body;
        
};

class WhileStatement : public AST
{
public:
        WhileStatement(std::unique_ptr<AST> condition, std::unique_ptr<AST> body) :
        condition(std::move(condition)), body(std::move(body)) { }

private:
        std::unique_ptr<AST> condition, body;
};

class ReturnStatement : public AST
{
public:
        ReturnStatement(std::unique_ptr<AST> expr) :
        expr(std::move(expr)) { }

private:
        std::unique_ptr<AST> expr;
};


class Declaration : public AST
{
public:
        Declaration(Token & tok, std::vector<std::unique_ptr<AST>> vars) :
        tok(tok), vars(std::move(vars)) { }

private:
        Token tok;
        std::vector<std::unique_ptr<AST>> vars;
};

class CompoundStatement : public AST
{
public:
        CompoundStatement(std::vector<std::unique_ptr<AST>> statement_list) :
        statement_list(std::move(statement_list)) { }

private:
        std::vector<std::unique_ptr<AST>> statement_list;
};

class FuncCall : public AST
{
public:
        FuncCall(std::string & callee, std::vector<std::unique_ptr<AST>> args) :
        callee(callee), args(std::move(args)) { }

private:
        std::string callee;
        std::vector<std::unique_ptr<AST>> args;
};

class Prototype : public AST
{
public:
        Prototype(std::string func_name, std::vector<std::unique_ptr<AST>> args) :
        func_name(func_name), args(std::move(args)) { }

private:
        std::string func_name;
        std::vector<std::unique_ptr<AST>> args;
};

class Function : public AST
{
public:
        Function(std::unique_ptr<AST> prototype, std::unique_ptr<AST> body) :
        prototype(std::move(prototype)), body(std::move(body)) { }

private:
        std::unique_ptr<AST> prototype, body;
};

class Program : public AST
{
public:
        Program(std::vector<std::unique_ptr<AST>> functions) :
        functions(std::move(functions)) { }

private:
        std::vector<std::unique_ptr<AST>> functions;
};

#endif
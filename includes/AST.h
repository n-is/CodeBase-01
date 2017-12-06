#ifndef AST_H_
#define AST_H_

#include "Token.h"
#include <memory>
#include <vector>

#include "AST_Visitor.h"

class AST_Visitable
{
public:
        virtual ~AST_Visitable() { };
        virtual void Accept(AST_Visitor & visitor) = 0;
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

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

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

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

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

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }
        
private:
        std::string value;
};


class Unary : public AST
{
public:
        Unary(Operator & tok, std::unique_ptr<AST> expr) :
        tok(tok), expr(std::move(expr)) { }

        AST * getExpr() { return expr.get(); }

        Token * getToken() { return &tok; }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }
        
private:
        Operator tok;
        std::unique_ptr<AST> expr;
};

class Binary : public AST
{
public:
        Binary(std::unique_ptr<AST> lvalue, Operator & tok, std::unique_ptr<AST> rvalue) :
        lvalue(std::move(lvalue)), tok(tok), rvalue(std::move(rvalue)) { };

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::unique_ptr<AST> lvalue;
        Operator tok;
        std::unique_ptr<AST> rvalue;
};

class AssignmentStatement : public AST
{
public:
        AssignmentStatement(std::string & lvalue, AssignmentOperator & tok, std::unique_ptr<AST> rvalue) :
        lvalue(std::move(lvalue)), tok(tok), rvalue(std::move(rvalue)) { };

        std::string getLvalue() { return lvalue; }
        Token * getToken() { return &tok; }
        AST * getRvalue() { return rvalue.get(); }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::string lvalue;
        AssignmentOperator tok;
        std::unique_ptr<AST> rvalue;
};

class IfStatement : public AST
{
public:
        IfStatement(std::unique_ptr<AST> condition, std::unique_ptr<AST> body) :
        condition(std::move(condition)), body(std::move(body)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::unique_ptr<AST> condition, body;
        
};

class WhileStatement : public AST
{
public:
        WhileStatement(std::unique_ptr<AST> condition, std::unique_ptr<AST> body) :
        condition(std::move(condition)), body(std::move(body)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::unique_ptr<AST> condition, body;
};

class ReturnStatement : public AST
{
public:
        ReturnStatement(std::unique_ptr<AST> expr) :
        expr(std::move(expr)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::unique_ptr<AST> expr;
};


class Declaration : public AST
{
public:
        Declaration(Token & tok, std::vector<std::unique_ptr<AST>> vars) :
        tok(tok), vars(std::move(vars)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        Token tok;
        std::vector<std::unique_ptr<AST>> vars;
};

class CompoundStatement : public AST
{
public:
        CompoundStatement(std::vector<std::unique_ptr<AST>> statement_list) :
        statement_list(std::move(statement_list)) { }

        std::vector<std::unique_ptr<AST>> & getStatementList() { return statement_list; }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::vector<std::unique_ptr<AST>> statement_list;
};

class FuncCall : public AST
{
public:
        FuncCall(std::string & callee, std::vector<std::unique_ptr<AST>> args) :
        callee(callee), args(std::move(args)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::string callee;
        std::vector<std::unique_ptr<AST>> args;
};

class Prototype : public AST
{
public:
        Prototype(std::string func_name, std::vector<std::unique_ptr<AST>> args) :
        func_name(func_name), args(std::move(args)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::string func_name;
        std::vector<std::unique_ptr<AST>> args;
};

class Function : public AST
{
public:
        Function(std::unique_ptr<AST> prototype, std::unique_ptr<AST> body) :
        prototype(std::move(prototype)), body(std::move(body)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::unique_ptr<AST> prototype, body;
};

class Program : public AST
{
public:
        Program(std::vector<std::unique_ptr<AST>> functions) :
        functions(std::move(functions)) { }

        void Accept(AST_Visitor & visitor) { visitor.visit(this); }

private:
        std::vector<std::unique_ptr<AST>> functions;
};

#endif
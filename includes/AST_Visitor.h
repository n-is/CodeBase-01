#ifndef AST_VISITOR_H_
#define AST_VISITOR_H_

#include <memory>
#include <fstream>
#include "TokenVisitor.h"

class Int;
class Float;
class Id;
class Unary;
class Binary;
class AssignmentStatement;
class IfStatement;
class WhileStatement;
class ReturnStatement;
class Declaration;
class CompoundStatement;
class FuncCall;
class Parameter;
class Prototype;
class Function;
class Program;

class AST_Visitor
{
public:
        virtual ~AST_Visitor() { }
        virtual void visit(Int *) = 0;
        virtual void visit(Float *) = 0;
        virtual void visit(Id *) = 0;
        virtual void visit(Unary *) = 0;
        virtual void visit(Binary *) = 0;
        virtual void visit(AssignmentStatement *) = 0;
        virtual void visit(IfStatement *) = 0;
        virtual void visit(WhileStatement *) = 0;
        virtual void visit(ReturnStatement *) = 0;
        virtual void visit(Declaration *) = 0;
        virtual void visit(CompoundStatement *) = 0;
        virtual void visit(FuncCall *) = 0;
        virtual void visit(Parameter *) = 0;
        virtual void visit(Prototype *) = 0;
        virtual void visit(Function *) = 0;
        virtual void visit(Program *) = 0;
};

class AST_Printer : public AST_Visitor
{
public:
        AST_Printer();
        ~AST_Printer();

        void visit(Int *);
        void visit(Float *);
        void visit(Id *);
        void visit(Unary *);
        void visit(Binary *);
        void visit(AssignmentStatement *);
        void visit(IfStatement *);
        void visit(WhileStatement *);
        void visit(ReturnStatement *);
        void visit(Declaration *);
        void visit(CompoundStatement *);
        void visit(FuncCall *);
        void visit(Parameter *);
        void visit(Prototype *);
        void visit(Function *);
        void visit(Program *);
private:
        std::unique_ptr<TokenVisitor> token_plotter;
};

class C_CodeGen : public AST_Visitor
{
public:
        C_CodeGen(const char * file_name);
        ~C_CodeGen();

        void visit(Int *);
        void visit(Float *);
        void visit(Id *);
        void visit(Unary *);
        void visit(Binary *);
        void visit(AssignmentStatement *);
        void visit(IfStatement *);
        void visit(WhileStatement *);
        void visit(ReturnStatement *);
        void visit(Declaration *);
        void visit(CompoundStatement *);
        void visit(FuncCall *);
        void visit(Parameter *);
        void visit(Prototype *);
        void visit(Function *);
        void visit(Program *);
private:
        std::unique_ptr<TokenVisitor> token_plotter;
        std::ofstream source_output;
};

#endif
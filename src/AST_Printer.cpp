#include "../includes/AST_Visitor.h"
#include "../includes/AST.h"

#include <iostream>

using std::cout;
using std::endl;

AST_Printer::AST_Printer() :
token_plotter(new TokenPrinter())
{

}

AST_Printer::~AST_Printer()
{
        cout << endl;
}

void AST_Printer::visit(Int * ast_node)
{
        cout << ast_node->getValue();
}

void AST_Printer::visit(Float * ast_node)
{
        cout << ast_node->getValue();
}

void AST_Printer::visit(Id * ast_node)
{
        cout << "(" << ast_node->getValue() << ")";
}

void AST_Printer::visit(Unary * ast_node)
{
        cout << "( ";
        auto tok = static_cast<Operator *>(ast_node->getToken());
        tok->Accept(*token_plotter);
        ast_node->getExpr()->Accept(*this);
        cout << " )";
}

void AST_Printer::visit(Binary * ast_node)
{
        cout << "( ";
        ast_node->getLvalue()->Accept(*this);
        ast_node->getToken()->Accept(*token_plotter);
        ast_node->getRvalue()->Accept(*this);
        cout << " )";
}

void AST_Printer::visit(AssignmentStatement * ast_node)
{
        cout << ast_node->getLvalue() << " ";
        ast_node->getToken()->Accept(*token_plotter);
        ast_node->getRvalue()->Accept(*this);
        cout << ";";
}

void AST_Printer::visit(IfStatement * ast_node)
{
        cout << "? ";
        ast_node->getCondition()->Accept(*this);
        ast_node->getBody()->Accept(*this);
}

void AST_Printer::visit(WhileStatement * ast_node)
{
        cout << "[ ";
        ast_node->getCondition()->Accept(*this);
        cout << " ]";
        ast_node->getBody()->Accept(*this);
}

void AST_Printer::visit(ReturnStatement * ast_node)
{
        cout << "^ ";
        ast_node->getExpr()->Accept(*this);
}

void AST_Printer::visit(Declaration * ast_node)
{
        ast_node->getToken()->Accept(*token_plotter);
        unsigned int numberOfVariables = ast_node->getVars().size();
        for(auto & var : ast_node->getVars()) {
                cout << ' ';
                var->Accept(*this);
                if(--numberOfVariables) {
                        cout << ',';
                }
        }
        cout << ';';
}

static void printTabs(unsigned int n) {
        while(n--)
                cout << '\t';
}

void AST_Printer::visit(CompoundStatement * ast_node)
{
        cout << "{\n";
        for(auto& stmt : ast_node->getStatementList()) {
                printTabs(ast_node->getScopeLevel() + 1);
                stmt->Accept(*this);
                cout << endl;
        }
        printTabs(ast_node->getScopeLevel());
        cout << "}";
}

void AST_Printer::visit(FuncCall * ast_node)
{
        cout << ast_node->getFuncName() << "(";
        int numberOfArgs = ast_node->getArgs().size();
        for(auto& arg : ast_node->getArgs()) {
                if(numberOfArgs--) {
                        arg->Accept(*this);
                }
                if(numberOfArgs > 0) {
                        cout << ", ";
                }
        }
        cout << ")";
}

void AST_Printer::visit(Parameter * ast_node)
{
        auto tok = static_cast<DataType *>(ast_node->getToken());
        tok->Accept(*token_plotter);
        cout << " " << ast_node->getVar();
}

void AST_Printer::visit(Prototype * ast_node)
{
        cout << "task " << ast_node->getFuncName() << "(";
        int numberOfArgs = ast_node->getArgs().size();
        for(auto& arg : ast_node->getArgs()) {
                if(numberOfArgs--) {
                        arg->Accept(*this);
                }
                if(numberOfArgs > 0) {
                        cout << ", ";
                }
        }
        cout << ") : ";
        auto tok = static_cast<DataType *>(ast_node->getToken());
        tok->Accept(*token_plotter);
}

void AST_Printer::visit(Function * ast_node)
{
        ast_node->getPrototype()->Accept(*this);
        cout << " ";
        ast_node->getBody()->Accept(*this);
}

void AST_Printer::visit(Program * ast_node)
{
        int numberOfFuncs = ast_node->getFunctions().size();
        for(auto& arg : ast_node->getFunctions()) {
                if(numberOfFuncs--) {
                        arg->Accept(*this);
                }
                cout << endl << endl;
        }
}

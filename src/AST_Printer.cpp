#include "../includes/AST_Visitor.h"
#include "../includes/AST.h"

#include <iostream>

using std::cout;
using std::endl;

AST_Printer::AST_Printer() :
token_plotter(new TokenPrinter())
{

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
        cout << "Id(" << ast_node->getValue() << ")";
}

void AST_Printer::visit(Unary * ast_node)
{
        auto tok = static_cast<Operator *>(ast_node->getToken());
        tok->Accept(*token_plotter);
        ast_node->getExpr()->Accept(*this);
}

void AST_Printer::visit(Binary * ast_node)
{
        cout << " (";
        ast_node->getLvalue()->Accept(*this);
        ast_node->getToken()->Accept(*token_plotter);
        ast_node->getRvalue()->Accept(*this);
        cout << ") ";
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

}

void AST_Printer::visit(WhileStatement * ast_node)
{

}

void AST_Printer::visit(ReturnStatement * ast_node)
{

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
        cout << "}\n";
}

void AST_Printer::visit(FuncCall * ast_node)
{

}

void AST_Printer::visit(Prototype * ast_node)
{

}

void AST_Printer::visit(Function * ast_node)
{

}

void AST_Printer::visit(Program * ast_node)
{

}


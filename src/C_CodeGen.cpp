#include "../includes/AST_Visitor.h"
#include "../includes/AST.h"
#include "../helpers/tokensToStrings.h"

#include <fstream>

using std::endl;

C_CodeGen::C_CodeGen(const char * file_name) :
token_plotter(new TokenPrinter())
{
        source_output.open(file_name, std::ios::out);
}

C_CodeGen::~C_CodeGen()
{
        source_output << "\n";
        source_output.close();
}

void C_CodeGen::visit(Int * ast_node)
{
        source_output << ast_node->getValue();
}

void C_CodeGen::visit(Float * ast_node)
{
        source_output << ast_node->getValue();
}

void C_CodeGen::visit(Id * ast_node)
{
        source_output << ast_node->getValue();
}

void C_CodeGen::visit(Unary * ast_node)
{
        // cout << "( ";
        source_output << ' ';        
        auto tok = static_cast<Operator *>(ast_node->getToken());
        source_output << getStr(tok->getOperatorType());
        ast_node->getExpr()->Accept(*this);
        // cout << " )";
}

void C_CodeGen::visit(Binary * ast_node)
{
        // cout << "( ";
        ast_node->getLvalue()->Accept(*this);
        auto tok = static_cast<Operator *>(ast_node->getToken());
        source_output << ' ';        
        source_output << getStr(tok->getOperatorType());
        source_output << ' ';        
        ast_node->getRvalue()->Accept(*this);
        // cout << " )";
}

void C_CodeGen::visit(AssignmentStatement * ast_node)
{
        source_output << ast_node->getLvalue();
        auto tok = static_cast<AssignmentOperator *>(ast_node->getToken());
        source_output << ' ';
        source_output << getStr(tok->getType());
        source_output << ' ';        
        ast_node->getRvalue()->Accept(*this);
        source_output << ";";
        // cout << ";";
}

void C_CodeGen::visit(IfStatement * ast_node)
{
        source_output << "if (";
        ast_node->getCondition()->Accept(*this);
        source_output << ") ";
        ast_node->getBody()->Accept(*this);
}

void C_CodeGen::visit(WhileStatement * ast_node)
{
        source_output << "while (";
        ast_node->getCondition()->Accept(*this);
        source_output << ") ";
        ast_node->getBody()->Accept(*this);
}

void C_CodeGen::visit(ReturnStatement * ast_node)
{
        source_output << "return ";
        ast_node->getExpr()->Accept(*this);
        source_output << ";";
}

void C_CodeGen::visit(Declaration * ast_node)
{
        auto tok = static_cast<DataType *>(ast_node->getToken());
        source_output << getStr(tok->getType());
        unsigned int numberOfVariables = ast_node->getVars().size();
        for(auto & var : ast_node->getVars()) {
                source_output << ' ';
                var->Accept(*this);
                if(--numberOfVariables) {
                        source_output << ',';
                }
        }
        source_output << ';';
}

static std::string printTabs(unsigned int n) {
        std::string str;
        while(n--)
                str.push_back('\t');
        return str;
}

void C_CodeGen::visit(CompoundStatement * ast_node)
{
        source_output << "{\n";
        for(auto& stmt : ast_node->getStatementList()) {
                source_output << printTabs(ast_node->getScopeLevel() + 1);
                stmt->Accept(*this);
                source_output << endl;
        }
        source_output << printTabs(ast_node->getScopeLevel());
        source_output << "}";
}

void C_CodeGen::visit(FuncCall * ast_node)
{
        source_output << ast_node->getFuncName() << "(";
        int numberOfArgs = ast_node->getArgs().size();
        for(auto& arg : ast_node->getArgs()) {
                if(numberOfArgs--) {
                        arg->Accept(*this);
                }
                if(numberOfArgs > 0) {
                        source_output << ", ";
                }
        }
        source_output << ")";
}

void C_CodeGen::visit(Parameter * ast_node)
{
        auto tok = static_cast<DataType *>(ast_node->getToken());
        source_output << getStr(tok->getType());
        source_output << " " << ast_node->getVar();
}

void C_CodeGen::visit(Prototype * ast_node)
{
        // source_output << "task ";
        source_output << ast_node->getFuncName() << "(";
        int numberOfArgs = ast_node->getArgs().size();
        for(auto& arg : ast_node->getArgs()) {
                if(numberOfArgs--) {
                        arg->Accept(*this);
                }
                if(numberOfArgs > 0) {
                        source_output << ", ";
                }
        }
        source_output << ")";
}

void C_CodeGen::visit(Function * ast_node)
{
        ast_node->getPrototype()->Accept(*this);
        source_output << " ";
        ast_node->getBody()->Accept(*this);
}

void C_CodeGen::visit(Program * ast_node)
{
        int numberOfFuncs = ast_node->getFunctions().size();
        for(auto& arg : ast_node->getFunctions()) {
                if(numberOfFuncs--) {
                        arg->Accept(*this);
                }
                source_output << endl << endl;
        }
}

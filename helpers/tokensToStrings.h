#ifndef TOKENS_TO_STRING_H_
#define TOKENS_TO_STRING_H_

#include <iostream>
enum class TokenType;
enum class OperatorType;
enum class AssignmentType;
enum class Type;

std::string getStr(TokenType t);
std::string getStr(OperatorType op);
std::string getStr(AssignmentType assign);
std::string getStr(Type datatype);

#endif
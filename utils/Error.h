#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>

enum class Error
{
        TokenError,
        NameError,
        TypeError,
        SyntaxError
};

int raise(Error e);
int raise(Error e, std::string message);

#endif
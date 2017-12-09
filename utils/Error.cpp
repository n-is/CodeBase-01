#include "Error.h"

using namespace std;

static string getErrorToken(Error e)
{
        switch(e) {
                case Error::TokenError : {
                        return "TokenError";
                }break;
                case Error::NameError : {
                        return "NameError";
                }break;
                case Error::TypeError : {
                        return "TypeError";
                }break;
                case Error::SyntaxError : {
                        return "SyntaxError";
                }break;
        }
        return "None";
}

int raise(Error e)
{
        #ifdef TEST
        return -1;
        #else
        cerr << getErrorToken(e) << endl;
        #endif
        exit(1);
}

int raise(Error e, string message)
{
        cerr << getErrorToken(e) << ": " << message << endl;
        exit(1);
}


int raise(Error e, std::string message, int atLine)
{
        cerr << "Error at or near line : " << atLine << endl;
        cerr << getErrorToken(e) << ": " << message << endl;
        exit(1);
}

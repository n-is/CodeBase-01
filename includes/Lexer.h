#ifndef LEXER_H_
#define LEXER_H_

#include "Token.h"
#include <array>
#include <vector>

class Lexer
{
public:
        Lexer(const char * filename);
        Token * getNextToken();
        unsigned int getCurrentLineNumber() const;

private:
        std::array<std::string, 2> keywords {
                "int", "float"
        };
        unsigned int file_lines_ = 0;
        std::vector<std::string> source_lines_;
        unsigned int line_number_;
        std::string text_;
        unsigned int len_;
        char curr_char_;
        unsigned int curr_index_;

        void advance();
        char peek(int level);
        void getNextLine();
        void skipComment();

        Token * getNum();
        Token * getWord();
};

#endif
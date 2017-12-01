#include "../includes/Lexer.h"
#include "../includes/Token.h"
#include "../utils/Error.h"

#include <iostream>
#include <fstream>

Lexer::Lexer(const char * file_name)
{
        std::ifstream source_file;
        source_file.open(file_name, std::ios::in);
        std::string source;
        while(getline(source_file,source)) {
                source_lines_.push_back(source);
                ++file_lines_;
        }

        line_number_ = 0;
        text_ = source_lines_.at(0);
        len_ = text_.length();
        curr_index_ = 0;
        curr_char_ = text_[0];
}

unsigned int Lexer::getCurrentLineNumber() const
{
        return line_number_;
}

/* Returns Tokens for following tokens :
        " \t"   : Spaces and tabs are skipped,
        "+="    : PLUS_EQ,
        "+"     : PLUS,
        "-="    : MINUS_EQ,
        "->"    : RIGHT_ARROW,
        "-"     : MINUS,
        "/="    : DIVIDE_EQ,
        C-Style Comments skip,
        "/"     : DIVIDE,
        "*="    : MULTIPLY_EQ,
        "*"     : MULTIPLY,
        "%="    : MODULO_EQ,
        "%"     : MODULO,
        "("     : LPAREN,
        ")"     : RPAREN,
        "{"     : LCURLY,
        "}"     : RCURLY,
        "["     : LSQUARE,
        "[]"    : SCREEN,
        "]"     : RSQUARE,
        "="     : ASSIGN,
        "=="    : EQUALS,
        ","     : COMMA,
        "."     : DOT,
        ";"     : SEMICOLON,
        ":"     : COLON,
        "<-"    : LEFT_ARROW,
        "<="    : LESSER_EQUALS,
        "<"     : LESSER,
        ">="    : GREATER_EQUALS,
        ">"     : GREATER,
        "!="    : NOT_EQUALS,
        "?"     : QUESTION,
        "!"     : BANG,
        "^"     : CARET,
        number,
        identifier,
        keyword
*/
Token * Lexer::getNextToken()
{
        while(curr_char_) {
                switch(curr_char_) {
                        case ' ' : {
                                advance();
                                continue;
                        }break;

                        case '\t' : {
                                advance();
                                continue;
                                // return new Token(TokenType::TAB);
                        }break;

                        case '+' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new AssignmentOperator(AssignmentType::PLUS_EQ) ;
                                }
                                return new Operator(OperatorType::PLUS);
                        }break;

                        case '-' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new AssignmentOperator(AssignmentType::MINUS_EQ);
                                }
                                if(curr_char_ == '>') {
                                        advance();
                                        return new Token(TokenType::RIGHT_ARROW);
                                }
                                return new Operator(OperatorType::MINUS);
                        }break;

                        case '/' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new AssignmentOperator(AssignmentType::DIVIDE_EQ);
                                }
                                else if(curr_char_ == '*') {
                                        advance();
                                        skipComment();
                                        continue;
                                }
                                return new Operator(OperatorType::DIVIDE);
                        }break;

                        case '*' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new AssignmentOperator(AssignmentType::MULTIPLY_EQ);
                                }
                                return new Operator(OperatorType::MULTIPLY);
                        }break;

                        case '%' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new AssignmentOperator(AssignmentType::MODULO_EQ);
                                }
                                return new Operator(OperatorType::MODULO);
                        }break;

                        case '(' : {
                                advance();
                                return new Token(TokenType::LPAREN);
                        }break;

                        case ')' : {
                                advance();
                                return new Token(TokenType::RPAREN);
                        }break;

                        case '{' : {
                                advance();
                                return new Token(TokenType::LCURLY);
                        }break;

                        case '}' : {
                                advance();
                                return new Token(TokenType::RCURLY);
                        }break;

                        case '[' : {
                                advance();
                                if(curr_char_ == ']') {
                                        advance();
                                        return new Token(TokenType::SCREEN);
                                }
                                return new Token(TokenType::LSQUARE);
                        }break;

                        case ']' : {
                                advance();
                                return new Token(TokenType::RSQUARE);
                        }break;

                        case '=' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new Operator(OperatorType::EQUALS);
                                }
                                return new AssignmentOperator(AssignmentType::ASSIGN);
                        }break;

                        case ',' : {
                                advance();
                                return new Token(TokenType::COMMA);
                        }break;

                        case '.' : {
                                advance();
                                return new Token(TokenType::DOT);
                        }break;

                        case ';' : {
                                advance();
                                return new Token(TokenType::SEMICOLON);
                        }break;

                        case ':' : {
                                advance();
                                return new Token(TokenType::COLON);
                        }break;

                        case '<' : {
                                advance();
                                if(curr_char_ == '-') {
                                        advance();
                                        return new Token(TokenType::LEFT_ARROW);
                                }
                                else if(curr_char_ == '=') {
                                        advance();
                                        return new RelationOperator(RelationType::LESSER_EQUALS);
                                }
                                return new RelationOperator(RelationType::LESSER);
                        }break;

                        case '>' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new RelationOperator(RelationType::GREATER_EQUALS);
                                }
                                return new RelationOperator(RelationType::GREATER);
                        }break;

                        case '?' : {
                                advance();
                                return new Token(TokenType::QUESTION);
                        }break;

                        case '!' : {
                                advance();
                                if(curr_char_ == '=') {
                                        advance();
                                        return new Operator(OperatorType::NOT_EQUALS);
                                }
                                return new Token(TokenType::BANG);
                        }break;

                        case '^' : {
                                advance();
                                return new Token(TokenType::CARET);
                        }break;

                        default : {
                                if(isdigit(curr_char_)) {
                                        return getNum();
                                }
                                else if(isalpha(curr_char_) || curr_char_ == '_') {
                                        return getWord();
                                }
                        }
                }
                raise(Error::TokenError, "Undefined Token in Source Code");
        }
        if(line_number_ < file_lines_ - 1) {
                getNextLine();
                return getNextToken();
                // return new Token(TokenType::NEWLINE);
        }
        return new Token(TokenType::EOS);
}


Token * Lexer::getNum()
{
        std::string inte = "";
        while(isdigit(curr_char_)) {
                inte.push_back(curr_char_);
                advance();
        }
        if(curr_char_ == '.') {
                inte.push_back(curr_char_);
                advance();
                while(isdigit(curr_char_)) {
                        inte.push_back(curr_char_);
                        advance();
                }
                return new FloatLiteral(stod(inte));
        }
        return new IntegerLiteral(stoi(inte));
}

Token * Lexer::getWord()
{
        std::string word = "";
        while(isalnum(curr_char_) || curr_char_ == '_') {
                word.push_back(curr_char_);
                advance();
        }
        for(std::string w : keywords) {
                if(w == word)
                        return new KeyWord(word);
        }
        return new Identifier(word);
}

void Lexer::advance()
{
        ++curr_index_;
        if(curr_index_ > len_ - 1)
                curr_char_ = '\0';
        else
                curr_char_ = text_[curr_index_];
}

void Lexer::getNextLine()
{
        ++line_number_;
        curr_index_ = 0;
        text_ = source_lines_.at(line_number_);
        len_ = text_.length();
        curr_char_ = text_[0];
}

void Lexer::skipComment()
{
        while(curr_char_ != '*' && peek(1) != '/'){
                advance();
                if(curr_char_ == '\0') {
                        getNextLine();
                }
        }
        advance();
        advance();
}

char Lexer::peek(int level)
{
        unsigned int peek_index = curr_index_ + level;
        if(peek_index > len_ - 1)
                return '\0';
        return text_[peek_index];
}

#ifndef TOKEN_VISITOR_H_
#define TOKEN_VISITOR_H_

class Token;
class Literal;

class TokenVisitor
{
public:
        virtual ~TokenVisitor() { }

        virtual void visit(Token *) = 0;
        virtual void visit(Literal *) = 0;
};

class TokenPrinter : public TokenVisitor
{
public:
        void visit(Token *);
        void visit(Literal *);
};

#endif /* !TOKEN_VISITOR_H_ */
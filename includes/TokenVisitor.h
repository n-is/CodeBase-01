#ifndef TOKEN_VISITOR_H_
#define TOKEN_VISITOR_H_

class Token;
class IntegerLiteral;
class FloatLiteral;
class Operator;
class AssignmentOperator;
class RelationOperator;
class Identifier;
class KeyWord;


class TokenVisitor
{
public:
        virtual ~TokenVisitor() { }

        virtual void visit(Token *) = 0;
        virtual void visit(IntegerLiteral *) = 0;
        virtual void visit(FloatLiteral *) = 0;
        virtual void visit(Operator *) = 0;
        virtual void visit(AssignmentOperator *) = 0;
        virtual void visit(RelationOperator *) = 0;
        virtual void visit(Identifier *) = 0;
        virtual void visit(KeyWord *) = 0;
};

class TokenPrinter : public TokenVisitor
{
public:
        void visit(Token *);
        void visit(IntegerLiteral *);
        void visit(FloatLiteral *);
        void visit(Operator *);
        void visit(AssignmentOperator *);
        void visit(RelationOperator *);
        void visit(Identifier *);
        void visit(KeyWord *);
};

#endif /* !TOKEN_VISITOR_H_ */
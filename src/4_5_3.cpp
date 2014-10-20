#include <cassert>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

struct Transformer;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Scope
{
    virtual ~Scope() { }
    virtual double variableValue(std::string const &name) const = 0;
};

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate(Scope const * s) const = 0;
    virtual Expression *transform(Transformer *tr) const = 0;
};

struct Transformer
{
    virtual ~Transformer() { }
    virtual Expression *transformNumber(Number const *) = 0;
    virtual Expression *transformBinaryOperation(BinaryOperation const *) = 0;
    virtual Expression *transformFunctionCall(FunctionCall const *) = 0;
    virtual Expression *transformVariable(Variable const *) = 0;
};

struct Number : Expression
{
    Number(double value)
        : value_(value)
    {}

    double value() const
    { return value_; }

    double evaluate(Scope const * s) const
    { return value_; }

    Expression *transform(Transformer *tr) const
	{ return tr->transformNumber(this); };

private:
    double value_;
};

struct BinaryOperation : Expression
{
    enum {
        PLUS = '+',
        MINUS = '-',
        DIV = '/',
        MUL = '*'
    };

    BinaryOperation(Expression const *left, int op, Expression const *right)
        : left_(left), op_(op), right_(right)
    { assert(left_ && right_); }

    ~BinaryOperation()
    {
        delete left_;
        delete right_;
    }

    Expression const *left() const
    { return left_; }

    Expression const *right() const
    { return right_; }

    int operation() const
    { return op_; }

    double evaluate(Scope const * s) const
    {
        double left = left_->evaluate(s);
        double right = right_->evaluate(s);
        switch (op_)
        {
        case PLUS: return left + right;
        case MINUS: return left - right;
        case DIV: return left / right;
        case MUL: return left * right;
        }
        assert(0);
        return 0.0;
    }

	Expression *transform(Transformer *tr) const
	{ return tr->transformBinaryOperation(this); };

private:
    Expression const *left_;
    Expression const *right_;
    int op_;
};

struct FunctionCall : Expression
{
    FunctionCall(std::string const &name, Expression const *arg)
        : name_(name), arg_(arg)
    {
        assert(arg_);
        assert(name_ == "sqrt" || name_ == "abs");
    }

    // реализуйте оставшие методы из
    // интерфейса Expression и не забудьте
    // удалить arg_, как это сделано в классе
    // BinaryOperation
    
    ~FunctionCall() {
        delete arg_;
    }

    std::string const & name() const
    {
        // put your code here
        return name_;
    }

    Expression const *arg() const
    {
        // here
        return arg_;
    }

    // and here
    double evaluate(Scope const * s) const
    {
        double arg = arg_->evaluate(s);
        if (name() == "sqrt")
            return sqrt(arg);
        else if (name() == "abs")
            return fabs(arg);
    }

	Expression *transform(Transformer *tr) const
	{ return tr->transformFunctionCall(this); };

private:
    std::string const name_;
    Expression const *arg_;
};

struct Variable : Expression
{
	Variable(std::string const &name) : name_(name) { }
    std::string const &name() const { return name_; }
    double evaluate(Scope const * s) const
    {
        assert(0);
        return 0.0;
    }
    Expression *transform(Transformer *tr) const { return tr->transformVariable(this); }
private:
    std::string const name_;
};

int main() {
}
#include <cassert> // assert
#include <cstring>
#include <iostream>
using namespace std;

struct Expression
{
// put your code here
    virtual ~Expression() {};
    virtual double evaluate() const = 0;
};

struct Number : Expression
{
	Number() {}

    Number(double value)
        : value_(value)
    {}

    double value() const
    { return value_; }

    double evaluate() const
    { return value_; }

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

	BinaryOperation() {}

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

    double evaluate() const
    {
        double left = left_->evaluate();
        double right = right_->evaluate();
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

private:
    Expression const *left_;
    Expression const *right_;
    int op_;
};

bool check_equals(Expression const *left, Expression const *right)
{
    // put your code here
    size_t * sLeft;
    size_t * sRight;
    memcpy(&sLeft,  &left,  sizeof(size_t));
    memcpy(&sRight, &right, sizeof(size_t));
    return (*(&sLeft[0]) == *(&sRight[0]));
}

int main() {
	//Expression e;
	Number * n1 = new Number;
	Number * n2 = new Number;
	BinaryOperation * b1 = new BinaryOperation;
	BinaryOperation * b2 = new BinaryOperation;
	cout << check_equals(n1, b1);
}
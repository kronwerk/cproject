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

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate() const = 0;
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

    double evaluate() const
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
    double evaluate() const
    {
        double arg = arg_->evaluate();
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
    double evaluate() const
    {
        assert(0);
        return 0.0;
    }
    Expression *transform(Transformer *tr) const { return tr->transformVariable(this); }
private:
    std::string const name_;
};


/**
 * реализуйте все необходимые методы
 * если считаете нужным, то можете
 * заводить любые вспомогательные
 * методы
 */
struct FoldConstants : Transformer
{
	Expression * swch(Expression const * e)
	{
		Expression * res = 0;
		Number const * tmpN = dynamic_cast<Number const *>(e);
		if (tmpN)
			res = transformNumber(tmpN);
		Variable const * tmpV = dynamic_cast<Variable const *>(e);
		if (tmpV)
			res = transformVariable(tmpV);
		FunctionCall const * tmpF = dynamic_cast<FunctionCall const *>(e);
		if (tmpF)
			res = transformFunctionCall(tmpF);
		BinaryOperation const * tmpB = dynamic_cast<BinaryOperation const *>(e);
		if (tmpB)
			res = transformBinaryOperation(tmpB);
		return res;
	}

    Expression *transformNumber(Number const *number)
    { 
		Number const * tmp = dynamic_cast<Number const *>(number);
		Number * res = 0;
		if (tmp)
			res = new Number(number->value());
		return res;
	}

    Expression *transformBinaryOperation(BinaryOperation const *binop)
    { 
		Expression * res = 0;
		BinaryOperation const * tmp = dynamic_cast<BinaryOperation const *>(binop);
		if (tmp) {
			Expression const * left = swch(binop->left());
			Expression const * right = swch(binop->right());
			Number const * leftN = dynamic_cast<Number const *>(left);
			Number const * rightN = dynamic_cast<Number const *>(right);
			if (leftN && rightN) {
				tmp = new BinaryOperation(left, binop->operation(), right);
				res = new Number(tmp->evaluate());
				delete tmp;
			}
			else {
				res = new BinaryOperation(left, binop->operation(), right);
			};
			//delete right;
			//delete left;
		};
		return res;	
	}

    Expression *transformFunctionCall(FunctionCall const *fcall)
    { 
		Expression * res = 0;
		FunctionCall const * tmp = dynamic_cast<FunctionCall const *>(fcall);
		if (tmp) {
			Expression const * arg = swch(fcall->arg());
			Number const * argN = dynamic_cast<Number const *>(arg);
			if (argN) {
				tmp = new FunctionCall(fcall->name(), arg);
				res = new Number(tmp->evaluate());
				delete tmp;
			}
			else {
				res = new FunctionCall(fcall->name(), arg);
			};
			//delete arg;
		};
		return res;	
	}

    Expression *transformVariable(Variable const *var)
    { 
		Variable const * tmp = dynamic_cast<Variable const *>(var);
		Variable * res = 0;
		if (tmp)
			res = new Variable(var->name());
		return res;
	}
};

int main() {
  struct Number *x = new Number(10);
  struct Number *y = new Number(6);

  Expression *expression1 = new BinaryOperation(x,BinaryOperation::PLUS,y);
  Transformer *transformer1 = new FoldConstants();
  Expression *new_expression1 = expression1->transform(transformer1);

  cout<<"binary operation 1: "<<new_expression1->evaluate()<<endl;

  Expression *expression2 = new FunctionCall("sqrt", new_expression1);
  Transformer *transformer2 = new FoldConstants();
  Expression *new_expression2 = expression2->transform(transformer1);

  cout<<"function call 1: "<<new_expression2->evaluate()<<endl;

  Expression *expression3 = new FunctionCall("sqrt", new_expression2);
  Transformer *transformer3 = new FoldConstants();
  Expression *new_expression3 = expression3->transform(transformer1);

  cout<<"function call 2: "<<new_expression3->evaluate()<<endl;

  Expression *expression4 = new BinaryOperation(new_expression3,BinaryOperation::DIV,y);
  Transformer *transformer4 = new FoldConstants();
  Expression *new_expression4 = expression4->transform(transformer1);

  cout<<"binary operation 2: "<<new_expression4->evaluate()<<endl;
  system("pause");
  return 0;
}
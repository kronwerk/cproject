#include <string>

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
    Number(double value);
    double value() const;
    double evaluate() const;
    Expression *transform(Transformer *tr) const;

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
    BinaryOperation(Expression const *left, int op, Expression const *right);
    ~BinaryOperation();
    double evaluate() const;
    Expression *transform(Transformer *tr) const;
    Expression const *left() const;
    Expression const *right() const;
    int operation() const;

private:
    Expression const *left_;
    Expression const *right_;
    int op_;
};

struct FunctionCall : Expression
{
    FunctionCall(std::string const &name, Expression const *arg);
    ~FunctionCall();
    double evaluate() const;
    Expression *transform(Transformer *tr) const;
    std::string const &name() const;
    Expression const *arg() const;

private:
    std::string const name_;
    Expression const *arg_;
};

struct Variable : Expression
{
    Variable(std::string const name);
    std::string const & name() const;
    double evaluate() const;
    Expression *transform(Transformer *tr) const;

private:
    std::string const name_;
};


/**
 * реализуйте все необходимые методы класса
 * вы можете определять любые вспомогательные
 * методы, если хотите
 */
struct CopySyntaxTree : Transformer
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
		BinaryOperation * res = 0;
		BinaryOperation const * tmp = dynamic_cast<BinaryOperation const *>(binop);
		if (tmp) {
			Expression const * left = binop->left();
			Expression const * right = binop->right();
			res = new BinaryOperation(swch(left), binop->operation(), swch(right));
		};
		return res;	
	}

    Expression *transformFunctionCall(FunctionCall const *fcall)
    { 
		FunctionCall * res = 0;
		FunctionCall const * tmp = dynamic_cast<FunctionCall const *>(fcall);
		if (tmp) {
			Expression const * arg = fcall->arg();
			res = new FunctionCall(fcall->name(), swch(arg));
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
struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct ScopedPtr
{
    explicit ScopedPtr(Expression *ptr = 0) {
		ptr_ = ptr;
	}

	~ScopedPtr() {
		delete ptr_;
	}

    Expression* get() const {
		return ptr_;
	}

    Expression* release() {
		Expression *tmp = ptr_;
		ptr_ = 0;
		return tmp;
	}

    void reset(Expression *ptr = 0) {
		delete ptr_;
		ptr_ = ptr;
	}

    Expression& operator*() const {
		return *ptr_;
	}

    Expression* operator->() const {
		return ptr_;
	}

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};
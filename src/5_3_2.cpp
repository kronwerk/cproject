#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <assert.h>

#include <algorithm>
using namespace std;

struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct SharedPtr
{
	void init(Expression * ptr) {
		ptr_ = ptr;
		if (ptr) 
			counter = new int(1);
		else
			counter = 0;
	}

    explicit SharedPtr(Expression *ptr = 0) {
		init(ptr);
	}

	SharedPtr(const SharedPtr& sp) {
		ptr_ = sp.get();
		if (sp.counter) {
			++(*sp.counter);
			counter = sp.counter;
		}
		else
			counter = 0;
	}

	void swap(SharedPtr & sp) {
		std::swap(counter, sp.counter);
		std::swap(ptr_, sp.ptr_);
	}

    SharedPtr& operator=(const SharedPtr& sp) {
		if (this != &sp) 
			SharedPtr(sp).swap(*this);
		return *this;
	}

	void clearPtr() {
		if (get()) {
			delete ptr_;
			ptr_ = 0;
		};
	}

	void clearCounter() {
		delete counter;
		counter = 0;
	}

	~SharedPtr() {
		decrementClearIfNeeded();
	}

    void reset(Expression *ptr = 0) {
		if (get() != ptr)
			decrementClearIfNeeded();
			init(ptr);
	}

	void decrementClearIfNeeded() {
		if ((counter) && (--(*counter) <= 0)) {
			clearPtr();
			clearCounter();
		};
	}
	
    Expression* get() const {
		return ptr_;
	}

    Expression& operator*() const {
		return *ptr_;
	}

    Expression* operator->() const {
		return get();
	}

	int * count() {
		return counter;
	}

private:
    Expression *ptr_;
	int * counter;
};

void test1() {
	Expression * e1 = new Expression;
	SharedPtr sp1(e1);
}

void test2() {
	Expression * e1;
	e1 = 0;
	SharedPtr sp1(e1);
}

void test3() {
	Expression * e1;
	e1 = 0;
	SharedPtr sp1(e1);
	sp1 = sp1;
}

void test4() {
	Expression * e1;
	e1 = 0;
	SharedPtr sp1(e1);
	sp1.reset(e1);
}

void test5() {
	Expression * e1;
	Expression * e2 = new Expression;
	e1 = 0;
	SharedPtr sp1(e1);
	sp1.reset(e2);
}

void test6() {
	Expression * e1 = new Expression;
	Expression * e2;
	e2 = 0;
	SharedPtr sp1(e1);
	sp1.reset(e2);
}

void test7() {
	Expression * e1 = new Expression;
	Expression * e2 = new Expression;
	SharedPtr sp1(e1);
	SharedPtr sp2(e2);
	sp1.reset(e2);
	sp2.reset(e1);
}

void test8() {
	Expression * e1 = new Expression;
	Expression * e2 = new Expression;
	SharedPtr sp1(e1);
	SharedPtr sp2(e2);
	sp1 = sp2;
	sp2.reset(e1);
}

void test9() {
	Expression * e1 = new Expression;
	SharedPtr sp1(e1);
	SharedPtr sp2 = SharedPtr(sp1);
}

/*int main() {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test9();
	test7();
	test8();
}*/

int main() {

  Expression *n16 = new Expression();
  Expression *n32 = new Expression();
  Expression *n42 = new Expression();

  cout<<"------------------"<<std::endl;
  cout<<"Test 1. SharedPtr p1(n32)"<<std::endl;
  SharedPtr p1(n32);
  cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
  cout<<"------------------"<<std::endl;

   cout<<"Test 2. SharedPtr p2 = p1"<<std::endl;
     SharedPtr p2 = p1;
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"------------------"<<std::endl;
    
     cout<<"Test 3. SharedPtr p3(p1)"<<std::endl;
     SharedPtr p3(p1);
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
     cout<<"------------------"<<std::endl;
     
     cout<<"Test 4. p3.reset(n16)"<<std::endl;
     p3.reset(n16);
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
     cout<<"------------------"<<std::endl;
    
    cout<<"Test 5. p3.reset(0)"<<std::endl;
    p3.reset(NULL);
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    cout<<"------------------"<<std::endl;  
    
    cout<<"Test 6. p1 = p1"<<std::endl;
    p1 = p1; 
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    cout<<"------------------"<<std::endl;
    
     cout<<"Test 7. p3.~SharedPtr()"<<std::endl;
     p3.~SharedPtr();
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"------------------"<<std::endl;
    
     cout<<"Test 8. p1.reset(n42)"<<std::endl;
     p1.reset(n42);
     cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"------------------"<<std::endl;
    
     cout<<"Test 9. p1.~SharedPtr()"<<std::endl;
     p1.~SharedPtr();
     cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
     cout<<"------------------"<<std::endl;
    
     cout<<"Test 10. p2.~SharedPtr()"<<std::endl;
     p2.~SharedPtr();
     cout<<"------------------"<<std::endl;

  cout<<"Test 11. SharedPtr p4(NULL)"<<std::endl;
  SharedPtr p4(NULL);
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  cout<<"Test 12. SharedPtr p5(NULL)"<<std::endl;
  SharedPtr p5(NULL);
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  cout<<"Test 13. p5 = p4"<<std::endl;
  p5 = p4;
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  cout<<"Test 14. SharedPtr p6(p4)"<<std::endl;
  SharedPtr p6(p4);
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  cout<<"Test 15. p6.reset(n16)"<<std::endl;
    p6.reset(n16);
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    cout<<"------------------"<<std::endl;

  cout<<"Test 16. p5 = p6"<<std::endl;
  p5 = p6;
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  cout<<"Test 17. p6 = p4"<<std::endl;
  p6 = p4;
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  cout<<"Test 18. p5.reset(NULL)"<<std::endl;
  p5.reset(NULL);
    cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
  cout<<"------------------"<<std::endl;

  system("pause");
  return 0;
}
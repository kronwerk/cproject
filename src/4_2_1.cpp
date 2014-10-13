#include <iostream>
using namespace std;

struct Some {
	void foo(char) { std::cout << "char" << std::endl; }
	void foo(signed char) { std::cout << "signed char" << std::endl; }
	void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }
};

int main() {
	Some s;
	s.foo('a');
	s.foo(97);
}
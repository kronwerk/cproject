#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
#include <cstdlib>
#include <algorithm> // swap
using namespace std;

struct String {
    String(const char *str = "") {
        size_ = strlen(str);
        str_ = new char[size_];
        strcpy(str_, str);
    }

    String(size_t n, char c) : size_(n) {
        str_ = new char[n];
        for(int i = 0;i < size_;i++)
            str_[i] = c;
    }

	String(const String &str) : size_(str.size_), str_(new char[size_]) {
        // put your code here
		for(size_t i = 0;i != size_;i++)
			str_[i] = str.str_[i];
    }

	String &operator=(const String &str) {
        // put your code here
		if (this != &str)
			String(str).swap(*this);
    }

    ~String() {
        delete [] str_;
    }

	void swap(String & a) {
		std::swap(size_, a.size_);
		std::swap(str_, a.str_);
	}

    size_t size() {
        return size_;
    }

    char &at(size_t idx) {
        return str_[idx];
    }

	char at(size_t idx) const {
        return str_[idx];		
	}

    const char *c_str() {
        char * tmp = (char *) malloc(size_+1);
        int i = 0;
        for(i = 0;i < size_;i++)
            tmp[i] = str_[i];
        tmp[i] = '\0';
        return tmp;
    }

    int compare(String &str) {
        return strcmp(this->c_str(), str.c_str());
    }

    void append(String &str) {
        char * old = str_;
        size_t old_size = size_;
        size_ += str.size();
        str_ = new char[size_ + 1];
        size_t i = 0;
        for(;i < old_size;i++)
            str_[i] = old[i];
        for(;i < size_;i++)
            str_[i] = str.str_[i - old_size];
        str_[i] = '\0';
        delete [] old;
    }

    size_t size_;
    char *str_;
};

int main () {
	String greet("Hello");
	char ch1 = greet.at(0);
	String const const_greet("Hello, Const!");
	char const &ch2 = const_greet.at(0);
    return 0;
}

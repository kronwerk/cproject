#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
#include <cstdlib>
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

    ~String() {
        delete [] str_;
    }

    size_t size() {
        return size_;
    }

    char &at(size_t idx) {
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
    String s("asdf");
    String p("hjk");
    s.append(p);
    cout << s.str_ << s.size() << strlen(s.str_) << endl;
    return 0;
}

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
using namespace std;

struct String {
    // для аллокации памяти не используйте malloc
    // иначе ваша программа может не пройти
    // тестирование
    String(const char *str = "") {
        // put your code here
        size_ = strlen(str);
        str_ = new char[size_];
        strcpy(str_, str);

    }

    // заполните строку n повторениями символа c,
    // например, для n == 3 и c == 'a', в строке
    // должно быть "aaa" (и не забудьте про
    // завершающий нулевой символ)
    // n == 0 допустимое значение
    String(size_t n, char c) : size_(n) {
        // put your code here
        str_ = new char[n];
        for(int i = 0;i < size_;i++)
            str_[i] = c;
    }

    ~String() {
        delete [] str_;
    }
    // не изменяйте эти имена, иначе ваша программа
    // не пройдет тестирование
    size_t size_;
    char *str_;
};

int main () {
    String s(0, 'd');
    cout << s.size_ << "|" << s.str_ << endl;
    return 0;
}

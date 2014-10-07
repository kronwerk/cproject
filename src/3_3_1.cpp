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

    // не изменяйте эти имена, иначе ваша программа
    // не пройдет тестирование
    size_t size_;
    char *str_;
};

int main () {
    String s("12345");
    cout << s.size_ << "|" << s.str_ << endl;
    return 0;
}

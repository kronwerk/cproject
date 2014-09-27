#include <iostream>
using namespace std;

unsigned strlen(const char *str) {
    // put your code here
    unsigned count = 0;
    while (*(str++) != '\0') {
        count++;
    };
    return count;
};

int main() {
    const char * str = "123450";
    cout << strlen(str) << endl;
    return 0;
}

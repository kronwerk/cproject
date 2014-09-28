#include <iostream>
using namespace std;

int strstr(const char *str, const char *pattern) {
    // put your code here
    const char * main_ptr = str;
    const char * local_pattern = 0;
    const char * inner_ptr = 0;
    int count = 0;
    if (!*pattern)
        return 0;
    while (*main_ptr) {
        inner_ptr = main_ptr++;
        local_pattern = pattern;
        while (*inner_ptr++ == *local_pattern++) {
            if (*local_pattern == '\0')
                return count;
        };
        count++;
    };
    return -1;
}

int main() {
    const char * str = "211";
    const char * pattern = "1";
    cout << strstr(str, pattern);
    return 0;
}

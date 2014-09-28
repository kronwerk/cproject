#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

void strcat1(char * to, const char * from) {
    // put your code here
    char * str = to;
    while (*str)
        str++;
    while (*str++ = *from++);
    return;
};

int main() {
    char *s1 = "fir";
    const char * from = "sec";
    int n = strlen(s1) + strlen(from) + 1;
    char *to = (char *)malloc(n);
    strcpy(to, s1);
    strcat1(to, from);
    cout << "|" << to << "|" << endl;
    return 0;
}

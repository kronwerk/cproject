#include <iostream>

using namespace std;

char *getline() {
    char c = '\0';
    int k = 0;
    int i = 0;
    char * res = new char[1];
    char * tmp = 0;
    char * old = 0;
    while (cin.get(c) and c != '\n') {
        tmp = new char[k+2];
        old = res;
        for(i=0;i<k;i++)
            tmp[i] = res[i];
        tmp[k++] = c;
        res = tmp;
        delete [] old;
    };
    res[k] = '\0';
    return res;
}

int main () {
    char * line = getline();
    cout << line << endl;
    delete [] line;
}

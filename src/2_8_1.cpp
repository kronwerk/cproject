#include <iostream>
using namespace std;

int main() {
    // put your code here
    char c = '\0';
    bool start = true;
    while(cin.get(c) && c != '\n') {
        if(c == ' ') {
            while(cin.get(c) && c == ' ');
            if(start) {
                start = !start;
                if (c == '\n')
                    break;
            }
            else if(c != '\n')
                cout << ' ';
            else
                break;
        }
		else
			start = false;
        cout << c;
    };
    return 0;
}

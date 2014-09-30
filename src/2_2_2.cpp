#include <iostream>

using namespace std;

void get_print() {
    int input;
    cin >> input;
    if (input == 0)
        return;
    get_print();
    cout << input << " ";
};

int main()
{
    // put your code here
    get_print();
    cout << endl;
    return 0;
}

#include <iostream>
using namespace std;

int main()
{
    // put your code here
    int A;
    int B;
    int count = 0;
    cin >> A >> B;
    for (int i=A;i<B;i++) {
        if (((i % 4 == 0)&&(i % 100 != 0))||(i % 400 == 0))
            count++;
    };
    cout << count << endl;
    return 0;
}

#include <iostream>
using namespace std;

int gcd(int a, int b) {
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	return gcd(b, a % b);
};

// put your code here
int main()
{
    int res = gcd(22, 121);
    cout << res << endl;
    return res;
}

#include <iostream>
using namespace std;

int gcd(int a, int b) {
	if a == 0:
		return a;
	if b == 0:
		return b;
	return gcd(b, a % b);
};

// put your code here
int main()
{
	int res = gcd(10, 8);
    cout << res << endl;
    return res;
}
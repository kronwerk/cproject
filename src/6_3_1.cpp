#include <iostream>
#include <cstddef>
using namespace std;

// ���������� ������ SameType � ����� ��������
// �����������. � ������� ������ ���� ����������
// ���� ����������� ��������� ���� bool � ������
// value

template < class T, class V >
struct SameType {
	static const bool value = false;
};

template < class T >
struct SameType<T, T> {
	static const bool value = true;
};

struct Dummy { };
typedef int type;

void main() {
	std::cout << SameType<int, int>::value << std::endl; // ������� 1, �. �. true
	std::cout << SameType<int, type>::value << std::endl; // 1, type == int
	std::cout << SameType<int, int&>::value << std::endl; // 0, int � ������ �� int - ��������� ����
	std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
	std::cout << SameType<int, const int>::value << std::endl; // 0, const - ����� ����
}
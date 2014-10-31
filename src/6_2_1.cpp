#include <cstddef>

// ��������� ������� copy_n ���� � ���������
// �������:
//   1. ������� ������
//   2. ������ ��������
//   3. ���������� ���������, ������� �����
//      �����������
//
// ��� ����� ����������� ������ ������� copy_n,
// ����� �� ����� ���� ������� ���, ��� ��������
// � �������.

template <typename TSrc, typename TTarget>
void copy_n(TTarget * target, TSrc * src, size_t num) {
	for(size_t i = 0;i < num;i++)
		target[i] = (TTarget) src[i];
}

int main() {
	int ints[] = {1, 2, 3, 4};
	double doubles[4] = {};
	copy_n(doubles, ints, 4);
}
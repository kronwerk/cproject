#include <cstddef> // size_t

template <typename T, size_t n>
size_t array_size(const T (&a)[n]) {
	return n;
}

void main() {
	int ints[] = {1, 2, 3, 4};
	int *iptr = ints;
	double doubles[] = {3.14};
	size_t a1 = array_size(ints); // вернет 4
	size_t a2 = array_size(doubles); // вернет 1
	int ints2[1] = {};
	//size_t a3 = array_size(ints2); // вернет 1
	size_t a3 = array_size(iptr);
}
#include <cstddef>

// Параметры функции copy_n идут в следующем
// порядке:
//   1. целевой массив
//   2. массив источник
//   3. количество элементов, которые нужно
//      скопировать
//
// Вам нужно реализовать только функцию copy_n,
// чтобы ее можно было вызвать так, как показано
// в примере.

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
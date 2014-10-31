#include <iostream>
#include <algorithm>
#include <cstddef>
using namespace std;

struct T {
	T(int a = 0) {
		value_ = a;
	}

	T(const T & t) {
		value_ = t.value_;
	}

private:
	int value_;
    T& operator=(const T& a);
};

template <typename T>
class Array
{
	T * data_;
	size_t size_;

public:

	void init() {
		data_ = (T*)(new char[sizeof(T) * size_]);
	}

	Array() : size_(0) {	
		init();
	}

    explicit Array(size_t size, const T& value = T()) : size_(size) {
		init();
        for(size_t i = 0;i < size_;i++)
			new (data_ + i) T(value);
	}

    Array(const Array & a) : size_(a.size()) {
		init();
        for(size_t i = 0;i < size_;i++)
			new (data_ + i) T(a[i]);
	}

    ~Array() {
		for(size_t i = 0;i < size_;i++)
			data_[i].~T();
		delete [] (char *) data_;
	}

	void swap(Array & a) {
		std::swap(size_, a.size_);
		std::swap(data_, a.data_);
	}

    Array& operator=(const Array& a) {
		if (this != &a)
			Array(a).swap(*this);
		return *this;
	}

    size_t size() const {
		return size_;
	}

	T& operator[](size_t i) {
		return data_[i];
	}

	const T& operator[](size_t i) const  {
		return data_[i];
	}
};

// Весь вывод должен осущствляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогаетльные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.
template <typename T>
void flatten(T value, std::ostream& out) { 
	out << value << " ";
}

template <typename T>
void flatten(const Array<T>& array, std::ostream& out) { 
	for(size_t i = 0; i < array.size(); i++)
		flatten(array[i], out);
}

int main() {
	Array<int> ints(2, 0);
	ints[0] = 10;
	ints[1] = 20;
	flatten(ints, std::cout); // выводит на экран строку "10 20"
	Array< Array<int> > array_of_ints(2, ints);
	flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
	Array<double> doubles(10, 0.0);
	flatten(doubles, std::cout); // работать должно не только для типа int
}
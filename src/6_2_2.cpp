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

template <typename T, class Comp>
T minimum(Array<T> arr, Comp func) {
	T res = arr[0];
	for(size_t i = 1; i < arr.size(); i++)
		res = func(res, arr[i]) ? res : arr[i];
	return res;
}

bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) { return b < a; } };

int main() {
	Array<int> ints(3);
	ints[0] = 10;
	ints[1] = 2;
	ints[2] = 15;
	int min = minimum(ints, less); // в min должно попасть число 2
	int max = minimum(ints, Greater());
}
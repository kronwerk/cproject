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

int main() {
	{
	size_t size = 10;
	T const len(5);
	Array<T> a(size, len);
	Array<T> b(a);
	Array<T> c;
	b = a;
	a = c;
	c = b;
	};
}
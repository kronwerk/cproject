#include <algorithm>
#include <cstddef>
using namespace std;

template <typename T>
class Array
{
	T * data_;
	size_t size_;

public:
    explicit Array(size_t size = 0, const T& value = T()) : data_(new T[size]), size_(size) {
        for(size_t i = 0;i < size_;i++)
			data_[i] = value;
	}

    Array(const Array & a) {
		size_ = a.size();
		data_ = new T[size_];
        for(size_t i = 0;i < size_;i++)
			data_[i] = a[i];
	}

    ~Array() {
		delete [] data_;
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
	size_t size = 10;
	int const len = 5;
	Array<int> a(size, len);
	Array<int> b(a);
	b = a;
}
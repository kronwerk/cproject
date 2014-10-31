#include <algorithm>
#include <cstddef>
using namespace std;

// ��� ������ ������������� ������ �� �����
struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// ���� data_ ���� T � ������ ValueHolder
// �������, � ���� ����� ����������
template <typename T>
struct ValueHolder : ICloneable {
	T data_;

	ValueHolder(T const& d = 0) : data_(d) {}

	ValueHolder* clone() const { return new ValueHolder(* this); }
};

// ��� �����, ������� ��� ����� �����������
class Any
{
public:
	ICloneable * data_;
    // � ������ Any ������ ���� �����������,
    // ������� ����� ������� ��� ����������,
    // ����� ������� ��������� ���:
    //    Any empty; // empty ������ �� ������

	Any() : data_(0) {}

    // � ������ Any ������ ���� ���������
    // ����������� �� ������ ���������, �����
    // ����� ���� ��������� ������� ���� Any,
    // ��������, ��������� �������:
    //    Any i(10); // i ������ �������� 10
	template <typename T>
	Any(T obj) : data_(new ValueHolder<T>(obj)) {}

    // �� �������� ��� ����������. ��� ����������
    // ������� ����� ����������.
	~Any() { 
		if (data_)
			delete data_;
	}

    // � ������ Any ����� ������ ���� �����������
    // ����������� (��� ������� ����� clone
    // ���������� ICloneable)
	Any(const Any & a) : data_(a.data_->clone()) {}

    // � ������ ������ ���� �������� ������������ �/���
    // ��������� �������� ������������, ����� �������
    // ��������� ���:
    //    Any copy(i); // copy ������ 10, ��� � i
    //    empty = copy; // empty ������ 10, ��� � copy
    //    empty = 0; // � ������ empty ������ 0
	void swap(Any & a) {
		std::swap(data_, a.data_);
	}

    Any& operator=(const Any& a) {
		if (this != &a)
			Any(a).swap(*this);
		return *this;
	}

    // �� � �������, �� ����� ����� �������� ��������
    // ��������, ��� ����� ���������� � ������ Any
    // ��������� ����� cast, ������� ����������
    // ��������� �� �������� ��������, ��� �������
    // ��������� � ������ �������������� ����� ���
    // ���� ������ Any ������ �� ������:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // ������ ��� i ������ int, � �� char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // ��� ���������� ����������� dynamic_cast,
    // ������� �� ��� ��������� �����.
	template <typename T>
	T * cast() {
		ValueHolder<T> *vh = dynamic_cast<ValueHolder<T> *>(data_);
		return (vh) ? &vh->data_ : 0;
	}
};

int main() {
	{
	Any empty;
	Any i(10);
	Any copy(i); // copy ������ 10, ��� � i
    empty = copy; // empty ������ 10, ��� � copy
    empty = 0; // � ������ empty ������ 0
	int *iptr = i.cast<int>(); // *iptr == 10
    char *cptr = i.cast<char>(); // cptr == 0,
            // ������ ��� i ������ int, � �� char
    Any empty2;
    int *p = empty2.cast<int>(); // p == 0
	};
}
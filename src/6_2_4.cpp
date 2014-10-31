#include <algorithm>
#include <cstddef>
using namespace std;

// Эти классы реализовывать заново не нужно
struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// Поле data_ типа T в классе ValueHolder
// открыто, к нему можно обращаться
template <typename T>
struct ValueHolder : ICloneable {
	T data_;

	ValueHolder(T const& d = 0) : data_(d) {}

	ValueHolder* clone() const { return new ValueHolder(* this); }
};

// Это класс, который вам нужно реализовать
class Any
{
public:
	ICloneable * data_;
    // В классе Any должен быть конструктор,
    // который можно вызвать без параметров,
    // чтобы работал следующий код:
    //    Any empty; // empty ничего не хранит

	Any() : data_(0) {}

    // В классе Any должен быть шаблонный
    // конструктор от одного параметра, чтобы
    // можно было создавать объекты типа Any,
    // например, следующим образом:
    //    Any i(10); // i хранит значение 10
	template <typename T>
	Any(T obj) : data_(new ValueHolder<T>(obj)) {}

    // Не забудьте про деструктор. Все выделенные
    // ресурсы нужно освободить.
	~Any() { 
		if (data_)
			delete data_;
	}

    // В классе Any также должен быть конструктор
    // копирования (вам поможет метод clone
    // интерфейса ICloneable)
	Any(const Any & a) : data_(a.data_->clone()) {}

    // В классе должен быть оператор присваивания и/или
    // шаблонный оператор присваивания, чтобы работал
    // следующий код:
    //    Any copy(i); // copy хранит 10, как и i
    //    empty = copy; // empty хранит 10, как и copy
    //    empty = 0; // а теперь empty хранит 0
	void swap(Any & a) {
		std::swap(data_, a.data_);
	}

    Any& operator=(const Any& a) {
		if (this != &a)
			Any(a).swap(*this);
		return *this;
	}

    // Ну и наконец, мы хотим уметь получать хранимое
    // значение, для этого определите в классе Any
    // шаблонный метод cast, который возвращает
    // указатель на хранимое значение, или нулевой
    // указатель в случае несоответствия типов или
    // если объект Any ничего не хранит:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // потому что i хранит int, а не char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // При реализации используйте dynamic_cast,
    // который мы уже обсуждали ранее.
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
	Any copy(i); // copy хранит 10, как и i
    empty = copy; // empty хранит 10, как и copy
    empty = 0; // а теперь empty хранит 0
	int *iptr = i.cast<int>(); // *iptr == 10
    char *cptr = i.cast<char>(); // cptr == 0,
            // потому что i хранит int, а не char
    Any empty2;
    int *p = empty2.cast<int>(); // p == 0
	};
}
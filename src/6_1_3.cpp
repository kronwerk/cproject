struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// Ўаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// ¬ шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Ўаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта созданную в куче из метода
// clone.

template <typename T>
struct ValueHolder : ICloneable {
	T data_;

	ValueHolder(T const& d = 0) : data_(d) {}

	ValueHolder* clone() const { return new ValueHolder(* this); }
};

int main() {
	ValueHolder<int> v(1);
	ValueHolder<int> * v2 = v.clone();
}
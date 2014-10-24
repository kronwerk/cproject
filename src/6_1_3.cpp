struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// ������ ValueHolder � ������� ���������� T,
// ������ ��������� ���� �������� ���� data_
// ���� T.
//
// � ������� ValueHolder ������ ���� ���������
// ����������� �� ������ ��������� ���� T,
// ������� �������������� ���� data_.
//
// ������ ValueHolder ������ �������������
// ��������� ICloneable, � ���������� ���������
// �� ����� ������� ��������� � ���� �� ������
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
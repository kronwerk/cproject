struct Rational
{
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;

    Rational& operator+=(Rational rational);
    Rational& operator-=(Rational rational);
    Rational& operator*=(Rational rational);
    Rational& operator/=(Rational rational);

    Rational operator-();
    Rational operator+();

private:
    int numerator_;
    unsigned denominator_;
};

Rational operator+(Rational lhs, Rational rhs);
Rational operator-(Rational lhs, Rational rhs);
Rational operator*(Rational lhs, Rational rhs);
Rational operator/(Rational lhs, Rational rhs);

bool operator <(Rational const & a, Rational const & b) {
	return (a.to_double() < b.to_double());
}

bool operator ==(Rational const & a, Rational const & b) {
	return !(a<b) && !(b<a);
}

bool operator !=(Rational const & a, Rational const & b) {
	return !(a == b);
}

bool operator >(Rational const & a, Rational const & b) {
	return b < a;
}

bool operator <=(Rational const & a, Rational const & b) {
	return !(b < a);
}

bool operator >=(Rational const & a, Rational const & b) {
	return !(a < b);
}
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
    
    	Rational & operator +=(Rational const & s) {
		this->add(s);
		return * this;
	}

	Rational & operator -=(Rational const & s) {
		this->sub(s);
		return * this;
	}

	Rational & operator *=(Rational const & s) {
		this->mul(s);
		return * this;
	}

	Rational & operator /=(Rational const & s) {
		this->div(s);
		return * this;
	}

	Rational operator -() {
		Rational tmp(*this);
		tmp.neg();
		return tmp; 
	}
	
	Rational operator +() const { 
		return * this; 
	}

private:
    int numerator_;
    unsigned denominator_;
};
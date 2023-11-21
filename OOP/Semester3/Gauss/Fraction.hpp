#include <cmath>
#include <iostream>

namespace LinearAlgebra
{
	struct Fraction
	{
	private:
		long _numerator;
		unsigned long _denominator;

	public:
		Fraction(long numerator = 0, unsigned long denominator = 1)
		{
			_numerator = denominator >= 0 ? numerator : -numerator;
			_denominator = abs(denominator);
		}

		Fraction(const Fraction &frac)
		{
			_numerator = frac._numerator;
			_denominator = frac._denominator;
		}

		long getNumerator() const { return _numerator; }
		unsigned long getDenominator() const { return _denominator; }
		void setNumerator(long n) { _numerator = n; }
		void setDenominator(unsigned long n) { _denominator = n; }
		double getValue() const { return (double)_numerator / (double)_denominator; }

		Fraction &Simplify()
		{
			return *this;
		}

		explicit operator double() const
		{
			return (double)_numerator / (double)_denominator;
		}

		Fraction operator*(int x);
		Fraction operator/(int x);
		Fraction operator+(int x);
		Fraction operator-(int x);

		Fraction operator*(const Fraction &frac);
		Fraction operator/(const Fraction &frac);
		Fraction operator+(const Fraction &frac);
		Fraction operator-(const Fraction &frac);

		bool operator==(const Fraction &frac);
		bool operator!=(const Fraction &frac);
		Fraction &operator=(const Fraction &frac);

		friend Fraction operator*(int x, Fraction frac);
		friend Fraction operator/(int x, Fraction frac);
		friend Fraction operator+(int x, Fraction frac);
		friend Fraction operator-(int x, Fraction frac);

		friend std::istream &operator<<(std::istream &stream, Fraction frac);
		friend std::ostream &operator>>(std::ostream &stream, Fraction frac);
	};

	Fraction Fraction::operator*(int x)
	{
		if (_denominator % x == 0)
			return Fraction(_numerator, _denominator / x);

		return Fraction(_numerator * x, _denominator);
	}

	Fraction Fraction::operator/(int x)
	{
		if (_numerator % x == 0)
			return Fraction(_numerator / x, _denominator);

		return Fraction(_numerator, _denominator * x);
	}
}
#include <iostream>
#include <fstream>

using namespace std;

struct Fraction
{
private:
	long _numerator;
	unsigned long _denominator;

public:
	Fraction(long n = 1)
	{
		_numerator = n;
		_denominator = 1;
	}

	friend ofstream &operator<<(ofstream &stream, const Fraction &frac);
	friend ostream &operator<<(ostream &stream, const Fraction &frac);
	friend ifstream &operator>>(ifstream &stream, Fraction &frac);
};

ostream &operator<<(ostream &stream, const Fraction &frac)
{
	stream << frac._numerator << '/' << frac._denominator;
	return stream;
}

ofstream &operator<<(ofstream &stream, const Fraction &frac)
{
	stream << frac._numerator << ' ' << frac._denominator;

	return stream;
}

ifstream &operator>>(ifstream &stream, Fraction &frac)
{
	stream >> frac._numerator >> frac._denominator;

	return stream;
}

int main(int argc, char *argv[])
{
	return 0;
}
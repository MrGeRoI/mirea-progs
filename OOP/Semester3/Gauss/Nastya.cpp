#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdexcept>

using namespace std;

class MatrixException : public exception
{
public:
	virtual const char *what() const noexcept { return "MatrixException"; };
};

template <class T>
class Matrix
{
private:
	int _width, _height;
	T *_value;

public:
	Matrix(int width, int height, T init_value = 0) : _width(width), _height(height), _value(new T[width * height])
	{
		if (width <= 0 || height <= 0)
			throw out_of_range("");

		for (int i = 0; i < width * height; i++)
			_value[i] = init_value;
	}

	Matrix(const vector<vector<T>> &vec) : _width(vec[0].size()), _height(vec.size()), _value(new T[_width * _height])
	{
		for (int i = 0; i < _height; i++)
			for (int j = 0; j < _width; j++)
				_value[i * _width + j] = vec[i][j];
	}

	Matrix(const Matrix<T> &matrix) : _width(matrix._width), _height(matrix._height), _value(new T[_width * _height])
	{
		for (int i = 0; i < _width * _height; i++)
			_value[i] = matrix._value[i];
	}

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	const T &getValue(int row, int col) const
	{
		if (col < 0 || col >= _width || row < 0 || row >= _height)
			throw out_of_range("");

		return _value[row * _width + col];
	}
	void setValue(int row, int col, const T &value)
	{
		if (col < 0 || col >= _width || row < 0 || row >= _height)
			throw out_of_range("");

		_value[row * _width + col] = value;
	}
	void swap(int row1, int col1, int row2, int col2)
	{
		if (col1 < 0 || col1 >= _width || row1 < 0 || row1 >= _height || col2 < 0 || col2 >= _width || row2 < 0 || row2 >= _height)
			throw out_of_range("");

		std::swap(_value[row1 * _width + col1], _value[row2 * _width + col2]);
	}

	Matrix<T> operator*(T x)
	{
		Matrix<T> result(_width, _height);

		for (int i = 0; i < _width * _height; ++i)
			result._value[i] = _value[i] * x;

		return result;
	};
	Matrix<T> operator/(T x)
	{
		Matrix<T> result(_width, _height);

		for (int i = 0; i < _width * _height; ++i)
			result._value[i] = _value[i] / x;

		return result;
	};
	Matrix<T> operator+(const Matrix<T> &matrix)
	{
		if (_width != matrix._width || _height != matrix._height)
			throw invalid_argument("Invalid matrix size");

		Matrix<T> result(_width, _height);

		for (int i = 0; i < _width * _height; ++i)
			result._value[i] = _value[i] + matrix._value[i];

		return result;
	};
	Matrix<T> operator-(const Matrix<T> &matrix)
	{
		if (_width != matrix._width || _height != matrix._height)
			throw invalid_argument("Invalid matrix size");

		Matrix<T> result(_width, _height);

		for (int i = 0; i < _width * _height; ++i)
			result._value[i] = _value[i] - matrix._value[i];

		return result;
	};
	bool operator==(const Matrix<T> &matrix)
	{
		if (_width != matrix._width || _height != matrix._height)
			return false;

		for (int i = 0; i < _width * _height; ++i)
			if (_value[i] != matrix._value[i])
				return false;

		return true;
	};
	bool operator!=(const Matrix<T> &matrix)
	{
		if (_width != matrix._width || _height != matrix._height)
			return true;

		for (int i = 0; i < _width * _height; ++i)
			if (_value[i] != matrix._value[i])
				return true;

		return false;
	};
	Matrix<T> &operator=(const Matrix<T> &matrix)
	{
		if (_width != matrix._width || _height != matrix._height)
		{
			_width = matrix._width;
			_height = matrix._height;

			delete[] _value;
			_value = new T[_width * _height];
		}

		for (int i = 0; i < _width * _height; i++)
			_value[i] = matrix._value[i];
	};

	template <class T1>
	friend Matrix<T1> operator*(T1 x, const Matrix<T1> &matrix);

	template <class T1>
	friend ofstream &operator<<(ofstream &stream, const Matrix<T1> &matrix);

	template <class T1>
	friend ostream &operator<<(ostream &stream, const Matrix<T1> &matrix);

	template <class T1>
	friend ifstream &operator>>(ifstream &stream, Matrix<T1> &matrix);
};

template <class T>
Matrix<T> operator*(T x, const Matrix<T> &matrix)
{
	Matrix<T> result(matrix._width, matrix._height);

	for (int i = 0; i < matrix._width * matrix._height; ++i)
		result._value[i] = matrix._value[i] * x;

	return result;
}

template <class T>
ostream &operator<<(ostream &stream, const Matrix<T> &matrix)
{
	for (int i = 0; i < matrix._height; ++i)
	{
		for (int j = 0; j < matrix._width; ++j)
			cout << matrix._value[i * matrix._width + j] << '\t';

		cout << '\n';
	}

	return stream;
}

template <class T>
ofstream &operator<<(ofstream &stream, const Matrix<T> &matrix)
{
	stream << matrix._width << ' ' << matrix._height;

	for (int i = 0; i < matrix._width * matrix._height; ++i)
		cout << ' ' << matrix._values[i];

	return stream;
}

template <class T>
ifstream &operator>>(ifstream &stream, Matrix<T> &matrix)
{
	stream >> matrix._width >> matrix._height;

	delete[] matrix._values;
	matrix._values = new T[matrix._width * matrix._height];

	for (int i = 0; i < matrix._width * matrix._height; ++i)
		cout >> matrix._values[i];

	return stream;
}

struct Fraction
{
private:
	long _numerator;
	unsigned long _denominator;

	// НОД (greatest_common_divisor)
	static unsigned long gcd(unsigned long a, unsigned long b)
	{
		if (a % b == 0)
			return b;

		if (b % a == 0)
			return a;

		if (a > b)
			return gcd(a % b, b);

		return gcd(a, b % a);
	}

	// НОК (least_common_multiple)
	static unsigned long lcm(unsigned long a, unsigned long b)
	{
		return (a * b) / gcd(a, b);
	}

public:
	Fraction(int numerator = 0, int denominator = 1)
	{
		if (denominator == 0)
			throw invalid_argument("");

		_numerator = static_cast<unsigned long>(denominator > 0 ? numerator : -numerator);
		_denominator = static_cast<unsigned long>(abs(denominator));
	}

	Fraction(const Fraction &frac)
	{
		_numerator = frac._numerator;
		_denominator = frac._denominator;
	}

	long getNumerator() const { return _numerator; }
	unsigned long getDenominator() const { return _denominator; }
	void setNumerator(int n) { _numerator = n; }
	void setDenominator(int n)
	{
		if (n == 0)
			throw invalid_argument("");

		_denominator = static_cast<unsigned long>(n);
	}
	double getValue() const { return (double)_numerator / (double)_denominator; }

	Fraction &simplify()
	{
		unsigned long gcd_ = gcd(_numerator, _denominator);

		_numerator /= gcd_;
		_denominator /= gcd_;

		return *this;
	}

	Fraction operator*(int x) const
	{
		if (_denominator % x == 0)
			return Fraction(_numerator, _denominator / x);

		return Fraction(_numerator * x, _denominator);
	};

	Fraction operator/(int x) const
	{
		if (x == 0)
			throw invalid_argument("Division by zero");

		if (_numerator % x == 0)
			return Fraction(_numerator / x, _denominator);

		return Fraction(_numerator, _denominator * x);
	};

	Fraction operator+(int x) const
	{
		return Fraction(_numerator + x * _denominator, _denominator);
	};

	Fraction operator-(int x) const
	{
		return Fraction(_numerator - x * _denominator, _denominator);
	};

	Fraction operator*(const Fraction &frac) const
	{
		unsigned long gcd1 = gcd(_numerator, frac._denominator),
					  gcd2 = gcd(frac._numerator, _denominator);

		return Fraction(
			(_numerator / gcd1) * (frac._numerator / gcd2),
			(_denominator / gcd2) * (frac._denominator / gcd1));
	};

	Fraction operator/(const Fraction &frac) const
	{
		if (frac._numerator == 0)
			throw invalid_argument("Division by zero");

		unsigned long gcd1 = gcd(_numerator, frac._numerator),
					  gcd2 = gcd(frac._denominator, _denominator);

		return Fraction(
			(_numerator / gcd1) * (frac._denominator / gcd2),
			(_denominator / gcd2) * (frac._numerator / gcd1));
	};

	Fraction operator+(const Fraction &frac) const
	{
		unsigned long gcd_ = gcd(_denominator, frac._denominator);

		return Fraction(
			(_numerator * frac._denominator) / gcd_ + (frac._numerator * _denominator) / gcd_,
			(_denominator * frac._denominator) / gcd_);
	};

	Fraction operator-(const Fraction &frac) const
	{
		unsigned long gcd_ = gcd(_denominator, frac._denominator);

		return Fraction(
			(_numerator * frac._denominator) / gcd_ - (frac._numerator * _denominator) / gcd_,
			(_denominator * frac._denominator) / gcd_);
	};

	void operator+=(const Fraction &frac)
	{
		unsigned long gcd_ = gcd(_denominator, frac._denominator);

		_numerator =
			(_numerator * frac._denominator) / gcd_ + (frac._numerator * _denominator) / gcd_;

		_denominator = (_denominator * frac._denominator) / gcd_;
	}

	void operator-=(const Fraction &frac)
	{
		unsigned long gcd_ = gcd(_denominator, frac._denominator);

		_numerator =
			(_numerator * frac._denominator) / gcd_ - (frac._numerator * _denominator) / gcd_;

		_denominator = (_denominator * frac._denominator) / gcd_;
	}

	bool operator==(int x) const
	{
		if (_numerator % _denominator == 0)
			return (_numerator / _denominator) == x;

		return false;
	}

	bool operator!=(int x) const
	{
		if (_numerator % _denominator == 0)
			return (_numerator / _denominator) != x;

		return true;
	}

	bool operator>(const Fraction &frac) const
	{
		return _numerator * frac._denominator > frac._numerator * _denominator;
	}

	bool operator<(const Fraction &frac) const
	{
		return _numerator * frac._denominator < frac._numerator * _denominator;
	}

	bool operator==(const Fraction &frac) const
	{
		return _numerator == frac._numerator && _denominator == frac._denominator;
	}

	bool operator!=(const Fraction &frac) const
	{
		return _numerator != frac._numerator || _denominator != frac._denominator;
	}

	Fraction &operator=(const Fraction &frac)
	{
		_numerator = frac._numerator;
		_denominator = frac._denominator;

		return *this;
	}

	Fraction &operator=(int x)
	{
		_numerator = static_cast<long>(x);
		_denominator = 1l;

		return *this;
	}

	friend Fraction operator*(int x, const Fraction &frac);
	friend Fraction operator/(int x, const Fraction &frac);
	friend Fraction operator+(int x, const Fraction &frac);
	friend Fraction operator-(int x, const Fraction &frac);

	friend Fraction operator==(int x, const Fraction &frac);
	friend Fraction operator!=(int x, const Fraction &frac);

	// friend ofstream &operator<<(ofstream &stream, const Fraction &frac);
	friend ostream &operator<<(ostream &stream, const Fraction &frac);
	friend ifstream &operator>>(ifstream &stream, Fraction &frac);

	friend Fraction abs(const Fraction &frac);
};

ostream &operator<<(ostream &stream, const Fraction &frac)
{
	stream << frac._numerator << '/' << frac._denominator;

	return stream;
}
/*
ofstream &operator<<(ofstream &stream, const Fraction &frac)
{
	stream << frac._numerator << ' ' << frac._denominator;

	return stream;
}
*/
ifstream &operator>>(ifstream &stream, Fraction &frac)
{
	char c;

	stream >> frac._numerator >> c >> frac._denominator;

	return stream;
}

Fraction operator/(int x, const Fraction &frac)
{
	if (frac._numerator == 0)
		throw invalid_argument("Division by zero");

	if (frac._numerator % x == 0)
		return Fraction(frac._numerator / x, frac._denominator);

	return Fraction(frac._numerator, frac._denominator * x);
}

Fraction abs(const Fraction &frac)
{
	return Fraction(labs(frac._numerator), frac._denominator);
}

// Infinity Solutions - бесконечное число решений
const int infsol = -1;

int gaussanSolve(Matrix<Fraction> matrix, vector<Fraction> fre, vector<Fraction> &answer)
{
	int n = matrix.getHeight();
	int m = matrix.getWidth();

	vector<int> where(m, -1);

	for (int col = 0, row = 0; col < m && row < n; ++col)
	{
		int sel = row;

		for (int i = row; i < n; ++i)
			if (abs(matrix.getValue(i, col)) > abs(matrix.getValue(sel, col)))
				sel = i;

		if (matrix.getValue(sel, col).getNumerator() == 0)
			continue;

		for (int i = col; i < m; ++i)
			matrix.swap(sel, i, row, i);

		swap(fre[sel], fre[row]);

		where[col] = row;

		for (int i = 0; i < n; ++i)
			if (i != row)
			{
				Fraction c = matrix.getValue(i, col) / matrix.getValue(row, col);

				for (int j = col; j < m; ++j)
					matrix.setValue(i, j, matrix.getValue(i, j) - matrix.getValue(row, j) * c);

				fre[i] = fre[i] - fre[row] * c;
			}

		++row;
	}

	answer.assign(m, 0);

	for (int i = 0; i < m; ++i)
		if (where[i] != -1)
			answer[i] = fre[where[i]] / matrix.getValue(where[i], i);

	for (int i = 0; i < n; ++i)
	{
		Fraction sum = 0;

		for (int j = 0; j < m; ++j)
			sum += answer[j] * matrix.getValue(i, j);

		if (abs(sum - fre[i]).getNumerator() > 0)
			return 0;
	}

	for (int i = 0; i < m; ++i)
		if (where[i] == -1)
			return infsol;

	return 1;
}

int main()
{
	Matrix<Fraction> matrix({{1, Fraction(1, 2)},
							 {0, 1}});

	Fraction f1(1, 6), f2(1, 4);

	vector<Fraction> answer(2);

	cout << matrix << gaussanSolve(matrix, {1, 5}, answer) << ": " << answer[0] << ", " << answer[1] << endl;

	return 0;
}

#include <stdexcept>

namespace
{
	template <class T>
	class Matrix
	{
	private:
		int _width, _height;

		T **_value;

	public:
		Matrix(int width, int height, T init_value = 0) : _width(width), _height(height)
		{
			if (width <= 0 || height <= 0)
				throw std::out_of_range("");

			_value = new T *[height];

			for (int i = 0; i < height; i++)
			{
				_value[i] = new T[width];

				for (int j = 0; j < width; j++)
					_value[i][j] = init_value;
			}
		}

		Matrix(const Matrix<T> &matrix) : _width(matrix._width), _height(matrix._height)
		{
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					_value[i][j] = matrix._value[i][j];
		}

		int getWidth() const { return _width; }
		int getHeight() const { return _height; }
		T getValue(int x, int y) const { return _value[x][y]; }
		void setValue(int x, int y, const T &value) { _value[x][y] = value; }

		Matrix<T> operator*(T x);
		Matrix<T> operator/(T x);
		Matrix<T> operator*(const Matrix<T> &matrix);
		Matrix<T> operator+(const Matrix<T> &matrix);
		Matrix<T> operator-(const Matrix<T> &matrix);
		bool operator==(const Matrix<T> &matrix);
		bool operator!=(const Matrix<T> &matrix);
		Matrix<T> &operator=(const Matrix<T> &matrix);

		template <class T1>
		friend Matrix<T1> operator*(T1 x, const Matrix<T1> &matrix);
	};

	template <class T>
	Matrix<T> Matrix<T>::operator*(T x)
	{
	}

	template <class T>
	Matrix<T> Matrix<T>::operator/(T x)
	{
	}

	template <class T>
	Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix)
	{
	}

	template <class T>
	Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix)
	{
	}

	template <class T>
	Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix)
	{
	}

	template <class T>
	Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
	{
	}

	template <class T>
	bool Matrix<T>::operator==(const Matrix<T> &matrix)
	{
	}

	template <class T>
	bool Matrix<T>::operator!=(const Matrix<T> &matrix)
	{
	}

	template <class T>
	Matrix<T> operator*(T x, const Matrix<T> &matrix)
	{
	}
}
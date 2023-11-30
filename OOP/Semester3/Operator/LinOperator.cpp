#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <random>

#include <chrono>

using namespace std;

template <int _Dimentions = 3>
class LinMatrix;

template <int _Dimentions = 3>
class LinVector
{
public:
	friend class LinMatrix<_Dimentions>;

private:
	double _value[_Dimentions];

public:
	LinVector()
	{
		for (int i = 0; i < _Dimentions; ++i)
			_value[i] = 0.0;
	}

	LinVector(vector<double> vec)
	{
		if (vec.size() < _Dimentions)
			throw invalid_argument("");

		for (int i = 0; i < _Dimentions; ++i)
			_value[i] = vec[i];
	}

	LinVector(const LinVector<_Dimentions> &vec)
	{
		for (int i = 0; i < _Dimentions; i++)
			_value[i] = vec._value[i];
	}

	int getDimensions() const { return _Dimentions; }

	double getValue(int n) const
	{
		if (n < 0 || n >= _Dimentions)
			throw out_of_range("");

		return _value[n];
	}

	void setValue(int n, double value)
	{
		if (n < 0 || n >= _Dimentions)
			throw out_of_range("");

		_value[n] = value;
	}

	LinVector<_Dimentions> getNormalized() const
	{
		double sum = 0.0;

		for (int i = 0; i < _Dimentions; i++)
			sum += _value[i];

		sum = sqrt(sum);

		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; i++)
			result._value[i] = _value[i] / sum;

		return result;
	}

	double getLength() const
	{
		double sum = 0.0;

		for (int i = 0; i < _Dimentions; i++)
			sum += _value[i];

		return sqrt(sum);
	}

	// Скалярное произведение
	double operator*(const LinVector<_Dimentions> &vec) const
	{
		double result = 0.0;

		for (int i = 0; i < _Dimentions; ++i)
			result += _value[i] * vec._value[i];

		return result;
	};
	LinVector<_Dimentions> operator*(double x) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			result._value[i] = _value[i] * x;

		return result;
	};
	LinVector<_Dimentions> operator/(double x) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			result._value[i] = _value[i] / x;

		return result;
	};
	LinVector<_Dimentions> operator+(const LinVector<_Dimentions> &vec) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			result._value[i] = _value[i] + vec._value[i];

		return result;
	};
	LinVector<_Dimentions> operator-(const LinVector<_Dimentions> &vec) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			result._value[i] = _value[i] - vec._value[i];

		return result;
	};
	bool operator==(const LinVector<_Dimentions> &vec) const
	{
		for (int i = 0; i < _Dimentions; ++i)
			if (_value[i] != vec._value[i])
				return false;

		return true;
	};
	bool operator!=(const LinVector<_Dimentions> &vec) const
	{
		for (int i = 0; i < _Dimentions; ++i)
			if (_value[i] != vec._value[i])
				return true;

		return false;
	};
	LinVector<_Dimentions> &operator=(const LinVector<_Dimentions> &vec)
	{
		for (int i = 0; i < _Dimentions; i++)
			_value[i] = vec._value[i];

		return *this;
	};

	template <int _Dimentions1>
	friend LinVector<_Dimentions1> operator*(double x, const LinVector<_Dimentions1> &vec);

	template <int _Dimentions1>
	friend ostream &operator<<(ostream &stream, const LinVector<_Dimentions1> &vec);
};

template <int _Dimentions1>
LinVector<_Dimentions1> operator*(double x, const LinVector<_Dimentions1> &vec)
{
	LinVector<_Dimentions1> result;

	for (int i = 0; i < _Dimentions1; ++i)
		result._value[i] = vec._value[i] * x;

	return result;
}

template <int _Dimentions1>
ostream &operator<<(ostream &stream, const LinVector<_Dimentions1> &vec)
{
	for (int i = 0; i < _Dimentions1; ++i)
		stream << vec._value[i] << '\t';

	return stream;
}

template <int _Dimentions>
class LinMatrix
{
private:
	// Матрица линейного оператора всегда квадратная
	double _value[_Dimentions * _Dimentions];

public:
	LinMatrix(double d = 1.0)
	{
		if (_Dimentions <= 0)
			throw out_of_range("");

		for (int i = 0; i < _Dimentions * _Dimentions; i++)
			_value[i] = ((i % _Dimentions) == (i / _Dimentions)) ? d : 0.0;
	}

	LinMatrix(const vector<vector<double>> &vec)
	{
		for (int i = 0; i < _Dimentions; i++)
			for (int j = 0; j < _Dimentions; j++)
				_value[i * _Dimentions + j] = vec[i][j];
	}

	LinMatrix(const LinMatrix<_Dimentions> &matrix)
	{
		for (int i = 0; i < _Dimentions * _Dimentions; i++)
			_value[i] = matrix._value[i];
	}

	int getDimensions() const { return _Dimentions; }
	double getValue(int row, int col) const
	{
		if (col < 0 || col >= _Dimentions || row < 0 || row >= _Dimentions)
			throw out_of_range("");

		return _value[row * _Dimentions + col];
	}
	void setValue(int row, int col, double value)
	{
		if (col < 0 || col >= _Dimentions || row < 0 || row >= _Dimentions)
			throw out_of_range("");

		_value[row * _Dimentions + col] = value;
	}

	// Получение траспонированной матрицы
	LinMatrix<_Dimentions> getTransposed() const
	{
		LinMatrix<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			for (int j = 0; j < _Dimentions; ++j)
				result._value[i * _Dimentions + j] = _value[j * _Dimentions + i];

		return result;
	}

	LinMatrix<_Dimentions> getInversed() const
	{
		// Создаем расширенную матрицу [A | I], где A - исходная матрица, I - единичная матрица
		LinMatrix<_Dimentions> matrix(*this);

		LinMatrix<_Dimentions> augmented;

		// Приводим левую часть матрицы к единичной форме
		for (int i = 0; i < _Dimentions; ++i)
		{
			// Поиск главного элемента в столбце
			int maxRow = i;

			for (int k = i + 1; k < _Dimentions; ++k)
				if (abs(matrix._value[k * _Dimentions + i]) > abs(matrix._value[k * maxRow + i]))
					maxRow = k;

			// Обмен строк
			for (int j = 0; j < _Dimentions; j++)
			{
				swap(matrix._value[i * _Dimentions + j], matrix._value[maxRow * _Dimentions + j]);
				swap(augmented._value[i * _Dimentions + j], augmented._value[maxRow * _Dimentions + j]);
			}

			// Приведение к единичному виду
			double pivot = matrix._value[i * _Dimentions + i];
			for (int j = 0; j < _Dimentions; ++j)
			{
				matrix._value[i * _Dimentions + j] /= pivot;
				augmented._value[i * _Dimentions + j] /= pivot;
			}

			// Вычитание из других строк
			for (int k = 0; k < _Dimentions; ++k)
			{
				if (k != i)
				{
					double factor = matrix._value[k * _Dimentions + i];

					for (int j = 0; j < _Dimentions; ++j)
					{
						matrix._value[k * _Dimentions + j] -= factor * matrix._value[i * _Dimentions + j];
						augmented._value[k * _Dimentions + j] -= factor * augmented._value[i * _Dimentions + j];
					}
				}
			}
		}

		return augmented;
	}

	LinVector<_Dimentions> getColumn(int column) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			result._value[i] = _value[i * _Dimentions + column];

		return result;
	}

	LinVector<_Dimentions> getRow(int row) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			result._value[i] = _value[row * _Dimentions + i];

		return result;
	}
	LinVector<_Dimentions> operator*(const LinVector<_Dimentions> &vec) const
	{
		LinVector<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
		{
			result._value[i] = 0.0;

			for (int j = 0; j < _Dimentions; ++j)
				result._value[i] += vec._value[j] * _value[i * _Dimentions + j];
		}

		return result;
	};

	LinMatrix<_Dimentions> operator*(LinMatrix<_Dimentions> m) const
	{
		LinMatrix<_Dimentions> result;

		for (int i = 0; i < _Dimentions; ++i)
			for (int j = 0; j < _Dimentions; ++j)
				for (int k = 0; k < _Dimentions; ++k)
					result._value[i * _Dimentions + j] = _value[i * _Dimentions + k] * m._value[k * _Dimentions + j];

		return result;
	}

	LinMatrix<_Dimentions> operator*(double x) const
	{
		LinMatrix<_Dimentions> result;

		for (int i = 0; i < _Dimentions * _Dimentions; ++i)
			result._value[i] = _value[i] * x;

		return result;
	};
	LinMatrix<_Dimentions> operator/(double x) const
	{
		LinMatrix<_Dimentions> result;

		for (int i = 0; i < _Dimentions * _Dimentions; ++i)
			result._value[i] = _value[i] / x;

		return result;
	};
	LinMatrix<_Dimentions> operator+(const LinMatrix<_Dimentions> &matrix) const
	{
		LinMatrix<_Dimentions> result;

		for (int i = 0; i < _Dimentions * _Dimentions; ++i)
			result._value[i] = _value[i] + matrix._value[i];

		return result;
	};
	LinMatrix<_Dimentions> operator-(const LinMatrix<_Dimentions> &matrix) const
	{
		LinMatrix<_Dimentions> result;

		for (int i = 0; i < _Dimentions * _Dimentions; ++i)
			result._value[i] = _value[i] - matrix._value[i];

		return result;
	};
	bool operator==(const LinMatrix<_Dimentions> &matrix) const
	{
		for (int i = 0; i < _Dimentions * _Dimentions; ++i)
			if (_value[i] != matrix._value[i])
				return false;

		return true;
	};
	bool operator!=(const LinMatrix<_Dimentions> &matrix) const
	{
		for (int i = 0; i < _Dimentions * _Dimentions; ++i)
			if (_value[i] != matrix._value[i])
				return true;

		return false;
	};
	LinMatrix<_Dimentions> &operator=(const LinMatrix<_Dimentions> &matrix)
	{
		for (int i = 0; i < _Dimentions * _Dimentions; i++)
			_value[i] = matrix._value[i];

		return *this;
	};

	template <int _Dimentions1>
	friend LinMatrix<_Dimentions1> operator*(double x, const LinMatrix<_Dimentions1> &matrix);

	template <int _Dimentions1>
	friend ofstream &operator<<(ofstream &stream, const LinMatrix<_Dimentions1> &matrix);

	template <int _Dimentions1>
	friend ostream &operator<<(ostream &stream, const LinMatrix<_Dimentions1> &matrix);

	template <int _Dimentions1>
	friend ifstream &operator>>(ifstream &stream, LinMatrix<_Dimentions1> &matrix);
};

template <int _Dimentions1>
LinMatrix<_Dimentions1> operator*(double x, const LinMatrix<_Dimentions1> &matrix)
{
	LinMatrix<_Dimentions1> result;

	for (int i = 0; i < _Dimentions1 * _Dimentions1; ++i)
		result._value[i] = matrix._value[i] * x;

	return result;
}

template <int _Dimentions1>
ofstream &operator<<(ofstream &stream, const LinMatrix<_Dimentions1> &matrix)
{
	for (int i = 0; i < _Dimentions1 * _Dimentions1; ++i)
		stream << ' ' << matrix._value[i];

	return stream;
}

template <int _Dimentions1>
ostream &operator<<(ostream &stream, const LinMatrix<_Dimentions1> &matrix)
{
	for (int i = 0; i < _Dimentions1; ++i)
	{
		for (int j = 0; j < _Dimentions1; ++j)
			stream << matrix._value[i * _Dimentions1 + j] << '\t';

		stream << '\n';
	}

	return stream;
}

template <int _Dimentions1>
ifstream &operator>>(ifstream &stream, LinMatrix<_Dimentions1> &matrix)
{
	for (int i = 0; i < _Dimentions1 * _Dimentions1; ++i)
		stream >> matrix._value[i];

	return stream;
}
// Метод степенных итераций
template <int N>
void powerIteration(const LinMatrix<N> &matrix, double &eigenvalue, LinVector<N> &eigenvector, int maxIterations = 1000, double tolerance = 1e-6)
{
	// Начальное приближение для собственного вектора
	for (int i = 0; i < N; i++)
		eigenvector.setValue(i, 1.0);

	for (int iteration = 0; iteration < maxIterations; ++iteration)
	{
		// Умножаем матрицу на текущий собственный вектор
		LinVector<N> result = matrix * eigenvector;

		// Находим новое собственное число
		double newEigenvalue = (result * eigenvector) / (eigenvector * eigenvector);

		// Нормализуем вектор
		result = result.getNormalized();

		// Проверяем на соответствие условия сходимости
		if (fabs(newEigenvalue - eigenvalue) < tolerance)
		{
			break;
		}

		eigenvalue = newEigenvalue;
		eigenvector = result;
	}
}

// Обратный степенной метод
template <int N>
void inversePowerIteration(const LinMatrix<N> &matrix, double &eigenvalue, LinVector<N> &eigenvector, int maxIterations = 1000, double tolerance = 1e-6)
{
	// Начальное приближение для собственного вектора
	for (int i = 0; i < N; i++)
		eigenvector.setValue(i, 1.0);

	for (int iteration = 0; iteration < maxIterations; ++iteration)
	{
		// Умножаем матрицу на текущий собственный вектор
		LinVector<N> result = (matrix - LinMatrix<N>(eigenvalue)).getInversed() * eigenvector;

		// Находим новое собственное число
		double newEigenvalue = (result * eigenvector) / (eigenvector * eigenvector);

		// Нормализуем вектор
		result = result.getNormalized();

		// Проверяем на соответствие условия сходимости
		if (fabs(newEigenvalue - eigenvalue) < tolerance)
		{
			break;
		}

		eigenvalue = newEigenvalue;
		eigenvector = result;
	}
}

// Функция для выполнения разложения Грама-Шмидта
template <int N>
void gramSchmidt(const LinMatrix<N> &inputMatrix, LinMatrix<N> &Q, LinMatrix<N> &R)
{
	for (int j = 0; j < N; ++j)
	{
		// Получаем j-й столбец из исходной матрицы
		LinVector<N> vj = inputMatrix.getColumn(j);

		// Проходим по предыдущим векторам и вычитаем их проекции
		for (int i = 0; i < j; ++i)
		{
			double proj = (Q.getRow(i) * vj) / Q.getRow(i).getLength();

			for (int k = 0; k < N; ++k)
				vj.setValue(k, vj.getValue(k) - proj * Q.getValue(i, k));

			R.setValue(i, j, proj);
		}

		// Нормализуем получившийся вектор и добавляем его в Q
		double length = vj.getLength();
		for (int i = 0; i < N; ++i)
		{
			Q.setValue(j, i, vj.getValue(i) / length);
		}
		R.setValue(j, j, length);
	}
}
// QR-алгоритм для поиска всех собственных чисел матрицы
template <int N>
void qrAlgorithm(LinMatrix<N> matrix, double eigenvalues[N], int maxIterations = 1000, double tolerance = 1e-6)
{
	for (int iteration = 0; iteration < maxIterations; ++iteration)
	{
		// Разложение QR
		LinMatrix<N> Q, R;

		gramSchmidt(matrix, Q, R);

		// Обновляем матрицу
		matrix = R * Q;

		// Проверяем на соответствие условия сходимости
		// На главной диагонали матрицы остаются собственные числа
		bool converged = true;
		for (int i = 0; i < N - 1; ++i)
		{
			if (fabs(matrix.getValue(i + 1, i)) > tolerance)
			{
				converged = false;
				break;
			}
		}

		if (converged)
		{
			break;
		}
	}

	// Извлекаем собственные числа
	for (int i = 0; i < N; ++i)
	{
		eigenvalues[i] = matrix.getValue(i, i);
	}
}

const int TEST_DIM = 50; // 10 20 30 40 50

int main(int argc, char *argv[])
{
	// Пример матрицы (линейный оператор)
	LinMatrix<2> matrix2x2({{2.0, 1.0},
							{1.0, 3.0}});

	cout << matrix2x2.getInversed() << endl;

	ofstream file("test.txt");
	file << matrix2x2;
	file.close();

	LinMatrix<2> matrix2x2_1;

	ifstream file2("test.txt");
	file2 >> matrix2x2_1;
	file2.close();

	cout << matrix2x2_1;

	double eigenvalue2 = 3.0;
	LinVector<2> eigenvector2({1.0, 2.0});

	// Вызов метода степенных итераций
	powerIteration(matrix2x2_1, eigenvalue2, eigenvector2);

	// Вывод результата
	cout << "Eigenvalue: " << eigenvalue2 << endl
		 << "Eigenvector: " << eigenvector2 << endl;

	cout << "Power Iteration 20 matrixies " << TEST_DIM << "x" << TEST_DIM << "\n\n";

	int tmin = 100000, tmax = 0, tsum = 0;

	// Замеры
	for (int i = 0; i < 20; i++)
	{
		LinMatrix<TEST_DIM> matrix;

		uniform_real_distribution<double> unif(-100.0, 100.0);
		default_random_engine re;

		for (int j = 0; j < TEST_DIM; j++)
			for (int k = 0; k < TEST_DIM; k++)
				matrix.setValue(j, k, unif(re));

		double eigenvalue = 1.0;
		LinVector<TEST_DIM> eigenvector;

		auto begin = chrono::steady_clock::now();

		powerIteration(matrix, eigenvalue, eigenvector, 100'000, __DBL_EPSILON__);

		auto end = chrono::steady_clock::now();
		int len = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

		tsum += len;
		tmin = std::min(tmin,len);
		tmax = std::max(tmax,len);

		cout << "Elapsed: " << len << " ms\n";
	}
	
	cout << "\nMin: " << tmin << " ms\nMax:" << tmax << " ms\nAverage: " << tsum / 20 << " ms\n";

	return 0;
}
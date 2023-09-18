#include <iostream>
#include <fstream>
#include <exception>

// библиотеки из C - это зло
#include <cstring>

class MatrixException : public std::exception {
protected:
    char* _str;
public:
    MatrixException(const char* s)
	{
		_str = new char[strlen(s) + 1];
		//strcpy_s(_str, strlen(s) + 1, s);
		strcpy(_str,s);
	}

	MatrixException(const MatrixException& e)
	{
		_str = new char[strlen(e._str) + 1];
		//strcpy_s(_str, strlen(e._str) + 1, e._str);
		strcpy(_str,e._str);
	}

	~MatrixException()
	{
		delete[] _str;
	}

    virtual void Print()
	{
		std::cout << "MatrixException: " << _str << "; " << what() << std::endl;
	}
};

class InvalidOperationException : public MatrixException { };

class IndexOutOfBoundsException : public MatrixException
{
protected:
	int _rows, _columns;
public:
	IndexOutOfBoundsException(const char* s, int row, int col) : MatrixException(s) { _rows = row; _columns = col; }
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : MatrixException(e) { _rows = e._rows; _columns = e._columns; }

	virtual void Print() override
	{
		std::cout << "IndexOutOfBoundsException: " << _str << "; Rows: " << _rows << ", Columns: " << _columns << "; " << what();
	}
};

class InvalidSizeException : public MatrixException
{
protected:
	int _rows, _columns;
public:
	InvalidSizeException(const char* s, int row, int col) : MatrixException(s) { _rows = row; _columns = col; }
	InvalidSizeException(const InvalidSizeException& e) : MatrixException(e) { _rows = e._rows; _columns = e._columns; }

	virtual void Print() override
	{
		std::cout << "InvalidSizeException: " << _str << "; Rows: " << _rows << ", Columns: " << _columns << "; " << what();
	}
};

class WrongSizeException : public MatrixException
{
protected:
	int _rows, _columns;
public:
	WrongSizeException(const char* s, int row, int col) : MatrixException(s) { _rows = row; _columns = col; }
	WrongSizeException(const WrongSizeException& e) : MatrixException(e) { _rows = e._rows; _columns = e._columns; }

	virtual void Print() override
	{
		std::cout << "WrongSizeException: " << _str << "; Rows: " << _rows << ", Columns: " << _columns << "; " << what();
	}
};

class NonPositiveSizeException : public WrongSizeException
{
public:
    NonPositiveSizeException(const char* s, int row, int col) : WrongSizeException(s,row,col) { }
	NonPositiveSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) { }

	virtual void Print() override
	{
		std::cout << "NonPositiveSizeException: " << _str << "; Rows: " << _rows << ", Columns: " << _columns << "; " << what();
	}
};

class TooLargeSizeException : public WrongSizeException
{
public:
    TooLargeSizeException(const char* s, int row, int col) : WrongSizeException(s,row,col) { }
	TooLargeSizeException(const TooLargeSizeException& e) : WrongSizeException(e) { }

	virtual void Print() override
	{
		std::cout << "TooLargeSizeException: " << _str << "; Rows: " << _rows << ", Columns: " << _columns << "; " << what();
	}
};

// Встройте собственный тип исключения, которое может возникнуть при решении задачи из Вашего варианта, в общую структуру наследования. 
class TooSmallSizeException : public WrongSizeException
{
public:
    TooSmallSizeException(const char* s, int row, int col) : WrongSizeException(s,row,col) { }
	TooSmallSizeException(const TooSmallSizeException& e) : WrongSizeException(e) { }

	virtual void Print() override
	{
		std::cout << "TooSmallSizeException: " << _str << "; Rows: " << _rows << ", Columns: " << _columns << "; " << what();
	}
};

template<class T>
class BaseMatrix
{
protected:
    T** _ptr;
    int _height,_width;

public:
    BaseMatrix<T>(int h, int w)
    {
		if (h <= 0 || w <= 0)
			throw NonPositiveSizeException("Matrix size can't be negative or zero in constructor int, int", h, w);

        if(h > 50 || w > 50)
            throw TooLargeSizeException("Matrix size can't be more than 50 in constructor int, int", h, w);

        _ptr = new T*[h];

        for(int i = 0;i < h;i++)
			_ptr[i] = new T[w];

		_height = h;
		_width = w;
    }


	// Введите конструктор, принимающий массив типа double**
    BaseMatrix<T>(T** arr,int h, int w)
    {
        _ptr = new T*[h];

        for(int i = 0;i < h;i++)
        {
            _ptr[i] = new T[w];

            for(int j = 0;j < w;j++)
                _ptr[i][j] = arr[i][j];
        }

        _height = h;
        _width = w;
    }

    BaseMatrix<T>(const BaseMatrix& matrix)
    {
        _ptr = new T*[matrix._height];

        for(int i = 0;i < matrix._height;i++)
        {
            _ptr[i] = new T[matrix._width];

            for(int j = 0;j < matrix._width;j++)
                _ptr[i][j] = matrix._ptr[i][j];
        }

        _height = matrix._height;
        _width = matrix._width;
    }

	// Введите конструкторы и методы для чтения матрицы произвольного размера из файла.
    BaseMatrix<T>(std::istream& stream)
	{
		stream >> this->_height >> this->_width;
		
		this->_ptr = new T*[this->_height];

		for (int i = 0; i < this->_width; i++)
		{
			this->_ptr[i] = new T[this->_width];

			for (int j = 0; j < this->_height; j++)
				stream >> this->_ptr[i][j];
		}
	};

    int GetWidth()
    {
        return _width;
    }

    int GetHeight()
    {
        return _height;
    }

    T GetValue(int row,int column)
    {
        if(row < 0 || row >= _height || column < 0 || column >= _width)
            throw IndexOutOfBoundsException("Index out of bounds in GetValue(row,column)", row, column);

        return _ptr[row][column];
    }

	// , а также перегрузите оператор=.
    BaseMatrix& operator=(const BaseMatrix& matrix)
    {
        if(_height == matrix._height || _width == matrix._width)
        {  
            for(int i = 0;i < matrix._height;i++)
                for(int j = 0;j < matrix._width;j++)
                    _ptr[i][j] = matrix._ptr[i][j];

            return *this;
        }

        for(int i = 0;i < _height;i++)
                delete[] _ptr[i];

        delete[] _ptr;

        _ptr = new T*[matrix._height];

        for(int i = 0;i < matrix._height;i++)
        {
            _ptr[i] = new T[matrix._width];

            for(int j = 0;j < matrix._width;j++)
                _ptr[i][j] = matrix._ptr[i][j];
        }

        _height = matrix._height;
        _width = matrix._width;

        return *this;
    }

    ~BaseMatrix()
    {
        for(int i = 0;i < _height;i++)
            delete[] _ptr[i];

        delete[] _ptr;
    }
};

template<class T>
class ChildMatrix : public BaseMatrix<T>
{
private:
    bool IsLocalMinimum(int n,int m)
    {
		if(n <= 0 || n >= this->_height - 1 || m <= 0 || m >= this->_width - 1)
			return false;
        
		if(this->_ptr[n - 1][m] < this->_ptr[n][m] ||
			this->_ptr[n + 1][m] < this->_ptr[n][m] ||
			this->_ptr[n][m - 1] < this->_ptr[n][m] ||
			this->_ptr[n][m + 1] < this->_ptr[n][m])
            return false;

        return true;
    }
public:
	ChildMatrix<T>(int h,int w) : BaseMatrix<T>(h,w) { };
    ChildMatrix<T>(T** arr, int h,int w) : BaseMatrix<T>(arr,h,w) { };
	ChildMatrix<T>(const ChildMatrix& matrix) : BaseMatrix<T>(matrix) { };
    ChildMatrix<T>(std::istream& stream) : BaseMatrix<T>(stream) { };

	// В производном классе напишите метод заполнения массива произвольным нетривиальным образом.
    void Fill(int a,int b,int c)
    {
        for(int i = 0;i < this->_height;i++)
            for(int j = 0;j < this->_width;j++)
                this->_ptr[i][j] = (a*i + b*j) % c;
    }

    /*
    Элементы входной матрицы считать высотами некоторого участка
    поверхности. Получить на выходе матрицу, в которой отмечены
    локальные минимумы карты
    */
    ChildMatrix LocalMinimum()
    {
		if(this->_width < 3 && this->_height < 3)
			throw TooSmallSizeException("Matrix with both size less than 3 not contains local minimum in LocalMinimum", this->_height, this->_width);

        ChildMatrix matrix(this->_width,this->_height);

        for(int i = 0;i < this->_height;i++)
            for(int j = 0;j < this->_width;j++)
                matrix._ptr[i][j] = IsLocalMinimum(i,j) ? 1.0 : 0.0;

        return matrix;
    }

	template<class T2>
	friend std::ostream& operator<<(std::ostream& stream, ChildMatrix<T2> matrix);

	template<class T2>
	friend std::istream& operator>>(std::istream& stream, ChildMatrix<T2>& matrix);
};

//Сохраните результат обработки нескольких матриц (массива матриц) в файл, извлеките результаты из файла (в массив), выведите их в консоль. 
template <class T>
std::ostream& operator<<(std::ostream& stream, ChildMatrix<T> matrix)
{
	if (typeid(stream) == typeid(std::ofstream))
	{
		stream << matrix._height << ' ' << matrix._width << ' ';

		for (int i = 0; i < matrix._height; i++)
			for (int j = 0; j < matrix._width; j++)
				stream << matrix._ptr[i][j] << ' ';
	}
	else
		for (int i = 0; i < matrix._height; i++)
		{
			for (int j = 0; j < matrix._width; j++)
				stream << matrix._ptr[i][j] << ' ';

			stream << std::endl;
		}
		
	return stream;
}

template <class T>
std::istream& operator>>(std::istream& stream, ChildMatrix<T>& matrix)
{
	if (typeid(stream) == typeid(std::ifstream))
	{
		int w, h;
		
		stream >> h >> w;
		
		if (h != matrix._height || w != matrix._width)
		{
			
			for(int i = 0;i < matrix._height;i++)
					delete[] _ptr[i];

			delete[] _ptr;

			matrix._ptr = new T*[h];

			for (int i = 0; i < w; i++)
			{
				matrix._ptr[i] = new T[w];

				for (int j = 0; j < h; j++)
					stream >> matrix._ptr[i][j];
			}

			matrix._height = h;
			matrix._width = w;

			return stream;
		}
	}

	for (int i = 0; i < matrix._height; i++)
		for (int j = 0; j < matrix._width; j++)
			stream >> matrix._ptr[i][j];

	return stream;
}

template<class T>
void PrintMatrix(BaseMatrix<T> matrix)
{
     for(int i = 0;i < matrix.GetHeight();i++)
     {
        for(int j = 0;j < matrix.GetWidth();j++)
            std::cout << matrix.GetValue(i,j) << '\t';

        std::cout << std::endl;
    }
};

int main(int argc,char* argv[])
{	
    double** arr = new double*[3]
    {
        new double[3]{1.0,2.0,3.0},
        new double[3]{4.0,-5.0,4.5},
        new double[3]{-1.0,-2.0,3.0},
    };

	// Тестовая матрица
    ChildMatrix<double> matrix(arr,3,3);

    PrintMatrix(matrix);

    std::cout << "Local Minimum: " << std::endl;

	// Вывожу локальеые минимумы
    PrintMatrix(matrix.LocalMinimum());

	double** arr2 = new double*[2]
	{
		new double[1]{2.0},
		new double[1]{1.0},
	};

	ChildMatrix<double> matrix2(arr2,2,1);

	// Тестирую своё исключение TooSmallSizeException
	try
	{

		matrix2.LocalMinimum();
	}
	catch (IndexOutOfBoundsException e)
	{
		std::cout << std::endl << "IndexOutOfBoundsException has been caught: "; e.Print();
	}
	catch (InvalidSizeException e)
	{
		std::cout << std::endl << "InvalidSizeException has been caught: "; e.Print();
	}
	catch (WrongSizeException e)
	{
		std::cout << std::endl << "WrongSizeException has been caught: "; e.Print();
	}
	catch (MatrixException e)
	{
		std::cout << std::endl << "MatrixException has been caught: "; e.Print();
	}
	catch (std::exception e)
	{
		std::cout << std::endl << "std::exception has been caught: "; e.what();
	}

	std::cout << std::endl;

	std::ofstream out("out.txt");

	out << 10 << std::endl;

	for(int i = 0;i < 10;i++)
	{
		ChildMatrix<double> m(5,5);
		m.Fill(i,20 - i, 47);

		out << m.LocalMinimum() << std::endl;

		std::cout << "=========" << i << " matrix=========" << std::endl;
		PrintMatrix(m);
	}

	out.close();

	std::ifstream in("out.txt");

	int n; in >> n;

	for(int i = 0;i < n;i++)
	{
		ChildMatrix<double> m(in);

		// Продемонстрируйте, что результаты, которые записывались в файл, и прочитанные из файла данные не отличаются
		std::cout << "=========" << i << " local minimums=========" << std::endl;
		PrintMatrix(m);
	}

	in.close();

    return 0;
}
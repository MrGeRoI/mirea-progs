#pragma once

#include <algorithm>

class MyArrayParent
{
protected:
	int _capacity, _count;

	double* _ptr;
public:

	MyArrayParent(int dimension = 100)
	{
		_ptr = new double[dimension];
		_capacity = dimension;
		_count = 0;
	}

	//Конструктором, принимающим и копирующим информацию из су-ществующего массива.
	MyArrayParent(double* arr, int len)
	{
		_ptr = new double[len];
		_capacity = len;

		for (int i = 0; i < len; i++)
			_ptr[i] = arr[i];
	}

	//Конструктором копий MyArrayParent (const MyArrayParent& v).	
	MyArrayParent(const MyArrayParent& array)
	{
		_ptr = new double[array._capacity];
		_count = array._count;
		_capacity = array._capacity;
		
		for (int i = 0; i < array._capacity; i++)
			_ptr[i] = array._ptr[i];
	}

	~MyArrayParent()
	{
		delete[] _ptr;
	}

	int GetCapacity()
	{
		return _capacity;
	}

	int GetSize()
	{
		return _count;
	}

	double GetComponent(int n)
	{
		if (n < 0 || n >= _capacity)
			return 0.0;

		return _ptr[n];
	}
	
	void SetComponent(int n, double value)
	{
		if (n >= 0 && n < _count)
			_ptr[n] = value;
	}

	virtual void RemoveLastValue()
	{
		if (_count > 0)
			_count--;
	}

	//Оператором [ ] для обращения к элементу по индексу.
	double& operator[](int n)
	{
		return _ptr[n];
	};

	virtual void Push(double value)
	{
		if(_count < _capacity)
		{
			_ptr[_count] = value;
			_count++;
		}
	}

	//поиск элемента
	virtual int IndexOf(double value, bool bFindFromStart = true)
	{
		if(bFindFromStart)
		{
			for(int i = 0;i < _count;i++)
				if(_ptr[i] == value)
					return i;
		}
		else
		{
			for(int i = _count-1;i >= 0;i--)
				if(_ptr[i] == value)
					return i;
		}

		return -1;
	};

	//Оператором =.
	MyArrayParent operator =(MyArrayParent array)
	{
		if(_capacity != array._capacity)
		{
			_capacity = array._capacity;
			delete[] _ptr;
			_ptr = new double[_capacity];
		}

		_count = array._count;

		for(int i = 0;i < array._capacity;i++)
			_ptr[i] = array._ptr[i];
		
		return *this;
	};

	double GetAverage()
	{
		// Нахожу среднее арифметическое
		double average = 0.0;

		for(int i = 0;i < _count;i++)
			average += _ptr[i];

		average /= _count;

		return average;
	};
};


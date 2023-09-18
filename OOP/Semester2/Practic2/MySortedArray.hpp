#pragma once

#include <iostream>
#include "MyArrayChild.hpp"

class MySortedArray : public MyArrayChild
{
protected:
	virtual int BinarySearchInsert(double value)
	{
		// Бинарный поиск

		int left = -1,right = _count;

		while(left + 1 < right)
		{
			int midd = (left + right) / 2;

			if(_ptr[midd] == value)
				return midd;
			else if (_ptr[midd] > value)
				right = midd;
			else
				left = midd;
		}

		return right;
	}

	virtual int BinarySearchRecursion(double value, int left, int right)
	{
		int middle = (left + right) / 2;
	
		if (_ptr[middle] == value)
			return middle;
			
		if (middle == right || middle == left)
			return -1;
	
		if (_ptr[middle] < value)
			return BinarySearchRecursion(value, middle, right);
		else if (_ptr[middle] > value)
			return BinarySearchRecursion(value, left, middle);

		return -1;
	}

public:
	MySortedArray(int dimension = 100) : MyArrayChild(dimension) { }

	MySortedArray(double *arr,int len) : MyArrayChild(arr,len) { };

	MySortedArray(const MySortedArray& arr) : MyArrayChild(arr) { };

	~MySortedArray() { }

	virtual void Push(double value) override
	{
		if(_count >= _capacity)
			return;

		InsertAt(value,BinarySearchInsert(value));
	}

	MySortedArray ReplaceRepeats()
	{
		double average = GetAverage();

		MySortedArray array(*this);

		// Заменяю повторы
		for(int i = 1;i < _count;i++)
			if(_ptr[i - 1] == _ptr[i])
			{
				array.RemoveAt(i - 1);
				array.RemoveAt(i - 1);

				array.Push(average);
				array.Push(average);
			}

		return array;
	}

	virtual int IndexOf(double value, bool bFindFromStart = true) override
	{
		int i = BinarySearchInsert(value);

		return _ptr[i] == value ? i : -1;
	}
};
#pragma once

#include <iostream>
#include <stdexcept>

template <class T>
class Heap
{
private:
	T *m_pArray;

	int m_iLength;

	int m_iSize;

	void swap(int index1, int index2);

	T getLeftChild(int index) { return m_pArray[getLeftChildIndex(index)]; }

	T getRightChild(int index) { return m_pArray[getRightChildIndex(index)]; }

	T getParent(int index) { return m_pArray[getParentIndex(index)]; }

	int getLeftChildIndex(int index);

	int getRightChildIndex(int index);

	int getParentIndex(int index);

	void siftUp(int index = -1);

	void siftDown(int index = 0);

	void heapify(int index = 0) { siftDown(index); };

public:
	int getCapacity() { return m_iSize; }
	int getCount() { return m_iLength; }

	T &operator[](int index);

	const T &operator[](int index) const;

	Heap<T>(int memory = 100)
	{
		m_pArray = new T[memory];
		m_iLength = 0;
		m_iSize = memory;
	}

	void Push(T N);

	void Remove(int index);

	T extractMin();

	void straight(void (*func)(T));

	template <class T1>
	friend std::ostream &operator<<(std::ostream &stream, const Heap<T1> &node);

	~Heap() { delete[] m_pArray; };
};

template <class T>
T &Heap<T>::operator[](int index)
{
	if (index < 0 || index >= m_iLength)
		throw std::out_of_range;

	return m_pArray[index];
}

template <class T>
void Heap<T>::swap(int index1, int index2)
{
	if (index1 < 0 || index1 >= m_iLength)
		throw std::out_of_range;

	if (index2 < 0 || index2 >= m_iLength)
		throw std::out_of_range;

	T temp;
	temp = m_pArray[index1];
	m_pArray[index1] = m_pArray[index2];
	m_pArray[index2] = temp;
}

template <class T>
int Heap<T>::getLeftChildIndex(int index)
{
	if (index < 0 || index >= m_iLength)
		throw std::out_of_range;

	return index * 2 + 1;
}

template <class T>
int Heap<T>::getRightChildIndex(int index)
{
	if (index < 0 || index >= m_iLength)
		throw std::out_of_range;

	return index * 2 + 2;
}

template <class T>
int Heap<T>::getParentIndex(int index)
{
	if (index <= 0 || index >= m_iLength)
		throw std::out_of_range;

	if (index % 2 == 0)
		return index / 2 - 1;

	return index / 2;
}

template <class T>
void Heap<T>::siftUp(int index)
{
	if (index == -1)
		index = m_iLength - 1;

	if (index == 0)
		return;

	int parent = getParentIndex(index);

	if (m_pArray[index] < m_pArray[parent])
	{
		swap(index, parent);
		siftUp(parent);
	}
}

template <class T>
void Heap<T>::siftDown(int index)
{
	if (m_iLength <= 0)
		return;

	int maximum = index;

	int left = getLeftChildIndex(index), right = getRightChildIndex(index);

	if (left < m_iLength && m_pArray[left] < m_pArray[maximum])
		maximum = left;

	if (right < m_iLength && m_pArray[right] < m_pArray[maximum])
		maximum = right;

	if (index != maximum)
	{
		swap(index, maximum);
		siftDown(maximum);
	}
}

template <class T>
void Heap<T>::Push(T N)
{

	if (m_iLength < m_iSize)
	{
		m_pArray[m_iLength] = N;
		m_iLength++;
		siftUp();
	}
}

template <class T>
void Heap<T>::Remove(int index)
{
	if (index < 0 || index >= m_iLength)
		throw std::out_of_range;

	if (index >= m_iLength - 1)
	{
		m_iLength--;
		return;
	}

	swap(index, m_iLength - 1);
	m_iLength--;
	siftUp(index);
	siftDown(index);
}

template <class T>
T Heap<T>::extractMin()
{

	T res = m_pArray[0];
	swap(0, m_iLength - 1);
	m_iLength--;
	heapify();
	return res;
}

template <class T>
void Heap<T>::straight(void (*func)(T))
{
	for (int i = 0; i < m_iLength; i++)
		func(m_pArray[i]);
}

template <class T>
std::ostream &operator<<(std::ostream &stream, const Heap<T> &heap)
{
	for (int i = 0; i < heap.m_iLength; i++)
		stream << heap.m_pArray[i] << ' ';

	return stream;
}
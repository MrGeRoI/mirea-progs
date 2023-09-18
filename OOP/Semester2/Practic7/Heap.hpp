#include <iostream>

class HeapExcepction : std::exception
{
public:
	virtual const char* what() const noexcept override { return "HeapExcepction"; };
};

class IndexOutOfBoundsExcepction : HeapExcepction
{
public:
	int _index;

	IndexOutOfBoundsExcepction(int i) { _index = i; }

	virtual const char* what() const noexcept override { return "IndexOutOfBoundsExcepction"; };
};

//куча (heap)
template <class T>
class Heap
{
private:
	//массив
	T* _array;
	//сколько элементов добавлено
	int _length;
	//сколько памяти выделено
	int _size;
public:

	//доступ к вспомогательным полям кучи и оператор индекса
	int GetCapacity() { return _size; }
	int GetCount() { return _length; }

	T& operator[](int index);

	//конструктор
	Heap<T>(int memory = 100)
	{
		_array = new T[memory];
		_length = 0;
		_size = memory;
	}

	//поменять местами элементы _array[index1], _array[index2]
	void Swap(int index1, int index2);

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	T GetLeftChild(int index) { return _array[GetLeftChildIndex(index)]; }

	T GetRightChild(int index) { return _array[GetRightChildIndex(index)]; }

	T GetParent(int index) { return _array[GetParentIndex(index)]; }

	int GetLeftChildIndex(int index);

	int GetRightChildIndex(int index);

	int GetParentIndex(int index);

	//просеить элемент вверх
	void SiftUp(int index = -1);

	void SiftDown(int index = 0);

	//восстановление свойств кучи после удаления или добавления элемента
	void Heapify(int index = 0) { SiftDown(index); };

	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	void Push(T N);

	void Remove(int index);

	T ExtractMin();

	T ExtractMax();

	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*func)(T));

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void(*func)(T), int index = 0);

	void InOrder(void(*func)(T), int index = 0);

	void PostOrder(void(*func)(T), int index = 0);

	template<class T1>
	friend std::ostream& operator<<(std::ostream& stream,const Heap<T1>& node);

	~Heap() { delete[] _array; };
};

template <class T>
T& Heap<T>::operator[](int index)
{
	if (index < 0 || index >= _length)
		throw IndexOutOfBoundsExcepction(index);//?

	return _array[index];
}

template <class T>
void Heap<T>::Swap(int index1, int index2)
{
	if (index1 < 0 || index1 >= _length)
		throw IndexOutOfBoundsExcepction(index1);
		
	if (index2 < 0 || index2 >= _length)
		throw IndexOutOfBoundsExcepction(index2);
	//здесь нужна защита от дурака

	T temp;
	temp = _array[index1];
	_array[index1] = _array[index2];
	_array[index2] = temp;
}

template <class T>
int Heap<T>::GetLeftChildIndex(int index)
{
	if (index < 0 || index >= _length)
		throw IndexOutOfBoundsExcepction(index);
	//здесь нужна защита от дурака
	return index * 2 + 1;
}

template <class T>
int Heap<T>::GetRightChildIndex(int index)
{
	if (index < 0 || index >= _length)
		throw IndexOutOfBoundsExcepction(index);
	//здесь нужна защита от дурака

	return index * 2 + 2;
}

template <class T>
int Heap<T>::GetParentIndex(int index)
{
	if (index <= 0 || index >= _length)
		throw IndexOutOfBoundsExcepction(index);
	//здесь нужна защита от дурака

	if (index % 2 == 0)
		return index / 2 - 1;

	return index / 2;
}

template <class T>
void Heap<T>::SiftUp(int index)
{
	if (index == -1)
		index = _length - 1;

	if (index == 0)
		return;

	int parent = GetParentIndex(index);

	if (_array[index] < _array[parent])
	{
		Swap(index, parent);
		SiftUp(parent);
	}
}

template <class T>
void Heap<T>::SiftDown(int index)
{
	if(_length <= 0)
		return;

	int maximum = index;

	int left = GetLeftChildIndex(index), right = GetRightChildIndex(index);
	
	if (left < _length && _array[left] < _array[maximum])
		maximum = left;
	
	if (right < _length && _array[right] < _array[maximum])
		maximum = right;

	if (index != maximum)
	{
		Swap(index, maximum);
		SiftDown(maximum);
	}
}

template <class T>
void Heap<T>::Push(T N)
{
	//добавить элемент и включить просеивание
	if (_length < _size)
	{
		_array[_length] = N;
		_length++;
		SiftUp();
	}
}

template <class T>
void Heap<T>::Remove(int index)
{
	if (index < 0 || index >= _length)
		throw IndexOutOfBoundsExcepction(index);

	// Если удаляем последний, то просто "забываем" про него
	if(index >= _length - 1)
	{
        _length--;
        return;
    }

	Swap(index, _length - 1);
	_length--;
	SiftUp(index);
	SiftDown(index);
}

template <class T>
T Heap<T>::ExtractMin()
{
	//исключить минимум и запустить просеивание кучи
	T res = _array[0];
	Swap(0, _length - 1);
	_length--;
	Heapify();
	return res;
}

template <class T>
void Heap<T>::Straight(void(*func)(T))
{
	for (int i = 0; i < _length; i++)
		func(_array[i]);
}

template <class T>
void Heap<T>::PreOrder(void(*func)(T), int index)
{
	if (index >= 0 && index < _length)
		func(_array[index]);

	if (GetLeftChildIndex(index) < _length)
		PreOrder(func, GetLeftChildIndex(index));

	if (GetRightChildIndex(index) < _length)
		PreOrder(func, GetRightChildIndex(index));
}

template <class T>
void Heap<T>::InOrder(void(*func)(T), int index)
{
	if (GetLeftChildIndex(index) < _length)
		PreOrder(func, GetLeftChildIndex(index));

	if (index >= 0 && index < _length)
		func(_array[index]);

	if (GetRightChildIndex(index) < _length)
		PreOrder(func, GetRightChildIndex(index));
}

template <class T>
void Heap<T>::PostOrder(void(*func)(T), int index)
{
	if (GetLeftChildIndex(index) < _length)
		PreOrder(func, GetLeftChildIndex(index));

	if (GetRightChildIndex(index) < _length)
		PreOrder(func, GetRightChildIndex(index));

	if (index >= 0 && index < _length)
		func(_array[index]);
}

template<class T>
std::ostream& operator<<(std::ostream& stream,const Heap<T>& heap)
{
	for (int i = 0; i < heap._length; i++)
		stream << heap._array[i] << ' ';

	return stream;
}
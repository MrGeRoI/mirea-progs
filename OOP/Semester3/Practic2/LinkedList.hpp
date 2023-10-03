#pragma once

#pragma warning(disable : 4996) // Вырубает предупреждение про итераторы

#include <iostream>
#include <fstream>

template <class T>
class Element
{
	// элемент связного списка
private:
	// указатель на предыдущий и следующий элемент
	Element *_next;
	Element *_previous;

	// информация, хранимая в поле
	T _value;

public:
	// доступ к полю *_next
	virtual Element *GetNext() const { return _next; }
	virtual void SetNext(Element *value) { _next = value; }

	// доступ к полю *_previous
	virtual Element *GetPrevious() const { return _previous; }
	virtual void SetPrevious(Element *value) { _previous = value; }

	// доступ к полю с хранимой информацией _value
	virtual T GetValue() const { return _value; }
	virtual void SetValue(T value) { _value = value; }

	template <class T1>
	friend ostream &operator<<(ostream &stream, const Element<T1> &obj);

	Element(T value)
	{
		_value = value;
		_next = _previous = nullptr;
	}
};

template <class T>
ostream &operator<<(ostream &stream, const Element<T> &obj)
{
	return stream << obj._value;
}

template <class T>
class LinkedList
{
protected:
	// достаточно хранить начало и конец
	Element<T> *_head;
	Element<T> *_tail;
	// для удобства храним количество элементов
	int _count;

public:
	virtual int Count() const { return _count; }

	virtual Element<T> *GetBegin() const { return _head; }

	virtual Element<T> *GetEnd() const { return _tail; }

	// конструктор без параметров
	LinkedList()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	// чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T> *Push(T value) = 0;

	// чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual T Pop() = 0;

	virtual ~LinkedList()
	{
		// деструктор - освобождение памяти
		Element<T> *previous;
		for (Element<T> *current = _head; current != nullptr;)
		{
			previous = current;
			current = current->GetNext();
			delete previous;
		}
	}

	// получение элемента по индексу - какова асимптотическая оценка этого действия?
	//  O(n)
	virtual Element<T> *operator[](int i) const
	{
		// индексация
		if (i < 0 || i > _count)
			return nullptr;

		// ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T> *cur = _head;
		for (int k = 0; k < i; k++)
			cur = cur->GetNext();

		return cur;
	}

	template <class T1>
	friend ofstream &operator<<(ofstream &stream, const LinkedList<T1> &obj);
	template <class T1>
	friend ostream &operator<<(ostream &stream, const LinkedList<T1> &obj);
	template <class T1>
	friend istream &operator>>(istream &stream, LinkedList<T1> &obj);
};

/*Петрусевич, какого хуя тут такие костыли, ты долбаёб?
Надо просто сделать перегрузки функций ввода/ввывода из файла и консоли
для типов ostream и ofstream*/
template <class T>
ofstream &operator<<(ofstream &stream, const LinkedList<T> &obj)
{
	stream << obj._count << "\n";
	for (Element<T> *current = obj.GetBegin(); current != nullptr; current = current->GetNext())
		stream << current->GetValue() << " ";
	return stream;
}

template <class T>
ostream &operator<<(ostream &stream, const LinkedList<T> &obj)
{
	for (Element<T> *current = obj.GetBegin(); current != nullptr; current = current->GetNext())
		stream << current->GetValue() << "\n";

	return stream;
}

template <class T>
istream &operator>>(istream &stream, LinkedList<T> &list)
{
	// чтение из файла и консоли совпадают
	stream >> list._count;
	// здесь надо очистить память под obj, установить obj.num = 0

	Element<T> *previous;
	for (Element<T> *current = list._head; current != nullptr;)
	{
		previous = current;
		current = current->GetNext();
		delete previous;
	}

	for (int i = 0; i < list._count; i++)
	{
		T value;
		stream >> value;
		list.Push(value);
	}

	return stream;
}

// дописать класс итератора по списку
template <typename T>
class ListIterator : public iterator<input_iterator_tag, T>
{
public:
	// конструкторы
	ListIterator() { _element = nullptr; }
	ListIterator(Element<T> *p) { _element = p; }
	ListIterator(const ListIterator &it) { _element = it._element; }

	// методы работы с итераторами
	// присваивание
	ListIterator &operator=(const ListIterator &it)
	{
		_element = it._element;
		return *this;
	}
	ListIterator &operator=(Element<T> *p)
	{
		_element = p;
		return *this;
	}

	// проверка итераторов на равенство
	bool operator!=(ListIterator const &other) const { return _element != other._element; }
	bool operator==(ListIterator const &other) const { return _element == other._element; }

	Element<T> *GetElement() const { return _element; }
	void SetElement(Element<T> *element) { _element = element; }

	// получить значение
	Element<T> &operator*() const
	{
		if (_element == nullptr)
			throw std::runtime_error("Invalid pointer");

		return *_element;
	}
	// перемещение с помощью итераторов
	ListIterator &operator++()
	{
		_element = _element->GetNext();
		return *this;
	} // Префиксный ++
	ListIterator operator++(int)
	{
		ListIterator it(*this);
		_element = _element->GetNext();
		return it;
	} // Постфиксный ++
	ListIterator &operator--()
	{
		_element = _element->GetPrevious();
		return *this;
	} // Префиксный --
	ListIterator operator--(int)
	{
		ListIterator it(*this);
		_element = _element->GetPrevious();
		return it;
	} // Постфиксный --

private:
	// текущий элемент
	Element<T> *_element;
};

/*Постройте шаблон класса двусвязного списка путём наследования от
класса IteratedLinkedList.*/

// класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedList<T>
{
public:
	IteratedLinkedList() : LinkedList<T>() {}
	virtual ~IteratedLinkedList() {}

	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedList<T>::_head;
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = LinkedList<T>::_tail;
		return it;
	}
};

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	Stack() : IteratedLinkedList<T>() {}
	/*Реализуйте функции добавления элемента push() и
	удаления элемента pop() в классе-наследнике D (для четных вариантов D –
	Стек, для нечетных – Очередь) согласно схеме: для класса Стек элементы
	добавляются в конец, извлекаются с конца; для класса Очереди элементы
	добавляются в конец, извлекаются с начала. */
	Element<T> *Push(T value) // To the end
	{
		Element<T> *elem = new Element<T>(value);

		if (this->_tail == nullptr)
			this->_head = this->_tail = elem;
		else
		{
			this->_tail->SetNext(elem);
			elem->SetPrevious(this->_tail);
			this->_tail = elem;
		}

		this->_count++;

		return elem;
	}

	T Pop()
	{
		T value;

		value = this->_tail->GetValue();

		Element<T> *prev = this->_tail->GetPrevious();
		prev->SetNext(nullptr);

		this->_tail->SetPrevious(nullptr);
		this->_tail = prev;
		this->_count--;

		return value;
	}

	ListIterator<T> Insert(ListIterator<T> it, T value)
	{
		Element<T> *inserted = Insert(it.GetElement(), value);

		if (inserted != nullptr)
			it = inserted;

		return it;
	}

	Element<T> *Insert(Element<T> *current, T value)
	{
		if (this->_tail == current)
			return Stack<T>::Push(value);

		Element<T> *elem = new Element<T>(value);

		if (current == nullptr)
		{
			elem->SetNext(this->_head);
			this->_head->SetPrevious(elem);
			this->_head = elem;
			return elem;
		}

		elem->SetNext(current->GetNext());
		current->GetNext()->SetPrevious(elem);

		current->SetNext(elem);

		elem->SetPrevious(current);

		this->_count++;

		return elem;
	}

	// Push, Pop, Remove, Insert
	virtual ListIterator<T> Remove(ListIterator<T> it)
	{
		if (it.GetElement() == nullptr)
		{
			Pop();
			return it;
		}
		Element<T> *elem = it.GetElement();
		it--;
		Remove(elem);
		return it;
	}

	virtual Element<T> *Remove(Element<T> *elem)
	{
		Element<T> *prev = elem->GetPrevious(), *next = elem->GetNext();

		if (elem == this->_head)
			this->_head = next;

		if (elem == this->_tail)
			this->_tail = prev;

		if (next != nullptr)
			next->SetPrevious(prev);

		if (prev != nullptr)
			prev->SetNext(next);

		this->_count--;

		return elem;
	}

	/*Реализуйте функцию универсального фильтра,
	принимающего список произвольного типа (участвующего в схеме
	наследования) и возвращающего список произвольного типа (тип
	обрабатываемого списка не обязан совпадать с типом списка-результата).
	*/
	virtual void Filter(LinkedList<T> &list, bool (*filter)(T))
	{
		for (Element<T> *elem = this->_head; elem != nullptr; elem = elem->GetNext())
			if (filter(elem->GetValue()))
				list.Push(elem->GetValue());
	}

	// Реализуйте функцию filter() из пункта 1 – результатом должен стать объект типа D.
	virtual Stack<T> Filter(bool (*filter)(T))
	{
		Stack<T> result;

		Filter(result, filter);

		return result;
	}
};

// Постройте наследник класса D. Переопределите функцию добавления
// нового элемента таким образом, чтобы контейнер оставался упорядоченным
template <class T>
class SortedStack : public Stack<T>
{
public:
	SortedStack() : Stack<T>() {}

	virtual Element<T> *Push(T value)
	{
		if (this->_head == nullptr || this->_tail->GetValue() < value)
			return Stack<T>::Push(value);

		for (Element<T> *element = this->_head; element != nullptr; element = element->GetNext())
			if (value < element->GetValue())
				return Stack<T>::Insert(element->GetPrevious(), value);
	}
};

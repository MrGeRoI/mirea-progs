#pragma warning(disable : 4996) // Вырубает предупреждение про итераторы

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Laptop
{
public:
	string _company, _model, _CPU, _storage_device;
	int _screensize, _cores, _RAM, _storage, _price;

	Laptop()
	{
		_screensize = 0;
		_cores = 0;
		_RAM = 0;
		_storage = 0;
		_price = 0;
	}

	Laptop(const char *company, const char *model, const char *CPU, const char *storage_device,
		   int screensize, int cores, int RAM, int storage, int price)
	{
		_company = company;
		_model = model;
		_CPU = CPU;
		_storage_device = storage_device;
		_screensize = screensize;
		_cores = cores;
		_RAM = RAM;
		_storage = storage;
		_price = price;
	}

	Laptop(const Laptop &laptop)
	{
		_company = laptop._company;
		_model = laptop._model;
		_CPU = laptop._CPU;
		_storage_device = laptop._storage_device;
		_screensize = laptop._screensize;
		_cores = laptop._cores;
		_RAM = laptop._RAM;
		_storage = laptop._storage;
		_price = laptop._price;
	}

	~Laptop() {}

	friend ostream &operator<<(ostream &s, const Laptop &value);
	friend istream &operator>>(istream &s, Laptop &value);

	bool operator<(const Laptop &laptop) const
	{
		if (_price < laptop._price)
			return true;

		if (_cores < laptop._cores)
			return true;

		if (_RAM < laptop._RAM)
			return true;

		if (_screensize < laptop._screensize)
			return true;

		return false;
	}

	bool operator>(const Laptop &laptop) const
	{
		if (_price > laptop._price)
			return true;

		if (_cores > laptop._cores)
			return true;

		if (_RAM > laptop._RAM)
			return true;

		if (_screensize > laptop._screensize)
			return true;

		return false;
	}

	bool operator==(const Laptop &laptop) const
	{
		return _company == laptop._company &&
			   _model == laptop._model &&
			   _CPU == laptop._CPU &&
			   _storage_device == laptop._storage_device &&
			   _screensize == laptop._screensize &&
			   _cores == laptop._cores &&
			   _RAM == laptop._RAM &&
			   _storage == laptop._storage &&
			   _price == laptop._price;
	}
};

ostream &operator<<(ostream &stream, const Laptop &value)
{
	return stream << value._company << ' ' << value._model << ' ' << value._CPU << ' ' << value._storage_device
				  << ' ' << value._screensize << ' ' << value._cores << ' ' << value._RAM << ' ' << value._storage << ' ' << value._price;
}

istream &operator>>(istream &stream, Laptop &value)
{
	return stream >> value._company >> value._model >> value._CPU >> value._storage_device >> value._screensize >> value._cores >> value._RAM >> value._storage >> value._price;
}

template <class T>
class LinkedList
{
public:
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
		virtual Element *getNext() const { return _next; }
		virtual void setNext(Element *value) { _next = value; }

		// доступ к полю *_previous
		virtual Element *getPrevious() const { return _previous; }
		virtual void setPrevious(Element *value) { _previous = value; }

		// доступ к полю с хранимой информацией _value
		virtual T getValue() const { return _value; }
		virtual void setValue(T value) { _value = value; }

		template <class T1>
		friend ostream &operator<<(ostream &stream, const typename LinkedList<T1>::Element &obj);

		Element(T value)
		{
			_value = value;
			_next = _previous = nullptr;
		}
	};

protected:
	// достаточно хранить начало и конец
	Element *_head;
	Element *_tail;
	// для удобства храним количество элементов
	int _count;

public:
	virtual int count() const { return _count; }

	virtual Element *getBegin() const { return _head; }

	virtual Element *getEnd() const { return _tail; }

	// конструктор без параметров
	LinkedList()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	// чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element *push_R(T value) = 0;

	// чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual T pop() = 0;

	virtual ~LinkedList()
	{
		// деструктор - освобождение памяти
		Element *previous;
		for (Element *current = _head; current != nullptr;)
		{
			previous = current;
			current = current->getNext();
			delete previous;
		}
	}

	// получение элемента по индексу - какова асимптотическая оценка этого действия?
	//  O(n)
	virtual Element *operator[](int i) const
	{
		// индексация
		if (i < 0 || i > _count)
			return nullptr;

		// ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element *cur = _head;
		for (int k = 0; k < i; k++)
			cur = cur->getNext();

		return cur;
	}

	template <class T1>
	friend ofstream &operator<<(ofstream &stream, const LinkedList<T1> &obj);
	template <class T1>
	friend ostream &operator<<(ostream &stream, const LinkedList<T1> &obj);
	template <class T1>
	friend istream &operator>>(istream &stream, LinkedList<T1> &obj);
};

template <class T>
ostream &operator<<(ostream &stream, const typename LinkedList<T>::Element &obj)
{
	return stream << obj._value;
}

template <class T>
ofstream &operator<<(ofstream &stream, const LinkedList<T> &obj)
{
	stream << obj._count << "\n";
	for (typename LinkedList<T>::Element *current = obj.getBegin(); current != nullptr; current = current->getNext())
		stream << current->getValue() << " ";
	return stream;
}

template <class T>
ostream &operator<<(ostream &stream, const LinkedList<T> &obj)
{
	for (typename LinkedList<T>::Element *current = obj.getBegin(); current != nullptr; current = current->getNext())
		stream << current->getValue() << "\n";

	return stream;
}

template <class T>
istream &operator>>(istream &stream, LinkedList<T> &list)
{
	// чтение из файла и консоли совпадают
	stream >> list._count;
	// здесь надо очистить память под obj, установить obj.num = 0

	typename LinkedList<T>::Element *previous;
	for (typename LinkedList<T>::Element *current = list._head; current != nullptr;)
	{
		previous = current;
		current = current->getNext();
		delete previous;
	}

	for (int i = 0; i < list._count; i++)
	{
		T value;
		stream >> value;
		list.push_R(value);
	}

	return stream;
}

/*Постройте шаблон класса двусвязного списка путём наследования от
класса IteratedLinkedList.*/

// класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedList<T>
{
public:
	using typename LinkedList<T>::Element;

	// дописать класс итератора по списку
	class Iterator : public iterator<input_iterator_tag, T>
	{
	private:
		// текущий элемент
		Element *_element;

	public:
		// конструкторы
		Iterator() { _element = nullptr; }
		Iterator(Element *p) { _element = p; }
		Iterator(const Iterator &it) { _element = it._element; }

		// методы работы с итераторами
		// присваивание
		Iterator &operator=(const Iterator &it)
		{
			_element = it._element;
			return *this;
		}
		Iterator &operator=(Element *p)
		{
			_element = p;
			return *this;
		}

		// проверка итераторов на равенство
		bool operator!=(Iterator const &other) const { return _element != other._element; }
		bool operator==(Iterator const &other) const { return _element == other._element; }

		Element *getElement() const { return _element; }
		void setElement(Element *element) { _element = element; }

		// получить значение
		const T &operator*() const
		{
			if (_element == nullptr)
				throw runtime_error("Invalid pointer");

			return _element->getValue();
		}
		// перемещение с помощью итераторов
		Iterator &operator++()
		{
			if (_element)
				_element = _element->getNext();

			return *this;
		} // Префиксный ++
		Iterator operator++(int)
		{
			Iterator it(*this);

			if (_element)
				_element = _element->getNext();

			return it;
		} // Постфиксный ++
		Iterator &operator--()
		{
			if (_element)
				_element = _element->getPrevious();

			return *this;
		} // Префиксный --
		Iterator operator--(int)
		{
			Iterator it(*this);

			if (_element)
				_element = _element->getPrevious();

			return it;
		} // Постфиксный --
	};

	IteratedLinkedList() : LinkedList<T>() {}
	virtual ~IteratedLinkedList() {}

	Iterator begin()
	{
		Iterator it = LinkedList<T>::_head;
		return it;
	}
	Iterator end()
	{
		Iterator it = LinkedList<T>::_tail;
		return it;
	}
};

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	using typename LinkedList<T>::Element;
	using typename IteratedLinkedList<T>::Iterator;

	Stack() : IteratedLinkedList<T>() {}
	/*Реализуйте функции добавления элемента push() и
	удаления элемента pop() в классе-наследнике D (для четных вариантов D –
	Стек, для нечетных – Очередь) согласно схеме: для класса Стек элементы
	добавляются в конец, извлекаются с конца; для класса Очереди элементы
	добавляются в конец, извлекаются с начала. */
	Element *push_R(T value) // To the end
	{
		Element *elem = new Element(value);

		if (this->_tail == nullptr)
			this->_head = this->_tail = elem;
		else
		{
			this->_tail->setNext(elem);
			elem->setPrevious(this->_tail);
			this->_tail = elem;
		}

		this->_count++;

		return elem;
	}

	Iterator push(T value)
	{
		return Iterator(this->push_R(value));
	}

	T pop()
	{
		T value;

		value = this->_tail->getValue();

		Element *prev = this->_tail->getPrevious();
		prev->setNext(nullptr);

		this->_tail->setPrevious(nullptr);
		this->_tail = prev;
		this->_count--;

		return value;
	}

	Iterator insert(Element *current, T value)
	{
		if (this->_tail == current)
			return Stack<T>::push(value);

		Element *elem = new Element(value);

		if (current == nullptr)
		{
			elem->setNext(this->_head);
			this->_head->setPrevious(elem);
			this->_head = elem;
			return elem;
		}

		elem->setNext(current->getNext());
		current->getNext()->setPrevious(elem);

		current->setNext(elem);

		elem->setPrevious(current);

		this->_count++;

		return Iterator(elem);
	}

	// push, pop, remove, insert
	virtual Iterator remove(Iterator it)
	{
		if (it.getElement() == nullptr)
		{
			pop();
			return it;
		}
		Element *elem = it.getElement();
		it--;
		remove(elem);
		return it;
	}

	virtual Element *remove(Element *elem)
	{
		Element *prev = elem->getPrevious(), *next = elem->getNext();

		if (elem == this->_head)
			this->_head = next;

		if (elem == this->_tail)
			this->_tail = prev;

		if (next != nullptr)
			next->setPrevious(prev);

		if (prev != nullptr)
			prev->setNext(next);

		this->_count--;

		return elem;
	}

	/*Реализуйте функцию универсального фильтра,
	принимающего список произвольного типа (участвующего в схеме
	наследования) и возвращающего список произвольного типа (тип
	обрабатываемого списка не обязан совпадать с типом списка-результата).
	*/
	virtual void filter(LinkedList<T> &list, bool (*func)(T))
	{
		for (Element *elem = this->_head; elem != nullptr; elem = elem->getNext())
			if (func(elem->getValue()))
				list.push_R(elem->getValue());
	}

	// Реализуйте функцию filter() из пункта 1 – результатом должен стать объект типа D.
	virtual Stack<T> filter(bool (*func)(T))
	{
		Stack<T> result;

		filter(result, func);

		return result;
	}
};

// Постройте наследник класса D. Переопределите функцию добавления
// нового элемента таким образом, чтобы контейнер оставался упорядоченным
template <class T>
class SortedStack : public Stack<T>
{
public:
	using typename LinkedList<T>::Element;
	using typename IteratedLinkedList<T>::Iterator;

	SortedStack() : Stack<T>() {}

	virtual Iterator push(T value)
	{
		if (this->_head == nullptr || this->_tail->getValue() < value)
			return Stack<T>::push(value);

		for (Element *element = this->_head; element != nullptr; element = element->getNext())
			if (value < element->getValue())
				return Stack<T>::insert(element->getPrevious(), value);

		return Iterator(nullptr);
	}
};

bool price_filter(Laptop laptop)
{
	return laptop._price <= 1500;
}

int main()
{
	SortedStack<int> nums;

	for (int i = 0; i < 25; i += 3)
		nums.push(i % 7);

	cout << "count: " << nums.count() << endl
		 << nums << endl
		 << "popped: " << nums.pop() << endl;

	typename SortedStack<int>::Iterator num_it = nums.begin();
	num_it++;
	num_it++;
	num_it++;
	nums.remove(num_it);
	cout << "After remove: " << endl
		 << nums << endl;

	Stack<Laptop> Laptops;
	Laptops.push(Laptop("ASUS", "Vivobook", "Intel Core i7", "SSD", 15, 4, 16, 512, 1200));
    Laptops.push(Laptop("Dell", "Inspiron", "AMD Ryzen 5", "HDD", 14, 6, 8, 256, 800));
    Laptops.push(Laptop("HP", "Pavilion", "Intel Core i5", "SSD", 13, 2, 12, 256, 1000));
    Laptops.push(Laptop("Lenovo", "ThinkPad", "Intel Core i9", "SSD", 15, 8, 32, 1, 2000));
    Laptops.push(Laptop("Acer", "Aspire", "AMD Ryzen 7", "HDD", 17, 6, 16, 1, 1500));
    Laptops.push(Laptop("Apple", "MacBook Pro", "Apple M1", "SSD", 13, 8, 16, 512, 2500));


	cout << Laptops << endl;

	SortedStack<Laptop> lowpriced;

	Laptops.filter(lowpriced, price_filter);

	cout << "Low priced: " << endl
		 << lowpriced << endl;

	return 0;
}

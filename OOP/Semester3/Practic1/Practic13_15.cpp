#pragma warning(disable : 4996) // Вырубает предупреждение про итераторы

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*«Школьник».
Минимальный набор полей: фамилия,
имя, пол, класс, дата рождения, адрес.*/
class Student
{
public:
	string _firstname, _lastname, _address;
	bool _male;
	int _birthday, _grade;

	Student()
	{
		_male = true;
		_birthday = _grade = 0;
	}

	Student(const char *firstname, const char *lastname, const char *address, bool male, int birthday, int grade)
	{
		_firstname = firstname;
		_lastname = lastname;
		_address = address;
		_male = male;
		_birthday = birthday;
		_grade = grade;
	}

	Student(const Student &stud)
	{
		_firstname = stud._firstname;
		_lastname = stud._lastname;
		_address = stud._address;
		_male = stud._male;
		_birthday = stud._birthday;
		_grade = stud._grade;
	}

	~Student() {}

	friend ostream &operator<<(ostream &s, const Student &value);
	friend istream &operator>>(istream &s, Student &value);

	bool operator<(const Student &stud) const
	{
		if (_birthday < stud._birthday)
			return true;

		if (_lastname < stud._lastname)
			return true;

		if (_firstname < stud._firstname)
			return true;

		return false;
	}

	bool operator>(const Student &stud) const
	{
		if (_birthday > stud._birthday)
			return true;

		if (_lastname > stud._lastname)
			return true;

		if (_firstname > stud._firstname)
			return true;

		return false;
	}

	bool operator==(const Student &stud) const
	{
		return _firstname == stud._firstname &&
			   _lastname == stud._lastname &&
			   _birthday == stud._birthday;
	}
};

ostream &operator<<(ostream &stream, const Student &value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

istream &operator>>(istream &stream, Student &value)
{
	return stream >> value._firstname >> value._lastname >> value._address >> value._male >> value._birthday >> value._grade;
}

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
	virtual Element *getNext() const { return _next; }
	virtual void setNext(Element *value) { _next = value; }

	// доступ к полю *_previous
	virtual Element *getPrevious() const { return _previous; }
	virtual void setPrevious(Element *value) { _previous = value; }

	// доступ к полю с хранимой информацией _value
	virtual T getValue() const { return _value; }
	virtual void setValue(T value) { _value = value; }

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
	virtual int count() const { return _count; }

	virtual Element<T> *getBegin() const { return _head; }

	virtual Element<T> *getEnd() const { return _tail; }

	// конструктор без параметров
	LinkedList()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	// чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T> *push_R(T value) = 0;

	// чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual T pop() = 0;

	virtual ~LinkedList()
	{
		// деструктор - освобождение памяти
		Element<T> *previous;
		for (Element<T> *current = _head; current != nullptr;)
		{
			previous = current;
			current = current->getNext();
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

/*Петрусевич, какого хуя тут такие костыли, ты долбаёб?
Надо просто сделать перегрузки функций ввода/ввывода из файла и консоли
для типов ostream и ofstream*/
template <class T>
ofstream &operator<<(ofstream &stream, const LinkedList<T> &obj)
{
	stream << obj._count << "\n";
	for (Element<T> *current = obj.getBegin(); current != nullptr; current = current->getNext())
		stream << current->getValue() << " ";
	return stream;
}

template <class T>
ostream &operator<<(ostream &stream, const LinkedList<T> &obj)
{
	for (Element<T> *current = obj.getBegin(); current != nullptr; current = current->getNext())
		stream << current->getValue() << "\n";

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

	Element<T> *getElement() const { return _element; }
	void setElement(Element<T> *element) { _element = element; }

	// получить значение
	const T &operator*() const
	{
		if (_element == nullptr)
			throw runtime_error("Invalid pointer");

		return _element->getValue();
	}
	// перемещение с помощью итераторов
	ListIterator &operator++()
	{
		if(_element)
			_element = _element->getNext();

		return *this;
	} // Префиксный ++
	ListIterator operator++(int)
	{
		ListIterator it(*this);

		if(_element)
			_element = _element->getNext();

		return it;
	} // Постфиксный ++
	ListIterator &operator--()
	{
		if(_element)
			_element = _element->getPrevious();

		return *this;
	} // Префиксный --
	ListIterator operator--(int)
	{
		ListIterator it(*this);

		if(_element)
			_element = _element->getPrevious();

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
	Element<T> *push_R(T value) // To the end
	{
		Element<T> *elem = new Element<T>(value);

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

	ListIterator<T> push(T value)
	{
		return ListIterator<T>(this->push_R(value));
	}

	T pop()
	{
		T value;

		value = this->_tail->getValue();

		Element<T> *prev = this->_tail->getPrevious();
		prev->setNext(nullptr);

		this->_tail->setPrevious(nullptr);
		this->_tail = prev;
		this->_count--;

		return value;
	}

	ListIterator<T> insert(Element<T> *current, T value)
	{
		if (this->_tail == current)
			return Stack<T>::push(value);

		Element<T> *elem = new Element<T>(value);

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

		return ListIterator<T>(elem);
	}

	// push, pop, remove, insert
	virtual ListIterator<T> remove(ListIterator<T> it)
	{
		if (it.getElement() == nullptr)
		{
			pop();
			return it;
		}
		Element<T> *elem = it.getElement();
		it--;
		remove(elem);
		return it;
	}

	virtual Element<T> *remove(Element<T> *elem)
	{
		Element<T> *prev = elem->getPrevious(), *next = elem->getNext();

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
		for (Element<T> *elem = this->_head; elem != nullptr; elem = elem->getNext())
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
	SortedStack() : Stack<T>() {}

	virtual ListIterator<T> push(T value)
	{
		if (this->_head == nullptr || this->_tail->getValue() < value)
			return Stack<T>::push(value);

		for (Element<T> *element = this->_head; element != nullptr; element = element->getNext())
			if (value < element->getValue())
				return Stack<T>::insert(element->getPrevious(), value);

		return ListIterator<T>(nullptr);
	}
};

bool older_filter(Student stud)
{
	return stud._birthday <= 2004;
}

int main()
{
	SortedStack<int> nums;

	for (int i = 0; i < 25; i += 3)
		nums.push(i % 7);

	cout << "count: " << nums.count() << endl
		 << nums << endl
		 << "popped: " << nums.pop() << endl;

	ListIterator<int> num_it = nums.begin();
	num_it++;
	num_it++;
	num_it++;
	nums.remove(num_it);
	cout << "After remove: " << endl
		 << nums << endl;

	Stack<Student> students;
	students.push(Student("Danya", "Lykov", "Branks", true, 2007, 8));
	students.push(Student("Vika", "Kuslieva", "Moscow", false, 2006, 7));
	students.push(Student("Sanya", "Lazarev", "Moscow", true, 2005, 6));
	students.push(Student("Yarik", "Malysh", "Zamkad", true, 2004, 5));
	students.push(Student("Nastya", "Pak", "kiev", false, 2003, 4));
	cout << students << endl;

	SortedStack<Student> olders;

	students.filter(olders, older_filter);

	cout << "Olders: " << endl
		 << olders << endl;

	return 0;
}

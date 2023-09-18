#pragma warning(disable : 4996) //Вырубает предупреждение про итераторы

#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* _next;
	Element* _previous;

	//информация, хранимая в поле
	T _value;
public:
	//доступ к полю *_next
	virtual Element* GetNext() const { return _next; }
	virtual void SetNext(Element* value) { _next = value; }

	//доступ к полю *_previous
	virtual Element* GetPrevious() const { return _previous; }
	virtual void SetPrevious(Element* value) { _previous = value; }

	//доступ к полю с хранимой информацией _value
	virtual T GetValue() const { return _value; }
	virtual void SetValue(T value) { _value = value; }

	template<class T1> friend ostream& operator << (ostream& ustream,const Element<T1>& obj);

	Element(T value) { _value = value; _next = _previous = nullptr; }
};

template<class T>
ostream& operator << (ostream& ustream,const Element<T>& obj)
{
	ustream << obj._value;
	return ustream;
}

template <class T>
class LinkedList
{
protected:
	//достаточно хранить начало и конец
	Element<T>* _head;
	Element<T>* _tail;
	//для удобства храним количество элементов
	int _count;

public:
	virtual int Count() const { return _count; }

	virtual Element<T>* GetBegin() const { return _head; }

	virtual Element<T>* GetEnd() const { return _tail; }

	//конструктор без параметров
	LinkedList()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* Push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual T Pop() = 0;

	virtual ~LinkedList()
	{
		//деструктор - освобождение памяти
		
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i) const
	{
		//индексация
		if (i < 0 || i > _count) return nullptr;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = _head;
		for (int k = 0; k < i; k++)
			cur = cur->GetNext();

		return cur;
	}

	template<class T1> friend ofstream& operator << (ofstream& ustream,const LinkedList<T1>& obj);
	template<class T1> friend ostream& operator << (ostream& ustream,const LinkedList<T1>& obj);
	template<class T1> friend istream& operator >> (istream& ustream, LinkedList<T1>& obj);
};

/*Петрусевич, какого хуя тут такие костыли, ты долбаёб?
Надо просто сделать перегрузки функций ввода/ввывода из файла и консоли
для типов ostream и ofstream*/
template<class T>
ofstream& operator << (ofstream& ustream,const LinkedList<T>& obj)
{
	ustream << obj._count << "\n";
	for (Element<T>* current = obj.GetBegin(); current != nullptr; current = current->GetNext())
		ustream << current->GetValue() << " ";
	return ustream;
}

template<class T>
ostream& operator << (ostream& ustream,const LinkedList<T>& obj)
{
	ustream << "\nLength: " << obj._count << "\n";
	int i = 0;
	for (Element<T>* current = obj.GetBegin(); current != nullptr; current = current->GetNext(), i++)
		ustream << "arr[" << i << "] = " << current->GetValue() << "\n";

	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedList<T>& obj)
{
	//чтение из файла и консоли совпадают
	ustream >> obj._count;
	//здесь надо очистить память под obj, установить obj.num = 0
	
	for (int i = 0; i < obj._count; i++)
	{
		T value;
		ustream >> value;
		obj.Push(value);
	}
	return ustream;
}

//дописать класс итератора по списку
template<typename T>
class ListIterator : public iterator<input_iterator_tag, T>
{
public:
	//конструкторы
	ListIterator() { _pointer = nullptr; }
	ListIterator(Element<T>* p) { _pointer = p; }
	ListIterator(const ListIterator& it) { _pointer = it._pointer; }

	//методы работы с итераторами
	//присваивание
	ListIterator& operator=(const ListIterator& it) { _pointer = it._pointer; return *this; }
	ListIterator& operator=(Element<T>* p) { _pointer = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const& other) const { return _pointer != other._pointer; }
	bool operator==(ListIterator const& other) const { return _pointer == other._pointer; }

	//получить значение
	Element<T>& operator*() const
	{
		if(_pointer == nullptr)
			throw std::runtime_error("Invalid pointer");

		return *_pointer;
	}
	//перемещение с помощью итераторов
	ListIterator& operator++() { _pointer = _pointer->GetNext();  return *this; } //Префиксный ++
	ListIterator& operator++(int v) { _pointer = _pointer->GetNext(); return *this; } //Постфиксный ++
	ListIterator& operator--() { _pointer = _pointer->GetPrevious();  return *this; } //Префиксный --
	ListIterator& operator--(int v) { _pointer = _pointer->GetPrevious(); return *this; } //Постфиксный --

private:
	//текущий элемент
	Element<T>* _pointer;
};

/*Постройте шаблон класса двусвязного списка путём наследования от
класса IteratedLinkedList.*/

//класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedList<T>
{
public:
	IteratedLinkedList() : LinkedList<T>() { }
	virtual ~IteratedLinkedList() { }

	ListIterator<T> begin() { ListIterator<T> it = LinkedList<T>::_head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedList<T>::_tail; return it; }
};

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	Stack() : IteratedLinkedList<T>() { }
	/*Реализуйте функции добавления элемента push() и
	удаления элемента pop() в классе-наследнике D (для четных вариантов D –
	Стек, для нечетных – Очередь) согласно схеме: для класса Стек элементы
	добавляются в конец, извлекаются с конца; для класса Очереди элементы
	добавляются в конец, извлекаются с начала. */
	
	Element<T>* Push(T obj) //To the end
	{
		Element<T>* x = new Element<T>(obj);

		if (this->_tail != nullptr)
		{
			this->_tail->SetNext(x);
			x->SetPrevious(this->_tail);
			this->_tail = x;
		}
		else
		{
			this->_head = x;
			this->_tail = this->_head;
		}
		this->_count++;
		return this->_tail;
	}
	T Pop()
	{
		T x;
		Element<T>* prev;
		x = this->_tail->GetValue();
		prev = this->_tail->GetPrevious();
		prev->SetNext(nullptr);
		this->_tail->SetPrevious(nullptr);
		this->_tail = prev;
		this->_count--;
		return x;
	}

	ListIterator<T> Insert(T val, ListIterator<T> it)
	{
		Element<T>* cur = it._pointer;
		Element<T>* n = new Element<T>(val);
		if (this->_tail == cur)
		{
			Push(val);
			return this->end();
		}
		if (it == nullptr)
		{
			n->SetNext(this->_head);
			this->_head->SetPrevious(n);
			this->_head = n;
			return this->begin();
		}

		n->SetNext(cur->GetNext());
		cur->SetNext(n);
		n->SetPrevious(cur);
		n->GetNext()->SetPrevious(n);
		this->num++;
		return it++;
	}

	//Push, Pop, Remove, Insert
};

int main()
{

	Stack<int> S;
	S.Push(1);
	cout << S.Count();
	S.Push(2);
	cout << S.Count();
	S.Push(3);
	cout << S.Count();
	cout << S;
	cout << "\n";
	int e1 = S.Pop();
	cout << "\nElement = " << e1;
	cout << S;
	cout << "\nIndex in the Stack class: " << S[1]->GetValue();

	cout << S;
	cout << "\nIterators:\n";
	ListIterator<int> iterator = S.begin();
	while (iterator != S.end())
	{
		cout << *iterator << " ";
		iterator++;
	}
	cout << *iterator << " ";

	char c; cin >> c;
	return 0;
}

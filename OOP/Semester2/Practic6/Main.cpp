#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

/*
Структура «Школьник».
Минимальный набор полей: фамилия, имя, пол, класс, дата
рождения, адрес.
*/
class Student
{
public:
	std::string _firstname, _lastname, _address;
	bool _male;
	int _birthday,_grade;

	Student()
	{
		_male = 0;
		_birthday = 0;
		_grade = 0;
	}

	Student(const char* firstname,const char* lastname,const char* address,bool male, int birthday,int grade)
	{
		_firstname = firstname;
		_lastname = lastname;
		_address = address;
		_male = male;
		_birthday = birthday;
		_grade = grade;
	}

	Student(const Student& stud)
	{
		_firstname = stud._firstname;
		_lastname = stud._lastname;
		_address = stud._address;
		_male = stud._male;
		_birthday = stud._birthday;
		_grade = stud._grade;
	}

	~Student() { }

	friend std::ostream& operator<<(std::ostream& s, Student& value);
	friend std::istream& operator>>(std::istream& s, Student& value);

	bool operator==(Student& stud)
	{
		return _firstname == stud._firstname &&
			_lastname == stud._lastname &&
			_address == stud._address &&
			_male == stud._male &&
			_birthday == stud._birthday &&
			_grade == stud._grade;
	}
};

std::ostream& operator<<(std::ostream& stream, Student& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

std::istream& operator>>(std::istream& stream, Student& value)
{
	return stream >> value._firstname >> value._lastname >> value._address >> value._male >> value._birthday >> value._grade;
}

template<class T>
class LinkedList;

template<class T>
class Element
{
protected:
	Element* _next;
	Element* _previous;
	T _info;
public:

	Element(T data)
	{
		_next = _previous = nullptr;
		_info = data;
	}

	Element(Element* next, Element* prev, T data)
	{
		_next = next;
		_previous = prev;
		_info = data;
	}

	// Функцию фильтра и поиска реализовать в итеративной и рекурсивной формах
	virtual Element<T>* FindRecursive(T value)
	{
		if(GetInfo() == value)
			return this;

		if(GetNext() != nullptr)
			 return GetNext()->FindRecursive(value);

		return nullptr;
	}

	virtual void FilterRecursive(bool (*filter)(T),LinkedList<T>* list)
	{
		if(filter(GetInfo()))
			list->Push(GetInfo());

		if(GetNext() != nullptr)
			GetNext()->FilterRecursive(filter,list);
	}

	T GetInfo() { return _info; }
	void SetInfo(T value) { _info = value; }

	Element<T>* GetNext() { return _next; }
	void SetNext(Element<T>* value) { _next = value; }

	Element<T>* GetPrevious() { return _previous; }
	void SetPrevious(Element<T>* value) { _previous = value; }

	template<class T1>
	friend std::ostream& operator<<(std::ostream& s, Element<T1>& el);
};

// Информация в элемент структуры вводится со стандартного потока ввода (предусмотреть автоматическое заполнение).
template<class T>
std::ostream& operator<<(std::ostream& s, Element<T>& el)
{
	s << el._info;
	return s;
}

// Реализовать структуру для хранения представленных в задании данных (класс, представляющий Связный список, является шаблоном класса)
template<class T>
class LinkedList
{
// Поля класса должны быть защищёнными (protected).
protected:
	Element<T>* _head;
	Element<T>* _tail;
	int _count;

// Ввести открытый интерфейс (public) 
public:
	LinkedList()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	LinkedList(T* arr, int len)
	{
		for(int i = 0;i < len;i++)
			this->Push(arr[i]);
	}

	virtual Element<T>* Pop() = 0;
	virtual Element<T>* Push(T value) = 0;

	Element<T>& operator[](int index)
	{
		//if(index<0 || index>=_count) throw ?;

		Element<T>* current = _head;

		for (int i = 0;
			current != nullptr && i < index;
			current = current->GetNext(), i++);

		return *current;
	}

	// поиска элемента find() по значению
	virtual Element<T>* Find(T value)
	{
		for (Element<T>* current = _head; current != nullptr; current = current->GetNext())
			if(current->GetInfo() == value)
				return current;

		return nullptr;
	}

	// Реализовать указанный вид поиска: под функцией фильтра предполагается поиск элементов
	// Фильтр возвращает новый список элементов, удовлетворяющих условию.
	virtual void Filter(LinkedList<T>* list,bool (*filter)(T))
	{
		for (Element<T>* current = _head; current != nullptr; current = current->GetNext())
			if(filter(current->GetInfo()))
				list->Push(current->GetInfo());
	}

	virtual void FilterRecursive(bool (*filter)(T),LinkedList<T>* list)
	{
		if(_head != nullptr)
			_head->FilterRecursive(filter,list);
	}

	virtual bool IsEmpty() { return (LinkedList<T>::_count == 0); }

	virtual void Load(std::ifstream& stream)
	{
		int count;
		stream >> count;

		for(int i = 0;i < count;i++)
		{
			T data;
			stream >> data;
			this->Push(data);
		}
	}

	virtual void Save(std::ofstream& stream)
	{
		stream << this->_count << ' ';
		
		for (Element<T>* current = _head; current != nullptr; current = current->GetNext())
		{
			T info = current->GetInfo();
			stream << info << ' ';
		}
	}

	template<class T1>
	friend std::ostream& operator<<(std::ostream& s, LinkedList<T1>& el);

	virtual ~LinkedList()
	{
		Element<T>* previous;
		for (Element<T>* current = _head; current != nullptr;)
		{
			previous = current;
			current = current->GetNext();
			delete previous;
		}
	}

};

// Вывод в 16-ричной системе счисления, с символом заполнения ‘_’ и шириной поля в 10 символов при выводе числа
std::ostream& special_manip(std::ostream& stream)
{
    return stream << std::hex << std::setfill('_') << std::setw(10);
}

template<class T1>
std::ostream& operator<<(std::ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;

	// Свой манипулятор
	for (current = el._head; current != nullptr; current = current->GetNext())
		s << special_manip << *current << "; ";

	return s;
}

// Унаследовать класс односвязного списка от базового класса Связный список с ключевым словом public
template<class T>
class SingleLinkedList : public LinkedList<T>
{
public:
	using LinkedList<T>::_head;
	using LinkedList<T>::_tail;
	using LinkedList<T>::_count;

	SingleLinkedList() : LinkedList<T>() {};
	
	// Переопределить функции push() и pop() – для добавления и извлечения элементов из списка в каждом классе
	virtual Element<T>* Pop() override
	{
		Element<T>* res = LinkedList<T>::_tail;

		if (LinkedList<T>::_tail == nullptr) return nullptr;

		if (LinkedList<T>::_head == LinkedList<T>::_tail)
		{
			LinkedList<T>::_count = 0;
			res = LinkedList<T>::_tail;
			LinkedList<T>::_head = LinkedList<T>::_tail = nullptr;
			return res;
		}

		Element<T>* current;
		for (current = LinkedList<T>::_head; current->GetNext() != LinkedList<T>::_tail; current = current->GetNext());
		current->SetNext(nullptr);
		LinkedList<T>::_count--;
		LinkedList<T>::_tail = current;
		return res;
	}

	virtual Element<T>* Push(T value) override
	{
		Element<T>* newElem = new Element<T>(value);
		if (LinkedList<T>::_tail != nullptr)
		{
			LinkedList<T>::_tail->SetNext(newElem);
			LinkedList<T>::_tail = LinkedList<T>::_tail->GetNext();
		}
		else
			LinkedList<T>::_head = LinkedList<T>::_tail = newElem;

		LinkedList<T>::_count++;
		return LinkedList<T>::_tail;
	}

	// Написать функцию вставки нового элемента в произвольное место списка insert(),
	virtual Element<T>* Insert(T value, Element<T>* previous = nullptr)
	{
		if (previous == nullptr) return Push(value);

		Element<T>* inserted = new Element<T>(value);
		Element<T>* next = previous->GetNext();

		previous->SetNext(inserted);
		inserted->SetNext(next);

		LinkedList<T>::_count++;

		return inserted;
	}

	// удаления remove() 
	virtual Element<T>* Remove(T value, Element<T>* marked = nullptr)
	{
		if (marked == nullptr) return nullptr;

		for(Element<T>* current = _head;current != nullptr;current = current->GetNext())
			if(current->GetNext() == marked)
			{
				current->SetNext(marked->GetNext());
				return marked;
			}

		return nullptr;
	}

	virtual ~SingleLinkedList() { }
};

// унаследовать класс двусвязного списка от базового класса Односвязный список с ключевым словом public
template<class T>
class DoubleLinkedList : public SingleLinkedList<T>
{
public:
	using LinkedList<T>::_head;
	using LinkedList<T>::_tail;
	using LinkedList<T>::_count;

	DoubleLinkedList() : SingleLinkedList<T>() {};
	
	// при необходимости переопределять функции в производном классе, но по возможности вызывать из них функции базового класса, не дублируя код
	virtual Element<T>* Pop() override
	{
		if (_head == _tail)
			return SingleLinkedList<T>::Pop();

		Element<T>* res = _head;
		Element<T>* next = _head->GetNext();

		_head = next;
		next->SetPrevious(nullptr);

		_count--;

		return res;
	}

	virtual Element<T>* Push(T value) override
	{
		Element<T>* head_before = _head;
		_head = new Element<T>(value);
		_head->SetNext(head_before);

		_count++;

		return _head;
	}

	virtual Element<T>* Insert(T value, Element<T>* previous = nullptr) override
	{
		Element<T>* inserted = SingleLinkedList<T>::Insert(value, previous);

		if (_head != _tail)
		{
			if(inserted->GetNext() != nullptr)
				inserted->GetNext()->SetPrevious(inserted);

			inserted->SetPrevious(previous);
		}

		return inserted;
	}

	virtual Element<T>* Remove(T value, Element<T>* marked = nullptr) override
	{
		if (marked == nullptr)
			return nullptr;

		Element<T> *previous = marked->GetPrevious(),*next = marked->GetNext();

		if(previous != nullptr)
			previous->SetNext(next);

		if(next != nullptr)
			next->SetPrevious(previous);

		return marked;
	}
	
	virtual ~DoubleLinkedList() { }
};

class StudentLinkedList : public DoubleLinkedList<Student>
{
public:
	virtual Element<Student>* FindStudent(const char* lastname)
	{
		for (Element<Student>* current = _head; current != nullptr; current = current->GetNext())
			if(current->GetInfo()._lastname.compare(lastname) == 0)
				return current;

		return nullptr;
	}

	// Реализовать указанный вид поиска: под функцией фильтра предполагается поиск элементов
	// Фильтр возвращает новый список элементов, удовлетворяющих условию.
	virtual void FilterStudent(StudentLinkedList* list,int startYear)
	{
		for (Element<Student>* current = _head; current != nullptr; current = current->GetNext())
			if(current->GetInfo()._birthday >= startYear)
				list->Push(current->GetInfo());
	}

	virtual ~StudentLinkedList() { }
};

bool int_filter(int x)
{
	return x % 2 == 0;
}

int main(int argc,char* argv[])
{
	LinkedList<int>* list = new SingleLinkedList<int>();

	list->Push(1);
	list->Push(2);

	std::cout << *list << std::endl;

	std::ofstream test1("test.txt");
	list->Save(test1);
	test1.close();

	delete list;

	LinkedList<int>* list11 = new SingleLinkedList<int>();

	std::ifstream test2("test.txt");
	list11->Load(test2);
	test2.close();

	std::cout << "Loaded ints: " << *list11 << std::endl;

	LinkedList<int>* list2 = new SingleLinkedList<int>();
	
	list2->Push(3);
	list2->Push(4);

	SingleLinkedList<int> list4;

	list2->FilterRecursive(int_filter,&list4);
	
	std::cout << "Filtered ints: " << list4 << std::endl;

	SingleLinkedList<int>* list3 = dynamic_cast<SingleLinkedList<int>*>(list2);

	std::cout << *list3 << std::endl;

	delete list3;

	StudentLinkedList students,filtered;

	students.Push(Student("Danya","Lykov","Branks",true,2007,8));
	students.Push(Student("Vika","Kuslieva","Moscow",false,2006,7));
	students.Push(Student("Sanya","Lazarev","Moscow",true,2005,6));
	students.Push(Student("Yarik","Malysh","Zamkad",true,2004,5));
	students.Push(Student("Nastya","Pak","kiev",false,2003,4));

	std::cout << "Students:" << std::endl << students << std::endl;

	students.FilterStudent(&filtered,2005);

	std::cout << "Filter >= 2005: " << std::endl << filtered << std::endl;

	std::cout << "Find Malysh: " << std::endl << *students.FindStudent("Malysh") << std::endl;

	return 0;
}

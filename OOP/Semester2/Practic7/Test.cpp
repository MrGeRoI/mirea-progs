#include <string>

#include <cmath>

#include "AVLTree.hpp"
#include "Heap.hpp"

template <class T>
void print(T val)
{
	std::cout << val << "\n";
}

class Human
{
public:
	// фамилия, имя, пол, рост, возраст, вес, дата рождения, телефон, адрес.
	std::string _lastname,_firstname,_number,_address;
	int _height,_age,_weight,_birthday;
	bool _male;

	Human()
	{
		_male = true;
		_height = _age = _weight = _birthday = 0;
	}

	Human(const char* firstname,const char* lastname,const char* number,const char* address,bool male,int height,int age,int weight, int birthday)
	{
		_firstname = firstname;
		_lastname = lastname;
		_number = number;
		_address = address;
		_male = male;
		_height = height;
		_age = age;
		_weight = weight;
		_birthday = birthday;
	}

	Human(const Human& hum)
	{
		_firstname = hum._firstname;
		_lastname = hum._lastname;
		_number = hum._number;
		_address = hum._address;
		_male = hum._male;
		_height = hum._height;
		_age = hum._age;
		_weight = hum._weight;
		_birthday = hum._birthday;
	}

	~Human() { }

	friend std::ostream& operator<<(std::ostream& s, const Human& value);
	friend std::istream& operator>>(std::istream& s, Human& value);

	bool operator<(const Human& hum);
	bool operator>(const Human& hum);

	bool operator==(const Human& hum)
	{
		return _firstname == hum._firstname &&
			_lastname == hum._lastname;
	}
};

std::ostream& operator<<(std::ostream& stream, const Human& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._number << ' ' << value._address << ' ' << value._male << ' '  << value._height << ' ' << value._age << ' ' << value._weight << ' ' << value._birthday;
}

std::istream& operator>>(std::istream& stream, Human& value)
{
	return stream >> value._firstname >> value._lastname >> value._number >> value._address >> value._male >> value._height >> value._age >> value._weight >> value._birthday;
}

bool Human::operator<(const Human& hum)
{
	if(_age != hum._age)
		return _age < hum._age;

	if(_height != hum._height)
		return _height < hum._height;

	if(_weight != hum._weight)
		return _weight < hum._weight;

	return false;
};

bool Human::operator>(const Human& hum)
{
	if(_age != hum._age)
		return _age > hum._age;

	if(_height != hum._height)
		return _height > hum._height;

	if(_weight != hum._weight)
		return _weight > hum._weight;

	return false;
}

class Goverment
{
public:
	std::string _name,_capital,_language;
	int _population,_area;

	Goverment()
	{
		_population = _area = 0;
	}

	Goverment(const char* name,const char* capital,const char* language, int population,int area)
	{
		_name = name;
		_capital = capital;
		_language = language;

		_population = population;
		_area = area;
	}

	Goverment(const Goverment& gov)
	{
		_name = gov._name;
		_capital = gov._capital;
		_language = gov._language;

		_population = gov._population;
		_area = gov._area;
	}

	friend std::ostream& operator<<(std::ostream& s,const Goverment& value);
	friend std::istream& operator>>(std::istream& s, Goverment& value);

	// Размещение в дереве по ПОПУЛЯЦИИ (остальные поля не важны для сортировки)
	bool operator<(const Goverment& gov) { return _population < gov._population; };
	bool operator>(const Goverment& gov) { return _population > gov._population; };

	bool operator==(const Goverment& gov) { return _name == gov._name; }
};

std::ostream& operator<<(std::ostream& stream,const Goverment& value)
{
	return stream << value._name << ' ' << value._capital << ' ' << value._language << ' ' << value._population << ' ' << value._area;
}

std::istream& operator>>(std::istream& stream, Goverment& value)
{
	return stream >> value._name >> value._capital >> value._language >> value._population >> value._area;
}

template<class T>
void print(Node<T>* N)
{
	T data = N->GetData();
	std::cout << std::endl << data;
}

int main()
{
	Tree<double> T;
	for(int i = 0; i < 15; i++) T.Push((int)(100 * cos(15 * double(i))));
	std::cout << T << std::endl;

	AVLTree<Goverment> govers;

	govers.Push(Goverment("Russia","Moscow","Russian",100,999));
	govers.Push(Goverment("Belarus","Minsk","Russian",20,150));
	govers.Push(Goverment("Ukraine","Kiev","Russian",15,100));
	govers.Push(Goverment("USA","Washington","English",150,500));
	govers.Push(Goverment("China","Pekin","Chinese",7777,30));

	govers.InOrder(print); std::cout << std::endl;

	Heap<int> heap;

	try
	{
		heap.Push(1);
		heap.Push(-1);
		heap.Push(-2);
		heap.Push(2);
		heap.Push(5);

		heap.Push(6);
		heap.Push(-3);
		heap.Push(-4);
		heap.Push(4);
		heap.Push(3);
	}
	catch(const HeapExcepction& e)
	{
		std::cerr << e.what() << std::endl;
	}

	heap.Remove(heap.GetCount() - 1);
	
	std::cout << "\n-----\nStraight:";
	void(*f_ptr)(int); f_ptr = print;
	heap.Straight(f_ptr);
	
	std::cout << "\n-----\nExtractMin:";

	while (heap.GetCount() > 0)
		std::cout << heap.ExtractMin() << std::endl;

	Heap<Human> humans;

	humans.Push(Human("Danya","Lykov", "+7999999999", "Vladivostok", true, 173, 18, 63, 2004));
    humans.Push(Human("Yarik", "Malysh", "+75555555555", "Krym", true, 180, 18, 75, 2004));
    humans.Push(Human("Vika", "Kuslieva", "+73333333333", "Moscow", false, 171, 18, 57, 2004));
    humans.Push(Human("Sasha", "Lazarev", "+72222222", "Krym", true, 172, 19, 62, 2004));
    humans.Push(Human("Nastya", "Pak", "+7666666666", "Saint-Petersburg", false, 160, 18, 46, 2004));
	
	std::cout << "Sorted humans:" << std::endl;

	while(humans.GetCount() > 0)
		std::cout << humans.ExtractMin() << std::endl;

	return 0;
}
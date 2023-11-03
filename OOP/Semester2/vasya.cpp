#include <string>

#include <cmath>

using namespace std;

class Airplane
{
public:
	// Минимальный набор полей: название, производитель, вместимость, дальность полета, максимальная скорость.
	string _name,_company;
	int _capacity,_far,_speed;

	Airplane()
	{
		_capacity = _far = _speed = 0;
	}

	Airplane(const char* name,const char* company,int capacity,int far,int speed)
	{
		_name = name;
		_company = company;

		_capacity = capacity;
		_far = far;
		_speed = speed;
	}

	Airplane(const Airplane& plane)
	{
		_name = plane._name;
		_company = plane._company;
		
		_capacity = plane._capacity;
		_far = plane._far;
		_speed = plane._speed;
	}

	~Airplane() { }

	friend ostream& operator<<(ostream& s, const Airplane& value);
	friend istream& operator>>(istream& s, Airplane& value);

	bool operator<(const Airplane& hum);
	bool operator>(const Airplane& hum);

	bool operator==(const Airplane& hum)
	{
		return _name == hum._name &&
			_company == hum._company;
	}
};

ostream& operator<<(ostream& stream, const Airplane& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._number << ' ' << value._address << ' ' << value._male << ' '  << value._height << ' ' << value._age << ' ' << value._weight << ' ' << value._birthday;
}

istream& operator>>(istream& stream, Airplane& value)
{
	return stream >> value._firstname >> value._lastname >> value._number >> value._address >> value._male >> value._height >> value._age >> value._weight >> value._birthday;
}

bool Airplane::operator<(const Airplane& hum)
{
	if(_age != hum._age)
		return _age < hum._age;

	if(_height != hum._height)
		return _height < hum._height;

	if(_weight != hum._weight)
		return _weight < hum._weight;

	return false;
};

bool Airplane::operator>(const Airplane& hum)
{
	if(_age != hum._age)
		return _age > hum._age;

	if(_height != hum._height)
		return _height > hum._height;

	if(_weight != hum._weight)
		return _weight > hum._weight;

	return false;
}

template<class T>
void print(Node<T>* N)
{
	T data = N->GetData();
	cout << endl << data;
}

int main()
{
	Tree<double> T;
	for(int i = 0; i < 15; i++) T.Push((int)(100 * cos(15 * double(i))));
	cout << T << endl;

	AVLTree<Goverment> govers;

	govers.Push(Goverment("Russia","Moscow","Russian",100,999));
	govers.Push(Goverment("Belarus","Minsk","Russian",20,150));
	govers.Push(Goverment("Ukraine","Kiev","Russian",15,100));
	govers.Push(Goverment("USA","Washington","English",150,500));
	govers.Push(Goverment("China","Pekin","Chinese",7777,30));

	govers.InOrder(print); cout << endl;

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
		cerr << e.what() << endl;
	}

	heap.Remove(heap.GetCount() - 1);
	
	cout << "\n-----\nStraight:";
	void(*f_ptr)(int); f_ptr = print;
	heap.Straight(f_ptr);
	
	cout << "\n-----\nExtractMin:";

	while (heap.GetCount() > 0)
		cout << heap.ExtractMin() << endl;

	Heap<Airplane> humans;

	humans.Push(Airplane("Danya","Lykov", "+7999999999", "Vladivostok", true, 173, 18, 63, 2004));
    humans.Push(Airplane("Yarik", "Malysh", "+75555555555", "Krym", true, 180, 18, 75, 2004));
    humans.Push(Airplane("Vika", "Kuslieva", "+73333333333", "Moscow", false, 171, 18, 57, 2004));
    humans.Push(Airplane("Sasha", "Lazarev", "+72222222", "Krym", true, 172, 19, 62, 2004));
    humans.Push(Airplane("Nastya", "Pak", "+7666666666", "Saint-Petersburg", false, 160, 18, 46, 2004));
	
	cout << "Sorted humans:" << endl;

	while(humans.GetCount() > 0)
		cout << humans.ExtractMin() << endl;

	return 0;
}
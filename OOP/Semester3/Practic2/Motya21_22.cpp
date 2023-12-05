// красно-черное (сблансированное) дерево map, есть интерфейс доступа к значению по ключу

#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <exception>

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

// Постройте функции поиска элемента по значению и по ключу.
template <class K, class V>
V find(const map<K, V> &tree, K key)
{
	typename map<K, V>::const_iterator it = tree.find(key);

	if (it != tree.end())
		return it->second;

	return V();
}

template <class K, class V>
V find(const multimap<K, V> &tree, K key)
{
	typename map<K, V>::const_iterator it = tree.find(key);

	if (it != tree.end())
		return it->second;

	return V();
}

// Постройте функцию вывода содержимого дерева с помощью итераторов
template <class K, class V>
void print(const map<K, V> &tree)
{
	// итератор пробегает по map
	for (typename map<K, V>::const_iterator it = tree.begin(); it != tree.end(); it++)
		// перемещение по списку с помощью итератора, нет операции [i]
		cout << it->first << ": " << it->second << '\n';

	cout << endl;
}

template <class K, class V>
void print(const multimap<K, V> &tree)
{
	for (typename multimap<K, V>::const_iterator it = tree.begin(); it != tree.end(); it++)
		cout << it->first << ": " << it->second << '\n';

	cout << endl;
}

/* Постройте функцию
filter(), которая принимает предикат P и возвращает новое дерево с
объектами, для которых предикат принимает истинное значение (для всех
вариантов условие предиката: значение поля V выше некоторого порога
threshold, в случае хранения нескольких полей достаточно проверить одно из
них) */
template <class K, class V>
map<K, V> filter(const map<K, V> &source, bool (*pred)(V))
{
	map<K, V> result;

	for (pair<K, V> item : source)
		if (pred(item.second))
			result[item.first] = item.second;

	return result;
}

template <class K, class V>
multimap<K, V> filter(const multimap<K, V> &source, bool (*pred)(V))
{
	multimap<K, V> result;

	for (pair<K, V> item : source)
		if (pred(item.second))
			result.insert(item);

	return result;
}

template <class K, class V>
void push(map<K, V> &dest, K key, V value)
{
	// Введите исключения для случаев, когда пользователь пытается добавить новый элемент с ключом, уже присутствующим в дереве.
	if (dest.count(key) > 0)
		throw out_of_range("There is already a key like that");

	dest[key] = value;
}

template <class K, class V>
void push(multimap<K, V> &dest, K key, V value)
{
	dest.insert(pair(key, value));
}

/*Напишите функцию, которая возвращает вектор из различных значений,
которые встречаются в объекте класса map, заполненном при решении задачи
(рекомендуется использовать класс set)*/
template <class K, class V>
set<V> unique(const map<K, V> &source)
{
	set<V> result;

	for (pair<K, V> item : source)
		result.insert(item.second);

	return result;
}

template <class K, class V>
set<V> unique(const multimap<K, V> &source)
{
	set<V> result;

	for (pair<K, V> item : source)
		result.insert(item.second);

	return result;
}

/*Введите
функцию, возвращающую все элементы дерева с одинаковыми ключами
(ключ передаётся в функцию как параметр).*/
template <class K, class V>
list<V> bykey(const multimap<K, V> &source, K key)
{
	typename map<K, V>::const_iterator it = source.find(key);

	if (it == source.end())
		return list<V>();

	list<V> result;

	for (; it != source.end(); it++)
	{
		if (it->first != key)
			return result;

		result.push_back(it->second);
	}

	return result;
}

int main()
{
	map<string, int> marks;

	marks["Petrov"] = 5;
	marks["Ivanov"] = 4;
	marks["Sidorov"] = 5;
	marks["Nikolaev"] = 3;
	marks["Abramov"] = 4;

	cout << "\nMap:\n";
	print(marks);

	map<string, Laptop> laptops;
	laptops["asus"] = Laptop("ASUS", "Vivobook", "Intel Core i7", "SSD", 15, 4, 16, 512, 1200);
	laptops["dell"] = Laptop("Dell", "Inspiron", "AMD Ryzen 5", "HDD", 14, 6, 8, 256, 800);
	laptops["hp"] = Laptop("HP", "Pavilion", "Intel Core i5", "SSD", 13, 2, 12, 256, 1000);
	laptops["lenovo"] = Laptop("Lenovo", "ThinkPad", "Intel Core i9", "SSD", 15, 8, 32, 1, 2000);
	laptops["acer"] = Laptop("Acer", "Aspire", "AMD Ryzen 7", "HDD", 17, 6, 16, 1, 1500);
	laptops["apple"] = Laptop("Apple", "MacBook Pro", "Apple M1", "SSD", 13, 8, 16, 512, 2500);

	cout << "\nStudents:\n";
	print(laptops);

	multimap<string, int> marks2;
	marks2.insert(pair("Petrov", 5));
	marks2.insert(pair("Ivanov", 4));
	marks2.insert(pair("Sidorov", 5));
	marks2.insert(pair("Nikolaev", 3));
	marks2.insert(pair("Abramov", 4));
	marks2.insert(pair("Petrov", 2));

	cout << "\nMultimap:\n";
	print(marks2);

	cout << "\nPetrov:\n";
	for (int n : bykey(marks2, string("Petrov")))
		cout << n << ", \n";

}

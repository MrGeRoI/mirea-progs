//красно-черное (сблансированное) дерево map, есть интерфейс доступа к значению по ключу

#include <map>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

/*«Школьник».
Минимальный набор полей: фамилия,
имя, пол, класс, дата рождения, адрес.*/
class Student
{
public:
	string _firstname, _lastname, _address;
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

	friend ostream& operator << (ostream& s,const Student& value);
	friend istream& operator >> (istream& s, Student& value);

	bool operator < (const Student& stud) const
	{
		if(_birthday < stud._birthday)
			return true;

		if(_lastname < stud._lastname)
			return true;

		if(_firstname < stud._firstname)
			return true;

		return false;
	}

	bool operator > (const Student& stud) const
	{
		if(_birthday > stud._birthday)
			return true;

		if(_lastname > stud._lastname)
			return true;

		if(_firstname > stud._firstname)
			return true;

		return false;
	}

	bool operator == (const Student& stud) const
	{
		return _firstname == stud._firstname &&
			_lastname == stud._lastname &&
			_birthday == stud._birthday;
	}
};

ostream& operator << (ostream& stream,const Student& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

istream& operator >> (istream& stream, Student& value)
{
	return stream >> value._firstname >> value._lastname >> value._address >> value._male >> value._birthday >> value._grade;
}

//Постройте функции поиска элемента по значению и по ключу.
template<class K, class V>
V find(const map<K,V>& tree,K key)
{
	return tree.find(key)->second;
}

template<class K, class V>
V find(const multimap<K,V>& tree,K key)
{
	return tree.find(key)->second;
}

// Постройте функцию вывода содержимого дерева с помощью итераторов
template<class K, class V>
void print(const map<K,V>& tree)
{
	//итератор пробегает по map
	for(typename map<K,V>::const_iterator it = tree.begin();it != tree.end();it++)
		//перемещение по списку с помощью итератора, нет операции [i]
		cout << it->first << ": " << it->second << '\n';

	cout << endl;
}

template<class K, class V>
void print(const multimap<K,V>& tree)
{
	for(typename multimap<K,V>::const_iterator it = tree.begin();it != tree.end();it++)
		cout << it->first << ": " << it->second << '\n';

	cout << endl;
}

/* Постройте функцию
filter(), которая принимает предикат P и возвращает новое дерево с
объектами, для которых предикат принимает истинное значение (для всех
вариантов условие предиката: значение поля V выше некоторого порога
threshold, в случае хранения нескольких полей достаточно проверить одно из
них) */
template<class K, class V>
map<K,V> filter(const map<K,V>& source, bool(*pred)(V))
{
	map<K,V> result;
	
	for(pair<K,V> item : source)
		if(pred(item.second))
			result[item.first] = item.second;

	return result;
}

template<class K, class V>
multimap<K,V> filter(const multimap<K,V>& source, bool(*pred)(V))
{
	multimap<K,V> result;
	
	for(pair<K,V> item : source)
		if(pred(item.second))
			result.insert(item);
		
	return result;
}

template<class K, class V>
void push(map<K,V>& dest,K key,V value)
{
	//Введите исключения для случаев, когда пользователь пытается добавить новый элемент с ключом, уже присутствующим в дереве.
	if(dest.count(key) > 0)
		throw out_of_range("There is already a key like that");

	dest[key] = value;
}

template<class K, class V>
void push(multimap<K,V>& dest,K key,V value)
{
	dest.insert(pair(key,value));
}

/*Напишите функцию, которая возвращает вектор из различных значений,
которые встречаются в объекте класса map, заполненном при решении задачи
(рекомендуется использовать класс set)*/
template<class K, class V>
set<V> unique(const map<K,V>& source)
{
	set<V> result;
	
	for(pair<K,V> item : source)
		result.insert(item.second);

	return result;
}

template<class K, class V>
set<V> unique(const multimap<K,V>& source)
{
	set<V> result;
	
	for(pair<K,V> item : source)
		result.insert(item.second);

	return result;
}

/*Введите
функцию, возвращающую все элементы дерева с одинаковыми ключами
(ключ передаётся в функцию как параметр).*/
template<class K, class V>
vector<V> bykey(const multimap<K,V>& source, K key)
{
	vector<V> result;
	
	for(pair<K,V> item : source)
		if(item.first == key)
			result.push_back(item.second);

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

	map<string,Student> students;
	students["Danaya"] =	Student("Danya","Lykov","Branks",true,2007,8);
	students["Sanya"] =		Student("Sanya","Lazarev","Moscow",true,2005,6);
	students["Yarik"] =		Student("Yarik","Malysh","Zamkad",true,2004,5);
	students["German"] =	Student("German","Zaycev","Krasnodar",true,2004,4);
	students["Senya"] =		Student("Senya","Lenin","Penza",true,2004,3);
	students["Pepsi"] =		Student("Ksusha","Egorova","Zamkad",false,2004,2);

	cout << "\nStudents:\n";
	print(students);

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
	for(int n : bykey(marks2, string("Petrov")))
		cout << n << ", \n";

	//print(students);
}

//красно-черное (сблансированное) дерево map, есть интерфейс доступа к значению по ключу

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <exception>

#include "../Student.hpp"

using namespace std;

//Постройте функции поиска элемента по значению и по ключу.
template<class K, class V>
V find(const map<K,V>& tree,K key)
{
	return tree.find(key)->second;
	/*
	for(typename map<K,V>::const_iterator it = tree.begin();it != tree.end();it++)
		if(it->first == key)
			return it->second;

	return 0;
	*/
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
void push(map<K,V>& dest,K key,V value)
{
	//Введите исключения для случаев, когда пользователь пытается добавить новый элемент с ключом, уже присутствующим в дереве.
	if(dest.count(key) > 0)
		throw out_of_range("There is already a key like that");

	dest[key] = value;
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

	cout << "Find Yarik: " << find(students,string("Yarik")) << endl;
}

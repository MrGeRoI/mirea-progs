#include <map>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <exception>

#include "../Student.hpp"

using namespace std;

template<class K, class V>
V find(const multimap<K,V>& tree,K key)
{
	for(typename multimap<K,V>::const_iterator it = tree.begin();it != tree.end();it++)
		if(it->first == key)
			return it->second;

	return 0;
}

template<class K, class V>
void print(const multimap<K,V>& tree)
{
	for(typename multimap<K,V>::const_iterator it = tree.begin();it != tree.end();it++)
		cout << it->first << ": " << it->second << '\n';

	cout << endl;
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
void push(multimap<K,V>& dest,K key,V value)
{
	dest.insert(pair(key,value));
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
	multimap<string, int> marks;
	marks.insert(pair("Petrov", 5));
	marks.insert(pair("Ivanov", 4));
	marks.insert(pair("Sidorov", 5));
	marks.insert(pair("Nikolaev", 3));
	marks.insert(pair("Abramov", 4));
	marks.insert(pair("Petrov", 2));
	
	cout << "\nMultimap:\n";
	print(marks);

	cout << "\nPetrov:\n";
	for(int n : bykey(marks, string("Petrov")))
		cout << n << ", \n";

	//print(students);
}

#include <list>
#include <string>
#include <iostream>

#include "../Student.hpp"

using namespace std;

//Только числа, кратные 3
bool predict(int x) { return x % 3 == 0; }

/*
	Постройте
	функции добавления push() и удаления pop() элементов таким образом, чтобы
	список оставался отсортированным при выполнении этих операций
	(допустимо удаление из начала контейнера, с конца и из произвольного
	места).
*/
template<class T>
void push(list<T>& lst, T element)
{
	typename list<T>::iterator p;

	for(p = lst.begin();p != lst.end();p++)
		if (*p > element)
			break;
	
	lst.insert(p, element);
}

/*
	Функция pop() должна удалять объект из контейнера и возвращать
	как результат объект с наибольшим приоритетом (определяется по полям,
	указанным в третьем столбце таблицы 1.2: больший приоритет имеет объект
	с большим значением первого поля; если значение первого поля совпадает,
	то сравниваются значения второго поля и так далее). Если больший
	приоритет имеют объекты с меньшим значением поля (упорядоченность по
	возрастанию), это указано в скобках.
*/
template<class T>
T pop(list<T>& lst) 
{
	typename list<T>::iterator end = lst.end();
	end--;
	T val = *end;
	lst.erase(end);
	return val;
}

/*
Постройте функцию filter(), которая принимает предикат P (см.
таблицу 1.1) и возвращает новый список с объектами, для которых предикат
принимает истинное значение
*/
template<class T>
list<T> filter(const list<T>& source, bool(*pred)(T))
{
	list<T> result;
	
	for(T item : source)
		if(pred(item))
			result.push_back(item);

	return result;
}

/*
	Постройте функцию вывода содержимого
	списка с помощью итераторов.
*/
template<class T>
void print(const list<T>& lst)
{
	for(typename list<T>::const_iterator p = lst.begin();p != lst.end();p++)
		cout << *p << '\n';

	cout << endl;
}

int main()
{
	//Постройте связный список (используйте класс list библиотеки STL), который содержит объекты указанного в таблице 1.1 типа T. 
	list<char> lst;

	int i=0;

	for(i=0;i<10;i+=2)
		lst.push_back('A' + i);

	push(lst, 'B'); // Встала на своё место (после A)
	/*A
	B
	C																																						
	E
	G
	I*/
	print(lst);

	char popped = pop(lst);

	cout << "Popped: " << popped << endl; // I

	list<Student> students;
	push(students,Student("Danya","Lykov","Branks",true,2007,8));
	push(students,Student("Vika","Kuslieva","Moscow",false,2006,7));
	push(students,Student("Sanya","Lazarev","Moscow",true,2005,6));
	push(students,Student("Yarik","Malysh","Zamkad",true,2004,5));
	push(students,Student("Nastya","Pak","kiev",false,2003,4));
	print(students);

	list<int> numbers;

	for(int i=0;i<15;i++)
		numbers.push_back(i);

	cout << "Numbers:\n";
	print(numbers); // 0 <= n <= 14

	list<int> predicted = filter(numbers,predict);

	cout << "Predicted:\n";
	print(predicted); // 0 <= 3*k <= 12

	return 0;
}
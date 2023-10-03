#include "../Student.hpp"

#include "LinkedList.hpp"

using namespace std;

bool older_filter(Student stud)
{
	return stud._birthday <= 2004;
}

int main()
{
	SortedStack<int> nums;

	for (int i = 0; i < 25; i += 3)
		nums.Push(i % 7);

	cout << "Count: " << nums.Count() << endl
		 << nums << endl
		 << "Popped: " << nums.Pop() << endl;

	ListIterator<int> num_it = nums.begin();
	num_it++;
	num_it++;
	num_it++;
	nums.Remove(num_it);
	cout << "After remove: " << endl
		 << nums << endl;

	Stack<Student> students;
	students.Push(Student("Danya", "Lykov", "Branks", true, 2007, 8));
	students.Push(Student("Vika", "Kuslieva", "Moscow", false, 2006, 7));
	students.Push(Student("Sanya", "Lazarev", "Moscow", true, 2005, 6));
	students.Push(Student("Yarik", "Malysh", "Zamkad", true, 2004, 5));
	students.Push(Student("Nastya", "Pak", "kiev", false, 2003, 4));
	cout << students << endl;

	SortedStack<Student> olders;

	students.Filter(olders, older_filter);

	cout << "Olders: " << endl
		 << olders << endl;

	return 0;
}

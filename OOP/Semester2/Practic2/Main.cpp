#include <iostream>

#include "MySortedArray.hpp"

void PrintArray(MyArrayParent array)
{
	int capacity = array.GetCapacity();
	int size = array.GetSize();

	for(int i = 0;i < capacity;i++)
		if(i < size)
			std::cout << '[' << i << "]\t" << array.GetComponent(i) << std::endl;
		else
			std::cout << '[' << i << "]\t[_]" << std::endl;
}

int main()
{
	MyArrayParent arr(2);
	arr.Push(1.0);
	arr.Push(2.0);
	std::cout << "before:" << std::endl; PrintArray(arr);
	arr.Push(3.0);
	std::cout << "after:" << std::endl; PrintArray(arr);

	return 0;
}
#include <iostream>
#include <queue>

#include "../Student.hpp"
#include "Heap.hpp"
#include "FibonacciHeap.hpp"

using namespace std;

template<typename T>
void print_queue(T& q)
{
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}

	cout << '\n';
}

int main(int argc, char* argv[])
{
	priority_queue<int> q;
	
	for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 7, 2})
		q.push(n);

	print_queue(q);

	FibonacciHeap<int> tree1;
	tree1.push(1);
	tree1.push(2);
	tree1.push(3);
	tree1.push(4);
	tree1.push(5);
	// for (int i = 0; i < 5; i++)
	// cout<<tree1.removeMaximum()<<" ";
	FibonacciHeap<int> tree2;
	tree2.push(10);
	tree2.push(20);
	tree2.push(30);
	tree2.push(40);
	tree2.push(50);
	tree1.merge(tree2);
	for (int i = 0; i < 10; i++)
		cout << tree1.extractMaximum() << " ";
	cout << "\n";

	return 0;
}
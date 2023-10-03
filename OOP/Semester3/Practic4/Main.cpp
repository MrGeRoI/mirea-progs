#include <string>

#include "../Student.hpp"
#include "SplayTree.hpp"

using namespace std;

template<class K,class V>
void print(Node<K,V>* node)
{
	cout << endl << node->GetKey() << node->GetValue() << endl;
}

int main()
{
	SplayTree<string,Student> tree;

	tree.Push("",)
	return 0;
}
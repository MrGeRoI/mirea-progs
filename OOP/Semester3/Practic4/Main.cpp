#include <string>

#include "SplayTree.hpp"
#include "Residue.hpp"

template<class K,class V>
void print(Node<K,V>* node)
{
	std::cout << std::endl << node->GetKey() << "\tHeight: " << get_height(node);
}

int main()
{
	return 0;
}
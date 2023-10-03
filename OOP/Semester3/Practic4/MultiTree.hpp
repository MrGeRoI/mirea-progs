#include "../Practic2/LinkedList.hpp"

#include "Tree.hpp"

template <class K, class V>
class MultiNode : public Node<V,LinkedList<int,V>>
{
	
};

template<class K,class V>
class MultiTree : public Tree<K,V>
{
public:
	virtual Node<K,V> Push(K key, V value, Node<K, V> *current) override
	{	
		if (current->GetKey() == key)
		{
			Node<K, V>* node = new Node<K, V>(key, value);
			current->SetRight(node);
			node->SetParent(current);
			return node;
		}

		return Tree<K,V>::Push(key, value, current);
	}
};
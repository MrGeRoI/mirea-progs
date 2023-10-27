#pragma once

#include "../Practic2/LinkedList.hpp"

#include "Tree.hpp"

template <class K, class V>
class MultiTree : public Tree<K, V>
{
public:
	virtual Node<K, V> *Push(K key, V value, Node<K, V> *current) override
	{
		if (current->GetKey() == key)
		{
			Node<K, V> *node = new Node<K, V>(key, value);
			current->SetRight(node);
			node->SetParent(current);
			return node;
		}

		return Tree<K, V>::Push(key, value, current);
	}

	virtual Node<K, V> *Push(K key, V value) override { return Push(key, value, Tree<K, V>::_root); }

	virtual IteratedLinkedList<V> operator[](K key) const
	{
		Stack<V> values;

		Node<K, V> *node = (Node<K, V> *)Find(key);

		while (node != nullptr && node->GetKey() == key)
		{
			values.Push(node->GetValue());
			node = node->GetRight();
		}

		return values;
	}
};
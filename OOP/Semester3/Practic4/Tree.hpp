#pragma once

#include <iostream>
#include <fstream>

#include "Node.hpp"

template <class K, class V>
class Tree
{
protected:
	Node<K, V> *_root;

	Node<K, V> *Rotate(Node<K, V> *parent, Node<K, V> *child);

	Node<K, V> *RotateRight(Node<K, V> *node) { return Rotate(node, node->GetRight()); };

	Node<K, V> *RotateLeft(Node<K, V> *node) { return Rotate(node, node->GetLeft()); };

	virtual Node<K, V> *Push(K key, V value, Node<K, V> *current);

public:
	virtual Node<K, V> *GetRoot() const { return _root; }

	Tree<K, V>() { _root = nullptr; }

	virtual Node<K, V> *Push(K key, V value) { Push(key, value, _root); }

	virtual Node<K, V> *Remove(Node<K, V> *node);

	virtual Node<K, V> *Minimum(Node<K, V> *current = nullptr) const;

	virtual Node<K, V> *Maximum(Node<K, V> *current = nullptr) const;

	virtual Node<K, V> *Find(K find) const { return Find(find, _root); }

	virtual Node<K, V> *Find(K key, Node<K, V> *current) const;

	virtual Node<K, V> *Find(bool (*find)(K, V)) const { return Find(find, _root); }

	virtual Node<K, V> *Find(bool (*find)(K, V), Node<K, V> *current) const;

	virtual V operator[](K key) const { return Find(key)->GetValue(); }

	virtual void PreOrder(Node<K, V> *node, void (*func)(Node<K, V> *)) const;

	virtual void InOrder(Node<K, V> *node, void (*func)(Node<K, V> *)) const;

	virtual void PostOrder(Node<K, V> *node, void (*func)(Node<K, V> *)) const;

	virtual void PreOrder(void (*func)(Node<K, V> *)) const { PreOrder(_root, func); }

	virtual void InOrder(void (*func)(Node<K, V> *)) const { InOrder(_root, func); }

	virtual void PostOrder(void (*func)(Node<K, V> *)) const { PostOrder(_root, func); }

	virtual TreeIterator<K, V> begin() { return TreeIterator(Minimum()); }

	virtual TreeIterator<K, V> end() { return TreeIterator(Maximum()); }
};

template <class K, class V>
Node<K, V> *Tree<K, V>::Push(K key, V value, Node<K, V> *current)
{
	if (current == nullptr)
		current = _root;

	if (_root == nullptr)
		return _root = new Node<K, V>(key, value);

	if (current->GetKey() == key)
		return current;

	if (current->GetKey() > key)
	{
		if (current->GetLeft() != nullptr)
			return this->Push(key, value, current->GetLeft());
		else
		{
			Node<K, V> *node = new Node<K, V>(key, value);
			current->SetLeft(node);
			node->SetParent(current);
			return node;
		}
	}

	// if (current->GetKey() < key)
	//{
	if (current->GetRight() != nullptr)
		return Push(key, value, current->GetRight());
	else
	{
		Node<K, V> *node = new Node<K, V>(key, value);
		current->SetRight(node);
		node->SetParent(current);
		return node;
	}
	//}

	return nullptr;
}

template <class K, class V>
Node<K, V> *Tree<K, V>::Remove(Node<K, V> *node)
{
	if (node == nullptr)
		return nullptr;

	if (node == _root)
	{
		_root = nullptr;
		return node;
	}

	Node<K, V> *parent = node->GetParent();

	if (parent == nullptr)
		return node;

	Node<K, V> *replace = nullptr;

	if (node->GetLeft() != nullptr && node->GetRight() != nullptr)
		replace = Tree<K, V>::Minimum(node->GetRight());
	else if (node->GetLeft() == nullptr)
		replace = node->GetRight();
	else /*if(node->GetRight() == nullptr)*/
		replace = node->GetLeft();

	if (parent->GetLeft() == node)
		parent->SetLeft(replace);
	else /*if(parent->GetRight() == node)*/
		parent->SetRight(replace);

	return node;
}

template <class K, class V>
Node<K, V> *Tree<K, V>::Minimum(Node<K, V> *current) const
{
	if (_root == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	while (current->GetLeft() != nullptr)
		current = current->GetLeft();

	return current;
}

template <class K, class V>
Node<K, V> *Tree<K, V>::Maximum(Node<K, V> *current) const
{
	if (_root == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	while (current->GetRight() != nullptr)
		current = current->GetRight();

	return current;
}

template <class K, class V>
Node<K, V> *Tree<K, V>::Rotate(Node<K, V> *parent, Node<K, V> *child)
{
	if (parent == nullptr || child == nullptr)
		return nullptr;

	if (child->GetParent() != parent)
		throw std::invalid_argument("Child is not child of parent");

	Node<K, V> *grand = parent->GetParent();

	if (grand == nullptr)
		Tree<K, V>::_root = child;
	else
	{
		if (grand->GetLeft() == parent)
			grand->SetLeft(child);
		else
			grand->SetRight(child);
	}

	if (parent->GetLeft() == child)
	{
		parent->SetLeft(child->GetRight());
		child->SetRight(parent);

		if (parent->GetLeft() != nullptr)
			parent->GetLeft()->SetParent(parent);
	}
	else
	{
		parent->SetRight(child->GetLeft());
		child->SetLeft(parent);

		if (parent->GetRight() != nullptr)
			parent->GetRight()->SetParent(parent);
	}

	parent->SetParent(child);
	child->SetParent(grand);

	return child;
}

template <class K, class V>
Node<K, V> *Tree<K, V>::Find(K key, Node<K, V> *current) const
{

	if (current == nullptr || current->GetKey() == key)
		return current;

	if (current->GetKey() > key)
		return Find(key, current->GetLeft());
	if (current->GetKey() < key)
		return Find(key, current->GetRight());

	return nullptr;
}

// В функции поиска вместо операции == используйте вызов функции
// сравнения по указателю на функцию, передаваемому в функцию find().
template <class K, class V>
Node<K, V> *Tree<K, V>::Find(bool (*find)(K, V), Node<K, V> *current) const
{
	if (current != nullptr)
		if (find(current->GetKey(), current->GetValue()))
			return current;

	if (current != nullptr && current->GetLeft() != nullptr)
		Find(find, current->GetLeft());

	if (current != nullptr && current->GetRight() != nullptr)
		Find(find, current->GetRight());

	return nullptr;
}
template <class K, class V>
void Tree<K, V>::PreOrder(Node<K, V> *node, void (*func)(Node<K, V> *)) const
{
	if (node != nullptr)
		func(node);

	if (node != nullptr && node->GetLeft() != nullptr)
		PreOrder(node->GetLeft(), func);

	if (node != nullptr && node->GetRight() != nullptr)
		PreOrder(node->GetRight(), func);
}

template <class K, class V>
void Tree<K, V>::InOrder(Node<K, V> *node, void (*func)(Node<K, V> *)) const
{
	if (node != nullptr && node->GetLeft() != nullptr)
		InOrder(node->GetLeft(), func);

	if (node != nullptr)
		func(node);

	if (node != nullptr && node->GetRight() != nullptr)
		InOrder(node->GetRight(), func);
}

template <class K, class V>
void Tree<K, V>::PostOrder(Node<K, V> *node, void (*func)(Node<K, V> *)) const
{
	if (node != nullptr && node->GetLeft() != nullptr)
		PostOrder(node->GetLeft(), func);

	if (node != nullptr && node->GetRight() != nullptr)
		PostOrder(node->GetRight(), func);

	if (node != nullptr)
		func(node);
}

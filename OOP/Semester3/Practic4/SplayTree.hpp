#include "Tree.hpp"
template <class K, class V>
class SplayTree : public Tree<K, V>
{
protected:
	using Tree<K, V>::_root;

	Node<K, V> *Splay(Node<K, V> *node);

public:
	SplayTree<K, V>() : Tree<K, V>() {}

	virtual Node<K, V> *Find(bool (*find)(K, V)) const { return Tree<K, V>::Find(find, Tree<K, V>::_root); };

	virtual Node<K, V> *Find(bool (*find)(K, V), Node<K, V> *current) const;

	virtual Node<K, V> *Find(K key) const override { return Tree<K, V>::Find(key, Tree<K, V>::_root); };

	virtual Node<K, V> *Find(K key, Node<K, V> *current) const override;

	virtual Node<K, V> *Push(K key, V value) override { return Tree<K, V>::Push(key, value); };

	virtual Node<K, V> *Push(Node<K, V> *node) override { return Tree<K, V>::Push(node); };

	virtual Node<K, V> *Push(Node<K, V> *node, Node<K, V> *current) override;

	virtual Node<K, V> *Remove(Node<K, V> *node) override;

	~SplayTree<K, V>(){};
};

template <class K, class V>
Node<K, V> *SplayTree<K, V>::Splay(Node<K, V> *node)
{
	Node<K, V> *parent = node->GetParent();

	if (parent == nullptr)
		return node;

	Node<K, V> *grand = parent->GetParent();

	if (grand == nullptr)
	{

		Tree<K, V>::Rotate(parent, node);
		return node;
	}
	else
	{
		if ((grand->GetLeft() == parent) == (parent->GetLeft() == node))
		{
			Tree<K, V>::Rotate(grand, parent);
			Tree<K, V>::Rotate(parent, node);
		}
		else
		{
			Tree<K, V>::Rotate(parent, node);
			Tree<K, V>::Rotate(grand, node);
		}
	}

	return Splay(node);
}

template <class K, class V>
Node<K, V> *SplayTree<K, V>::Find(K key, Node<K, V> *current) const
{
	Node<K, V> *found = Tree<K, V>::Find(key, current);

	if (found != nullptr)
		Splay(found);

	return found;
}

template <class K, class V>
Node<K, V> *SplayTree<K, V>::Push(Node<K, V> *node, Node<K, V> *current)
{
	Node<K, V> *pushed = Tree<K, V>::Push(node, current);

	if (pushed != nullptr)
		Splay(pushed);

	return pushed;
}

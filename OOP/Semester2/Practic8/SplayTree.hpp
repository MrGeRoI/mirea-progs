#include "Tree.hpp"

/* Моделирование splay-дерева */

// Реализовать набор классов для splay-дерева (включить классы в структуру наследования в практической работе №7)
template<class K,class V>
class SplayTree : public Tree<K,V>
{
protected:
	using Tree<K,V>::_root;

	Node<K,V>* Splay(Node<K,V>* node);
public:
	SplayTree<K,V>() : Tree<K,V>() { }

	virtual Node<K,V>* Find(K key) override { return Tree<K,V>::Find(key); };

	virtual Node<K,V>* Find(K key, Node<K,V>* current) override;

	virtual Node<K,V>* Push(K key, V value) override { return Tree<K,V>::Push(key,value); };

	virtual Node<K,V>* Push(Node<K,V>* node) override { return Tree<K,V>::Push(node); };

	// Реализовать операции создания дерева из множества элементов
	virtual Node<K,V>* Push(Node<K,V>* node, Node<K,V>* current) override;

	virtual Node<K,V>* Remove(Node<K,V>* node) override;

	// Слияние деревьев
	virtual void Join(Tree<K,V>* tree) { Join(tree->GetRoot()); };

	virtual void Join(Node<K,V>* node);

	~SplayTree<K,V>() { };
};

template<class K,class V>
Node<K,V>* SplayTree<K,V>::Splay(Node<K,V>* node)
{
	Node<K,V>* parent = node->GetParent();

	if(parent == nullptr)
		return node;

	Node<K,V>* grand = parent->GetParent();

	if(grand == nullptr)
	{
		// Zig
		Tree<K,V>::Rotate(parent, node);
		return node;
	}
	else
	{
		if( (grand->GetLeft() == parent) == (parent->GetLeft() == node) )
		{
			// ZigZig

			Tree<K,V>::Rotate(grand, parent);
			Tree<K,V>::Rotate(parent, node);
		}
		else
		{
			// ZigZag

			Tree<K,V>::Rotate(parent, node);
			Tree<K,V>::Rotate(grand, node);
		}
	}

	return Splay(node);
}

template<class K,class V>
Node<K,V>* SplayTree<K,V>::Find(K key, Node<K,V>* current)
{
	Node<K,V>* found = Tree<K,V>::Find(key, current);

	if(found != nullptr)
		Splay(found);

	return found;
}

template<class K,class V>
Node<K,V>* SplayTree<K,V>::Push(Node<K,V>* node, Node<K,V>* current)
{
	Node<K,V>* pushed = Tree<K,V>::Push(node, current);

	if(pushed != nullptr)
		Splay(pushed);

	return pushed;
}

template<class K,class V>
void SplayTree<K,V>::Join(Node<K,V>* node)
{
	if(Tree<K,V>::_root == nullptr)
	{
		Tree<K,V>::_root = node;
		return;
	}

	// Инвариант: все элементы текущего дерева меньше элементов node
	Node<K,V>* root = Splay(Tree<K,V>::Maximum());

	// Инвариант: элемент в корне (root) не имеет правого ребёнка
	root->SetRight(node);
	node->SetParent(root);
};

template<class K,class V>
Node<K,V>* SplayTree<K,V>::Remove(Node<K,V>* node)
{
	Splay(node);

	Tree<K,V>::_root = node->GetLeft();
	node->GetLeft()->SetParent(nullptr);

	Join(node->GetRight());

	return node;
};

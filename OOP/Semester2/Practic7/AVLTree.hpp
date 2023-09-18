#include "Tree.hpp"

template<class T>
class AVLTree : public Tree<T>
{
protected:
	//определение разности высот двух поддеревьев
	int BalanceFactor(Node<T>* node);

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void FixHeight(Node<T>* node);

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p);

public:
	//конструктор AVLTree вызывает конструктор базового класса Tree
	AVLTree<T>() : Tree<T>() {}
	
	virtual Node<T>* Push(T data) override { return Tree<T>::Push(data); }

	virtual Node<T>* Push(Node<T>* node) override { return Tree<T>::Push(node, Tree<T>::_root); }

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Push(Node<T>* node, Node<T>* current) override;

	//удаление узла
	virtual Node<T>* Remove(Node<T>* node) override;

	~AVLTree() { };
};

template<class T>
int AVLTree<T>::BalanceFactor(Node<T>* node)
{
	int hl = 0;
	int hr = 0;

	if (node->GetLeft() != nullptr)
		hl = node->GetLeft()->GetHeight();

	if (node->GetRight() != nullptr)
		hr = node->GetRight()->GetHeight();

	return (hr - hl);
}

template<class T>
void AVLTree<T>::FixHeight(Node<T>* node)
{
	int hl = 0;
	int hr = 0;

	if (node->GetLeft() != nullptr)
		hl = node->GetLeft()->GetHeight();

	if (node->GetRight() != nullptr)
		hr = node->GetRight()->GetHeight();

	node->SetHeight((hl > hr ? hl : hr) + 1);
}

template<class T>
Node<T>* AVLTree<T>::Balance(Node<T>* p) // балансировка узла p
{
	FixHeight(p);

	if (BalanceFactor(p) == 2)
	{
		if (BalanceFactor(p->GetRight()) < 0)
			Tree<T>::RotateRight(p->GetRight());

		return Tree<T>::RotateLeft(p);
	}
	if (BalanceFactor(p) == -2)
	{
		if (BalanceFactor(p->GetLeft()) > 0)
			Tree<T>::RotateLeft(p->GetLeft());

		return Tree<T>::RotateRight(p);
	}

	return p; // балансировка не нужна
}

template<class T>
Node<T>* AVLTree<T>::Push(Node<T>* node, Node<T>* current)
{
	//вызываем функцию Push из базового класса
	Node<T>* pushed = Tree<T>::Push(node, current);

	//применяем к добавленному узлу балансировку
	if (current != nullptr)
		return Balance(current);
		
	return pushed;
}

template<class T>
Node<T>* AVLTree<T>::Remove(Node<T>* node)
{
	Node<T>* parent = node->GetParent();

	//вызываем функцию Remove из базового класса
	Tree<T>::Remove(node);
	
	//применяем к удалённому узлу балансировку
	if(parent != nullptr)
		Balance(parent);

	return nullptr;
}
#include <fstream>

#include "Node.hpp"

class TreeExcepction : std::exception
{
public:
	virtual const char* what() const noexcept override { return "TreeExcepction"; };
};

class WrongParentException : TreeExcepction
{
public:
	WrongParentException() { };

	virtual const char* what() const noexcept override { return "WrongParentException"; };
};

template<class K,class V>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<K,V>* _root;

	Node<K,V>* Rotate(Node<K,V>* parent, Node<K,V>* child);

	// Реализовать операции создания дерева из операций поворотов, добавления и удаления узла, слияния деревьев
	// правый поворот вокруг node и его левого узла
	Node<K,V>* RotateRight(Node<K,V>* node) { return Rotate(node,node->GetRight()); };

	// левый поворот вокруг node и его правого узла
	Node<K,V>* RotateLeft(Node<K,V>* node) { return Rotate(node,node->GetLeft()); };

	void Save(std::ofstream& stream);

	void Save(std::ofstream& stream, Node<K,V>* node);

	void Load(std::ifstream& stream);

	void Load(std::ifstream& stream, Node<K,V>* node);

public:
	//доступ к корневому элементу
	virtual Node<K,V>* GetRoot() { return _root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<K,V>() { _root = nullptr; }

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<K,V>* Push(K key, V value) { return Push(new Node<K,V>(key,value)); }

	//функция добавления узла в дерево
	virtual Node<K,V>* Push(Node<K,V>* node) { return Push(node, _root); }

	//рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева, 
	//куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<K,V>* Push(Node<K,V>* node, Node<K,V>* current);

	//Введите функцию удаления узла Remove(), которая принимает указатель на удаляемый узел.
	//удаление узла
	virtual Node<K,V>* Remove(Node<K,V>* node);

	//поиск минимума и максимума в дереве
	virtual Node<K,V>* Minimum(Node<K,V>* current = nullptr);

	virtual Node<K,V>* Maximum(Node<K,V>* current = nullptr);
	
	//поиск узла в дереве
	virtual Node<K,V>* Find(K find) { return Find(find, _root); }

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<K,V>* Find(K key, Node<K,V>* current);

	//Создайте интерфейс для функции поиска в виде перегрузки операции [].
	virtual Node<K,V>* operator[](K key) { return Find(key); }
	
	//три обхода дерева
	virtual void PreOrder(Node<K,V>* node, void (*func)(Node<K,V>*));

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<K,V>* node, void (*func)(Node<K,V>*));

	virtual void PostOrder(Node<K,V>* node, void (*func)(Node<K,V>*));

	virtual void PreOrder(void (*func)(Node<K,V>*))	{ PreOrder(_root,func); }

	virtual void InOrder(void (*func)(Node<K,V>*))	{ InOrder(_root,func); }
	
	virtual void PostOrder(void (*func)(Node<K,V>*))	{ PostOrder(_root,func); }
	
	// Общий вывод (Консоль)
	template<class K1,class V1>
	friend std::ostream& operator<<(std::ostream& stream,Tree<K1,V1>& tree);

	// Частный вывод (Только в файл)
	template<class K1,class V1>
	friend std::ostream& operator<<(std::ofstream& stream,Tree<K1,V1>& tree);
		
	// Частный ввод (Только из файла)
	template<class K1,class V1>
	friend std::ifstream& operator>>(std::ifstream& stream,Tree<K1,V1>& tree);
};

template<class K,class V>
std::ostream& operator<<(std::ostream& stream,Tree<K,V>& tree)
{
	Node<K,V>* node = tree.Minimum();

	while(node != nullptr)
	{
		stream << node->GetKey() << ": " << node->GetValue() << ", ";
		
        node = node->Successor();
	}

	return stream;
}

template<class K,class V>
std::ostream& operator<<(std::ofstream& stream,Tree<K,V>& tree)
{
	tree.Save(stream);
	return stream;
};

template<class K,class V>
std::ifstream& operator>>(std::ifstream& stream,Tree<K,V>& tree)
{
	tree.Load(stream);
	return stream;
};

template<class K,class V>
void Tree<K,V>::Load(std::ifstream& stream)
{
	char root;
	
	stream >> root;

	if(root == 'f')
	{
		_root = nullptr;
		return;
	}
	else if(root == 't')
	{
		K key; V value;

		stream >> key >> value;

		_root = new Node<K,V>(key,value);

		Load(stream,_root);
	}
}

template<class K,class V>
void Tree<K,V>::Load(std::ifstream& stream,Node<K,V>* node)
{
	char left, right;

	stream >> left >> right;

	if(left == 't')
	{
		K key; V value;

		stream >> key >> value;

		Node<K,V>* child = new Node<K,V>(key,value);

		child->SetParent(node);
		node->SetLeft(child);

		Load(stream,child);
	}

	if(right == 't')
	{
		K key; V value;

		stream >> key >> value;

		Node<K,V>* child = new Node<K,V>(key,value);

		child->SetParent(node);
		node->SetRight(child);

		Load(stream,child);
	}
}

template<class K,class V>
void Tree<K,V>::Save(std::ofstream& stream)
{
	stream << ( _root == nullptr ? 'f' : 't' ) << ' ';

	if(_root != nullptr)
		Save(stream,_root);
}

template<class K,class V>
void Tree<K,V>::Save(std::ofstream& stream,Node<K,V>* node)
{
	K key = node->GetKey();
	V value = node->GetValue();

	stream << key << ' ' << value << ' ';

	stream << ( node->GetLeft() == nullptr ? 'f' : 't' ) << ' ';

	stream << ( node->GetRight() == nullptr ? 'f' : 't' ) << ' ';

	if(node->GetLeft() != nullptr)
		Save(stream,node->GetLeft());

	if(node->GetRight() != nullptr)
		Save(stream,node->GetRight());
}

template<class K,class V>
Node<K,V>* Tree<K,V>::Push(Node<K,V>* node, Node<K,V>* current)
{
	//не передан добавляемый узел
	if (node == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	//пустое дерево - добавляем в корень
	if (_root == nullptr)
	{
		_root = node;
		return _root;
	}

	if (current->GetKey() > node->GetKey())
	{
		//идем влево
		if (current->GetLeft() != nullptr)
			return Push(node, current->GetLeft());
		else
		{
			current->SetLeft(node);
			node->SetParent(current);
		}
	}

	if (current->GetKey() < node->GetKey())
	{
		//идем вправо
		if (current->GetRight() != nullptr)
			return Push(node, current->GetRight());
		else
		{
			current->SetRight(node);
			node->SetParent(current);
		}
	}

	return node;
}

template<class K,class V>
Node<K,V>* Tree<K,V>::Remove(Node<K,V>* node)
{
	if (node == nullptr)
		return nullptr;

	if(node == _root)
	{
		_root = nullptr;
		return node;
	}

	Node<K,V>* parent = node->GetParent();

	if(parent == nullptr)
		return node;

	Node<K,V>* replace = nullptr;

	// Если есть оба дочерних элемента, то заменяем на минимальный в правом поддереве.
	// Иначе заменяем на тот дочерний, что существует
	if(node->GetLeft() != nullptr && node->GetRight() != nullptr)
		replace = Tree<K,V>::Minimum(node->GetRight());
	else if(node->GetLeft() == nullptr)
		replace = node->GetRight();
	else /*if(node->GetRight() == nullptr)*/
		replace = node->GetLeft();

	// Заменяем узел у родителя	
	if(parent->GetLeft() == node)
		parent->SetLeft(replace);
	else /*if(parent->GetRight() == node)*/
		parent->SetRight(replace);

	return node;
}


template<class K,class V>
Node<K,V>* Tree<K,V>::Minimum(Node<K,V>* current)
{
	if (_root == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	while (current->GetLeft() != nullptr)
		current = current->GetLeft();

	return current;
}

template<class K,class V>
Node<K,V>* Tree<K,V>::Maximum(Node<K,V>* current)
{
	if (_root == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	while (current->GetRight() != nullptr)
		current = current->GetRight();

	return current;
}

template<class K,class V>
Node<K,V>* Tree<K,V>::Rotate(Node<K,V>* parent, Node<K,V>* child)
{
	if (parent == nullptr || child == nullptr)
		return nullptr;

	if(child->GetParent() != parent)
		throw WrongParentException();

	Node<K,V>* grand = parent->GetParent();

	if(grand == nullptr)
		Tree<K,V>::_root = child;
	else
	{
		if(grand->GetLeft() == parent)
			grand->SetLeft(child);
		else
			grand->SetRight(child);
	}

	if(parent->GetLeft() == child)
	{
		parent->SetLeft(child->GetRight());
		child->SetRight(parent);

		if(parent->GetLeft() != nullptr)
			parent->GetLeft()->SetParent(parent);
	}
	else
	{
		parent->SetRight(child->GetLeft());
		child->SetLeft(parent);

		if(parent->GetRight() != nullptr)
			parent->GetRight()->SetParent(parent);
	}

	parent->SetParent(child);
	child->SetParent(grand);

	return child;
}

template<class K,class V>
Node<K,V>* Tree<K,V>::Find(K key, Node<K,V>* current)
{
	//база рекурсии
	if (current == nullptr || current->GetKey() == key) return current;

	//рекурсивный вызов
	if (current->GetKey() > key) return Find(key, current->GetLeft());
	if (current->GetKey() < key) return Find(key, current->GetRight());

	return nullptr;
}

template<class K,class V>
void Tree<K,V>::PreOrder(Node<K,V>* node, void (*func)(Node<K,V>*))
{
	if (node != nullptr)
		func(node);

	if (node != nullptr && node->GetLeft() != nullptr)
		PreOrder(node->GetLeft(), func);

	if (node != nullptr && node->GetRight() != nullptr)
		PreOrder(node->GetRight(), func);
}

template<class K,class V>
void Tree<K,V>::InOrder(Node<K,V>* node, void (*func)(Node<K,V>*))
{
	if (node != nullptr && node->GetLeft() != nullptr)
		InOrder(node->GetLeft(), func);

	if (node != nullptr)
		func(node);

	if (node != nullptr && node->GetRight() != nullptr)
		InOrder(node->GetRight(), func);
}

template<class K,class V>
void Tree<K,V>::PostOrder(Node<K,V>* node, void (*func)(Node<K,V>*))
{
	if (node != nullptr && node->GetLeft() != nullptr)
		PostOrder(node->GetLeft(), func);

	if (node != nullptr && node->GetRight() != nullptr)
		PostOrder(node->GetRight(), func);

	if (node != nullptr)
		func(node);
}

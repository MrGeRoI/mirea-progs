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

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* _root;

	Node<T>* Rotate(Node<T>* parent, Node<T>* child);

	// Реализовать операции создания дерева из операций поворотов, добавления и удаления узла, слияния деревьев
	// правый поворот вокруг node и его левого узла
	Node<T>* RotateRight(Node<T>* node) { return Rotate(node,node->GetRight()); };

	// левый поворот вокруг node и его правого узла
	Node<T>* RotateLeft(Node<T>* node) { return Rotate(node,node->GetLeft()); };

	void Save(std::ofstream& stream);

	void Save(std::ofstream& stream, Node<T>* node);

	void Load(std::ifstream& stream);

	void Load(std::ifstream& stream, Node<T>* node);

public:
	//доступ к корневому элементу
	virtual Node<T>* GetRoot() { return _root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { _root = nullptr; }

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* Push(T value) { return Push(new Node<T>(value)); }

	//функция добавления узла в дерево
	virtual Node<T>* Push(Node<T>* node) { return Push(node, _root); }

	//рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева, 
	//куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Push(Node<T>* node, Node<T>* current);

	//Введите функцию удаления узла Remove(), которая принимает указатель на удаляемый узел.
	//удаление узла
	virtual Node<T>* Remove(Node<T>* node);

	//поиск минимума и максимума в дереве
	virtual Node<T>* Minimum(Node<T>* current = nullptr);

	virtual Node<T>* Maximum(Node<T>* current = nullptr);
	
	//поиск узла в дереве
	virtual Node<T>* Find(T find) { return Find(find, _root); }

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T>* Find(T data, Node<T>* current);

	//Создайте интерфейс для функции поиска в виде перегрузки операции [].
	virtual Node<T>* operator[](T data) { return Find(data); }
	
	//три обхода дерева
	virtual void PreOrder(Node<T>* node, void (*func)(Node<T>*));

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* node, void (*func)(Node<T>*));

	virtual void PostOrder(Node<T>* node, void (*func)(Node<T>*));

	virtual void PreOrder(void (*func)(Node<T>*))	{ PreOrder(_root,func); }

	virtual void InOrder(void (*func)(Node<T>*))	{ InOrder(_root,func); }
	
	virtual void PostOrder(void (*func)(Node<T>*))	{ PostOrder(_root,func); }
	
	// Общий вывод (Консоль)
	template<class T1>
	friend std::ostream& operator<<(std::ostream& stream,Tree<T1>& tree);

	// Частный вывод (Только в файл)
	template<class T1>
	friend std::ostream& operator<<(std::ofstream& stream,Tree<T1>& tree);
		
	// Частный ввод (Только из файла)
	template<class T1>
	friend std::ifstream& operator>>(std::ifstream& stream,Tree<T1>& tree);
};

template<class T>
std::ostream& operator<<(std::ostream& stream,Tree<T>& tree)
{
	Node<T>* node = tree.Minimum();

	while(node != nullptr)
	{
		stream << node->GetData() << ' ';
		
        node = node->Successor();
	}

	return stream;
}

template<class T>
std::ostream& operator<<(std::ofstream& stream,Tree<T>& tree)
{
	tree.Save(stream);
	return stream;
};

template<class T>
std::ifstream& operator>>(std::ifstream& stream,Tree<T>& tree)
{
	tree.Load(stream);
	return stream;
};

template<class T>
void Tree<T>::Load(std::ifstream& stream)
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
		T data;

		stream >> data;

		_root = new Node<T>(data);

		Load(stream,_root);
	}
}

template<class T>
void Tree<T>::Load(std::ifstream& stream,Node<T>* node)
{
	char left, right;

	stream >> left >> right;

	if(left == 't')
	{
		T data;

		stream >> data;

		Node<T>* child = new Node<T>(data);

		child->SetParent(node);
		node->SetLeft(child);

		Load(stream,child);
	}

	if(right == 't')
	{
		T data;

		stream >> data;

		Node<T>* child = new Node<T>(data);

		child->SetParent(node);
		node->SetRight(child);

		Load(stream,child);
	}
}

template<class T>
void Tree<T>::Save(std::ofstream& stream)
{
	stream << ( _root == nullptr ? 'f' : 't' ) << ' ';

	if(_root != nullptr)
		Save(stream,_root);
}

template<class T>
void Tree<T>::Save(std::ofstream& stream,Node<T>* node)
{
	T data = node->GetData();

	stream << data << ' ';

	stream << ( node->GetLeft() == nullptr ? 'f' : 't' ) << ' ';

	stream << ( node->GetRight() == nullptr ? 'f' : 't' ) << ' ';

	if(node->GetLeft() != nullptr)
		Save(stream,node->GetLeft());

	if(node->GetRight() != nullptr)
		Save(stream,node->GetRight());
}

template<class T>
Node<T>* Tree<T>::Push(Node<T>* node, Node<T>* current)
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

	if (current->GetData() > node->GetData())
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

	if (current->GetData() < node->GetData())
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

template<class T>
Node<T>* Tree<T>::Remove(Node<T>* node)
{
	if (node == nullptr)
		return nullptr;

	if(node == _root)
	{
		_root = nullptr;
		return node;
	}

	Node<T>* parent = node->GetParent();

	if(parent == nullptr)
		return node;

	Node<T>* replace = nullptr;

	// Если есть оба дочерних элемента, то заменяем на минимальный в правом поддереве.
	// Иначе заменяем на тот дочерний, что существует
	if(node->GetLeft() != nullptr && node->GetRight() != nullptr)
		replace = Tree<T>::Minimum(node->GetRight());
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


template<class T>
Node<T>* Tree<T>::Minimum(Node<T>* current)
{
	if (_root == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	while (current->GetLeft() != nullptr)
		current = current->GetLeft();

	return current;
}

template<class T>
Node<T>* Tree<T>::Maximum(Node<T>* current)
{
	if (_root == nullptr)
		return nullptr;

	if (current == nullptr)
		current = _root;

	while (current->GetRight() != nullptr)
		current = current->GetRight();

	return current;
}

template<class T>
Node<T>* Tree<T>::Rotate(Node<T>* parent, Node<T>* child)
{
	if (parent == nullptr || child == nullptr)
		return nullptr;

	if(child->GetParent() != parent)
		throw WrongParentException();

	Node<T>* grand = parent->GetParent();

	if(grand == nullptr)
		Tree<T>::_root = child;
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

template<class T>
Node<T>* Tree<T>::Find(T data, Node<T>* current)
{
	//база рекурсии
	if (current == nullptr || current->GetData() == data) return current;

	//рекурсивный вызов
	if (current->GetData() > data) return Find(data, current->GetLeft());
	if (current->GetData() < data) return Find(data, current->GetRight());

	return nullptr;
}

template<class T>
void Tree<T>::PreOrder(Node<T>* node, void (*func)(Node<T>*))
{
	if (node != nullptr)
		func(node);

	if (node != nullptr && node->GetLeft() != nullptr)
		PreOrder(node->GetLeft(), func);

	if (node != nullptr && node->GetRight() != nullptr)
		PreOrder(node->GetRight(), func);
}

template<class T>
void Tree<T>::InOrder(Node<T>* node, void (*func)(Node<T>*))
{
	if (node != nullptr && node->GetLeft() != nullptr)
		InOrder(node->GetLeft(), func);

	if (node != nullptr)
		func(node);

	if (node != nullptr && node->GetRight() != nullptr)
		InOrder(node->GetRight(), func);
}

template<class T>
void Tree<T>::PostOrder(Node<T>* node, void (*func)(Node<T>*))
{
	if (node != nullptr && node->GetLeft() != nullptr)
		PostOrder(node->GetLeft(), func);

	if (node != nullptr && node->GetRight() != nullptr)
		PostOrder(node->GetRight(), func);

	if (node != nullptr)
		func(node);
}

#include <iostream>

template<class T>
class Node
{
protected:
	//закрытые переменные Node node; node.data = 10 вызовет ошибку
	T _data;

	int _height;
	//не можем хранить Node, но имеем право хранить указатель
	Node<T> *_left,
	*_right,
	*_parent;
public:
	//доступные извне переменные и функции
	virtual void SetData(T d) { _data = d; }
	virtual T GetData() { return _data; }

	virtual int GetHeight() { return _height; }
	virtual void SetHeight(int h) { _height = h; }

	virtual Node<T>* GetLeft() { return _left; }
	virtual Node<T>* GetRight() { return _right; }
	virtual Node<T>* GetParent() { return _parent; }

	virtual void SetLeft(Node<T>* node) { _left = node; }
	virtual void SetRight(Node<T>* node) { _right = node; }
	virtual void SetParent(Node<T>* node) { _parent = node; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>(T value)
	{
		_height = 1;
		_data = value;
		_left = _right = _parent = nullptr;
	}

	Node<T>()
	{
		_left = _right = _parent = nullptr;
		_data = 0;
		_height = 1;
	}

    // переход к следующему элементу
	virtual Node<T>* Successor();

    // переход к предыдущему элементу
	virtual Node<T>* Predecessor();

	virtual Node<T>* Minimum();
	virtual Node<T>* Maximum();

    //  Создайте интерфейс для этих функций на основе перегрузки операций ++ и --.
    virtual Node<T>* operator++() { return Successor(); }

    virtual Node<T>* operator--() { return Predecessor(); }
	
	template<class T1>
	friend std::ostream& operator<<(std::ostream& stream,const Node<T1>& node);
	
	template<class T1>
	friend std::ostream& operator>>(std::ostream& stream,Node<T1>& node);
};

template<class T>
std::ostream& operator<<(std::ostream& stream,const Node<T>& node)
{
	return stream << node._data;
}

template<class T>
std::ostream& operator>>(std::ostream& stream,Node<T>& node)
{
	return stream >> node._data;
}

template<class T>
Node<T>* Node<T>::Minimum()
{
	//минимум - это самый "левый" узел. Идём по дереву всегда влево
	if(GetLeft() != nullptr)
		return GetLeft()->Minimum();

	return this;
}

template<class T>
Node<T>* Node<T>::Maximum()
{
	//максимум - это самый "правый" узел. Идём по дереву всегда вправо
	if(GetRight() != nullptr)
		return GetRight()->Maximum();

	return this;
}

template<class T>
Node<T>* Node<T>::Successor()
{
	// Если справа есть элемент, то вернуть минимальный у него.
	if (_right != nullptr)
		return _right->Minimum();

	Node<T>* current = _parent;

	// Иначе идём вверх по дереву
	while(current != nullptr && current->_data < _data)
		current = current->_parent;

	return current;
}

template<class T>
Node<T>* Node<T>::Predecessor()
{
	// Если слева есть элемент, то вернуть максимальный у него.
	if (_left != nullptr)
		return _left->Maximum();

	if (_parent == nullptr)
		return nullptr;

	Node<T>* current = this;

	// Иначе ищем узел, который висит справа и возвращаем его родителя
	while (current->_parent != nullptr && current->_parent->_left==current)
		current = current->_parent;

	return current->_parent;
}

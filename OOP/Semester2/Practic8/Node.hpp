#include <iostream>

template<class K,class V>
class Node
{
protected:
	//закрытые переменные Node node; node.data = 10 вызовет ошибку
	K _key;
	V _value;

	//не можем хранить Node, но имеем право хранить указатель
	Node<K,V> *_left,
	*_right,
	*_parent;
public:
	//доступные извне переменные и функции
	virtual void SetKey(K k) { _key = k; }
	virtual K GetKey() { return _key; }

	virtual void SetValue(V v) { _value = v; }
	virtual V GetValue() { return _value; }
	
	virtual Node<K,V>* GetLeft() { return _left; }
	virtual Node<K,V>* GetRight() { return _right; }
	virtual Node<K,V>* GetParent() { return _parent; }

	virtual void SetLeft(Node<K,V>* node) { _left = node; }
	virtual void SetRight(Node<K,V>* node) { _right = node; }
	virtual void SetParent(Node<K,V>* node) { _parent = node; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<K,V>(K key,V value)
	{
		_key = key;
		_value = value;
		_left = _right = _parent = nullptr;
	}

	Node<K,V>()
	{
		_left = _right = _parent = nullptr;
		_key = _value = 0;
	}

    // переход к следующему элементу
	virtual Node<K,V>* Successor();

    // переход к предыдущему элементу
	virtual Node<K,V>* Predecessor();

	virtual Node<K,V>* Minimum();
	virtual Node<K,V>* Maximum();

    //  Создайте интерфейс для этих функций на основе перегрузки операций ++ и --.
    virtual Node<K,V>* operator++() { return Successor(); }

    virtual Node<K,V>* operator--() { return Predecessor(); }
	
	template<class K1, class V1>
	friend std::ostream& operator<<(std::ostream& stream,const Node<K1,V1>& node);
	
	template<class K1, class V1>
	friend std::ostream& operator>>(std::ostream& stream,Node<K1,V1>& node);
};

template<class K,class V>
std::ostream& operator<<(std::ostream& stream,const Node<K,V>& node)
{
	return stream << node._value;
}

template<class K,class V>
std::ostream& operator>>(std::ostream& stream,Node<K,V>& node)
{
	return stream >> node._value;
}

template<class K,class V>
Node<K,V>* Node<K,V>::Minimum()
{
	//минимум - это самый "левый" узел. Идём по дереву всегда влево
	if(GetLeft() != nullptr)
		return GetLeft()->Minimum();

	return this;
}

template<class K,class V>
Node<K,V>* Node<K,V>::Maximum()
{
	//максимум - это самый "правый" узел. Идём по дереву всегда вправо
	if(GetRight() != nullptr)
		return GetRight()->Maximum();

	return this;
}

template<class K,class V>
Node<K,V>* Node<K,V>::Successor()
{
	// Если справа есть элемент, то вернуть минимальный у него.
	if (_right != nullptr)
		return _right->Minimum();

	Node<K,V>* current = _parent;

	// Иначе идём вверх по дереву
	while(current != nullptr && current->_key < _key)
		current = current->_parent;

	return current;
}

template<class K,class V>
Node<K,V>* Node<K,V>::Predecessor()
{
	// Если слева есть элемент, то вернуть максимальный у него.
	if (_left != nullptr)
		return _left->Maximum();

	if (_parent == nullptr)
		return nullptr;

	Node<K,V>* current = this;

	// Иначе ищем узел, который висит справа и возвращаем его родителя
	while (current->_parent != nullptr && current->_parent->_left==current)
		current = current->_parent;

	return current->_parent;
}

#include <iostream>

template <class K, class V>
class Node
{
protected:
	K _key;
	V _value;

	Node<K, V> *_left,
		*_right,
		*_parent;

public:
	virtual void SetKey(K k) { _key = k; }
	virtual K GetKey() const { return _key; }

	virtual void SetValue(V v) { _value = v; }
	virtual V GetValue() const { return _value; }

	virtual Node<K, V> *GetLeft() const { return _left; }
	virtual Node<K, V> *GetRight() const { return _right; }
	virtual Node<K, V> *GetParent() const { return _parent; }

	virtual void SetLeft(Node<K, V> *node) { _left = node; }
	virtual void SetRight(Node<K, V> *node) { _right = node; }
	virtual void SetParent(Node<K, V> *node) { _parent = node; }

	Node<K, V>(K key, V value)
	{
		_key = key;
		_value = value;
		_left = _right = _parent = nullptr;
	}

	Node<K, V>()
	{
		_left = _right = _parent = nullptr;
		_key = _value = 0;
	}

	V &operator*() { return _value; }

	const V &operator*() const { return _value; }

	virtual Node<K, V> *Successor() const;

	virtual Node<K, V> *Predecessor() const;

	virtual Node<K, V> *Minimum() const;
	virtual Node<K, V> *Maximum() const;

	template <class K1, class V1>
	friend std::ostream &operator<<(std::ostream &stream, const Node<K1, V1> &node);

	template <class K1, class V1>
	friend std::ostream &operator>>(std::ostream &stream, Node<K1, V1> &node);
};

template <class K, class V>
std::ostream &operator<<(std::ostream &stream, const Node<K, V> &node)
{
	return stream << node._value;
}

template <class K, class V>
std::ostream &operator>>(std::ostream &stream, Node<K, V> &node)
{
	return stream >> node._value;
}

template <class K, class V>
Node<K, V> *Node<K, V>::Minimum() const
{

	if (GetLeft() != nullptr)
		return GetLeft()->Minimum();

	return this;
}

template <class K, class V>
Node<K, V> *Node<K, V>::Maximum() const
{

	if (GetRight() != nullptr)
		return GetRight()->Maximum();

	return this;
}

template <class K, class V>
Node<K, V> *Node<K, V>::Successor() const
{

	if (_right != nullptr)
		return _right->Minimum();

	Node<K, V> *current = _parent;

	while (current != nullptr && current->_key < _key)
		current = current->_parent;

	return current;
}

template <class K, class V>
Node<K, V> *Node<K, V>::Predecessor() const
{

	if (_left != nullptr)
		return _left->Maximum();

	if (_parent == nullptr)
		return nullptr;

	Node<K, V> *current = this;

	while (current->_parent != nullptr && current->_parent->_left == current)
		current = current->_parent;

	return current->_parent;
}

// дописать класс итератора по списку
template <typename K, typename V>
class TreeIterator : public std::iterator<input_iterator_tag, K>
{
public:
	// конструкторы
	TreeIterator() { _node = nullptr; }
	TreeIterator(Node<K, V> *p) { _node = p; }
	TreeIterator(const TreeIterator &it) { _node = it._node; }

	// методы работы с итераторами
	// присваивание
	TreeIterator &operator=(const TreeIterator &it)
	{
		_node = it._node;
		return *this;
	}
	TreeIterator &operator=(Node<K, V> *p)
	{
		_node = p;
		return *this;
	}

	// проверка итераторов на равенство
	bool operator!=(TreeIterator const &other) const { return _node != other._node; }
	bool operator==(TreeIterator const &other) const { return _node == other._node; }

	Node<K, V> *GetNode() const { return _node; }
	void SetNode(Node<K, V> *node) { _node = node; }

	// получить значение
	Node<K, V> &operator*()
	{
		if (_node == nullptr)
			throw std::runtime_error("Invalid pointer");

		return _node;
	}
	// получить значение
	const Node<K, V> &operator*() const
	{
		if (_node == nullptr)
			throw std::runtime_error("Invalid pointer");

		return _node;
	}

	// перемещение с помощью итераторов
	TreeIterator &operator++()
	{
		_node = _node->Successor();
		return *this;
	} // Префиксный ++
	TreeIterator operator++(int)
	{
		TreeIterator it(*this);
		_node = _node->Successor();
		return it;
	} // Постфиксный ++
	TreeIterator &operator--()
	{
		_node = _node->Predecessor();
		return *this;
	} // Префиксный --
	TreeIterator operator--(int)
	{
		TreeIterator it(*this);
		_node = _node->Predecessor();
		return it;
	} // Постфиксный --

private:
	// текущий элемент
	Node<K, V> *_node;
};

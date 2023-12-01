#include <iostream>
#include <string>

using namespace std;

/*«Школьник».
Минимальный набор полей: фамилия,
имя, пол, класс, дата рождения, адрес.*/
class Student
{
public:
	string _firstname, _lastname, _address;
	bool _male;
	int _birthday,_grade;

	Student()
	{
		_male = 0;
		_birthday = 0;
		_grade = 0;
	}

	Student(const char* firstname,const char* lastname,const char* address,bool male, int birthday,int grade)
	{
		_firstname = firstname;
		_lastname = lastname;
		_address = address;
		_male = male;
		_birthday = birthday;
		_grade = grade;
	}

	Student(const Student& stud)
	{
		_firstname = stud._firstname;
		_lastname = stud._lastname;
		_address = stud._address;
		_male = stud._male;
		_birthday = stud._birthday;
		_grade = stud._grade;
	}

	~Student() { }

	friend ostream& operator << (ostream& s,const Student& value);
	friend istream& operator >> (istream& s, Student& value);

	bool operator < (const Student& stud) const
	{
		if(_birthday < stud._birthday)
			return true;

		if(_lastname < stud._lastname)
			return true;

		if(_firstname < stud._firstname)
			return true;

		return false;
	}

	bool operator > (const Student& stud) const
	{
		if(_birthday > stud._birthday)
			return true;

		if(_lastname > stud._lastname)
			return true;

		if(_firstname > stud._firstname)
			return true;

		return false;
	}

	bool operator == (const Student& stud) const
	{
		return _firstname == stud._firstname &&
			_lastname == stud._lastname &&
			_birthday == stud._birthday;
	}
};

ostream& operator << (ostream& stream,const Student& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

istream& operator >> (istream& stream, Student& value)
{
	return stream >> value._firstname >> value._lastname >> value._address >> value._male >> value._birthday >> value._grade;
}

#pragma once

#pragma warning(disable : 4996) 

#include <iostream>
#include <fstream>

template <class T>
class Element
{
	
private:
	
	Element *_next;
	Element *_previous;

	
	T _value;

public:
	
	virtual Element *GetNext() const { return _next; }
	virtual void SetNext(Element *value) { _next = value; }

	
	virtual Element *GetPrevious() const { return _previous; }
	virtual void SetPrevious(Element *value) { _previous = value; }

	
	virtual T GetValue() const { return _value; }
	virtual void SetValue(T value) { _value = value; }

	template <class T1>
	friend ostream &operator<<(ostream &stream, const Element<T1> &obj);

	Element(T value)
	{
		_value = value;
		_next = _previous = nullptr;
	}
};

template <class T>
ostream &operator<<(ostream &stream, const Element<T> &obj)
{
	return stream << obj._value;
}

template <class T>
class LinkedList
{
protected:
	
	Element<T> *_head;
	Element<T> *_tail;
	
	int _count;

public:
	virtual int Count() const { return _count; }

	virtual Element<T> *GetBegin() const { return _head; }

	virtual Element<T> *GetEnd() const { return _tail; }

	
	LinkedList()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	
	virtual Element<T> *Push(T value) = 0;

	
	virtual T Pop() = 0;

	virtual ~LinkedList()
	{
		
		Element<T> *previous;
		for (Element<T> *current = _head; current != nullptr;)
		{
			previous = current;
			current = current->GetNext();
			delete previous;
		}
	}

	
	
	virtual Element<T> *operator[](int i) const
	{
		
		if (i < 0 || i > _count)
			return nullptr;

		
		Element<T> *cur = _head;
		for (int k = 0; k < i; k++)
			cur = cur->GetNext();

		return cur;
	}

	template <class T1>
	friend ofstream &operator<<(ofstream &stream, const LinkedList<T1> &obj);
	template <class T1>
	friend ostream &operator<<(ostream &stream, const LinkedList<T1> &obj);
	template <class T1>
	friend istream &operator>>(istream &stream, LinkedList<T1> &obj);
};

/*Петрусевич, какого хуя тут такие костыли, ты долбаёб?
Надо просто сделать перегрузки функций ввода/ввывода из файла и консоли
для типов ostream и ofstream*/
template <class T>
ofstream &operator<<(ofstream &stream, const LinkedList<T> &obj)
{
	stream << obj._count << "\n";
	for (Element<T> *current = obj.GetBegin(); current != nullptr; current = current->GetNext())
		stream << current->GetValue() << " ";
	return stream;
}

template <class T>
ostream &operator<<(ostream &stream, const LinkedList<T> &obj)
{
	for (Element<T> *current = obj.GetBegin(); current != nullptr; current = current->GetNext())
		stream << current->GetValue() << "\n";

	return stream;
}

template <class T>
istream &operator>>(istream &stream, LinkedList<T> &list)
{
	
	stream >> list._count;
	

	Element<T> *previous;
	for (Element<T> *current = list._head; current != nullptr;)
	{
		previous = current;
		current = current->GetNext();
		delete previous;
	}

	for (int i = 0; i < list._count; i++)
	{
		T value;
		stream >> value;
		list.Push(value);
	}

	return stream;
}


template <typename T>
class ListIterator : public iterator<input_iterator_tag, T>
{
public:
	
	ListIterator() { _element = nullptr; }
	ListIterator(Element<T> *p) { _element = p; }
	ListIterator(const ListIterator &it) { _element = it._element; }

	
	
	ListIterator &operator=(const ListIterator &it)
	{
		_element = it._element;
		return *this;
	}
	ListIterator &operator=(Element<T> *p)
	{
		_element = p;
		return *this;
	}

	
	bool operator!=(ListIterator const &other) const { return _element != other._element; }
	bool operator==(ListIterator const &other) const { return _element == other._element; }

	Element<T> *GetElement() const { return _element; }
	void SetElement(Element<T> *element) { _element = element; }

	
	Element<T> &operator*() const
	{
		if (_element == nullptr)
			throw runtime_error("Invalid pointer");

		return *_element;
	}
	
	ListIterator &operator++()
	{
		_element = _element->GetNext();
		return *this;
	} 
	ListIterator operator++(int)
	{
		ListIterator it(*this);
		_element = _element->GetNext();
		return it;
	} 
	ListIterator &operator--()
	{
		_element = _element->GetPrevious();
		return *this;
	} 
	ListIterator operator--(int)
	{
		ListIterator it(*this);
		_element = _element->GetPrevious();
		return it;
	} 

private:
	
	Element<T> *_element;
};

template <class T>
class IteratedLinkedList : public LinkedList<T>
{
public:
	IteratedLinkedList() : LinkedList<T>() {}
	virtual ~IteratedLinkedList() {}

	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedList<T>::_head;
		return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = LinkedList<T>::_tail;
		return it;
	}
};

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	Stack() : IteratedLinkedList<T>() {}
	/*Реализуйте функции добавления элемента push() и
	удаления элемента pop() в классе-наследнике D (для четных вариантов D –
	Стек, для нечетных – Очередь) согласно схеме: для класса Стек элементы
	добавляются в конец, извлекаются с конца; для класса Очереди элементы
	добавляются в конец, извлекаются с начала. */
	Element<T> *Push(T value) 
	{
		Element<T> *elem = new Element<T>(value);

		if (this->_tail == nullptr)
			this->_head = this->_tail = elem;
		else
		{
			this->_tail->SetNext(elem);
			elem->SetPrevious(this->_tail);
			this->_tail = elem;
		}

		this->_count++;

		return elem;
	}

	T Pop()
	{
		T value;

		value = this->_tail->GetValue();

		Element<T> *prev = this->_tail->GetPrevious();
		prev->SetNext(nullptr);

		this->_tail->SetPrevious(nullptr);
		this->_tail = prev;
		this->_count--;

		return value;
	}

	ListIterator<T> Insert(ListIterator<T> it, T value)
	{
		Element<T> *inserted = Insert(it.GetElement(), value);

		if (inserted != nullptr)
			it = inserted;

		return it;
	}

	Element<T> *Insert(Element<T> *current, T value)
	{
		if (this->_tail == current)
			return Stack<T>::Push(value);

		Element<T> *elem = new Element<T>(value);

		if (current == nullptr)
		{
			elem->SetNext(this->_head);
			this->_head->SetPrevious(elem);
			this->_head = elem;
			return elem;
		}

		elem->SetNext(current->GetNext());
		current->GetNext()->SetPrevious(elem);

		current->SetNext(elem);

		elem->SetPrevious(current);

		this->_count++;

		return elem;
	}

	
	virtual ListIterator<T> Remove(ListIterator<T> it)
	{
		if (it.GetElement() == nullptr)
		{
			Pop();
			return it;
		}
		Element<T> *elem = it.GetElement();
		it--;
		Remove(elem);
		return it;
	}

	virtual Element<T> *Remove(Element<T> *elem)
	{
		Element<T> *prev = elem->GetPrevious(), *next = elem->GetNext();

		if (elem == this->_head)
			this->_head = next;

		if (elem == this->_tail)
			this->_tail = prev;

		if (next != nullptr)
			next->SetPrevious(prev);

		if (prev != nullptr)
			prev->SetNext(next);

		this->_count--;

		return elem;
	}

	/*Реализуйте функцию универсального фильтра,
	принимающего список произвольного типа (участвующего в схеме
	наследования) и возвращающего список произвольного типа (тип
	обрабатываемого списка не обязан совпадать с типом списка-результата).
	*/
	virtual void Filter(LinkedList<T> &list, bool (*filter)(T))
	{
		for (Element<T> *elem = this->_head; elem != nullptr; elem = elem->GetNext())
			if (filter(elem->GetValue()))
				list.Push(elem->GetValue());
	}

	
	virtual Stack<T> Filter(bool (*filter)(T))
	{
		Stack<T> result;

		Filter(result, filter);

		return result;
	}
};

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
	friend ostream &operator<<(ostream &stream, const Node<K1, V1> &node);

	template <class K1, class V1>
	friend ostream &operator>>(ostream &stream, Node<K1, V1> &node);
};

template <class K, class V>
ostream &operator<<(ostream &stream, const Node<K, V> &node)
{
	return stream << node._value;
}

template <class K, class V>
ostream &operator>>(ostream &stream, Node<K, V> &node)
{
	return stream >> node._value;
}

template <class K, class V>
Node<K, V> *Node<K, V>::Minimum() const
{
	if (GetLeft() != nullptr)
		return GetLeft()->Minimum();

	return (Node<K, V> *)this;
}

template <class K, class V>
Node<K, V> *Node<K, V>::Maximum() const
{
	if (GetRight() != nullptr)
		return GetRight()->Maximum();

	return (Node<K, V> *)this;
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

	Node<K, V> *current = (Node<K, V> *)this;

	while (current->_parent != nullptr && current->_parent->_left == current)
		current = current->_parent;

	return current->_parent;
}


template <typename K, typename V>
class TreeIterator : public iterator<input_iterator_tag, K>
{
public:
	
	TreeIterator() { _node = nullptr; }
	TreeIterator(Node<K, V> *p) { _node = p; }
	TreeIterator(const TreeIterator &it) { _node = it._node; }

	
	
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

	
	bool operator!=(TreeIterator const &other) const { return _node != other._node; }
	bool operator==(TreeIterator const &other) const { return _node == other._node; }

	Node<K, V> *GetNode() const { return _node; }
	void SetNode(Node<K, V> *node) { _node = node; }

	
	Node<K, V> &operator*()
	{
		if (_node == nullptr)
			throw runtime_error("Invalid pointer");

		return _node;
	}
	
	const Node<K, V> &operator*() const
	{
		if (_node == nullptr)
			throw runtime_error("Invalid pointer");

		return _node;
	}

	
	TreeIterator &operator++()
	{
		_node = _node->Successor();
		return *this;
	} 
	TreeIterator operator++(int)
	{
		TreeIterator it(*this);
		_node = _node->Successor();
		return it;
	} 
	TreeIterator &operator--()
	{
		_node = _node->Predecessor();
		return *this;
	} 
	TreeIterator operator--(int)
	{
		TreeIterator it(*this);
		_node = _node->Predecessor();
		return it;
	} 

private:
	
	Node<K, V> *_node;
};
template <class K, class V>
class Tree
{
protected:
	Node<K, V> *_root;

	Node<K, V> *Rotate(Node<K, V> *parent, Node<K, V> *child);

	Node<K, V> *RotateRight(Node<K, V> *node) { return Rotate(node, node->GetRight()); };

	Node<K, V> *RotateLeft(Node<K, V> *node) { return Rotate(node, node->GetLeft()); };

	virtual Node<K, V> *Push(K key, V value, Node<K, V> *current);

	virtual Node<K, V> *Remove(Node<K, V> *node);

	virtual Node<K, V> *Minimum(Node<K, V> *current = nullptr) const;

	virtual Node<K, V> *Maximum(Node<K, V> *current = nullptr) const;

	virtual Node<K, V> *Find(K key, Node<K, V> *current) const;

	virtual Node<K, V> *Find(bool (*find)(K, V)) const { return Find(find, _root); }

	virtual Node<K, V> *Find(bool (*find)(K, V), Node<K, V> *current) const;

public:
	virtual Node<K, V> *GetRoot() const { return _root; }

	Tree<K, V>() { _root = nullptr; }

	virtual TreeIterator<K, V> Push(K key, V value) { TreeIterator<K, V>(this->Push(key, value, _root)); }

	virtual void Remove(TreeIterator<K, V> it) { this->Remove(it.GetNode()) };

	virtual TreeIterator<K, V> Minimum(TreeIterator<K, V> it) const { TreeIterator<K, V>(this->Minimum(it.GetNode())) };

	virtual TreeIterator<K, V> Maximum(TreeIterator<K, V> it) const { TreeIterator<K, V>(this->Maximum(it.GetNode())) };

	virtual TreeIterator<K, V> Find(K find) const { return TreeIterator<K, V>(this->Find(find, _root)); }

	virtual TreeIterator<K, V> Find(bool (*find)(K, V)) const { return TreeIterator<K, V>(Find(this->find, _root)); }

	virtual TreeIterator<K, V> Find(bool (*find)(K, V), TreeIterator<K, V> current) const{ return TreeIterator<K, V>(this->Find(find, current.GetNode())); }

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

	if (current->GetRight() != nullptr)
		return Push(key, value, current->GetRight());
	else
	{
		Node<K, V> *node = new Node<K, V>(key, value);
		current->SetRight(node);
		node->SetParent(current);
		return node;
	}

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
		throw invalid_argument("Child is not child of parent");

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
template <class K, class V>
class SplayTree : public Tree<K, V>
{
protected:
	using Tree<K, V>::_root;

	Node<K, V> *Splay(Node<K, V> *node);

	virtual Node<K, V> *Find(K key, Node<K, V> *current) const override;

	virtual Node<K, V> *Push(Node<K, V> *node) override { return Tree<K, V>::Push(node); };

	virtual Node<K, V> *Push(Node<K, V> *node, Node<K, V> *current) override;

	virtual Node<K, V> *Remove(Node<K, V> *node) override;
public:
	SplayTree<K, V>() : Tree<K, V>() {}

	virtual Node<K, V> *Find(bool (*find)(K, V)) const { return Tree<K, V>::Find(find, Tree<K, V>::_root); };

	virtual Node<K, V> *Find(bool (*find)(K, V), Node<K, V> *current) const;

	virtual Node<K, V> *Find(K key) const override { return Tree<K, V>::Find(key, Tree<K, V>::_root); };

	virtual Node<K, V> *Push(K key, V value) override { return Tree<K, V>::Push(key, value); };

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
int main()
{
	// Дерево с итератором
	Tree<string, Student> tree;

	tree.Push("Danaya",Student("Danya","Lykov","Branks",true,2007,8));
	tree.Push("Sanya",Student("Sanya","Lazarev","Moscow",true,2005,6));
	tree.Push("Malysh",Student("Yarik","Malysh","Zamkad",true,2004,5));
	tree.Push("German",Student("German","Zaycev","Krasnodar",true,2004,4));
	tree.Push("Senya",Student("Senya","Lenin","Penza",true,2004,3));
	tree.Push("Pepsi",Student("Ksusha","Egorova","Zamkad",false,2004,2));

	// Вывод по порядку
	for(TreeIterator<string, Student> it = tree.begin();it != tree.end(); it++)
		cout << (*it).GetValue() << endl;

	Student found = (*tree.Find("Malysh")).GetValue();

	// Расширяющиеся дерево (элементы с одинаковыми ключами хранятся справа)
	SplayTree<string, Student> stree;

	tree.Push("KMBO001",Student("Yarik","Malysh","Zamkad",true,2004,5));
	TreeIterator<string, Student> it = tree.Push("KMBO002",Student("Danya","Lykov","Branks",true,2007,8));
	tree.Push("KMBO003",Student("Sanya","Lazarev","Moscow",true,2005,6));
	tree.Push("KMBO004",Student("German","Zaycev","Krasnodar",true,2004,4));
	tree.Push("KMBO005",Student("Senya","Lenin","Penza",true,2004,3));
	tree.Push("KMBO006",Student("Ksusha","Egorova","Zamkad",false,2004,2));

	// Обращаемся к узлам
	tree.Find("KMBO006"); 
	tree.Find("KMBO001");
	tree.Find("KMBO006");
	tree.Find("KMBO001");
	tree.Find("KMBO006");
	tree.Find("KMBO002");
	tree.Remove(it);
	tree.Find("KMBO001");

	// Теперь в корне и  его окрестности находятся значения, к которым чаще всего обращались
	cout << tree.GetRoot()->GetValue() << ", " <<
		tree.GetRoot()->GetRight()->GetValue() <<
		tree.GetRoot()->GetLeft()->GetValue() << endl;

	// Дерево с повторяющимися ключами по списку
	MultiTree<int, string> mtree;

	mtree.Push(3, "hello");
	mtree.Push(3, "hello2");
	mtree.Push(3, "hello3");

	mtree.Push(4, "world");

	IteratedLinkedList<string> elems = mtree[3];

	cout << elems << endl; // "hello", "hello2", "hello3"

	return 0;
}
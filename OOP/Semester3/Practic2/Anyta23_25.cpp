#include <iostream>
#include <string>

using namespace std;

class Movie
{
public:
	string _scenarist, _name, _country;
	int _year, _cost, _income;

	Movie()
	{
		_year = 0;
		_cost = 0;
		_income = 0;
	}

	Movie(const char *scenarist, const char *name, const char *country,
		  int year, int cost, int income)
	{
		_scenarist = scenarist;
		_name = name;
		_country = country;
		_year = year;
		_cost = cost;
		_income = income;
	}

	Movie(const Movie &movie)
	{
		_scenarist = movie._scenarist;
		_name = movie._name;
		_country = movie._country;
		_year = movie._year;
		_cost = movie._cost;
		_income = movie._income;
	}

	~Movie() {}

	friend ostream &operator<<(ostream &stream, const Movie &value)
	{
		return stream << value._scenarist << ' ' << value._name << ' ' << value._country << ' '
					  << value._year << ' ' << value._cost << ' ' << value._income;
	}

	friend istream &operator>>(istream &stream, Movie &value)
	{
		return stream >> value._scenarist >> value._name >> value._country >> value._year >> value._cost >> value._income;
	}

	bool operator<(const Movie &movie) const
	{
		if (_income < movie._income)
			return true;

		if (_cost < movie._cost)
			return true;

		if (_year < movie._year)
			return true;

		return false;
	}

	bool operator>(const Movie &movie) const
	{
		if (_income > movie._income)
			return true;

		if (_cost > movie._cost)
			return true;

		if (_year > movie._year)
			return true;

		return false;
	}

	bool operator==(const Movie &movie) const
	{
		return _name == movie._name &&
			   _scenarist == movie._scenarist &&
			   _country == movie._country;
	}
};

template <class T>
class Stack
{
public:
	class Element
	{
	private:
		Element *_next;
		Element *_previous;

		T _value;

	public:
		virtual Element *getNext() const { return _next; }
		virtual void setNext(Element *value) { _next = value; }

		virtual Element *getPrevious() const { return _previous; }
		virtual void setPrevious(Element *value) { _previous = value; }

		virtual T getValue() const { return _value; }
		virtual void setValue(T value) { _value = value; }

		template <class T1>
		friend ostream &operator<<(ostream &stream, const typename Stack<T1>::Element &obj);

		Element(T value)
		{
			_value = value;
			_next = _previous = nullptr;
		}
	};

	class Iterator : public iterator<input_iterator_tag, T>
	{
	public:
		Iterator() { _element = nullptr; }
		Iterator(Element *p) { _element = p; }
		Iterator(const Iterator &it) { _element = it._element; }

		Iterator &operator=(const Iterator &it)
		{
			_element = it._element;
			return *this;
		}
		Iterator &operator=(Element *p)
		{
			_element = p;
			return *this;
		}

		bool operator!=(Iterator const &other) const { return _element != other._element; }
		bool operator==(Iterator const &other) const { return _element == other._element; }

		Element *getElement() const { return _element; }
		void setElement(Element *element) { _element = element; }

		Element &operator*() const
		{
			if (_element == nullptr)
				throw runtime_error("Invalid pointer");

			return *_element;
		}

		Iterator &operator++()
		{
			_element = _element->getNext();
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator it(*this);
			_element = _element->getNext();
			return it;
		}
		Iterator &operator--()
		{
			_element = _element->getPrevious();
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator it(*this);
			_element = _element->getPrevious();
			return it;
		}

	private:
		Element *_element;
	};

protected:
	Element *_head;
	Element *_tail;

	int _count;

public:
	Stack()
	{
		_head = _tail = nullptr;
		_count = 0;
	}

	Stack(const Stack &stack)
	{
		_head = _tail = nullptr;
		_count = 0;

		for (Element *current = stack._head; current != nullptr; current = current->getNext())
			push(current->getValue());
	}

	virtual int getCount() const { return _count; }

	virtual Element *getBegin() const { return _head; }

	virtual Element *getEnd() const { return _tail; }

	virtual Element *push(T value)
	{
		Element *elem = new Element(value);

		if (this->_tail == nullptr)
			this->_head = this->_tail = elem;
		else
		{
			this->_tail->setNext(elem);
			elem->setPrevious(this->_tail);
			this->_tail = elem;
		}

		this->_count++;

		return elem;
	};

	virtual T pop()
	{
		T value;

		value = this->_tail->getValue();

		Element *prev = this->_tail->getPrevious();
		prev->setNext(nullptr);

		this->_tail->setPrevious(nullptr);
		this->_tail = prev;
		this->_count--;

		return value;
	};

	Iterator insert(Iterator it, T value)
	{
		Element *inserted = insert(it.getElement(), value);

		if (inserted != nullptr)
			it = inserted;

		return it;
	}

	Element *insert(Element *current, T value)
	{
		if (this->_tail == current)
			return Stack<T>::push(value);

		Element *elem = new Element(value);

		if (current == nullptr)
		{
			elem->setNext(this->_head);
			this->_head->setPrevious(elem);
			this->_head = elem;
			return elem;
		}

		elem->setNext(current->getNext());
		current->getNext()->setPrevious(elem);

		current->setNext(elem);

		elem->setPrevious(current);

		this->_count++;

		return elem;
	}

	virtual Iterator remove(Iterator it)
	{
		if (it.getElement() == nullptr)
		{
			pop();
			return it;
		}
		Element *elem = it.getElement();
		it--;
		remove(elem);
		return it;
	}

	virtual Element *remove(Element *elem)
	{
		Element *prev = elem->getPrevious(), *next = elem->getNext();

		if (elem == this->_head)
			this->_head = next;

		if (elem == this->_tail)
			this->_tail = prev;

		if (next != nullptr)
			next->setPrevious(prev);

		if (prev != nullptr)
			prev->setNext(next);

		this->_count--;

		return elem;
	}

	Iterator begin()
	{
		Iterator it = Stack<T>::_head;
		return it;
	}

	Iterator end()
	{
		Iterator it = Stack<T>::_tail;
		return it;
	}

	virtual ~Stack()
	{
		for (Element *previous = nullptr, *current = _head; current != nullptr;)
		{
			previous = current;
			current = current->getNext();
			delete previous;
		}
	}

	virtual Element *operator[](int i) const
	{
		if (i < 0 || i > _count)
			return nullptr;

		Element *cur = _head;
		for (int k = 0; k < i; k++)
			cur = cur->getNext();

		return cur;
	}

	virtual Stack &operator=(const Stack &stack)
	{
		for (Element *previous = nullptr, *current = _head; current != nullptr;)
		{
			previous = current;
			current = current->getNext();
			delete previous;
		}

		_head = _tail = nullptr;
		_count = 0;

		for (Element *current = stack._head; current != nullptr; current = current->getNext())
			push(current->getValue());

		return *this;
	}

	template <class T1>
	friend ostream &operator<<(ostream &stream, const Stack<T1> &obj);
	template <class T1>
	friend istream &operator>>(istream &stream, Stack<T1> &obj);
};

template <class T>
ostream &operator<<(ostream &stream, const typename Stack<T>::Element &obj)
{
	return stream << obj._value;
}

template <class T>
ostream &operator<<(ostream &stream, const Stack<T> &obj)
{
	for (typename Stack<T>::Element *current = obj.getBegin(); current != nullptr; current = current->getNext())
		stream << current->getValue() << "\n";

	return stream;
}

template <class T>
istream &operator>>(istream &stream, Stack<T> &list)
{

	stream >> list._count;

	typename Stack<T>::Element *previous;
	for (typename Stack<T>::Element *current = list._head; current != nullptr;)
	{
		previous = current;
		current = current->getNext();
		delete previous;
	}

	for (int i = 0; i < list._count; i++)
	{
		T value;
		stream >> value;
		list.push(value);
	}

	return stream;
}

template <class K, class V>
class AVL_Tree
{
public:
	class Node
	{
	protected:
		K _key;
		V _value;

		Node *_left,
			*_right,
			*_parent;

	public:
		virtual void setKey(K k) { _key = k; }
		virtual K getKey() const { return _key; }

		virtual void setValue(V v) { _value = v; }
		virtual V getValue() const { return _value; }

		virtual Node *getLeft() const { return _left; }
		virtual Node *getRight() const { return _right; }
		virtual Node *getParent() const { return _parent; }

		virtual void setLeft(Node *node) { _left = node; }
		virtual void setRight(Node *node) { _right = node; }
		virtual void setParent(Node *node) { _parent = node; }

		Node(K key, V value)
		{
			_key = key;
			_value = value;
			_left = _right = _parent = nullptr;
		}

		Node()
		{
			_left = _right = _parent = nullptr;
			_key = _value = 0;
		}

		V &operator*() { return _value; }

		const V &operator*() const { return _value; }

		virtual Node *successor() const
		{
			if (_right != nullptr)
				return _right->minimum();

			Node *current = _parent;

			while (current != nullptr && current->_key < _key)
				current = current->_parent;

			return current;
		}

		virtual Node *predecessor() const
		{
			if (_left != nullptr)
				return _left->maximum();

			if (_parent == nullptr)
				return nullptr;

			Node *current = (Node *)this;

			while (current->_parent != nullptr && current->_parent->_left == current)
				current = current->_parent;

			return current->_parent;
		}

		virtual Node *minimum() const
		{
			if (getLeft() != nullptr)
				return getLeft()->minimum();

			return (Node *)this;
		}

		virtual Node *maximum() const
		{
			if (getRight() != nullptr)
				return getRight()->maximum();

			return (Node *)this;
		}

		template <class K1, class V1>
		friend ostream &operator<<(ostream &stream, const typename AVL_Tree<K1, V1>::Node &node);

		template <class K1, class V1>
		friend ostream &operator>>(ostream &stream, typename AVL_Tree<K1, V1>::Node &node);
	};

	class Iterator : public iterator<input_iterator_tag, K>
	{
	private:
		Node *_node;

	public:
		Iterator() { _node = nullptr; }
		Iterator(Node *p) { _node = p; }
		Iterator(const Iterator &it) { _node = it._node; }

		Iterator &operator=(const Iterator &it)
		{
			_node = it._node;
			return *this;
		}

		Iterator &operator=(Node *p)
		{
			_node = p;
			return *this;
		}

		bool operator!=(Iterator const &other) const { return _node != other._node; }
		bool operator==(Iterator const &other) const { return _node == other._node; }

		Node *getNode() const { return _node; }
		void setNode(Node *node) { _node = node; }

		Node &operator*()
		{
			if (_node == nullptr)
				throw runtime_error("Invalid pointer");

			return *_node;
		}

		const Node &operator*() const
		{
			if (_node == nullptr)
				throw runtime_error("Invalid pointer");

			return *_node;
		}

		Iterator &operator++()
		{
			_node = _node->successor();
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator it(*this);
			_node = _node->successor();
			return it;
		}
		Iterator &operator--()
		{
			_node = _node->predecessor();
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator it(*this);
			_node = _node->predecessor();
			return it;
		}
	};

protected:
	Node *_root;

	Node *rotate(Node *parent, Node *child)
	{
		if (parent == nullptr || child == nullptr)
			return nullptr;

		if (child->getParent() != parent)
			throw invalid_argument("Child is not child of parent");

		Node *grand = parent->getParent();

		if (grand == nullptr)
			AVL_Tree<K, V>::_root = child;
		else
		{
			if (grand->getLeft() == parent)
				grand->setLeft(child);
			else
				grand->setRight(child);
		}

		if (parent->getLeft() == child)
		{
			parent->setLeft(child->getRight());
			child->setRight(parent);

			if (parent->getLeft() != nullptr)
				parent->getLeft()->setParent(parent);
		}
		else
		{
			parent->setRight(child->getLeft());
			child->setLeft(parent);

			if (parent->getRight() != nullptr)
				parent->getRight()->setParent(parent);
		}

		parent->setParent(child);
		child->setParent(grand);

		return child;
	}

	Node *rotateRight(Node *node) { return rotate(node, node->getRight()); }

	Node *rotateLeft(Node *node) { return rotate(node, node->getLeft()); }

	virtual Node *push(K key, V value, Node *current)
	{
		if (current == nullptr)
			current = _root;

		if (_root == nullptr)
			return _root = new Node(key, value);

		if (current->getKey() == key)
			return current;

		if (current->getKey() > key)
		{
			if (current->getLeft() != nullptr)
				return this->push(key, value, current->getLeft());
			else
			{
				Node *node = new Node(key, value);
				current->setLeft(node);
				node->setParent(current);
				return node;
			}
		}

		if (current->getRight() != nullptr)
			return push(key, value, current->getRight());
		else
		{
			Node *node = new Node(key, value);
			current->setRight(node);
			node->setParent(current);
			return node;
		}

		return nullptr;
	}

	virtual Node *remove(Node *node)
	{
		if (node == nullptr)
			return nullptr;

		if (node == _root)
		{
			_root = nullptr;
			return node;
		}

		Node *parent = node->getParent();

		if (parent == nullptr)
			return node;

		Node *replace = nullptr;

		if (node->getLeft() != nullptr && node->getRight() != nullptr)
			replace = AVL_Tree<K, V>::minimum(node->getRight());
		else if (node->getLeft() == nullptr)
			replace = node->getRight();
		else /*if(node->getRight() == nullptr)*/
			replace = node->getLeft();

		if (parent->getLeft() == node)
			parent->setLeft(replace);
		else /*if(parent->getRight() == node)*/
			parent->setRight(replace);

		return node;
	}

	virtual Node *minimum(Node *current = nullptr) const
	{
		if (_root == nullptr)
			return nullptr;

		if (current == nullptr)
			current = _root;

		while (current->getLeft() != nullptr)
			current = current->getLeft();

		return current;
	};

	virtual Node *maximum(Node *current = nullptr) const
	{
		if (_root == nullptr)
			return nullptr;

		if (current == nullptr)
			current = _root;

		while (current->getRight() != nullptr)
			current = current->getRight();

		return current;
	}

	virtual Node *find(K key, Node *current)
	{
		if (current == nullptr || current->getKey() == key)
			return current;

		if (current->getKey() > key)
			return find(key, current->getLeft());
		if (current->getKey() < key)
			return find(key, current->getRight());

		return nullptr;
	}

	virtual Node *find(bool (*func)(K, V), Node *current)
	{
		if (current != nullptr)
			if (func(current->getKey(), current->getValue()))
				return current;

		if (current != nullptr && current->getLeft() != nullptr)
			find(func, current->getLeft());

		if (current != nullptr && current->getRight() != nullptr)
			find(func, current->getRight());

		return nullptr;
	};

public:
	virtual Node *getRoot() const { return _root; }

	AVL_Tree<K, V>() { _root = nullptr; }

	virtual Iterator push(K key, V value) { return Iterator(this->push(key, value, _root)); }

	virtual void remove(Iterator it) { this->remove(it.getNode()); }

	virtual Iterator minimum(Iterator it) const { return Iterator(this->minimum(it.getNode())); }

	virtual Iterator maximum(Iterator it) const { return Iterator(this->maximum(it.getNode())); }

	virtual Iterator find(K find) { return Iterator(this->find(find, _root)); }

	virtual Iterator find(bool (*func)(K, V)) { return Iterator(find(func, _root)); }

	virtual Iterator find(bool (*func)(K, V), Iterator current) { return Iterator(this->find(func, current.getNode())); }

	virtual V operator[](K key) { return find(key, _root)->getValue(); }

	virtual void preOrder(Node *node, void (*func)(Node *)) const
	{
		if (node != nullptr)
			func(node);

		if (node != nullptr && node->getLeft() != nullptr)
			preOrder(node->getLeft(), func);

		if (node != nullptr && node->getRight() != nullptr)
			preOrder(node->getRight(), func);
	}

	virtual void inOrder(Node *node, void (*func)(Node *)) const
	{
		if (node != nullptr && node->getLeft() != nullptr)
			inOrder(node->getLeft(), func);

		if (node != nullptr)
			func(node);

		if (node != nullptr && node->getRight() != nullptr)
			inOrder(node->getRight(), func);
	}

	virtual void postOrder(Node *node, void (*func)(Node *)) const
	{
		if (node != nullptr && node->getLeft() != nullptr)
			postOrder(node->getLeft(), func);

		if (node != nullptr && node->getRight() != nullptr)
			postOrder(node->getRight(), func);

		if (node != nullptr)
			func(node);
	}

	virtual void preOrder(void (*func)(Node *)) const { preOrder(_root, func); }

	virtual void inOrder(void (*func)(Node *)) const { inOrder(_root, func); }

	virtual void postOrder(void (*func)(Node *)) const { postOrder(_root, func); }

	virtual Iterator begin() { return Iterator(minimum()); }

	virtual Iterator end() { return Iterator(maximum()); }
};

template <class K, class V>
ostream &operator<<(ostream &stream, const typename AVL_Tree<K, V>::Node &node)
{
	return stream << node._value;
}

template <class K, class V>
ostream &operator>>(ostream &stream, typename AVL_Tree<K, V>::Node &node)
{
	return stream >> node._value;
}

template <class K, class V>
class Splay_Tree : public AVL_Tree<K, V>
{
public:
	using typename AVL_Tree<K, V>::Node;
	using typename AVL_Tree<K, V>::Iterator;

protected:
	Node *Splay(Node *node)
	{
		Node *parent = node->getParent();

		if (parent == nullptr)
			return node;

		Node *grand = parent->getParent();

		if (grand == nullptr)
		{
			AVL_Tree<K, V>::rotate(parent, node);
			return node;
		}
		else
		{
			if ((grand->getLeft() == parent) == (parent->getLeft() == node))
			{
				AVL_Tree<K, V>::rotate(grand, parent);
				AVL_Tree<K, V>::rotate(parent, node);
			}
			else
			{
				AVL_Tree<K, V>::rotate(parent, node);
				AVL_Tree<K, V>::rotate(grand, node);
			}
		}

		return Splay(node);
	}

	virtual Node *find(K key, Node *current) override
	{
		Node *found = AVL_Tree<K, V>::find(key, current);

		if (found != nullptr)
			Splay(found);

		return found;
	};

	virtual Node *push(K key, V value, Node *current) override
	{
		Node *pushed = AVL_Tree<K, V>::push(key, value, current);

		if (pushed != nullptr)
			Splay(pushed);

		return pushed;
	};

public:
	Splay_Tree<K, V>() : AVL_Tree<K, V>() {}

	virtual Iterator find(K key) override { return AVL_Tree<K, V>::find(key, AVL_Tree<K, V>::_root); };

	virtual Iterator push(K key, V value) override { return AVL_Tree<K, V>::push(key, value); };

	~Splay_Tree<K, V>(){};
};

template <class K, class V>
class Multi_Tree : public AVL_Tree<K, Stack<V>>
{
public:
	using typename AVL_Tree<K, Stack<V>>::Node;
	using typename AVL_Tree<K, Stack<V>>::Iterator;

	virtual Iterator pushSingle(K key, V value)
	{
		Node *node = AVL_Tree<K, Stack<V>>::find(key, AVL_Tree<K, Stack<V>>::_root);

		if (node)
		{
			Stack<V> stack = node->getValue();

			stack.push(value);

			node->setValue(stack);

			return Iterator(node);
		}
		else
		{
			Stack<V> stack;

			stack.push(value);

			return AVL_Tree<K, Stack<V>>::push(key, stack);
		}
	}
};

int main()
{
	// Дерево с итератором
	AVL_Tree<string, Movie> tree;

	tree.push("Movie1", Movie("Quentin Tarantino", "Pulp Fiction", "USA", 1994, 8000000, 214000000));
	tree.push("Movie2", Movie("Christopher Nolan", "Inception", "USA", 2010, 160000000, 829895144));
	tree.push("Movie3", Movie("Martin Scorsese", "The Wolf of Wall Street", "USA", 2013, 100000000, 392000694));
	tree.push("Movie4", Movie("Denis Villeneuve", "Blade Runner 2049", "Canada", 2017, 150000000, 259239658));
	tree.push("Movie5", Movie("Greta Gerwig", "Little Women", "USA", 2019, 40000000, 218000000));
	tree.push("Movie6", Movie("Bong Joon-ho", "Parasite", "South Korea", 2019, 11000000, 258800000));

	// Вывод по порядку
	for (AVL_Tree<string, Movie>::Iterator it = tree.begin(); it != tree.end(); it++)
		cout << (*it).getValue() << endl;

	Movie found = (*tree.find("Movie3")).getValue();

	// Расширяющиеся дерево (элементы с одинаковыми ключами хранятся справа)
	Splay_Tree<string, Movie> stree;

	stree.push("Movie1", Movie("Quentin Tarantino", "Pulp Fiction", "USA", 1994, 8000000, 214000000));
	stree.push("Movie2", Movie("Christopher Nolan", "Inception", "USA", 2010, 160000000, 829895144));
	AVL_Tree<string, Movie>::Iterator it = stree.push("Movie3", Movie("Martin Scorsese", "The Wolf of Wall Street", "USA", 2013, 100000000, 392000694));
	stree.push("Movie4", Movie("Denis Villeneuve", "Blade Runner 2049", "Canada", 2017, 150000000, 259239658));
	stree.push("Movie5", Movie("Greta Gerwig", "Little Women", "USA", 2019, 40000000, 218000000));
	stree.push("Movie6", Movie("Bong Joon-ho", "Parasite", "South Korea", 2019, 11000000, 258800000));

	// Обращаемся к узлам
	stree.find("Movie3");
	stree.find("Movie1");
	stree.find("Movie3");
	stree.find("Movie1");
	stree.find("Movie3");
	stree.find("Movie2");
	stree.remove(it);
	stree.find("Movie1");

	// Дерево с повторяющимися ключами по списку
	Multi_Tree<int, string> mtree;

	mtree.pushSingle(3, "Who");
	mtree.pushSingle(3, "is");
	mtree.pushSingle(3, "my");

	mtree.pushSingle(6, "crash");

	Stack<string> elems = mtree[3];

	cout << elems << endl; // "Who", "is", "my"

	return 0;
}
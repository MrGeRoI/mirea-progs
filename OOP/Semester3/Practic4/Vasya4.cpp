#include <iostream>
#include <cmath>

using namespace std;

// Создайте класс «Декартово дерево» («Курево»).
class Treap
{
public:
	// класс узел
	struct Node
	{
	public:
		int m_key, m_priority;

		// не можем хранить Node, но имеем право хранить указатель
		Node *m_left, *m_right, *m_parent;

		Node(int k, int p)
		{
			m_key = k;
			m_priority = p;
			m_left = m_right = m_parent = nullptr;
		}

		Node(int k)
		{
			m_key = k;
			m_priority = rand();
			m_left = m_right = m_parent = nullptr;
		}

		Node()
		{
			m_left = m_right = m_parent = nullptr;
		}

		Node *getMinimum() const
		{
			if (m_left != nullptr)
				return m_left->getMinimum();

			return (Node *)this;
		}

		Node *getSuccessor() const
		{
			if (m_right != nullptr)
				return m_right->getMinimum();

			Node *current = m_parent;

			while (current != nullptr && current->m_key < m_key)
				current = current->m_parent;

			return current;
		}

		friend ostream &operator<<(ostream &stream, const Node &node)
		{
			stream << node.m_key << "; " << node.m_priority << "\n";

			if (node.m_left)
				stream << *node.m_left;

			if (node.m_right)
				stream << *node.m_right;

			return stream;
		}
	};

	class Iterator : public iterator<input_iterator_tag, int>
	{
	private:
		Node *m_node;

	public:
		Iterator() { m_node = nullptr; }
		Iterator(Node *p) { m_node = p; }
		Iterator(const Iterator &it) { m_node = it.m_node; }

		Iterator &operator=(const Iterator &it)
		{
			m_node = it.m_node;
			return *this;
		}

		Iterator &operator=(Node *p)
		{
			m_node = p;
			return *this;
		}

		bool operator!=(Iterator const &other) const { return m_node != other.m_node; }
		bool operator==(Iterator const &other) const { return m_node == other.m_node; }

		Node *getNode() const { return m_node; }
		void setNode(Node *node) { m_node = node; }

		int &operator*()
		{
			if (m_node == nullptr)
				throw runtime_error("Invalid pointer");

			return m_node->m_priority;
		}

		const int &operator*() const
		{
			if (m_node == nullptr)
				throw runtime_error("Invalid pointer");

			return m_node->m_priority;
		}

		Iterator &operator++()
		{
			m_node = m_node->getSuccessor();
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator it(*this);
			m_node = m_node->getSuccessor();
			return it;
		}
	};

protected:
	// корень - его достаточно для хранения всего дерева
	Node *m_root;

	virtual Node *merge(Node *left, Node *right)
	{
		// При выполнении операции left.merge(right) предполагается, что в левом дереве left все
		// ключи меньше любого ключа из правого дерева right.
		if (left->m_priority > right->m_priority)
		{
			if (left->m_right)
				left->m_right = merge(left->m_right, right);
			else
				left->m_right = right;
		}
		else
		{
			if (right->m_left)
				right->m_left = merge(left, right->m_left);
			else
				right->m_left = left;

			left = right;
		}

		return left;
	}

	virtual Node *split(Node *Current, int x, Treap &left, Treap &right)
	{
		if (m_root == nullptr || Current == nullptr)
			return nullptr;

		if (Current->m_key == x)
		{
			Node *Res = Current;
			left.merge(Current->m_left);
			right.merge(Current->m_right);
			Res->m_left = nullptr;
			Res->m_right = nullptr;
			// Res->setParent(nullptr);
			return Res;
		}

		if (Current->m_key < x)
		{
			left.merge(Current->m_left);
			left.merge(Current->m_key, Current->m_priority);

			return split(Current->m_right, x, left, right);
		}
		else
		{
			right.merge(Current->m_right);
			right.merge(Current->m_key, Current->m_priority);

			return split(Current->m_left, x, left, right);
		}
	}

	// Реализуйте операции объединения деревьев merge(),
	virtual void merge(Node *node)
	{
		if (m_root == nullptr)
		{
			m_root = node;
			return;
		}
		if (node == nullptr)
			return; // this;

		if (m_root->m_priority > node->m_priority)
		{
			if (m_root->m_right != nullptr)
				m_root->m_right = merge(m_root->m_right, node);
			else
				m_root->m_right = node;
		}
		else
		{
			if (node->m_left != nullptr)
				node->m_left = merge(m_root, node->m_left);
			else
				node->m_left = m_root;
			m_root = node;
		}
	}

public:
	// доступ к корневому элементу
	Node *getRoot() const { return m_root; }

	// конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Treap(Node *root = nullptr) { m_root = root; }

	void preOrder(Node *node, void (*func)(Node *))
	{
		if (node)
			func(node);

		if (node && node->m_left)
			preOrder(node->m_left, func);

		if (node && node->m_right)
			preOrder(node->m_right, func);
	}

	virtual void merge(int key, int priority)
	{
		merge(new Node(key, priority));
	}

	virtual void merge(Treap &tree)
	{
		merge(tree.m_root);
	}

	// разрезания деревьев по ключу split().
	virtual Iterator split(int x, Treap &left, Treap &right)
	{
		return Iterator(split(m_root, x, left, right));
	}

	Iterator begin()
	{
		return Iterator(m_root->getMinimum());
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	friend ostream &operator<<(ostream &stream, const Treap &tree)
	{
		if (tree.m_root)
			stream << *tree.m_root;

		return stream;
	}
};

// Создайте класс «Декартово дерево по неявному ключу», унаследовав
// его с ключевым словом protected от класса из задания №4.1.
class ImplictTreap : protected Treap
{
public:
	using Treap::Iterator;
	using Treap::Node;

protected:
	virtual Node *merge(Node *left, Node *right)
	{
		// При выполнении операции left.merge(right) предполагается, что в левом дереве left все
		// ключи меньше любого ключа из правого дерева right.
		if (left->m_priority > right->m_priority)
		{
			if (left->m_right)
				left->m_right = merge(left->m_right, right);
			else
				left->m_right = right;
		}
		else
		{
			if (right->m_left)
				right->m_left = merge(left, right->m_left);
			else
				right->m_left = left;

			left = right;
		}

		return left;
	}

	// Переопределите
	// слияние деревьев (работает так же, как merge() в родителе, но без учёта
	// ключей).
	virtual void merge(Node *node)
	{
		if (m_root == nullptr)
		{
			m_root = node;
			return;
		}
		if (node == nullptr)
			return; // this;

		if (m_root->m_priority > node->m_priority)
		{
			if (m_root->m_right != nullptr)
				m_root->m_right = Treap::merge(m_root->m_right, node);
			else
				m_root->m_right = node;
		}
		else
		{
			if (node->m_left != nullptr)
				node->m_left = Treap::merge(m_root, node->m_left);
			else
				node->m_left = m_root;
			m_root = node;
		}
	}

	// Переопределите разделение дерева split() так, чтобы оно работало по
	// значению групповой функции size().
	virtual Node *split(Node *Current, int x, ImplictTreap &left, ImplictTreap &right)
	{
		if (m_root == nullptr || Current == nullptr)
			return nullptr;

		int leftSize = getSize(Current->m_left);

		if (leftSize >= x)
		{
			right.m_root = Current;
			right.m_root->m_left = nullptr;

			if (Current->m_left)
			{
				left.m_root = split(Current->m_left, x, left, right);
			}
			else
			{
				left.m_root = nullptr;
			}

			right.m_root->m_parent = nullptr;
			return left.m_root;
		}
		else
		{
			left.m_root = Current;
			left.m_root->m_right = nullptr;

			if (Current->m_right)
			{
				right.m_root = split(Current->m_right, x - leftSize - 1, left, right);
			}
			else
			{
				right.m_root = nullptr;
			}

			left.m_root->m_parent = nullptr;
			return right.m_root;
		}
	}

	int getSize(Node *node) const
	{
		int size = 1;

		if (node->m_left)
			size += getSize(node->m_left);

		if (node->m_right)
			size += getSize(node->m_right);

		return size;
	}

public:
	int getSize() const
	{
		return getSize(m_root);
	}

	// Введите групповую функции size() – число элементов в дереве, корнем
	// которого является текущий узел.
	int getSize(Iterator it) const
	{
		return getSize(it.getNode());
	}

	// Функция для вычисления произведения на отрезке [start, end]
    double getProductOnSegment(int start, int end)
    {
        Node *node = m_root;
        ImplictTreap left, middle, right;

        // Разделяем дерево на три части: left, middle, right
        split(node, start, left, middle);
        split(middle.m_root, end - start + 1, middle, right);

        // Находим произведение на отрезке
        double product = 1.0;
        while (middle.m_root != nullptr)
        {
            product *= middle.m_root->m_key;
            middle.merge(middle.m_root->m_right);
        }

        // Объединяем деревья обратно
        merge(left.m_root);
        merge(middle.m_root);
        merge(right.m_root);

        return product;
    }

	// доступ к корневому элементу
	Node *getRoot() const { return Treap::getRoot(); }

	void preOrder(Node *node, void (*func)(Node *))
	{
		Treap::preOrder(node, func);
	}

	virtual void merge(int key, int priority)
	{
		Treap::merge(key, priority);
	}

	virtual void merge(Treap &tree)
	{
		Treap::merge(tree);
	}

	// разрезания деревьев по ключу split().
	virtual Iterator split(int x, Treap &left, Treap &right)
	{
		return Treap::split(x, left, right);
	}

	Iterator begin()
	{
		return Treap::begin();
	}

	Iterator end()
	{
		return Treap::end();
	}

	friend ostream &operator<<(ostream &stream, const ImplictTreap &tree)
	{
		if (tree.m_root)
			stream << *tree.m_root;

		return stream;
	}
};

void print(Treap::Node *node)
{
	cout << '(' << node->m_key << ": " << node->m_priority << ')';
}

int main()
{
	srand(time(nullptr));

	Treap tree;

	// заполнение дерева
	for (int i = 0; i < 15; i++)
		tree.merge(i, static_cast<int>(100 * sin(15 * double(i))));

	cout << tree;

	Treap tree1, tree2;
	Treap::Iterator it = tree.split(5, tree1, tree2);

	cout << "\n---\n"
		 << tree1 << "\n---\n"
		 << tree2;

	if (it != tree.end())
		cout << "\nNode: " << *it;

	// Создаем объект класса ImplictTreap
	ImplictTreap treap;

    // Вставляем элементы в дерево с произвольными приоритетами
    treap.merge(2, 5);
    treap.merge(3, 2);
    treap.merge(4, 8);
    treap.merge(5, 1);
    treap.merge(6, 7);
    treap.merge(7, 3);

    // Выводим дерево
    std::cout << "Original Treap:\n" << treap << std::endl;

    // Задаем отрезок [3, 6]
    int start = 3;
    int end = 6;

    // Находим произведение на заданном отрезке
    double product = treap.getProductOnSegment(start, end);

    // Выводим результат
    cout << "Product at [3;6]: " << product << endl;

	return 0;
}
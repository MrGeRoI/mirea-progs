#define HEAP_MAX_TREES 64


template <class T>
class FibonacciHeap
{
public:
	struct Node
	{
	public:
		Node *m_pPrevious, *m_pNext, *m_pChild, *m_pParent;

		T m_priority;
		int m_iDegree;
		bool m_bMarked;
	};

protected:
	Node *m_pRoot;

public:
	FibonacciHeap() : m_pRoot(nullptr) {}

	virtual ~FibonacciHeap()
	{
		if (m_pRoot)
			delete_(m_pRoot);
	}

	virtual void push(T priority)
	{
		Node *node = new Node;
		node->m_priority = priority;
		node->m_pPrevious = node->m_pNext = node;
		node->m_iDegree = 0;
		node->m_bMarked = false;
		node->m_pChild = nullptr;
		node->m_pParent = nullptr;

		m_pRoot = merge(m_pRoot, node);
	}

	virtual void merge(FibonacciHeap &other)
	{
		m_pRoot = merge(m_pRoot, other.m_pRoot);
		other.m_pRoot = nullptr;
	}

	virtual bool isEmpty() const
	{
		return m_pRoot == nullptr;
	}

	virtual T maximum() const
	{
		return m_pRoot->m_priority;
	}

	virtual T extractMaximum()
	{
		Node *old = m_pRoot;
		m_pRoot = removeMaximum(m_pRoot);
		T ret = old->m_priority;
		delete old;
		return ret;
	}

private:
	void delete_(Node *node)
	{
		if (node != nullptr)
		{
			Node *c = node;

			do
			{
				Node *d = c;

				c = c->m_pNext;

				delete_(d->m_pChild);

				delete d;
			} while (c != node);
		}
	}

	void addChild(Node *parent, Node *child)
	{
		Node *oldChild = parent->m_pChild;

		if (oldChild == nullptr)
		{
			parent->m_pChild = child;
			child->m_pParent = parent;

			return;
		}

		Node *next = oldChild->m_pNext;

		if (next)
		{
			next->m_pPrevious = child;
			child->m_pNext = next;
		}

		oldChild->m_pNext = child;
		child->m_pPrevious = oldChild;
	}

	void unMarkAndUnParentAll(Node *node)
	{
		if (node == nullptr)
			return;

		Node *c = node;

		do
		{
			c->m_bMarked = false;
			c->m_pParent = nullptr;
			c = c->m_pNext;
		} while (c != node);
	}

	Node *merge(Node *a, Node *b)
	{
		if (a == nullptr)
			return b;
		if (b == nullptr)
			return a;
		// делаем a бОльшим из двух
		if (a->m_priority < b->m_priority)
		{
			Node *temp = a;
			a = b;
			b = temp;
		}

		Node *an = a->m_pNext;
		Node *bp = b->m_pPrevious;

		a->m_pNext = b;
		b->m_pPrevious = a;

		an->m_pPrevious = bp;
		bp->m_pNext = an;

		return a;
	}

	Node *removeMaximum(Node *node)
	{
		if (node == nullptr)
			return node;

		unMarkAndUnParentAll(node->m_pChild);

		if (node->m_pNext == node)
			// один узел
			node = node->m_pChild;
		else
		{
			// много узлов, удалить максимум из списка и объединить node->m_pNext, node->m_pChild (левый ребенок поднялся вверх)
			Node *child = node->m_pChild,
				 *childPrev = child->m_pPrevious;

			if (childPrev)
			{
				merge(childPrev, child);
				addChild(node, childPrev);
			}

			merge(node->m_pNext, child);
		}

		// Консолидация

		Node *trees[HEAP_MAX_TREES] = {nullptr};

		while (true)
		{
			if (trees[node->m_iDegree] != nullptr)
			{
				Node *t = trees[node->m_iDegree];
				if (t == node)
					break;
				trees[node->m_iDegree] = nullptr;
				if (node->m_priority > t->m_priority)
				{
					t->m_pPrevious->m_pNext = t->m_pNext;
					t->m_pNext->m_pPrevious = t->m_pPrevious;
					addChild(node, t);
				}
				else
				{
					t->m_pPrevious->m_pNext = t->m_pNext;
					t->m_pNext->m_pPrevious = t->m_pPrevious;
					if (node->m_pNext == node)
					{
						t->m_pNext = t->m_pPrevious = t;
						addChild(t, node);
						node = t;
					}
					else
					{
						node->m_pPrevious->m_pNext = t;
						node->m_pNext->m_pPrevious = t;
						t->m_pNext = node->m_pNext;
						t->m_pPrevious = node->m_pPrevious;
						addChild(t, node);
						node = t;
					}
				}
				continue;
			}
			else
			{
				trees[node->m_iDegree] = node;
			}
			node = node->m_pNext;
		}

		return node;
	}
};
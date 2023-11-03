#define HEAP_MAX_TREES 64

template <class T>
class FibonacciHeap;

template <class T>
struct HeapNode
{
public:
	HeapNode<T> *m_pPrevious, *m_pNext, *m_pChild, *m_pParent;

	T m_priority;
	int m_iDegree;
	bool m_bMarked;
};
/*
template <class T>
class HeapNode
{
private:
	HeapNode<T> *m_pPrevious, *m_pNext, , *m_pChild, *m_pParent;

	T m_priority;
	int m_iDegree;
	bool m_bMarked;
public:
	friend class FibonacciHeap<T>;

	HeapNode<T> *getPrev() { return m_pPrevious; }
	HeapNode<T> *getNext() { return m_pNext; }
	HeapNode<T> *getChild() { return m_pChild; }
	HeapNode<T> *getParent() { return m_pParent; }

	T getPriority() { return m_priority; }

	bool isMarked() { return m_bMarked; }
};
*/
template <class T>
class FibonacciHeap
{
protected:
	HeapNode<T> *m_pRoot;

public:
	FibonacciHeap();

	virtual ~FibonacciHeap();

	virtual void push(T priority);

	virtual void merge(FibonacciHeap &other);

	virtual bool isEmpty() const;

	virtual T maximum() const;

	virtual T extractMaximum();

private:
	void delete_(HeapNode<T> *node);

	void addChild(HeapNode<T> *parent, HeapNode<T> *child);

	void unMarkAndUnParentAll(HeapNode<T> *node);

	HeapNode<T> *merge(HeapNode<T> *a, HeapNode<T> *b);

	HeapNode<T> *removeMaximum(HeapNode<T> *node);
};

template <class T>
FibonacciHeap<T>::FibonacciHeap() : m_pRoot(nullptr) {}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{
	if (m_pRoot)
		delete_(m_pRoot);
}

template <class T>
void FibonacciHeap<T>::push(T priority)
{
	HeapNode<T> *node = new HeapNode<T>;
	node->m_priority = priority;
	node->m_pPrevious = node->m_pNext = node;
	node->m_iDegree = 0;
	node->m_bMarked = false;
	node->m_pChild = nullptr;
	node->m_pParent = nullptr;

	m_pRoot = merge(m_pRoot, node);
}

template <class T>
void FibonacciHeap<T>::merge(FibonacciHeap &other)
{
	m_pRoot = _merge(m_pRoot, other.m_pRoot);
	other.m_pRoot = nullptr;
}

template <class T>
bool FibonacciHeap<T>::isEmpty() const
{
	return m_pRoot == nullptr;
}

template <class T>
T FibonacciHeap<T>::maximum() const
{
	return m_pRoot->m_priority;
}

template <class T>
T FibonacciHeap<T>::extractMaximum()
{
	HeapNode<T> *old = m_pRoot;
	m_pRoot = removeMaximum(m_pRoot);
	T ret = old->m_priority;
	delete old;
	return ret;
}

template <class T>
HeapNode<T> *FibonacciHeap<T>::merge(HeapNode<T> *a, HeapNode<T> *b)
{
	if (a == nullptr)
		return b;
	if (b == nullptr)
		return a;
	// делаем a бОльшим из двух
	if (a->m_priority < b->m_priority)
	{
		HeapNode<T> *temp = a;
		a = b;
		b = temp;
	}

	HeapNode<T> *an = a->m_pNext;
	HeapNode<T> *bp = b->m_pPrevious;

	a->m_pNext = b;
	b->m_pPrevious = a;

	an->m_pPrevious = bp;
	bp->m_pNext = an;

	return a;
}

template <class T>
void FibonacciHeap<T>::delete_(HeapNode<T> *node)
{
	if (node != nullptr)
	{
		HeapNode<T> *c = node;

		do
		{
			HeapNode<T> *d = c;

			c = c->m_pNext;

			delete_(d->m_pChild);

			delete d;
		} while (c != node);
	}
}

template <class T>
void FibonacciHeap<T>::addChild(HeapNode<T> *parent, HeapNode<T> *child)
{
	HeapNode<T> *oldChild = parent->m_pChild;

	if (oldChild == nullptr)
	{
		parent->m_pChild = child;
		child->m_pParent = parent;

		return;
	}

	HeapNode<T> *next = oldChild->m_pNext;

	if (next)
	{
		next->m_pPrevious = child;
		child->m_pNext = next;
	}

	oldChild->m_pNext = child;
	child->m_pPrevious = oldChild;
}

template <class T>
void FibonacciHeap<T>::unMarkAndUnParentAll(HeapNode<T> *node)
{
	if (node == nullptr)
		return;

	HeapNode<T> *c = node;

	do
	{
		c->m_bMarked = false;
		c->m_pParent = nullptr;
		c = c->m_pNext;
	} while (c != node);
}

template <class T>
HeapNode<T> *FibonacciHeap<T>::removeMaximum(HeapNode<T> *node)
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
		HeapNode<T> *child = node->m_pChild,
					*childPrev = child->m_pPrevious;

		if(childPrev)
		{
			merge(childPrev,childNext);
			addChild(childPrev);
		}

		merge(node->m_pNext,child);
	}

	// Консолидация

	HeapNode<T> *trees[HEAP_MAX_TREES] = {nullptr};

	while (true)
	{
		if (trees[node->m_iDegree] != nullptr)
		{
			HeapNode<T> *t = trees[node->m_iDegree];
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